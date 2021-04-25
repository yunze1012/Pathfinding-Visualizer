#include "Astar.h"
#include <stdlib.h>

Astar::Astar(shared_ptr<Graph> graph) : Algorithm(graph) {}

void Astar::run()
{
	graph->getStart()->setDistance(0);
	while (true)
	{
		shared_ptr<Square> closestSquare = getClosestSquare();
		if (closestSquare->getDistance() == INT_MAX)
		{
			break;
		}

		closestSquare->setVisited();
		
		if (closestSquare == graph->getEnd())
		{
			break;
		}
		updateUnvisitedNeighbors(closestSquare);
	}
	print();
} 

void Astar::updateUnvisitedNeighbors(shared_ptr<Square> s)
{
	vector<shared_ptr<Square>> unvisitedNeighbors = getUnvisitedNeighbors(s);
	omp_set_num_threads(THREADS);
	#pragma omp parallel shared(unvisitedNeighbors)
	{
	#pragma omp for nowait
		for (shared_ptr<Square> neighbor : unvisitedNeighbors)
		{
			neighbor->setG(s->getG() + 1);
			neighbor->setH(abs(neighbor->getX() - graph->getEnd()->getX()) + abs(neighbor->getY() - graph->getEnd()->getY()));
			neighbor->setDistance(neighbor->getG() + neighbor->getH());
			neighbor->setPreviousSquare(s);
		}
	}
}

shared_ptr<Square> Astar::getClosestSquare() 
{
	shared_ptr<Square> closestSquare = nullptr;
	shared_ptr<Square> closestSquare_THREAD = nullptr;

	omp_set_num_threads(THREADS);
	#pragma omp parallel private(closestSquare_THREAD) shared(closestSquare)
	{	
		#pragma omp for nowait collapse(2)
		for (int i = 0; i < graph->getDimension(); i++) 
		{
			for (int j = 0; j < graph->getDimension(); j++) 
			{
				if (!graph->getSquare(i, j)->isVisited() && 
					!graph->getSquare(i, j)->isWall() && 
					(closestSquare_THREAD == nullptr || graph->getSquare(i, j)->getDistance() < closestSquare_THREAD->getDistance())) 
				{
					closestSquare_THREAD = graph->getSquare(i, j);
				}
			}
		}

		#pragma omp critical
		{
			if (closestSquare == nullptr || closestSquare_THREAD->getDistance() < closestSquare->getDistance()) 
			{
				closestSquare = closestSquare_THREAD;
			}
		}
	}
	return closestSquare;
}
