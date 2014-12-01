#include "Controller.h"
#include <time.h>
#include <algorithm>  //sort
#include <list>


bool sortByGuessedTotalDistance(Vertex *lhs, Vertex *rhs) {
	return lhs->guessedTotalDistance < rhs->guessedTotalDistance;
}

Controller::Controller()
{
	Init();
}


Controller::~Controller()
{
	for (auto vertex : *vertici){
		delete vertex;
	}

	for (auto edge : *edges){
		delete edge;
	}

	delete vertici;
	delete edges;

	vertexCow = NULL;
	vertexRabbit = NULL;
}

void Controller::Init()
{
	vertici = new std::vector<Vertex*>;
	edges = new std::vector<Edge*>;

	//make vertexes and edges
	Vertex* vertex1 = new Vertex(10, 15);
	Vertex* vertex2 = new Vertex(24, 35);
	Vertex* vertex3 = new Vertex(130, 12);
	Vertex* vertex4 = new Vertex(67, 45);
	Vertex* vertex5 = new Vertex(135, 65);
	Vertex* vertex6 = new Vertex(17, 38);
	Vertex* vertex7 = new Vertex(33, 42);

	vertici->push_back(vertex1);
	vertici->push_back(vertex2);
	vertici->push_back(vertex3);
	vertici->push_back(vertex4);
	vertici->push_back(vertex5);
	vertici->push_back(vertex6);
	vertici->push_back(vertex7);

	//edges
	Edge* edgeBetween1And5 = new Edge(vertex1, vertex5, 100);
	Edge* edgeBetween1And2 = new Edge(vertex1, vertex2, 20);
	Edge* edgeBetween2And4 = new Edge(vertex2, vertex4, 60);
	Edge* edgeBetween2And3 = new Edge(vertex2, vertex3, 90);
	Edge* edgeBetween4And5 = new Edge(vertex4, vertex5, 220);
	Edge* edgeBetween1And4 = new Edge(vertex1, vertex4, 10);
	Edge* edgeBetween4And7 = new Edge(vertex4, vertex7, 150);
	Edge* edgeBetween1And6 = new Edge(vertex1, vertex6, 30);
	Edge* edgeBetween5And6 = new Edge(vertex2, vertex6, 50);
	Edge* edgeBetween7And6 = new Edge(vertex7, vertex6, 80);

	edges->push_back(edgeBetween1And5);
	edges->push_back(edgeBetween1And2);
	edges->push_back(edgeBetween2And4);
	edges->push_back(edgeBetween2And3);
	edges->push_back(edgeBetween4And5);
	edges->push_back(edgeBetween1And4);
	edges->push_back(edgeBetween1And6);
	edges->push_back(edgeBetween5And6);
	edges->push_back(edgeBetween4And7);
	edges->push_back(edgeBetween7And6);


	//set Edges to Vertices
	for (auto d : *vertici){
		setEdges(d);
	}

	/* initialize random seed: */
	srand(time(NULL));

	//randomize the verticis Cow and Rabbit
	vertexCow = vertici->at(rand() % vertici->size());
	vertexRabbit = vertici->at(rand() % vertici->size());
	if (vertexRabbit == vertexCow){
		vertexRabbit = vertici->at(rand() % vertici->size());
	}
}

void Controller::AStar(Vertex* start, Vertex* end)
{
	//a* algorithm
	std::vector<Vertex*>* closedList = new std::vector<Vertex*>();
	std::vector<Vertex*>* openList = new std::vector<Vertex*>();
	std::list<Vertex*>* route = new std::list<Vertex*>();

	openList->push_back(start); //add starting point

	for (Vertex* vertex : *vertici){
		vertex->visitedBy = nullptr;
		vertex->minDistance = std::numeric_limits<int>::max();
		vertex->guessedTotalDistance = 0;
	}

	start->minDistance = 0;

	while (openList->size() != 0)
	{
		Vertex* vertex = openList->front();
		openList->erase(openList->begin());

		float GuessedDistance;
		if (vertex == end){
			GuessedDistance = 0;
		}

		else{
			GuessedDistance = calculateHeuristic(vertex, end);

		}

		for (Edge* edge : *vertex->getEdges())
		{
			Vertex* target = edge->getTarget();

			if (std::find(closedList->begin(), closedList->end(), target) == closedList->end()) {
				int distance = edge->getWeight();

				int totalDistance = vertex->minDistance + distance;
				if ((totalDistance) < target->minDistance) {
					target->minDistance = totalDistance;
					target->guessedTotalDistance = totalDistance + GuessedDistance;
					target->visitedBy = vertex;
					openList->push_back(target);
				}
			}
		}

		closedList->push_back(vertex);

		std::sort(openList->begin(), openList->end(), sortByGuessedTotalDistance);
	}

	Vertex* current = end;
	while (current != nullptr && current != start){
		route->push_front(current);
		current = current->visitedBy;
	}

	closedList->clear();
}

void Controller::setEdges(Vertex* currentVertex){
	for (auto edge : *edges){
		if (edge->getSource() == currentVertex || edge->getTarget() == currentVertex){
			currentVertex->addEdge(edge);
		}
	}

}

int Controller::calculateHeuristic(Vertex* source, Vertex* target)
{
	int sourceX, sourceY, targetX, targetY;
	//check on negative numbers
	if (source->getX() < 0)
		sourceX = source->getX() * -1;
	else
		sourceX = source->getX();
	if (source->getY() < 0)
		sourceY = source->getY() * -1;
	else
		sourceY = source->getY();

	if (target->getX() < 0)
		targetX = target->getX() * -1;
	else
		targetX = target->getX();

	if (target->getY() < 0)
		targetY = target->getY() * -1;
	else
		targetY = target->getY();

	int diffX, diffY;

	if (targetX > sourceX)
		diffX = targetX - sourceX;
	else if (sourceX > targetX)
		diffX = sourceX - targetX;

	if (targetY > sourceY)
		diffY = targetY - sourceY;
	else if (sourceY > targetY)
		diffY = sourceY - targetY;
	//we dont square the final answer, this takes a lot of processing power away
	return (diffX * diffX) + (diffY * diffY);
}