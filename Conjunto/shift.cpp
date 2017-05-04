#include "shift.h"

Shift::Shift(unsigned int day, unsigned int startHour, unsigned int endHour, const Driver* Driver, const Bus* Bus, const Line* Line)
{
	this->day = day;
	this->startHour = startHour;
	this->endHour = endHour;
	this->Driver = Driver;
	this->Bus = Bus;
	this->Line = Line;
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
	return *(this->Driver);
}

const Bus& Shift::GetBus()
{
	return *(this->Bus);
}

const Line& Shift::GetLine()
{
	return *(this->Line);
}