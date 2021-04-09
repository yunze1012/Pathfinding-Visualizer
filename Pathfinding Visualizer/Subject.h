#pragma once
#include <memory>
#include "Info.h"
#include "Observer.h"

class Subject
{
	std::shared_ptr<Observer> observer;

public:
	void attach(std::shared_ptr<Observer> o);
	virtual Info getInfo() = 0;
	void notifyObserver();
};
