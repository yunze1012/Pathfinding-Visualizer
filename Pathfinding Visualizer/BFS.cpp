#include "BFS.h"

BFS::BFS(shared_ptr<Graph> graph) : Algorithm(graph) {}

void BFS::run() 
{
	graph->getStart()->setVisited();
	waitingList.push(graph->getStart());

	while (!waitingList.empty())
	{
		shared_ptr<Square> currentSquare = waitingList.front();
		waitingList.pop();
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
				neighbour->setVisited();
				waitingList.push(neighbour);
			}
		}
	}
}
