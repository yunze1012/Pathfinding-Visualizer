#include "Bidirectional.h"

Bidirectional::Bidirectional(shared_ptr<Graph> graph) : Algorithm(graph) {}

void Bidirectional::run()
{
	shared_ptr<Square> startSquare = graph->getStart();
	shared_ptr<Square> endSquare = graph->getEnd();
	startSquare->setVisited();
	startSquare->setVisitedBy('s');
	endSquare->setVisited();
	endSquare->setVisitedBy('e');
	waitingListStart.push(startSquare);
	waitingListEnd.push(endSquare);

	omp_set_num_threads(THREADS);
	#pragma omp parallel shared(startSquare, endSquare)
	{
		while (!waitingListStart.empty() && !waitingListEnd.empty())
		{
			// BFS from the start square:
			startSquare = waitingListStart.front();
			waitingListStart.pop();
			vector<shared_ptr<Square>> startUnvisitedNeighbours = getUnvisitedNeighbors(startSquare, 's');
			for (shared_ptr<Square> neighbour : startUnvisitedNeighbours)
			{
				if (!neighbour->isWall())
				{
					neighbour->setPreviousSquare(startSquare);
					if (neighbour->isVisited()) 
					{
						print(neighbour);
						return;
					}
					neighbour->setVisited();
					neighbour->setVisitedBy('s');
					waitingListStart.push(neighbour);
				}
			}

			// BFS from the end square:
			endSquare = waitingListEnd.front();
			waitingListEnd.pop();
			vector<shared_ptr<Square>> endUnvisitedNeighbours = getUnvisitedNeighbors(endSquare, 'e');
			for (shared_ptr<Square> neighbour : endUnvisitedNeighbours)
			{
				if (!neighbour->isWall())
				{
					neighbour->setNextSquare(endSquare);
					if (neighbour->isVisited()) 
					{
						print(neighbour);
						return;
					}
					neighbour->setVisited();
					neighbour->setVisitedBy('e');
					waitingListEnd.push(neighbour);
				}
			}
		}
	}
}

vector<shared_ptr<Square>> Bidirectional::getUnvisitedNeighbors(shared_ptr<Square> s, char visitedBy) {
	vector<shared_ptr<Square>> unvisitedNeighbors;
	int x = s->getX();
	int y = s->getY();

	// checking all 4 directions if not visited or visited by the other direction:
	if (x > 0 && (!(graph->getSquare(x - 1, y)->isVisited()) || graph->getSquare(x - 1, y)->getVisitedBy() != visitedBy))
	{
		unvisitedNeighbors.emplace_back(graph->getSquare(x - 1, y));
	}
	if (x < graph->getDimension() - 1 && (!(graph->getSquare(x + 1, y)->isVisited()) || graph->getSquare(x + 1, y)->getVisitedBy() != visitedBy))
	{
		unvisitedNeighbors.emplace_back(graph->getSquare(x + 1, y));
	}
	if (y > 0 && (!(graph->getSquare(x, y - 1)->isVisited()) || graph->getSquare(x, y - 1)->getVisitedBy() != visitedBy))
	{
		unvisitedNeighbors.emplace_back(graph->getSquare(x, y - 1));
	}
	if (y < graph->getDimension() - 1 && (!(graph->getSquare(x, y + 1)->isVisited()) || graph->getSquare(x, y + 1)->getVisitedBy() != visitedBy))
	{
		unvisitedNeighbors.emplace_back(graph->getSquare(x, y + 1));
	}
	return unvisitedNeighbors;
}

void Bidirectional::print(shared_ptr<Square> intersectionSquare) 
{
	vector<shared_ptr<Square>> finalPathEnd;
	vector<shared_ptr<Square>> finalPathStart;
	auto currentSquare = intersectionSquare;
	// creating path from intersection square to end square:
	while (currentSquare != nullptr)
	{
		finalPathEnd.emplace_back(currentSquare);
		currentSquare = currentSquare->getNextSquare();
	}
	currentSquare = intersectionSquare->getPreviousSquare();
	// creating path from intersection square to start square:
	while (currentSquare != nullptr)
	{
		finalPathStart.emplace_back(currentSquare);
		currentSquare = currentSquare->getPreviousSquare();
	}

	// printing from start to intersection:
	for (int i = finalPathStart.size() - 1; i >= 0; i--)
	{
		finalPathStart[i]->setPath();
	}

	// printing from intersection to end:
	for (int i = 0; i < finalPathEnd.size(); i++)
	{
		finalPathEnd[i]->setPath();
	}
}
