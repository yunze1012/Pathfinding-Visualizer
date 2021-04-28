#include "Display.h"

Display::Display(shared_ptr<Graph> graph, shared_ptr<Runner> runner) 
    : graph(graph), runner(runner)
{
    // creating window and canvas:
    window = make_shared<sf::RenderWindow>(sf::VideoMode(1200, 900), "Pathfinder Visualizer", sf::Style::Titlebar | sf::Style::Close);
    gui = make_shared<tgui::GuiSFML>(*window);
    canvas = tgui::Canvas::create();
    gui->add(canvas);

    squareDim = 899 / graph->getDimension();

    // attaching squares to observer:
    for (int i = 0; i < graph->getDimension(); i++)
    {
        for (int j = 0; j < graph->getDimension(); j++) 
        {
            graph->getSquare(i, j)->attach(make_shared<Display>(*this));
        }
    }
}

void Display::init()
{
    // draws separation line:
    // Line vector: start->end point.
    sf::Vertex line[2] =
    {
        sf::Vertex(sf::Vector2f(950, 0), sf::Color(192, 192, 192)),
        sf::Vertex(sf::Vector2f(950, 900), sf::Color(192, 192, 192))
    };
    canvas->clear(sf::Color(255, 255, 255));
    canvas->draw(line, 2, sf::Lines);

    // Run algorithm button:
    tgui::Button::Ptr runButton = tgui::Button::create();
    runButton->setPosition(1000, 800);
    runButton->setSize(150, 50);
    runButton->setText("Run");
    runButton->onPress([&] { run(); });
    gui->add(runButton, "run");

    // Reset graph button:
    tgui::Button::Ptr resetButton = tgui::Button::create();
    resetButton->setPosition(1000, 700);
    resetButton->setSize(150, 50);
    resetButton->setText("Reset");
    resetButton->onPress([&] { reset(); });
    gui->add(resetButton, "reset");

    // Edit start option:
    tgui::RadioButton::Ptr editStartOption = tgui::RadioButton::create();
    editStartOption->setPosition(1000, 100);
    editStartOption->tgui::RadioButton::setText("Edit Start");
    gui->add(editStartOption, "editStart");
    
    // Edit end option:
    tgui::RadioButton::Ptr editEndOption = tgui::RadioButton::create();
    editEndOption->setPosition(1000, 150);
    editEndOption->tgui::RadioButton::setText("Edit End");
    gui->add(editEndOption, "editEnd");

    // Edit wall option:
    tgui::RadioButton::Ptr editWallOption = tgui::RadioButton::create();
    editWallOption->setPosition(1000, 200);
    editWallOption->tgui::RadioButton::setText("Edit Wall");
    gui->add(editWallOption, "editWall");

    // Algorithm selection scroll list:
    tgui::ComboBox::Ptr selectAlgorithmComboBox = tgui::ComboBox::create();
    selectAlgorithmComboBox->setPosition(985, 400);
    selectAlgorithmComboBox->setSize(180, 30);
    selectAlgorithmComboBox->addItem("Dijkstra", "dijkstra");
    selectAlgorithmComboBox->addItem("A*", "astar");
    selectAlgorithmComboBox->addItem("Depth-first search", "DFS");
    selectAlgorithmComboBox->addItem("Breadth-first search", "BFS");
    selectAlgorithmComboBox->addItem("Bidirectional search", "bidirectional");
    gui->add(selectAlgorithmComboBox, "selectAlgorithm");
    selectAlgorithmComboBox->setSelectedItem("Dijkstra");

    // Runtime display box:
    tgui::Label::Ptr runtimeTitleLabel = tgui::Label::create();
    runtimeTitleLabel->setText("Runtime:");
    runtimeTitleLabel->setPosition(980, 475);
    runtimeTitleLabel->setTextSize(15);
    gui->add(runtimeTitleLabel, "runtimeTitle");

    tgui::Label::Ptr runtimeLabel = tgui::Label::create();
    runtimeLabel->setText("0 ms");
    runtimeLabel->setPosition(980, 500);
    runtimeLabel->setTextSize(15);
    gui->add(runtimeLabel, "runtime");
}

void Display::reset()
{
    graph->reset();
    draw();
}

void Display::run() 
{
    if (graph->isLocked()) return;
    
    // Cannot find start or end point:
    if (graph->getStart() == nullptr) 
    {
        MessageBox(NULL, "Please select a start point", "Undefined start point", MB_OK);
        return;
    }
    else if (graph->getEnd() == nullptr)
    {
        MessageBox(NULL, "Please select an end point", "Undefined end point", MB_OK);
        return;
    }

    // locks the graph after running algorithm to avoid modifying it and creating undefined behaviours:
    graph->lock();

    // Algorithm selection:
    if (gui->get<tgui::ComboBox>("selectAlgorithm")->getSelectedItemId() == "dijkstra")
    {
        runner->run(Option::DIJKSTRA);
    }
    else if (gui->get<tgui::ComboBox>("selectAlgorithm")->getSelectedItemId() == "astar")
    {
        runner->run(Option::ASTAR);
    }
    else if (gui->get<tgui::ComboBox>("selectAlgorithm")->getSelectedItemId() == "DFS")
    {
        runner->run(Option::DFS);
    }
    else if (gui->get<tgui::ComboBox>("selectAlgorithm")->getSelectedItemId() == "BFS")
    {
        runner->run(Option::BFS);
    }
    else if (gui->get<tgui::ComboBox>("selectAlgorithm")->getSelectedItemId() == "bidirectional")
    {
        runner->run(Option::BIDIRECTIONAL);
    }

    // display popup if there was no path found:
    if (!graph->hasSuccessfulPath())
    {
        MessageBox(NULL, "There was no path found :(", "No Path", MB_OK);
    }

    // printing runtime:
    gui->get<tgui::Label>("runtime")->setText(to_string(runner->getRuntime().count() / 1000) + " ms");
}

void Display::drawSquare(int x, int y, int size, sf::Color color)
{
    sf::RectangleShape squareShape;
    squareShape.setSize(sf::Vector2f(size, size));
    squareShape.setOutlineColor(sf::Color(192, 192, 192));
    squareShape.setOutlineThickness(1);
    squareShape.setFillColor(color);
    squareShape.setPosition(squareDim * x + 35, squareDim * y + 15);
    canvas->draw(squareShape);
}

shared_ptr<Square> Display::getSquareOnMousePos() 
{
    sf::Vector2i mousepos = sf::Mouse::getPosition(*window);
    int mouseX = mousepos.x;
    int mouseY = mousepos.y;
    if (mouseX > 35 && mouseX < (squareDim * graph->getDimension()) + 35 &&
        mouseY > 15 && mouseY < (squareDim * graph->getDimension()) + 15) 
    {
        int squareX = (mouseX - 35) / squareDim;
        int squareY = (mouseY - 15) / squareDim;
        return graph->getSquare(squareX, squareY);
    }
    // if mouse is not on a square:
    return nullptr;
}

void Display::editStart()
{
    shared_ptr<Square> squareObj = getSquareOnMousePos();
    if (squareObj != nullptr)
    {
        if (squareObj != graph->getEnd() && !squareObj->isWall())
        {
            // delete old start:
            shared_ptr<Square> startSquare = graph->getStart();
            if (startSquare != nullptr)
            {
                drawSquare(startSquare->getX(), startSquare->getY(), squareDim - 1, sf::Color(255, 255, 255));
            }

            // drawing:
            drawSquare(squareObj->getX(), squareObj->getY(), squareDim - 1, sf::Color(135, 206, 235));
            graph->setStart(squareObj->getX(), squareObj->getY());
        }
    }
}

void Display::editEnd() 
{
    shared_ptr<Square> squareObj = getSquareOnMousePos();
    if (squareObj != nullptr)
    {
        if (squareObj != graph->getStart() && !squareObj->isWall())
        {
            // delete old end:
            shared_ptr<Square> endSquare = graph->getEnd();
            if (endSquare != nullptr)
            {
                drawSquare(endSquare->getX(), endSquare->getY(), squareDim - 1, sf::Color(255, 255, 255));
            }

            // drawing:
            drawSquare(squareObj->getX(), squareObj->getY(), squareDim - 1, sf::Color(255, 204, 203));
            graph->setEnd(squareObj->getX(), squareObj->getY());
        }
    }
}

void Display::editWall() 
{
    shared_ptr<Square> squareObj = getSquareOnMousePos();
    if (squareObj != nullptr)
    {
        if (squareObj != graph->getStart() && squareObj != graph->getEnd())
        {
            // removing wall:
            if (squareObj->isWall())
            {
                drawSquare(squareObj->getX(), squareObj->getY(), squareDim - 1, sf::Color(255, 255, 255));
            }
            // creating wall:
            else
            {
                drawSquare(squareObj->getX(), squareObj->getY(), squareDim - 1, sf::Color(192, 192, 192));
            }
            squareObj->changeWall();
        }
    }
}

void Display::draw()
{
	for (int i = 0; i < graph->getDimension(); i++) 
    {
        for (int j = 0; j < graph->getDimension(); j++) 
        {
            sf::RectangleShape square;
            if (j == graph->getDimension() - 1 || i == graph->getDimension() - 1) 
            {
                drawSquare(j, i, squareDim - 1, sf::Color(255, 255, 255));
            }
            else 
            {
                drawSquare(j, i, squareDim, sf::Color(255, 255, 255));
            }
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
            {
                window->close();
            }
            // checking for the current edit map option before running algorithm:
            else if (!graph->isLocked() && event.type == sf::Event::MouseButtonPressed)
            {
                if (gui->get<tgui::RadioButton>("editStart")->isChecked())
                    editStart();
                else if (gui->get<tgui::RadioButton>("editWall")->isChecked())
                    editWall();
                else if (gui->get<tgui::RadioButton>("editEnd")->isChecked())
                    editEnd();
            }
        }
        window->clear(sf::Color(255, 255, 255));
        gui->draw();
        canvas->display();
        window->display();
    }
}


void Display::notify(Subject& who) 
{
    Info info = who.getInfo();
    // green squares:
    if (info.status == Status::PATH)
    {
        if (graph->getSquare(info.x, info.y) != graph->getStart() && graph->getSquare(info.x, info.y) != graph->getEnd())
        {
            drawSquare(info.x, info.y, squareDim - 1, sf::Color(0, 128, 0));
        }
    }
    // if it is not a path, then it is a normal visited square (orange squares):
    else if (graph->getSquare(info.x, info.y) != graph->getStart() && graph->getSquare(info.x, info.y) != graph->getEnd())
    {
        drawSquare(info.x, info.y, squareDim - 1, sf::Color(255, 165, 0));
    }
    gui->draw();
    canvas->display();
    window->display();
}

void Display::start() 
{
    init();
    draw();
    render();
}
