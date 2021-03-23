#include "Graph.h"

Graph::Graph()
{
	dimension = 50;
	for (int i = 0; i < dimension; i++) {
		vector<shared_ptr<Square>> squares;
		for (int j = 0; j < dimension; j++) {
			shared_ptr<Square> square = make_shared<Square>();
			squares.push_back(square);
		}
		graph.push_back(squares);
	}
}

Graph::Graph(int dimension)
{
	this->dimension = dimension;
	for (int i = 0; i < dimension; i++) {
		vector<shared_ptr<Square>> squares;
		for (int j = 0; j < dimension; j++) {
			shared_ptr<Square> square = make_shared<Square>();
			squares.push_back(square);
		}
		graph.push_back(squares);
	}
}

void Graph::setWall(int x, int y)
{
	graph[x][y]->setWall();
}

void Graph::setPath(int x, int y)
{
	graph[x][y].get()->setPath();
}

shared_ptr<Square> Graph::getSquare(int x, int y)
{
	return graph[x][y];
}

int Graph::getDimension()
{
	return dimension;
}

int Graph::getDistance(pair<int, int> start, pair<int, int> dest)
{
	if (abs(start.first - dest.first) > 1 || abs(start.second - dest.second) > 1 || graph[dest.first][dest.second]->isWall()) {
		return int(INFINITY);
	}
	return 1;
}

void Graph::init()
{
	for (vector<shared_ptr<Square>> squares : graph) {
		for (shared_ptr<Square> square : squares) {
			square.get()->reset();
		}
	}
}
