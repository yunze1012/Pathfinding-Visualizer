#pragma once

#include "Astar.h"

class Dijkstra : public Astar
{
	// updates the unvisited neighbours of the given square with the necessary informations for the next iteration but with h = 0
	void updateUnvisitedNeighbors(shared_ptr<Square> s) override;
	
public:
	Dijkstra(shared_ptr<Graph> graph);
};

