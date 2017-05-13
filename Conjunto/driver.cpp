#include "driver.h"

using namespace std;

// bool driver::LoadDrivers(string filename, vector<driver> &DriverSet) {
// 	ifstream drivers_file(filename);
// 	if (drivers_file.fail()) {
// 		drivers_file.close();
// 		return false;
// 	}

// 	// Load drivers
// 	string tempstr;
// 	while (getline(drivers_file, tempstr)) {
// 		// Take line from file to tempstr
// 		tempstr += ";";
// 		istringstream driver_stream(tempstr);
// 		driver tempdriver;
// 		string newtempstr;
// 		// Store driver ID
// 		getline(driver_stream, newtempstr, ';');
// 		utilities::trimString(newtempstr);
// 		tempdriver.ID = stoi(newtempstr);
// 		// Store driver name
// 		getline(driver_stream, newtempstr, ';');
// 		utilities::trimString(newtempstr);
// 		tempdriver.name = newtempstr;
// 		// Store driver's maximum hours per shift
// 		getline(driver_stream, newtempstr, ';');
// 		utilities::trimString(newtempstr);
// 		tempdriver.MaxHoursShift = stoi(newtempstr);
// 		// Store driver's maximum hours per week
// 		getline(driver_stream, newtempstr, ';');
// 		utilities::trimString(newtempstr);
// 		tempdriver.MaxHoursWeek = stoi(newtempstr);
// 		// Store driver's minimum hours between shifts
// 		getline(driver_stream, newtempstr, ';');
// 		utilities::trimString(newtempstr);
// 		tempdriver.MinHoursBetwenShifts = stoi(newtempstr);

// 		DriverSet.push_back(tempdriver); // Add tempdriver to DriverSet
// 	}
// 	drivers_file.close();
// 	return true;
// }

// void driver::SaveDrivers(string filename, vector<driver> &DriverSet) {
// 	ofstream drivers_file(filename);

// 	for (const driver &tempdriver : DriverSet) {
// 		drivers_file << tempdriver.ID << " ; " << tempdriver.name << " ; " << tempdriver.MaxHoursShift << " ; " << tempdriver.MaxHoursWeek << " ; " << tempdriver.MinHoursBetwenShifts;
		
// 		// Only write a newline if it's not the last driver
// 		if (tempdriver.ID != DriverSet.back().ID)
// 			drivers_file << "\n";
// 	}
// 	drivers_file.close();
// }



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

