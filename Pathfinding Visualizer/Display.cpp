#include "Display.h"

Display::Display(shared_ptr<Graph> g) 
    : g(g) 
{
    window = make_shared<sf::RenderWindow>(sf::VideoMode(1200, 900), "Pathfinder Visualizer V0.1", sf::Style::Titlebar | sf::Style::Close);
    gui = make_shared<tgui::GuiSFML>(*window);
    canvas = tgui::Canvas::create();
    gui->add(canvas);
}

void Display::init()
{
    // Line vector: start->end point.
    sf::Vertex line[2] =
    {
        sf::Vertex(sf::Vector2f(950, 0), sf::Color(192, 192, 192)),
        sf::Vertex(sf::Vector2f(950, 900), sf::Color(192, 192, 192))
    };
    canvas->clear(sf::Color(255, 255, 255));
    canvas->draw(line, 2, sf::Lines);


    tgui::Button::Ptr runButton = tgui::Button::create();
    runButton->setPosition(1000, 800);
    runButton->setSize(150, 50);
    runButton->setText("Run");

    tgui::Button::Ptr editStartButton = tgui::Button::create();
    editStartButton->setPosition(1000, 100);
    editStartButton->setSize(150, 50);
    editStartButton->setText("Edit Start");

    gui->add(editStartButton);
    gui->add(runButton);
}

void Display::draw()
{
    float squareDim = 899 / g->getDimension();
	for (int i = 0; i < g->getDimension(); i++) 
    {
        for (int j = 0; j < g->getDimension(); j++) 
        {
            sf::RectangleShape square;
            square.setSize(sf::Vector2f(squareDim, squareDim));
            square.setOutlineColor(sf::Color(192, 192, 192));
            square.setOutlineThickness(1);
            square.setPosition((squareDim * j) + 35, (squareDim * i) + 15);
            canvas->draw(square);
        }
	}
}

void Display::render()
{
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
        canvas->display();
        window->display();
    }
}

