#pragma once

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
	bool locked = false;

public:
	Graph();
	Graph(int dimension);
	void setDimension(int dim);
	void setPath(int x, int y);
	void setStart(int x, int y);
	void setEnd(int x, int y);
	void reset();
	shared_ptr<Square> getSquare(int x, int y);
	shared_ptr<Square> getStart();
	shared_ptr<Square> getEnd();
	int getDimension();

	void lock();
	bool isLocked();

	// reset the graph to initial state
	void init();
};
