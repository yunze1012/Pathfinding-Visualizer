#include "Square.h"


void Square::changeWall()
{
	wall = !wall;
}

int Square::getDistance()
{
	return distance;
}

shared_ptr<Square> Square::getPreviousSquare() {
	return previousSquare;
}

void Square::setPath()
{
	path = true;
}

void Square::setDistance(int distance)
{
	this->distance = distance;
}

void Square::setVisited()
{
	visited = true;
}

void Square::reset()
{
	wall = false;
	path = false;
	visited = false;
	distance = INT_MAX;
	previousSquare = nullptr;
}

bool Square::isWall()
{
	return wall;
}

bool Square::isVisited() {
	return visited;
}

int Square::getX()
{
	return x;
}

int Square::getY()
{
	return y;
}

void Square::setPreviousSquare(shared_ptr<Square> previousSquare)
{
	this->previousSquare = previousSquare;
}

Square::Square(int x, int y) : x{ x }, y{ y } {}
