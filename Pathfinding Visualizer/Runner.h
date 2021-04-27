#pragma once

#include "Dijkstra.h"
#include "Astar.h"
#include "DFS.h"
#include "BFS.h"
#include "Bidirectional.h"

// Algorithm selection:
enum class Option 
{
	DIJKSTRA,
	ASTAR,
	DFS,
	BFS,
	BIDIRECTIONAL
};

class Runner
{
	shared_ptr<Graph> graph;
	shared_ptr<Algorithm> algorithm;

public:
	Runner(shared_ptr<Graph> graph);
	void run(Option option);
};
