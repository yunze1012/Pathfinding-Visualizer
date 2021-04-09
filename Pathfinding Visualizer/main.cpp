#include "Astar.h"
#include "Dijkstra.h"
#include "Display.h"


using namespace std;


int main(int argc, char **argv) {
    shared_ptr<Graph> g = make_shared<Graph>();
    shared_ptr<Runner> runner = make_shared<Runner>(g);
    
    g->setDimension(25);

    Display d(g, runner);

    d.init();
    d.draw();
    d.render();

    return 0;
}

