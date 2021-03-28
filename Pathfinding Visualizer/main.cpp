#include "Astar.h"
#include "Dijkstra.h"
#include "Display.h"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
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

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pathfinder Visualizer V0.0");
    tgui::GuiSFML gui{ window };
    tgui::Button::Ptr button = tgui::Button::create();
    button->setPosition(50, 50);
    button->setSize(200, 50);

    gui.add(button);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        gui.draw();
        window.display();
    }

    /*priority_queue <shared_ptr<Square>, vector<shared_ptr<Square>>, greater<shared_ptr<Square>>> unvisitedNodes;
    shared_ptr<Square> two = make_shared<Square>(0, 0);
    two->setDistance(2);
    shared_ptr<Square> one = make_shared<Square>(0, 1);
    one->setDistance(1);
    shared_ptr<Square> four = make_shared<Square>(0, 2);
    four->setDistance(4);
    shared_ptr<Square> three = make_shared<Square>(0, 3);
    three->setDistance(3);
    unvisitedNodes.emplace(one);
    unvisitedNodes.emplace(two);
    unvisitedNodes.emplace(three);
    unvisitedNodes.emplace(four);
    
    cout << unvisitedNodes.top()->getDistance() << endl;
    four->setDistance(0);
    std::make_heap(const_cast<shared_ptr<Square>*>(&unvisitedNodes.top()),
        const_cast<shared_ptr<Square>*>(&unvisitedNodes.top()) + unvisitedNodes.size(),
        greater<shared_ptr<Square>>());

    cout << unvisitedNodes.top()->getDistance() << endl;*/

    /*while(unvisitedNodes.empty() == false) {
        cout << unvisitedNodes.top()->getDistance() << endl;
        unvisitedNodes.pop();
    }*/

    return 0;
}
