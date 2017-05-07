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

unsigned int Shift::GetDay() const
{
	return day;
}

unsigned int Shift::GetStartHour() const
{
	return startHour;
}


unsigned int Shift::GetEndHour() const
{
	return endHour;
}

unsigned int Shift::GetDuration() const
{
	return endHour - startHour;
}

const Driver& Shift::GetDriver() const
{
	return *driver;
}

const Bus& Shift::GetBus() const
{
	return *bus;
}

const Line& Shift::GetLine() const
{
	return *line;
}


bool operator<(const Shift &left, const Shift &right)
{
	if (left.GetDay() < right.GetDay()) {
		return true;
	}
	else if (left.GetStartHour() < right.GetStartHour()) {
		return true;
	}
	return false;
}