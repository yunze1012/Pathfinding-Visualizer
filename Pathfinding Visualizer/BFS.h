#pragma once

#include <queue>

#include "Algorithm.h"

class BFS : public Algorithm
{
	queue<shared_ptr<Square>> waitingList;
public:
	BFS(shared_ptr<Graph> graph);
	void run() override;
};
