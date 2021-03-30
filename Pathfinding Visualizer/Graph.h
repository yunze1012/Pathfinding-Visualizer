#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <memory>
#include <stdlib.h>
#include <vector>
#include "Square.h"

using namespace std;

class Graph
{
	vector<vector<shared_ptr<Square>>> graph;
	int dimension;

public:
	Graph();
	Graph(int dimension);
	void setWall(int x, int y);
	void setPath(int x, int y);
	void setDimension(int dim);
	shared_ptr<Square> getSquare(int x, int y);
	int getDimension();

	// reset the graph to initial state
	void init();
};

#endif
