#include "Subject.h"

void Subject::attach(std::shared_ptr<Observer> o)
{
	observer = o;
}

void Subject::notifyObserver() 
{
	observer->notify(*this);
}
