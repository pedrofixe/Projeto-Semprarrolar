#include "shift.h"

Shift::Shift(unsigned int argDay, unsigned int argStartHour, unsigned int argEndHour, const Driver* argDriver, const string& argBusID, const Line* argLine)
{
	day = argDay;
	startHour = argStartHour;
	endHour = argEndHour;
	driver = argDriver;
	BusID = argBusID;
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

const string& Shift::GetBusID() const
{
	return BusID;
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
	else if (left.GetLine().GetID() < right.GetLine().GetID()) {
		return true;
	}
	else if (left.GetDriver().GetID() < right.GetDriver().GetID()) {
		return true;
	}
	return false;
}