#pragma once
#include <vector>
#include "Vertex.h"
#include <list>
class Controller
{
public:
	Controller();
	virtual ~Controller();
	void AStar(Vertex* start, Vertex* end);
	void setEdges(Vertex* currentVertex);
	std::vector<Vertex*>* getVertices(){ return vertici; };
	std::vector<Edge*>* getEdges(){ return edges; };
	Vertex* getVertexCow(){ return vertexCow; };
	Vertex* getVertexRabbit(){ return vertexRabbit; };

	
	void walkThroughGraph();

	bool getRouteDone(){ return routeDone; };
	void setPositionCowAndRabbit();

private:
	void Init();
	std::vector<Vertex*>* vertici;
	std::vector<Edge*>* edges;

	Vertex* vertexCow;
	Vertex* vertexRabbit;

	/*bool sortByGuessedTotalDistance(Vertex *lhs, Vertex *rhs);*/
	int calculateHeuristic(Vertex* source, Vertex* target);
	std::list<Vertex*> route;
	bool routeDone = true;
};

