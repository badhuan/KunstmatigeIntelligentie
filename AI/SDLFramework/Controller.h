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

private:
	void Init();
	std::vector<Vertex*>* vertici;
};

