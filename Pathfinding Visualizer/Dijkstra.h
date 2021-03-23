#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <utility>
#include "Graph.h"


class Dijkstra
{
	shared_ptr<Graph> graph;
	vector<vector<int>> visited;
	
	Dijkstra(shared_ptr<Graph> graph);

	// computes the minimum distance starting from position x, y and add the destination square in visitedSquares.
	int minimumDistance(int x, int y);

	void run(pair<int, int> start, pair<int, int> end);
};

#endif
