#pragma once

#include "Dijkstra.h"
#include "Astar.h"
#include "DFS.h"
#include "BFS.h"

enum class Option 
{
	DIJKSTRA,
	ASTAR,
	DFS,
	BFS
};

class Runner
{
	shared_ptr<Graph> graph;
	shared_ptr<Algorithm> algorithm;

public:
	Runner(shared_ptr<Graph> graph);
	void run(Option option);
};

