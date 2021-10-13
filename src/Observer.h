#pragma once

class Subject;

class Observer
{
public:
	virtual void notify(Subject & who) = 0;
};

