#include "Graph.h"

Graph::Graph()
{
	dimension = 50;
	for (int i = 0; i < dimension; i++) {
		vector<shared_ptr<Square>> squares;
		for (int j = 0; j < dimension; j++) {
			shared_ptr<Square> square = make_shared<Square>(i, j);
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
			shared_ptr<Square> square = make_shared<Square>(i, j);
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

void Graph::init()
{
	for (vector<shared_ptr<Square>> squares : graph) {
		for (shared_ptr<Square> square : squares) {
			square.get()->reset();
		}
	}
}
