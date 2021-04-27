#pragma once

// struct for passing subject information

enum class Status
{
	VISITED,
	PATH
};

struct Info 
{
	Status status;
	int x, y;
};
