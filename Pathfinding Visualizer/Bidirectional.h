#pragma once

#include "Algorithm.h"

class Bidirectional : public Algorithm
{
	// queues for start and end squares
	queue<shared_ptr<Square>> waitingListStart;
	queue<shared_ptr<Square>> waitingListEnd;
	
	// overloaded function: returns unvisited neighbours and visited neighbours by the other direction
	vector<shared_ptr<Square>> getUnvisitedNeighbors(shared_ptr<Square> s, char visitedBy);

	// print using the intersection square as the mid point
	void print(shared_ptr<Square> intersectionSquare);
public:
	Bidirectional(shared_ptr<Graph> graph);
	void run() override;
};

