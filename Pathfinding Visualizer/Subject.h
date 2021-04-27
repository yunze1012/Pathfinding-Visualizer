#pragma once
#include <memory>
#include "Info.h"
#include "Observer.h"

class Subject
{
	std::shared_ptr<Observer> observer;
public:
	// attach observer to subject (setter)
	void attach(std::shared_ptr<Observer> o);

	// returns subject info for observer to know state
	virtual Info getInfo() = 0;

	// notifies observer
	void notifyObserver();
};
