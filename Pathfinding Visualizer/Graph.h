#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <memory>
#include <vector>
#include "Square.h"

using namespace std;

class Graph
{
	vector<vector<shared_ptr<Square>>> graph;

public:
	Graph();
	Graph(int dimension);
	void setWall(int x, int y);
	void setPath(int x, int y);

	// reset the graph to initial state
	void init();
};

#endif
