#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <climits>
#include <memory>
#include "Subject.h"

using namespace std;

class Square : public Subject
{
	int x;
	int y;
	bool wall = false;
	bool visited = false;
	bool path = false;
	int distance = INT_MAX;	// f for Astar
	int g = 0;
	int h = 0;
	shared_ptr<Square> previousSquare;

public:
	int getX();
	int getY();
	int getDistance();
	int getG();
	int getH();
	shared_ptr<Square> getPreviousSquare();

	void setDistance(int distance);
	void changeWall();
	void setPath();
	void setVisited();
	void setG(int);
	void setH(int);
	void reset();
	bool isWall();
	bool isVisited();
	void setPreviousSquare(shared_ptr<Square> previousSquare);
	Square(int x, int y);

	// observer methods:
	Info getInfo() override;
};

inline
bool operator<(const shared_ptr<Square> lhs, const shared_ptr<Square> rhs) 
{
	return lhs->getDistance() < rhs->getDistance();
}

inline
bool operator>(const shared_ptr<Square> lhs, const shared_ptr<Square> rhs) 
{
	return lhs->getDistance() > rhs->getDistance();
}

#endif
