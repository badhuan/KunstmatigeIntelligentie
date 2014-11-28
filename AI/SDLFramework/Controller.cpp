#include "Controller.h"
#include <time.h>


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

void Controller::AStar()
{
	//a* algorithm
	std::vector<Vertex*>* closedList = new std::vector<Vertex*>();
	std::vector<Vertex*>* openList = new std::vector<Vertex*>();

	openList->push_back(vertexCow); //add starting point
	while (running && openList->size() != 0)
	{
		std::vector<Edge*>* edges2 = openList->at(0)->getEdges();

		for (int i = 0; i < edges2->size(); i++)
		{
			
			//if  openList->at(0) == target, set the source of the edge edges2->at(i)
			if (edges2->at(i)->getTarget() == openList->at(0)){
				openList->push_back(edges2->at(i)->getSource());
			}
			else{
				openList->push_back(edges2->at(i)->getTarget());
			}

			Vertex* current = nullptr;
			//loop through openList, then calculate the smallest distance
			for (int i2 = 0; i2 < openList->size(); i2++)
			{
				if (current == nullptr)
					current = openList->at(i);
				else
				{
					if (current == vertexRabbit){
						running = false; // A* algoritme is klaar?
					}else 
					if (edges2->at(i2)->getWeight() + calculateHeuristic(openList->at(i2), vertexRabbit) > calculateHeuristic(current, vertexRabbit))
					{
						current = openList->at(i2);
					}
				}
			}
			swap(openList, openList->at(0), current);
		}

	}

	delete closedList;
	delete openList;
}

void Controller::setEdges(Vertex* currentVertex){
	//for ( auto edge : *getEdges()){
	//	if (edge->getSource() == currentVertex){
	//		currentVertex->addEdge(edge);
	//	}
	//	else if(edge->getTarget() == currentVertex){
	//		currentVertex->addEdge(edge);
	//	}
	//}
	for (auto edge : *edges){
		if (edge->getSource() == currentVertex || edge->getTarget() == currentVertex){
			currentVertex->addEdge(edge);
		}
	}

}

void Controller::swap(std::vector<Vertex*>* list, Vertex* source, Vertex* target)
{
	Vertex* tempVertex = nullptr;
	for (int i = 0; i < list->size(); i++)
	{
		if (list->at(i) == source)
		{
			tempVertex = source;
			list->at(i) = target;
			list->push_back(tempVertex);
			return;
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