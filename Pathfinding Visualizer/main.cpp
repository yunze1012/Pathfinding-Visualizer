#include "Astar.h"
#include "Dijkstra.h"
#include "Display.h"


using namespace std;


int main(int argc, char **argv) {
    shared_ptr<Graph> g = make_shared<Graph>();
    
    g->setDimension(25);

    Display d(g);

    d.init();
    d.draw();
    d.render();

    return 0;
}

