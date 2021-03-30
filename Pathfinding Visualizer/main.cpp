#include "Astar.h"
#include "Dijkstra.h"
#include "Display.h"


using namespace std;


int main(int argc, char **argv) {
    shared_ptr<Graph> g = make_shared<Graph>();

    Display d(g);

    d.init();

    return 0;
}

