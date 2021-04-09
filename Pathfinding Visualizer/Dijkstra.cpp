#include "Dijkstra.h"

Dijkstra::Dijkstra(shared_ptr<Graph> graph)
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

void Dijkstra::run()
{
	vector<shared_ptr<Square>> visitedNodes;
	graph->getStart()->setDistance(0);
	while (!unvisitedSquares.empty()) 
	{
		resortUnvisitedSquares();
		shared_ptr<Square> closestSquare = unvisitedSquares.top();
		unvisitedSquares.pop();
		if (closestSquare->isWall()) 
		{
			continue;
		}
		if (closestSquare->getDistance() == INT_MAX)
		{
			break;
		}

		closestSquare->setVisited();
		closestSquare->notifyObserver();
		visitedNodes.emplace_back(closestSquare);
		
		if (closestSquare == graph->getEnd())
		{
			break;
		}
		updateUnvisitedNeighbors(closestSquare);
	}
	print();
}

void Dijkstra::print()
{
	vector<shared_ptr<Square>> finalPath;
	auto currentSquare = graph->getEnd();
	while (currentSquare != nullptr)
	{
		finalPath.emplace_back(currentSquare);
		currentSquare = currentSquare->getPreviousSquare();
	}

	if (finalPath[finalPath.size() - 1] != graph->getStart())
	{
		cout << "No path" << endl;
		return;
	}

	for (int i = finalPath.size() - 1; i >= 0; i--)
	{
		finalPath[i]->setPath();
		finalPath[i]->notifyObserver();
		// cout << "(" << finalPath.at(i)->getX() << ", " << finalPath.at(i)->getY() << "), ";
	}
}

void Dijkstra::updateUnvisitedNeighbors(shared_ptr<Square> s)
{
	vector<shared_ptr<Square>> unvisitedNeighbors = getUnvisitedNeighbors(s);
	for (shared_ptr<Square> neighbor : unvisitedNeighbors)
	{
		neighbor->setDistance(s->getDistance() + 1);
		neighbor->setPreviousSquare(s);
	}
}

vector<shared_ptr<Square>> Dijkstra::getUnvisitedNeighbors(shared_ptr<Square> s)
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

void Dijkstra::resortUnvisitedSquares()
{
	make_heap(const_cast<shared_ptr<Square>*>(&unvisitedSquares.top()),
		const_cast<shared_ptr<Square>*>(&unvisitedSquares.top()) + unvisitedSquares.size(),
		greater<shared_ptr<Square>>());
}
