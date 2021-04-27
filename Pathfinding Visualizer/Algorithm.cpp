#include "Algorithm.h"

Algorithm::Algorithm(shared_ptr<Graph> graph) : graph{ graph } {}

vector<shared_ptr<Square>> Algorithm::getUnvisitedNeighbors(shared_ptr<Square> s)
{
	vector<shared_ptr<Square>> unvisitedNeighbors;
	int x = s->getX();
	int y = s->getY();
	// checking all 4 directions:
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


void Algorithm::print()
{
	vector<shared_ptr<Square>> finalPath;
	auto currentSquare = graph->getEnd();
	// creating final path:
	while (currentSquare != nullptr)
	{
		finalPath.emplace_back(currentSquare);
		currentSquare = currentSquare->getPreviousSquare();
	}

	// if there is no path found:
	if (finalPath[finalPath.size() - 1] != graph->getStart()) return;

	// printing final path if there is one:
	for (int i = finalPath.size() - 1; i >= 0; i--)
	{
		finalPath[i]->setPath();
	}
}
