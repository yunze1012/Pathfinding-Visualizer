#include "Dijkstra.h"

Dijkstra::Dijkstra(shared_ptr<Graph> graph) : Astar(graph) {}

void Dijkstra::updateUnvisitedNeighbours(shared_ptr<Square> s)
{
	vector<shared_ptr<Square>> unvisitedNeighbours = getUnvisitedNeighbours(s);
	omp_set_num_threads(THREADS);
	#pragma omp parallel shared(unvisitedNeighbours)
	{
		#pragma omp for nowait
		for (shared_ptr<Square> neighbour : unvisitedNeighbours)
		{
			neighbour->setG(s->getG() + 1);
			neighbour->setDistance(neighbour->getG() + neighbour->getH());
			neighbour->setPreviousSquare(s);
		}
	}
}
