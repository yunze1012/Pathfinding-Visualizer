#include "Astar.h"
#include <stdlib.h>

Astar::Astar(shared_ptr<Graph> graph) : Algorithm(graph) {}

void Astar::run()
{
	graph->getStart()->setDistance(0);
	while (true)
	{
		shared_ptr<Square> closestSquare = getClosestSquare();
		// no path:
		if (closestSquare->getDistance() == INT_MAX)
		{
			break;
		}

		closestSquare->setVisited();
		
		// reached the goal:
		if (closestSquare == graph->getEnd())
		{
			break;
		}
		// updating each neighbour with distance and heuristic information for the next iteration
		updateUnvisitedNeighbours(closestSquare);
	}
	print();
} 

void Astar::updateUnvisitedNeighbours(shared_ptr<Square> s)
{
	vector<shared_ptr<Square>> unvisitedNeighbours = getUnvisitedNeighbours(s);
	omp_set_num_threads(THREADS);
	#pragma omp parallel shared(unvisitedNeighbours)
	{
	#pragma omp for nowait
		for (shared_ptr<Square> neighbour : unvisitedNeighbours)
		{
			neighbour->setG(s->getG() + 1);
			neighbour->setH(abs(graph->getEnd()->getX() - neighbour->getX()) + abs(graph->getEnd()->getY() - neighbour->getY()));
			neighbour->setDistance(neighbour->getG() + neighbour->getH());
			neighbour->setPreviousSquare(s);
		}
	}
}

shared_ptr<Square> Astar::getClosestSquare() 
{
	shared_ptr<Square> closestSquare = nullptr;	// thread common memory
	shared_ptr<Square> closestSquare_THREAD = nullptr;	// thread independent memory

	omp_set_num_threads(THREADS);
	#pragma omp parallel private(closestSquare_THREAD) shared(closestSquare)
	{	
		// each thread searches for its own closest square in its own set of squares
		#pragma omp for nowait collapse(2)
		for (int i = 0; i < graph->getDimension(); i++) 
		{
			for (int j = 0; j < graph->getDimension(); j++) 
			{
				if (!graph->getSquare(i, j)->isVisited() && 

					!graph->getSquare(i, j)->isWall() &&

					(closestSquare_THREAD == nullptr ||
					graph->getEnd()->getX() - graph->getStart()->getX() >= 0 && graph->getSquare(i, j)->getDistance() <= closestSquare_THREAD->getDistance() ||
					graph->getEnd()->getX() - graph->getStart()->getX() < 0 && graph->getSquare(i, j)->getDistance() < closestSquare_THREAD->getDistance()))
				{
					closestSquare_THREAD = graph->getSquare(i, j);
				}
			}
		}

		// comparing the closest square found from each thread to find the common (or global) closest square between them 4:
		#pragma omp critical
		{
			if (closestSquare == nullptr ||
				graph->getEnd()->getX() - graph->getStart()->getX() >= 0 && closestSquare_THREAD->getDistance() <= closestSquare->getDistance() ||
				graph->getEnd()->getX() - graph->getStart()->getX() < 0 && closestSquare_THREAD->getDistance() < closestSquare->getDistance())
			{
				closestSquare = closestSquare_THREAD;
			}
		}
	}
	return closestSquare;
}
