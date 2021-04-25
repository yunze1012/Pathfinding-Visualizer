#pragma once

#include "Algorithm.h"

class Astar : public Algorithm
{
protected:
	virtual void updateUnvisitedNeighbors(shared_ptr<Square> s);
	shared_ptr<Square> getClosestSquare();

public:
	Astar(shared_ptr<Graph> graph);
	void run() override;
};

