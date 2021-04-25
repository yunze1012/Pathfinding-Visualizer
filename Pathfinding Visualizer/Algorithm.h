#pragma once

#include <climits>
#include <iostream>
#include <omp.h>
#include <queue>
#include <utility>

#include "Graph.h"

using namespace std;

const int THREADS = 8;

class Algorithm 
{
protected:
	shared_ptr<Graph> graph;
	vector<shared_ptr<Square>> getUnvisitedNeighbors(shared_ptr<Square> s);
	void print();
public:
	Algorithm(shared_ptr<Graph> graph);
	virtual void run() = 0;
};

