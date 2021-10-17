#pragma once

#include <climits>
#include <memory>
#include "Subject.h"

using namespace std;

class Square : public Subject
{
	bool path = false;
	bool wall = false;
	bool visited = false;
	char visitedBy;	// for bidirectional 
	int distance = INT_MAX;	// f for A*
	int g = 0;
	int h = 0;
	int x;
	int y;
	shared_ptr<Square> previousSquare;
	shared_ptr<Square> nextSquare;	// for bidirectional

public:
	// getters
	bool isWall();
	bool isVisited();
	char getVisitedBy(); // for bidirectional
	int getDistance();
	int getG(); // for A*
	int getH(); // for A*
	int getX();
	int getY();
	shared_ptr<Square> getPreviousSquare();
	shared_ptr<Square> getNextSquare(); // for bidirectional

	// setters
	void changeWall();
	void setDistance(int distance);
	void setG(int); // for A*
	void setH(int); // for A*
	void setNextSquare(shared_ptr<Square> nextSquare); // for bidirectional
	void setPath();
	void setPreviousSquare(shared_ptr<Square> previousSquare);
	void setVisited();
	void setVisitedBy(char); // for bidirectional
	
	Square(int x, int y);
	virtual void reset();

	// observer methods:
	Info getInfo() override;
};
