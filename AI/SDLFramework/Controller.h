#pragma once
#include <vector>
#include "Vertex.h"
class Controller
{
public:
	Controller();
	virtual ~Controller();
	void AStar();
	std::vector<Vertex*>* getVertices(){ return vertici; };
	std::vector<Edge*>* getEdges(){ return edges; };
	Vertex* getVertexCow(){ return vertexCow; };
	Vertex* getVertexRabbit(){ return vertexRabbit; };

private:
	void Init();
	std::vector<Vertex*>* vertici;
	std::vector<Edge*>* edges;

	Vertex* vertexCow;
	Vertex* vertexRabbit;

	void swap(std::vector<Vertex*>* list, Vertex* source, Vertex* target);
	int calculateHeuristic(Vertex* source, Vertex* target);
};

