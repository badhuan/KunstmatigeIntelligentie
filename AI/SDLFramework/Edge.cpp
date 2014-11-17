#include "Edge.h"

Edge::Edge()
{

}

Edge::~Edge()
{
}

Edge::Edge(Vertex* source, Vertex* target, int weight) : source(source), target(target), weight(weight)
{
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