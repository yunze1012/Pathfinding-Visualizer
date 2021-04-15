#pragma once

#include "Dijkstra.h"

class Astar : public Algorithm
{
	shared_ptr<Graph> graph;
	priority_queue <shared_ptr<Square>, vector<shared_ptr<Square>>, greater<shared_ptr<Square>>> unvisitedSquares;
	vector<shared_ptr<Square>> getUnvisitedNeighbors(shared_ptr<Square> s);
	void resortUnvisitedSquares();
	void updateUnvisitedNeighbors(shared_ptr<Square> s);
	void print();
	shared_ptr<Square> getClosestSquare();

public:
	Astar(shared_ptr<Graph> graph);
	void run() override;
};


