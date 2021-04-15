#pragma once
#include "Dijkstra.h"
#include "Astar.h"

enum class Option 
{
	DIJKSTRA,
	ASTAR
};

class Runner
{
	shared_ptr<Graph> graph;
	shared_ptr<Algorithm> algorithm;

public:
	Runner(shared_ptr<Graph> graph);
	void run(Option option);
};
