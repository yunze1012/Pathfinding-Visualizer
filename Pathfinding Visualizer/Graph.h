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
	void setWall(int x, int y);
};

#endif
