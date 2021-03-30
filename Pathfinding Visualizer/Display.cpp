#include "Display.h"

Display::Display(shared_ptr<Graph> g) 
    : g(g) 
{
    window = make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), "Pathfinder Visualizer V0.1");
    gui = make_shared<tgui::GuiSFML>(*window);
}

void Display::init()
{
    auto canvas = tgui::Canvas::create();
    gui->add(canvas);

    tgui::Button::Ptr button = tgui::Button::create();
    button->setPosition(1080, 620);
    button->setSize(150, 50);
    gui->add(button);

    // Line vector: start->end point.
    sf::Vertex line[2] =
    {
        sf::Vertex(sf::Vector2f(1030, 0), sf::Color(255, 255, 255)),
        sf::Vertex(sf::Vector2f(1030, 720), sf::Color(255, 255, 255))
    };
    canvas->draw(line, 2, sf::Lines);

    // TODO Move this block
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            gui->handleEvent(event);

            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color(255, 255, 255));
        gui->draw();
        window->display();
    }
}

void Display::draw()
{
	for (int i = 0; i < g->getDimension(); i++) {
		
	}
}
