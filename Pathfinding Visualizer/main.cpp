#include "Display.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main(int argc, char **argv)
{
    shared_ptr<Graph> g = make_shared<Graph>(25);
    shared_ptr<Runner> runner = make_shared<Runner>(g);
    
    Display d(g, runner);

    d.start();

    _CrtDumpMemoryLeaks();
    return 0;
}
