#pragma once

#include "Astar.h"

using namespace std;

class Dijkstra : public Astar
{
	void updateUnvisitedNeighbors(shared_ptr<Square> s) override;
	
public:
	Dijkstra(shared_ptr<Graph> graph);
};

