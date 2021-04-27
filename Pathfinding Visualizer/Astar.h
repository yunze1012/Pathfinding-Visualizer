#pragma once

#include "Algorithm.h"

class Astar : public Algorithm
{
protected:
	// updates the unvisited neighbours of the given square with the necessary informations for the next iteration
	virtual void updateUnvisitedNeighbors(shared_ptr<Square> s);
	shared_ptr<Square> getClosestSquare();

public:
	Astar(shared_ptr<Graph> graph);
	void run() override;
};
