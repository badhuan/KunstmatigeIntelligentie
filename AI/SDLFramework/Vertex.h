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
	Vertex* visitedBy;
	int getX();
	int getY();
	int minDistance;
	int guessedTotalDistance;


	std::vector<Edge*>* getEdges();

	enum StateType{ Wandering, Chase};
	StateType getStateType(){ return stateType; };
	void setStateType(StateType stateType){ this->stateType = stateType; };

private:
	int x, y;
	std::vector<Edge*>* edges;

	StateType stateType;
};

