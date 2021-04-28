#include "Runner.h"

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
	else if (option == Option::BIDIRECTIONAL)
	{
		algorithm = make_shared<Bidirectional>(graph);
	}

	// chrono is to computer the runtime of the selected algorithm:
	auto start = chrono::high_resolution_clock::now();

	algorithm->run();

	auto stop = chrono::high_resolution_clock::now();
	runtime = chrono::duration_cast<chrono::microseconds>(stop - start);
}

chrono::microseconds Runner::getRuntime()
{
	return runtime;
}