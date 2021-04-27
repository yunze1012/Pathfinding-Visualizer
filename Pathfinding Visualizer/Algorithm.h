#pragma once

#include <climits>
#include <iostream>
#include <omp.h>
#include <queue>
#include <utility>

#include "Graph.h"

const int THREADS = 8;

class Algorithm 
{
protected:
	shared_ptr<Graph> graph;

	// returns a set of unvisited neighbours of the given square:
	vector<shared_ptr<Square>> getUnvisitedNeighbors(shared_ptr<Square> s);

	// prints the final path of the graph after running the algorithm:
	void print();
public:
	Algorithm(shared_ptr<Graph> graph);

	// runs the concrete algorithm on graph
	virtual void run() = 0;
};

