#include "shift.h"

Shift::Shift(unsigned int day, unsigned int startHour, unsigned int endHour, const Driver* argDriver, const Bus* argBus, const Line* argLine)
{
	this->day = day;
	this->startHour = startHour;
	this->endHour = endHour;
	this->driver = argDriver;
	this->bus = argBus;
	this->line = argLine;
}

unsigned int Shift::GetStartHour()
{
	return this->startHour;
}


unsigned int Shift::GetEndHour()
{
	return this->endHour;
}

unsigned int Shift::GetDuration()
{
	return (this->endHour - this->startHour);
}

const Driver& Shift::GetDriver()
{
	return *(this->driver);
}

const Bus& Shift::GetBus()
{
	return *(this->bus);
}

const Line& Shift::GetLine()
{
	return *(this->line);
}