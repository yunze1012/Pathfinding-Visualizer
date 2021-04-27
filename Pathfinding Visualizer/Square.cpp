#include "Square.h"

Square::Square(int x, int y) : x{ x }, y{ y } {}

// getters:
bool Square::isWall()
{
	return wall;
}

bool Square::isVisited()
{
	return visited;
}

Info Square::getInfo()
{
	if (path)
	{
		return Info{ Status::PATH, x, y };
	}
	return Info{ Status::VISITED, x, y };
}

char Square::getVisitedBy()
{
	return visitedBy;
}

shared_ptr<Square> Square::getPreviousSquare()
{
	return previousSquare;
}

shared_ptr<Square> Square::getNextSquare()
{
	return nextSquare;
}

int Square::getX()
{
	return x;
}

int Square::getY()
{
	return y;
}

int Square::getDistance()
{
	return distance;
}

int Square::getG() { return g; }

int Square::getH() { return h; }

// setters:

void Square::changeWall()
{
	wall = !wall;
}

void Square::setPath()
{
	path = true;
	notifyObserver();
}

void Square::setVisited()
{
	visited = true;
	notifyObserver();
}

void Square::setDistance(int distance)
{
	this->distance = distance;
}

void Square::setG(int g) { this->g = g; }

void Square::setH(int h) { this->h = h; }

void Square::setPreviousSquare(shared_ptr<Square> previousSquare)
{
	this->previousSquare = previousSquare;
}

void Square::setNextSquare(shared_ptr<Square> nextSquare)
{
	this->nextSquare = nextSquare;
}

void Square::setVisitedBy(char visitedBy)
{
	this->visitedBy = visitedBy;
}

// resets the current square to initial status
void Square::reset()
{
	wall = false;
	path = false;
	visited = false;
	distance = INT_MAX;
	g = 0;
	h = 0;
	previousSquare = nullptr;
	nextSquare = nullptr;
}
