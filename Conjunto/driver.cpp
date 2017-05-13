#include "driver.h"

void Driver::SetID(const string& input)
{
	this->ID = input;
}

void Driver::SetName(const string& input)
{
	this->name = input;
}

void Driver::SetMaxHoursShift(const unsigned int& input)
{
	this->maxhoursshift = input;
}

void Driver::SetMaxHoursWeek(const unsigned int& input)
{
	this->maxhoursweek = input;
}

void Driver::SetMinHoursRest(const unsigned int& input)
{
	this->minhoursrest = input;
}

string Driver::GetID() const
{
	return ID;
}

string Driver::GetName() const
{
	return name;
}

unsigned int Driver::GetMaxHoursShift() const
{
	return maxhoursshift;
}

unsigned int Driver::GetMaxHoursWeek() const
{
	return maxhoursweek;
}

unsigned int Driver::GetMinHoursRest() const
{
	return minhoursrest;
}

int Driver::CanAddShift(const Shift& argShift) const
{
	// First we'll have to check if the driver is free at the specified time. Since we're looping the set we might as well count the work hours of the driver.
	// We'll also have to check if the resting hours are respected.
	unsigned int workHours = 0;
	for (const auto& shift : driverShifts) {
		if (shift.GetDay() == argShift.GetDay() && shift.GetStartHour() >= argShift.GetStartHour() && argShift.GetStartHour() < shift.GetEndHour()) {
			return NOT_AVAILABLE;
		}
		if (shift.GetDay() == argShift.GetDay() && (shift.GetEndHour() + GetMinHoursRest()) >= argShift.GetStartHour()) {
			return MUST_RESPECT_REST_TIME;
		}
		workHours += shift.GetDuration();
	}
	// if we reached this step then it seems the driver is available to work in the hour. But did we respect the weekly limit?
	if (workHours + argShift.GetDuration() > GetMaxHoursWeek()) {
		return WEEKLY_LIMIT_REACHED;
	}
	// but... is the shift too long?
	if (argShift.GetDuration() > GetMaxHoursShift()) {
		return SHIFT_TOO_LONG;
	}
	// it seems that the driver is able to work this shift.
	return AVAILABLE;
}

void Driver::AddShift(const Shift& argShift)
{
	driverShifts.insert(argShift);
}

void Driver::RemoveShift(const Shift& argShift)
{
	auto iterator = driverShifts.find(argShift);
	if (iterator != driverShifts.end()) {
		driverShifts.erase(iterator);
	}
}

const set<Shift>& Driver::GetDriverShifts() const
{
	return driverShifts;
}

