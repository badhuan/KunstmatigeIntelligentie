#include "Edge.h"

Edge::Edge()
{

}

Edge::~Edge()
{
}

Edge::Edge(Vertex* source, Vertex* target, int weight)
{
	this->source = source;
	this->target = target;
	this->weight = weight;
	
}


int Edge::getWeight()
{
	return weight;
}

Vertex* Edge::getSource()
{
	return source;
}

Vertex* Edge::getTarget()
{
	return target;
}