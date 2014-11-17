#include "Vertex.h"

Vertex::Vertex()
{

}

Vertex::Vertex(int x, int y) : x(x), y(y)
{
	edges = new std::vector<Edge*>();
}


Vertex::~Vertex()
{
	for (auto &it : *edges)
	{
		delete it;
	}
	delete edges;
}

int Vertex::getX()
{
	return x;
}

int Vertex::getY()
{
	return y;
}

std::vector<Edge*>* Vertex::getEdges()
{
	return edges;
}

void Vertex::addEdge(Edge* edge)
{
	edges->push_back(edge);
}