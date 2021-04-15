#include "Runner.h"
#include <chrono>

Runner::Runner(shared_ptr<Graph> graph) : graph{ graph } {}

void Runner::run(Option option) 
{
	if (option == Option::DIJKSTRA) 
	{
		algorithm = make_shared<Dijkstra>(graph);
		auto start = chrono::high_resolution_clock::now();
		algorithm->run();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		cout << duration.count() << endl;

	}
	else if (option == Option::ASTAR)
	{
		algorithm = make_shared<Astar>(graph);
		auto start = chrono::high_resolution_clock::now();
		algorithm->run();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		cout << duration.count() << endl;
	}
}
