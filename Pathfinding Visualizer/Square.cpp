#include "Square.h"


void Square::setWall()
{
	wall = true;
}

void Square::setPath()
{
	path = true;
}

void Square::reset()
{
	wall = false;
	path = false;
}

bool Square::isWall()
{
	return wall;
}
