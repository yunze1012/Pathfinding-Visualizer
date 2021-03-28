#include "Astar.h"
#include "Dijkstra.h"
#include "Display.h"

#include <SFML/Graphics.hpp>
// #include <TGUI/TGUI.hpp>

#include <iostream>
#include <memory>
#include <windows.h>

using namespace std;


int main(int argc, char **argv) {
    shared_ptr<Graph> g = make_shared<Graph>();
    Dijkstra d(g);
    g->getSquare(1, 0)->setWall();
    g->getSquare(1, 1)->setWall();
    d.run(g->getSquare(0, 0), g->getSquare(1, 2));
    d.print(g->getSquare(0, 0), g->getSquare(1, 2));

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
