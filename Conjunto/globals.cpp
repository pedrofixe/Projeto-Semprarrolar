#include "globals.h"

// -- LINES CLASS -- \\

void LinesClass::AddBusLine(const Line& inputLine)
{
	lines.push_back(inputLine);
}

bool LinesClass::RemoveBusLine(const Line& inputLine)
{
	for (int i = 0; i < lines.size(); ++i)
	{
		if (Lines[i].GetID() == inputLine.GetID())
		{
			lines.erase(lines.begin() + i);
			return true;
		}
	}

	return false;
}

bool LinesClass::RemoveBusLineByID(const string& argIdentifier)
{
	for (auto iterator = lines.cbegin(); iterator != lines.cend(); iterator++) {
		if (iterator->GetID == argIdentifier) { // found
			lines.erase(iterator);
			return true;
		}
	}

	return false;
}

bool LinesClass::LoadFromFile(const string& filename)
{
	ifstream lines_file(filename);

	if (lines_file.fail()) 
	{
		lines_file.close();
		return false;
	}

	// Load lines
	string tempstr;
	while (getline(lines_file, tempstr)) {
		// Take line from file to tempstr
		tempstr += ";";
		istringstream line_stream(tempstr);
		Line templine;
		string newtempstr;
		vector<Bus_Stop> stop_vector;
		Bus_Stop tempstop;
		vector<unsigned int> time_vector;


		// Store line ID
		getline(line_stream, tempstr, ';');
		utilities::trimString(tempstr);
		templine.SetID(tempstr);

		// Store line freq
		getline(line_stream, tempstr, ';');
		utilities::trimString(tempstr);
		templine.SetFreq(stoi(tempstr));

		// Store line's stops
		getline(line_stream, tempstr, ';');
		utilities::trimString(tempstr);
		tempstr += ',';
		istringstream Bus_Stop_stream(tempstr);

		while (getline(Bus_Stop_stream, tempstr, ','))
		{
			utilities::trimString(tempstr);
			tempstop.SetName(tempstr);
			stop_vector.push_back(tempstop);

		}
		templine.SetBus_Stops(stop_vector);

		// Store line's time between stops
		getline(line_stream, tempstr, ';');
		utilities::trimString(tempstr);
		tempstr += ',';
		istringstream time_stream(tempstr);

		while (getline(time_stream, tempstr, ','))
		{
			utilities::trimString(tempstr);
			time_vector.push_back(stoi(tempstr));

		}
		templine.SetTimeBetweenStops(time_vector);

		lines.push_back(templine); // Add templine to global line vector
	}
	lines_file.close();
	return true;
}


void LinesClass::SaveToFile(const string& filename) const {
	ofstream lines_file(filename);

	vector<Bus_Stop> stop_vector;
	vector<unsigned int> timebetweenstops;

	for (const Line &templine : lines) {
		lines_file <<  templine.GetID() << " ; " << templine.GetFreq() << " ; ";

		stop_vector = templine.GetBus_Stops();
		for (int i = 0; i < stop_vector.size(); ++i)
		{
			lines_file << stop_vector[i].GetName();
			if (i < stop_vector.size() - 1)
				lines_file << ", ";
		}

		lines_file << " ; ";

		timebetweenstops = templine.GetTimeBetweenStops();
		for (int i = 0; i < timebetweenstops.size(); ++i)
		{
			lines_file << timebetweenstops[i];
			if (i < timebetweenstops.size() - 1)
				lines_file << ", ";
		}

		// Only write a newline if it's not the last line
		if (templine.GetID() != lines.back().GetID())
			lines_file << "\n";
	}

	lines_file.close();
}

bool LinesClass::LineExists(const string & argIdentifier) const
{
	for (const auto& line : lines) {
		if (line.GetID() == argIdentifier)	return true;
	}
	return false;
}

void LinesClass::PrintLinesNames() const
{
	bool firstIteration = true;
	for (const Line &line : lines) {
		if (firstIteration) {
			(firstIteration = false);
		}
		else (std::cout << ",");
		std::cout << " " << line.GetID();
	}
}

const vector<Line>& LinesClass::GetLines() const
{
	return lines;
}

// -- DRIVERS CLASS -- \\

bool DriversClass::AddDriver(const Driver& argDriver)
{
	drivers.push_back(argDriver);
}

bool DriversClass::RemoveDriver(const Driver& argDriver)
{
	for (auto iterator = drivers.cbegin(); iterator != drivers.cend(); iterator++) {
		if (iterator->GetID() == argDriver.GetID) { // found
			drivers.erase(iterator);
			return true;
		}
	}

	return false;
}

bool DriversClass::RemoveDriverByID(const string& argDriverID)
{
	for (auto iterator = drivers.cbegin(); iterator != drivers.cend(); iterator++) {
		if (iterator->GetID() == argDriverID) { // found
			drivers.erase(iterator);
			return true;
		}
	}

	return false;
}

bool DriversClass::LoadFromFile(const string &)
{
	return false;
}

void DriversClass::SaveToFile() const
{

}

void DriversClass::ListDrivers() const
{
	cout << setw(2) << "" << setw(15) << left << "Identifier" << setw(30) << "Name" << setw(25) << "Hours per Shift" << setw(25) << "Weekly Load" << setw(20) << "Rest Hours" << endl;
	for (const Driver &driver : drivers) {
		cout << setw(2) << "" << setw(15) << driver.GetID() << setw(30) << driver.GetName() << setw(25) << driver.GetMaxHoursShift() << setw(25) << driver.GetMaxHoursWeek() << setw(20) << driver.GetMinHoursRest() << endl;
	}
	cout << right;
}

bool DriversClass::DriverExists(const string& argIdentifier) const
{
	for (const auto& driver : drivers) {
		if (driver.GetID() == argIdentifier)	return true;
	}
	return false;
}