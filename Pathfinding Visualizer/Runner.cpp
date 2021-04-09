#include "Runner.h"

Runner::Runner(shared_ptr<Graph> graph) : graph{ graph } {}

void Runner::run(Option option) 
{
	if (option == Option::DIJKSTRA) 
	{
		algorithm = make_shared<Dijkstra>(graph);
		algorithm->run();
	}
}
