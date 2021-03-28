#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <climits>
#include <iostream>
#include <utility>
#include <queue>
#include "Graph.h"

using namespace std;

class Dijkstra
{
	shared_ptr<Graph> graph;
	priority_queue <shared_ptr<Square>, vector<shared_ptr<Square>>, greater<shared_ptr<Square>>> unvisitedSquares;
	vector<shared_ptr<Square>> getUnvisitedNeighbors(shared_ptr<Square> s);
	void resortUnvisitedSquares();
	void updateUnvisitedNeighbors(shared_ptr<Square> s);
	
public:
	Dijkstra(shared_ptr<Graph> graph);
	void run(shared_ptr<Square> start, shared_ptr<Square> end);	
};

#endif
