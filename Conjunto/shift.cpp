#include "shift.h"

Shift::Shift(unsigned int argDay, unsigned int argStartHour, unsigned int argEndHour, const Driver* argDriver, const Bus* argBus, const Line* argLine)
{
	day = argDay;
	startHour = argStartHour;
	endHour = argEndHour;
	driver = argDriver;
	bus = argBus;
	line = argLine;
}

unsigned int Shift::GetStartHour()
{
	return startHour;
}


unsigned int Shift::GetEndHour()
{
	return endHour;
}

unsigned int Shift::GetDuration()
{
	return endHour - startHour;
}

const Driver& Shift::GetDriver()
{
	return *driver;
}

const Bus& Shift::GetBus()
{
	return *bus;
}

const Line& Shift::GetLine()
{
	return *line;
}