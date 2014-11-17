#include "Controller.h"


Controller::Controller()
{
	Init();
}


Controller::~Controller()
{
}

void Controller::Init()
{
	vertici = new std::vector<Vertex*>;

	//make vertexes and edges
	//we only put vertici in a vector, edges are saved within a vertex
	Vertex* vertex1 = new Vertex(10, 25);
	Vertex* vertex2 = new Vertex(24, 55);
	Vertex* vertex3 = new Vertex(130, 12);
	Vertex* vertex4 = new Vertex(67, 45);
	Vertex* vertex5 = new Vertex(110, 65);
	Vertex* vertex6 = new Vertex(17, 38);

	vertici->push_back(vertex1);
	vertici->push_back(vertex2);
	vertici->push_back(vertex3);
	vertici->push_back(vertex4);
	vertici->push_back(vertex5);
	vertici->push_back(vertex6);

	//edges
	Edge* edgeBetween1And5 = new Edge(vertex1, vertex5, 10);
	Edge* edgeBetween1And2 = new Edge(vertex1, vertex2, 2);
	Edge* edgeBetween2And4 = new Edge(vertex2, vertex4, 6);
	Edge* edgeBetween2And3 = new Edge(vertex2, vertex3, 9);
	Edge* edgeBetween4And5 = new Edge(vertex4, vertex5, 22);
	Edge* edgeBetween1And4 = new Edge(vertex1, vertex4, 1);
	Edge* edgeBetween1And6 = new Edge(vertex1, vertex6, 3);
	Edge* edgeBetween5And6 = new Edge(vertex2, vertex6, 5);
}

void Controller::AStar()
{
	//a* algorithm
}
