#include "Astar.h"
#include "Dijkstra.h"
#include "Display.h"

using namespace std;

int main(int argc, char **argv) {
    shared_ptr<Graph> g = make_shared<Graph>(25);
    shared_ptr<Runner> runner = make_shared<Runner>(g);
    
    Display d(g, runner);

    d.init();
    d.draw();
    d.render();

    return 0;
}

