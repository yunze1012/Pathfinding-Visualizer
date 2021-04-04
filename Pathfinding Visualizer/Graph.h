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
	shared_ptr<Square> start;
	shared_ptr<Square> end;
	int dimension;

public:
	Graph();
	Graph(int dimension);
	void setDimension(int dim);
	void setPath(int x, int y);
	// void setWall(int x, int y);
	void setStart(int x, int y);
	void setEnd(int x, int y);
	void reset();
	shared_ptr<Square> getSquare(int x, int y);
	shared_ptr<Square> getStart();
	shared_ptr<Square> getEnd();
	int getDimension();

	// reset the graph to initial state
	void init();
};

#endif
