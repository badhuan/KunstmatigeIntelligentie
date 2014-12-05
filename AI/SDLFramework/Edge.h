#pragma once
class Vertex;//forward declaration otherwise infinite include -> #include "vertex.h"

class Edge
{
public:
	Edge();
	Edge(Vertex* source, Vertex* target, int weight);
	virtual ~Edge();
	int getWeight();
	Vertex* getSource();
	Vertex* getTarget();
private:
	Vertex* source;
	Vertex* target;
	int weight;
};

