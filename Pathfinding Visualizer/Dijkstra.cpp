#include "Dijkstra.h"

Dijkstra::Dijkstra(shared_ptr<Graph> graph) : Astar(graph) {}

void Dijkstra::updateUnvisitedNeighbors(shared_ptr<Square> s)
{
	vector<shared_ptr<Square>> unvisitedNeighbors = getUnvisitedNeighbors(s);
	omp_set_num_threads(THREADS);
	#pragma omp parallel shared(unvisitedNeighbors)
	{
		#pragma omp for nowait
		for (shared_ptr<Square> neighbor : unvisitedNeighbors)
		{
			neighbor->setG(s->getG() + 1);
			neighbor->setDistance(neighbor->getG() + neighbor->getH());
			neighbor->setPreviousSquare(s);
		}
	}
}
