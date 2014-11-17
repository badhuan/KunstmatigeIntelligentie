#pragma once
#include <vector>
#include "Edge.h"
class Vertex
{
public:
	Vertex();
	Vertex(int x, int y);
	virtual ~Vertex();
	void addEdge(Edge* edge);
	int getX();
	int getY();
	std::vector<Edge*>* getEdges();
private:
	int x, y;
	std::vector<Edge*>* edges;
};

