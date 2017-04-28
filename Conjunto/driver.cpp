#include "driver.h"

using namespace std;

bool driver::LoadDrivers(string filename, vector<driver> &DriverSet) {
	ifstream drivers_file(filename);
	if (drivers_file.fail()) {
		drivers_file.close();
		return false;
	}

	// Load drivers
	string tempstr;
	while (getline(drivers_file, tempstr)) {
		// Take line from file to tempstr
		tempstr += ";";
		istringstream driver_stream(tempstr);
		driver tempdriver;
		string newtempstr;
		// Store driver ID
		getline(driver_stream, newtempstr, ';');
		utilities::trimstring(newtempstr);
		tempdriver.ID = stoi(newtempstr);
		// Store driver name
		getline(driver_stream, newtempstr, ';');
		utilities::trimstring(newtempstr);
		tempdriver.name = newtempstr;
		// Store driver's maximum hours per shift
		getline(driver_stream, newtempstr, ';');
		utilities::trimstring(newtempstr);
		tempdriver.MaxHoursShift = stoi(newtempstr);
		// Store driver's maximum hours per week
		getline(driver_stream, newtempstr, ';');
		utilities::trimstring(newtempstr);
		tempdriver.MaxHoursWeek = stoi(newtempstr);
		// Store driver's minimum hours between shifts
		getline(driver_stream, newtempstr, ';');
		utilities::trimstring(newtempstr);
		tempdriver.MinHoursBetwenShifts = stoi(newtempstr);

		DriverSet.push_back(tempdriver); // Add tempdriver to DriverSet
	}
	drivers_file.close();
	return true;
}

void driver::SaveDrivers(string filename, vector<driver> &DriverSet) {
	ofstream drivers_file(filename);

	for (const driver &tempdriver : DriverSet) {
		drivers_file << tempdriver.ID << " ; " << tempdriver.name << " ; " << tempdriver.MaxHoursShift << " ; " << tempdriver.MaxHoursWeek << " ; " << tempdriver.MinHoursBetwenShifts << endl;
	}
	drivers_file.close();
}