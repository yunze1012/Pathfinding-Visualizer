#include "Astar.h"
#include <stdlib.h>

Astar::Astar(shared_ptr<Graph> graph)
{
	this->graph = graph;
	for (int i = 0; i < graph->getDimension(); i++) 
	{
		for (int j = 0; j < graph->getDimension(); j++) 
		{
			unvisitedSquares.push(graph->getSquare(i, j));
		}
	}
}

//void Astar::run()
//{
//	graph->getStart()->setDistance(0);
//	while (!unvisitedSquares.empty()) 
//	{
//		resortUnvisitedSquares();
//		shared_ptr<Square> closestSquare = unvisitedSquares.top();
//		unvisitedSquares.pop();
//		if (closestSquare->isWall()) 
//		{
//			continue;
//		}
//		if (closestSquare->getDistance() == INT_MAX)
//		{
//			break;
//		}

//		closestSquare->setVisited();
//		closestSquare->notifyObserver();
		
//		if (closestSquare == graph->getEnd())
//		{
//			break;
//		}
//		updateUnvisitedNeighbors(closestSquare);
//	}
//	print();
//} 

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
		closestSquare->notifyObserver();
		
		if (closestSquare == graph->getEnd())
		{
			break;
		}
		updateUnvisitedNeighbors(closestSquare);
	}
	print();
} 



void Astar::print()
{
	vector<shared_ptr<Square>> finalPath;
	auto currentSquare = graph->getEnd();
	while (currentSquare != nullptr)
	{
		finalPath.emplace_back(currentSquare);
		currentSquare = currentSquare->getPreviousSquare();
	}

	if (finalPath[finalPath.size() - 1] != graph->getStart()) return;

	for (int i = finalPath.size() - 1; i >= 0; i--)
	{
		finalPath[i]->setPath();
		finalPath[i]->notifyObserver();
	}
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

vector<shared_ptr<Square>> Astar::getUnvisitedNeighbors(shared_ptr<Square> s)
{
	vector<shared_ptr<Square>> unvisitedNeighbors;
	int x = s->getX();
	int y = s->getY();
	if (x > 0 && !(graph->getSquare(x - 1, y)->isVisited()))
	{
		unvisitedNeighbors.emplace_back(graph->getSquare(x - 1, y));
	}
	if (x < graph->getDimension() - 1 && !(graph->getSquare(x + 1, y)->isVisited()))
	{
		unvisitedNeighbors.emplace_back(graph->getSquare(x + 1, y));
	}
	if (y > 0 && !(graph->getSquare(x, y - 1)->isVisited()))
	{
		unvisitedNeighbors.emplace_back(graph->getSquare(x, y - 1));
	}
	if (y < graph->getDimension() - 1 && !(graph->getSquare(x, y + 1)->isVisited()))
	{
		unvisitedNeighbors.emplace_back(graph->getSquare(x, y + 1));
	}
	return unvisitedNeighbors;
}

void Astar::resortUnvisitedSquares()
{
	make_heap(const_cast<shared_ptr<Square>*>(&unvisitedSquares.top()),
		const_cast<shared_ptr<Square>*>(&unvisitedSquares.top()) + unvisitedSquares.size(),
		greater<shared_ptr<Square>>());
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
