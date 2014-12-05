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
	Vertex* vertex2 = new Vertex(12, 35);
	Vertex* vertex3 = new Vertex(30, 41);
	Vertex* vertex4 = new Vertex(67, 45);
	Vertex* vertex5 = new Vertex(135, 65);
	Vertex* vertex7 = new Vertex(33, 42);

	vertici->push_back(vertex1);
	vertici->push_back(vertex2);
	vertici->push_back(vertex3);
	vertici->push_back(vertex4);
	vertici->push_back(vertex5);
	vertici->push_back(vertex7);

	//edges
	Edge* edgeBetween1And5 = new Edge(vertex5, vertex1, 10000);
	Edge* edgeBetween1And2 = new Edge(vertex2, vertex1, 2000);
	Edge* edgeBetween2And4 = new Edge(vertex4, vertex2, 6000);
	Edge* edgeBetween2And3 = new Edge(vertex3, vertex2, 9000);
	Edge* edgeBetween4And5 = new Edge(vertex5, vertex4, 22000);
	Edge* edgeBetween1And4 = new Edge(vertex4, vertex1, 1000);
	Edge* edgeBetween4And7 = new Edge(vertex7, vertex4, 15000);
	Edge* edgeBetween3And7 = new Edge(vertex3, vertex7, 1000);

	edges->push_back(edgeBetween1And5);
	edges->push_back(edgeBetween1And2);
	edges->push_back(edgeBetween2And4);
	edges->push_back(edgeBetween2And3);
	edges->push_back(edgeBetween4And5);
	edges->push_back(edgeBetween1And4);
	edges->push_back(edgeBetween4And7);
	edges->push_back(edgeBetween3And7);


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

void Controller::AStar(Vertex* source, Vertex* target)
{
	//a* algorithm
	std::vector<Vertex*> closedList;
	std::vector<Vertex*> openList;
	std::list<Vertex*> route;

	if (source == target){
		//ERROR
		return;
	}

	route.clear();

	for (Vertex* vertex : *vertici){
		vertex->visitedBy = nullptr;
		vertex->minDistance = std::numeric_limits<int>::max();
		vertex->guessedTotalDistance = 0;
	}

	source->minDistance = 0;
	openList.push_back(source);


	/* Loop through open list: */
	while (!openList.empty()) {
		Vertex* vertex = openList.front();
		openList.erase(openList.begin());

		/* Calculate guessed Distance: */
		float GuessedDistance;
		if (vertex == target){
			GuessedDistance = 0;
		}
		else{
			GuessedDistance = calculateHeuristic(vertex, target);
		}


		// Visit each edge  
		for (Edge* edge : *vertex->getEdges())
		{
			Vertex* target = edge->getTarget();

			if (std::find(closedList.begin(), closedList.end(), target) == closedList.end()) {
				int distance = edge->getWeight();

				int totalDistance = vertex->minDistance + distance;
				if ((totalDistance) < target->minDistance) {
					//m_OpenList->remove(target);//?!?!??!
					target->minDistance = totalDistance;
					target->guessedTotalDistance = totalDistance + GuessedDistance;
					target->visitedBy = vertex;
					openList.push_back(target);
				}
			}
		}
		closedList.push_back(vertex);

		// sort openlist by weight + guessedValue;
		std::sort(openList.begin(), openList.end(), sortByGuessedTotalDistance);

	}

	Vertex* current = target;
	while (current != nullptr && current != source){
		route.push_front(current);
		current = current->visitedBy;
	}

	//m_OpenList->
	closedList.clear();
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