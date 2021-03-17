#include "Astar.h"
#include "Dijkstra.h"
#include "Display.h"

#include <SFML/Graphics.hpp>


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pathfinder Visualizer V0.0");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
