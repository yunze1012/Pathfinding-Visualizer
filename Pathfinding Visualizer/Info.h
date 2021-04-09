#pragma once
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
