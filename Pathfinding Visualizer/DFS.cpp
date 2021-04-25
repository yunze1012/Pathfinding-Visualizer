#include "DFS.h"

DFS::DFS(shared_ptr<Graph> graph) : Algorithm(graph) {}

void DFS::run() 
{
	waitingList.push(graph->getStart());

	while (!waitingList.empty())
	{
		shared_ptr<Square> currentSquare = waitingList.top();
		waitingList.pop();
		currentSquare->setVisited();
		vector<shared_ptr<Square>> unvisitedNeighbours = getUnvisitedNeighbors(currentSquare);
		for (shared_ptr<Square> neighbour : unvisitedNeighbours)
		{
			if (!neighbour->isWall())
			{
				neighbour->setPreviousSquare(currentSquare);
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
