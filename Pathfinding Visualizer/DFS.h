#pragma once

#include <stack>

#include "Algorithm.h"

class DFS : public Algorithm
{
	// set of squares waiting to be checked:
	stack<shared_ptr<Square>> waitingList;
public:
	DFS(shared_ptr<Graph> graph);
	void run() override;
};

