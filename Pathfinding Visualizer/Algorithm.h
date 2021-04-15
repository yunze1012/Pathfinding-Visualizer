#pragma once

#include <omp.h>

const int THREADS = 8;

class Algorithm 
{
public:
	virtual void run() = 0;
};

