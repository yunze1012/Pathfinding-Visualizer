#pragma once

#include <memory>
#include <stdlib.h>
#include <vector>
#include "Square.h"

class Graph
{
	// contain squares using 2d list
	vector<vector<shared_ptr<Square>>> graph;

	// start and end squares for searching
	shared_ptr<Square> start;
	shared_ptr<Square> end;

	// number of squares on each row and column
	int dimension;

	// if true, graph cannot be modified
	bool locked = false;

	// if true, there is no path from start to end
	bool successfulPath = false;

public:
	Graph();
	Graph(int dimension);

	// getters
	int getDimension();
	shared_ptr<Square> getSquare(int x, int y);
	shared_ptr<Square> getStart();
	shared_ptr<Square> getEnd();
	bool isLocked();
	bool hasSuccessfulPath();

	// setters
	void lock();
	void setDimension(int dim);
	void setEnd(int x, int y);
	void setPath(int x, int y);
	void setStart(int x, int y);
	void setSuccessfulPath();
	
	// reset the graph to initial state
	void reset();
};
