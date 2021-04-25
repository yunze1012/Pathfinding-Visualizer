#include "Runner.h"
#include <chrono>

Runner::Runner(shared_ptr<Graph> graph) : graph{ graph } {}

void Runner::run(Option option) 
{
	if (option == Option::DIJKSTRA) 
	{
		algorithm = make_shared<Dijkstra>(graph);
	}
	else if (option == Option::ASTAR)
	{
		algorithm = make_shared<Astar>(graph);
	}
	else if (option == Option::DFS)
	{
		algorithm = make_shared<DFS>(graph);
	}
	else if (option == Option::BFS)
	{
		algorithm = make_shared<BFS>(graph);
	}

	auto start = chrono::high_resolution_clock::now();
	algorithm->run();
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << duration.count() << endl;
}
