#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <utility>
#include "Graph.h"


class Dijkstra
{
	Graph * graph;
	vector<Square*> visitedSquares;
	
	Dijkstra(shared_ptr<Graph> graph);

	void run(pair<int, int> start, pair<int, int> end);
};

#endif
