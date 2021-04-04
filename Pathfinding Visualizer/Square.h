#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <memory>
#include <climits>

using namespace std;

class Square
{
	int x;
	int y;
	bool wall = false; 
	bool path = false;
	bool visited = false;
	int distance = INT_MAX;
	shared_ptr<Square> previousSquare;

 public:
	int getX();
	int getY();
	int getDistance();
	shared_ptr<Square> getPreviousSquare();

	void setDistance(int distance);
	void changeWall();
	void setPath();
	void setVisited();
	void reset();
	bool isWall();
	bool isVisited();
	void setPreviousSquare(shared_ptr<Square> previousSquare);
	Square(int x, int y);
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
