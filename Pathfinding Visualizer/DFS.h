#pragma once

#include <stack>

#include "Algorithm.h"

using namespace std;

class DFS : public Algorithm
{
	stack<shared_ptr<Square>> waitingList;
public:
	DFS(shared_ptr<Graph> graph);
	void run() override;
};

