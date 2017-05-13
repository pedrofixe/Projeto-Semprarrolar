#include "shift.h"

Shift::Shift(unsigned int argDay, unsigned int argStartHour, unsigned int argEndHour, const string & argDriverID, const string & argBusID, const string & argLineID)
{
	day = argDay;
	startHour = argStartHour;
	endHour = argEndHour;
	driverID = argDriverID;
	busID = argBusID;
	lineID = argLineID;
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

const string& Shift::GetDriverID() const
{
	return driverID;
}

const string& Shift::GetBusID() const
{
	return busID;
}

const string& Shift::GetLineID() const
{
	return lineID;
}


bool operator<(const Shift &left, const Shift &right)
{
	if (left.GetDay() < right.GetDay()) {
		return true;
	}
	else if (left.GetStartHour() < right.GetStartHour()) {
		return true;
	}
	else if (left.GetLineID() < right.GetLineID()) {
		return true;
	}
	else if (left.GetBusID() < right.GetBusID()) {
		return true;
	}
	return false;
}