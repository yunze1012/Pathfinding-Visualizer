#pragma once
#include "Dijkstra.h"

enum class Option 
{
	DIJKSTRA
};

class Runner
{
	shared_ptr<Graph> graph;
	shared_ptr<Algorithm> algorithm;

public:
	Runner(shared_ptr<Graph> graph);
	void run(Option option);
};
