#include "DFS.h"

DFS::DFS(shared_ptr<Graph> graph) : Algorithm(graph) {}

void DFS::run() 
{
	waitingList.push(graph->getStart());

	while (!waitingList.empty())
	{
		shared_ptr<Square> currentSquare = waitingList.top();
		waitingList.pop();
		// skip visited squares in the waiting list:
		if (currentSquare->isVisited())
		{
			continue;
		}
		currentSquare->setVisited();
		vector<shared_ptr<Square>> unvisitedNeighbours = getUnvisitedNeighbours(currentSquare);
		// for each neighbour, link them to the current square and push them in the waiting list so they can be checked next:
		for (shared_ptr<Square> neighbour : unvisitedNeighbours)
		{
			if (!neighbour->isWall())
			{
				neighbour->setPreviousSquare(currentSquare);
				// reached the goal:
				if (neighbour == graph->getEnd()) 
				{
					print();
					return;
				}
				waitingList.push(neighbour);
			}
		}
	}
}
