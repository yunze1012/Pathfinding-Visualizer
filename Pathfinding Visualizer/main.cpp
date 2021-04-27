#include "Display.h"

using namespace std;

int main(int argc, char **argv)
{
    shared_ptr<Graph> g = make_shared<Graph>(25);
    shared_ptr<Runner> runner = make_shared<Runner>(g);
    
    Display d(g, runner);

    d.start();

    return 0;
}
