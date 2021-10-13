#include "Graph.h"

Graph::Graph()
{
	dimension = 50;
	for (int i = 0; i < dimension; i++) 
	{
		vector<shared_ptr<Square>> squares;
		for (int j = 0; j < dimension; j++) 
		{
			shared_ptr<Square> square = make_shared<Square>(i, j);
			squares.push_back(square);
		}
		graph.push_back(squares);
	}
}

Graph::Graph(int dimension)
{
	this->dimension = dimension;
	for (int i = 0; i < dimension; i++) 
	{
		vector<shared_ptr<Square>> squares;
		for (int j = 0; j < dimension; j++) 
		{
			shared_ptr<Square> square = make_shared<Square>(i, j);
			squares.push_back(square);
		}
		graph.push_back(squares);
	}
}

// getters:

shared_ptr<Square> Graph::getSquare(int x, int y)
{
	return graph[x][y];
}

int Graph::getDimension()
{
	return dimension;
}

bool Graph::isLocked() 
{
	return locked;
}

shared_ptr<Square> Graph::getStart()
{
	return start;
}

shared_ptr<Square> Graph::getEnd()
{
	return end;
}

bool Graph::hasSuccessfulPath()
{
	return successfulPath;
}

// setters:

void Graph::setPath(int x, int y)
{
	graph[x][y].get()->setPath();
}

void Graph::setDimension(int dim)
{
	this->dimension = dim;
}

void Graph::setStart(int x, int y)
{
	this->start = graph[x][y];
}

void Graph::setEnd(int x, int y)
{
	this->end = graph[x][y];
}

void Graph::lock() 
{
	locked = true;
}

void Graph::setSuccessfulPath()
{
	successfulPath = true;
}

void Graph::reset() 
{
	for (vector<shared_ptr<Square>> line : graph) 
	{
		for (shared_ptr<Square> square : line) 
		{
			square->reset();
		}
	}
	start = nullptr;
	end = nullptr;
	locked = false;
	successfulPath = false;
}