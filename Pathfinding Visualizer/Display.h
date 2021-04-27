#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <windows.h>
#pragma comment(lib,"user32.lib")

#include "Graph.h"
#include "Observer.h"
#include "Runner.h"

class Display : public Observer
{
	int squareDim;
	shared_ptr<Graph> graph;
	shared_ptr<Runner> runner;	// instantiates and runs each selected algorithm

	// graphic interface:
	shared_ptr<sf::RenderWindow> window;
	shared_ptr<tgui::GuiSFML> gui;
	shared_ptr<tgui::Canvas> canvas;

	// draws a new square with the given color and given size on the given position:
	void drawSquare(int x, int y, int size, sf::Color color);
	
	// user uses mouse click to edit the start square
	void editStart();

	// user uses mouse click to edit the end square
	void editEnd();

	// user uses mouse click to edit the walls
	void editWall();

	// resets the graph:
	void reset();

	// runs the display
	void run();

	// returns the square superposed with the current mouse position:
	shared_ptr<Square> getSquareOnMousePos();

	// Observer methods:
	void notify(Subject & who) override;

	// initialize the GUI: 
	void init();

	// draws the empty graph on the GUI:
	void draw();

	// renders the GUI on the display:
	void render();

public:
	Display(shared_ptr<Graph> graph, shared_ptr<Runner> runner);

	// starts the display:
	void start();
};

