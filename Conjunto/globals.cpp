#include "globals.h"

// -- LINES CLASS -- \\

void LinesClass::AddBusLine(const Line& inputLine)
{
	Lines.push_back(inputLine);
}

bool LinesClass::RemoveBusLine(const Line& inputLine)
{
	for (int i = 0; i < lines.size(); ++i)
	{
		if (Lines[i].GetID() == inputLine.GetID())
		{
			Lines.erase(lines.begin() + i);
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
			Bus_Stop tempstop(tempstr);
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

vector<Line>& LinesClass::GetLines()
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

bool DriversClass::LoadFromFile(const string& fileName)
{
	ifstream hFile_Drivers(fileName);
	if (hFile_Drivers.fail()) {
		hFile_Drivers.close();
		return false;
	}

	// READ FILE LINES
	string motorista_string;
	while (getline(hFile_Drivers, motorista_string)) {
		// PROCESS LINE
		istringstream ss_line(motorista_string);
		Driver newDriver;
		string Temp;
		// READ DRIVER ID
		getline(ss_line, Temp, ';');
		utilities::trimString(Temp);
		newDriver.SetID(Temp);
		// READ DRIVER NAME
		getline(ss_line, Temp, ';');
		utilities::trimString(Temp);
		newDriver.SetName(Temp);
		// READ MAX NR OF HOURS PER SHIFT 
		getline(ss_line, Temp, ';');
		utilities::trimString(Temp);
		newDriver.SetMaxHoursShift( stoi(Temp) );
		// READ MAX WEEKLY LOAD (WORKING HOURS)
		getline(ss_line, Temp, ';');
		utilities::trimString(Temp);
		newDriver.SetMaxHoursWeek( stoi(Temp) );
		// READ MIN NUMBER OF REST HOURS BETWEEN SHIFTS
		getline(ss_line, Temp, '\n');
		utilities::trimString(Temp);
		newDriver.SetMinHoursRest( stoi(Temp) );

		drivers.push_back(newDriver); // add to intern vector
	}
	hFile_Drivers.close();
	return true;
}

void DriversClass::SaveToFile(const string& fileName) const
{
	ofstream hFile_Drivers(fileName);
	for (const Driver &driver : drivers) {
		hFile_Drivers << driver.GetID() << " ; " << driver.GetName() << " ; " << driver.GetMaxHoursShift() << " ; " << driver.GetMaxHoursWeek << " ; " << driver.GetMinHoursRest() << endl;
	}
	hFile_Drivers.close();
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

Driver * DriversClass::FindDriver(const string & DriverID)
{
	for (auto& driver : drivers) {
		if (driver.GetID() == DriverID) {
			return &driver;
		}
	}
	return nullptr;
}

const vector<Driver>& DriversClass::GetDrivers() const
{
	return drivers;
}


// -- BUS STOPS CLASS -- \\

void Bus_StopsClass::AddLineToBusStop(Line * ptr_Line, const string & arg_Bus_Stop_Name)
{
	for (auto& Bus_Stop : vecBusStops) {
		if (Bus_Stop.GetName() == arg_Bus_Stop_Name) {
			Bus_Stop.AddLine(ptr_Line);
			return;
		}
	}
	// Else.. Create new bus stop
	Bus_Stop newBusStop(arg_Bus_Stop_Name);
	newBusStop.AddLine(ptr_Line);
	vecBusStops.push_back(newBusStop);
}
//
//void Bus_StopsClass::RemoveLineFromBusStop(Line * ptr_Line, const string & arg_Bus_Stop_Name)
//{
//	Bus_Stop* ptr_BusStop = FindBus_StopByName(arg_Bus_Stop_Name);
//	if (ptr_BusStop->GetLinesCount() > 1) {
//		ptr_BusStop->RemoveLineFromStop(ptr_Line);
//	}
//	else { // delete bus stop if no bus stops there
//		RemoveBusStop(arg_Bus_Stop_Name);
//	}
//}
//
//void Bus_StopsClass::RemoveLineFromALLBus_Stops(Line * ptr_Line)
//{
//	for (auto& bus_stop : vecBusStops) {
//		bus_stop.RemoveLineFromStop(ptr_Line); // will only remove the line if it is present on that bus stop
//	}
//}

Bus_Stop * Bus_StopsClass::FindBus_StopByName(const string & arg_Bus_Stop_Name)
{
	for (auto& bus_stop : vecBusStops) {
		if (bus_stop.GetName() == arg_Bus_Stop_Name) {
			return &bus_stop;
		}
	}
	return nullptr;
}

void Bus_StopsClass::PrintAllBus_Stops_Names() const
{
	bool firstIteration = true;
	for (auto& bus_stop : vecBusStops) {
		if (firstIteration) {
			(firstIteration = false);
		}
		else (cout << ",");
		cout << " " << bus_stop.GetName();
	}
}

void Bus_StopsClass::RebuildBus_Stops(vector<Line>& vecLines)
{
	vecBusStops.clear();
	for (Line& linha : vecLines) {
		for (const Bus_Stop& bus_stop : linha.GetBus_Stops()) {
			AddLineToBusStop(&linha, bus_stop.GetName());
		}
	}
}

void Bus_StopsClass::RemoveBusStop(const string & arg_Bus_Stop_Name)
{
	for (auto iterator = vecBusStops.cbegin(); iterator != vecBusStops.cend(); iterator++) {
		if (iterator->GetName() == arg_Bus_Stop_Name) { // found
			vecBusStops.erase(iterator);
			return;
		}
	}
}

// -- BUSES CLASS -- \\

bool Buses_Class::LoadFromFile(const string& filename)
{
	ifstream buses_file(filename);

	if (buses_file.fail())
	{
		buses_file.close();
		return false;
	}

	// Load lines
	string tempstr;
	while (getline(buses_file, tempstr)) {
		utilities::trimString(tempstr); 
		mapBusesIDs.insert(make_pair(tempstr, set<Shift>()));
	}
	buses_file.close();
	return true;
}

void Buses_Class::SaveToFile(const string& filename) const
{
	ofstream buses_file(filename);
	for (const auto& bus_pair : mapBusesIDs) {
		buses_file << bus_pair.first << endl;
	}
	buses_file.close();
}

void Buses_Class::PrintBuses() const
{
	cout << "  ";
	for (const auto& bus_pair : mapBusesIDs) {
		cout << bus_pair.first << endl;
	}
}

bool Buses_Class::InsertBus(const string & BusID)
{
	if (mapBusesIDs.insert(make_pair(BusID, set<Shift>())).second) { // element was inserted with success
		return true;
	}
	return false;
}

bool Buses_Class::RemoveBus(const string & BusID)
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		mapBusesIDs.erase(iterator);
		return true;
	}
	return false;
}

const set<Shift>& Buses_Class::GetShifts(const string & BusID) const
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		return iterator->second;
	}
	return set<Shift>(); // return empty set if the busID passed as argument isnt associated with a bus

}

bool Buses_Class::BusExists(const string & BusID)
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		return true;
	}
	return false;
}

bool Buses_Class::CanAddShift(const string & BusID, const Shift& argShift) const
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		for (const auto& bus_Shift : iterator->second) {
			if (bus_Shift.GetDay() == argShift.GetDay() && ( argShift.GetStartHour() >= bus_Shift.GetStartHour() && argShift.GetStartHour() < bus_Shift.GetEndHour()) ) {
				return false;
			}
		}
	}
	return true;
}

void Buses_Class::AddShift(const string & BusID, const Shift &argShift)
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		iterator->second.insert(argShift);
	}
}

void Buses_Class::RemoveShift(const string & BusID, const Shift& argShift)
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		auto iteratorToShift = iterator->second.find(argShift);
		if (iteratorToShift != iterator->second.end()) {
			iterator->second.erase(iteratorToShift);
		}
	}
}

// -- SHIFTS_INTERFACE CLASS -- \\

bool Shifts_InterfaceClass::LoadFromFile(const string& argFilename)
{
	ifstream shifts_file(argFilename);
	filename = argFilename;

	if (shifts_file.fail())
	{
		shifts_file.close();
		return false;
	}

	// Load lines
	string tempstr;
	while (getline(shifts_file, tempstr)) {
		utilities::trimString(tempstr); 
		istringstream sstreamFileLine(tempstr);
		unsigned int day, startHour, endHour;
		string driverID, busID, lineID;
		getline(sstreamFileLine, tempstr, ',');
		day = stoi(tempstr);
		getline(sstreamFileLine, tempstr, ',');
		startHour = stoi(tempstr);
		getline(sstreamFileLine, tempstr, ',');
		endHour = stoi(tempstr);
		//
		getline(sstreamFileLine, driverID, ',');
		getline(sstreamFileLine, busID, ',');
		getline(sstreamFileLine, lineID, ',');
		Shift newShift(day, startHour, endHour, driverID, busID, lineID);
		InsertShift(newShift);
		// but we will also have to add the shift to the corresponding driver and bus..

		
	}
	shifts_file.close();
	return true;

}

bool Shifts_InterfaceClass::LoadFromFile(const string &)
{
	return false;
}

void Shifts_InterfaceClass::InsertShift(const Shift &argShift)
{
	setShifts.insert(argShift);
}

void Shifts_InterfaceClass::RemoveShift(const Shift& argShift)
{
	auto iterator = setShifts.find(argShift);
	if (iterator != setShifts.end()) {
		setShifts.erase(iterator);
	}
}

const set<Shift>& Shifts_InterfaceClass::GetShifts() const
{
	return setShifts;
}

void Shifts_InterfaceClass::ListShifts() const
{
	cout << setw(2) << "" << setw(12) << left << "Day" << setw(15) << "Start Hour" << setw(15) << "End Hour" << setw(10) << "Line" << setw(30) << "Driver" << setw(10) << "Bus" << endl;
	for (const Shift &shift : setShifts) {
		string dayName = utilities::DayNumberToString(shift.GetDay());
		cout << setw(2) << "" << setw(12) << left << dayName << setw(15) << shift.GetStartHour() + ":00" << setw(15) << shift.GetEndHour() + ":00" << setw(10) << shift.GetLine().GetID() << setw(30) << "[" + shift.GetDriver().GetID() + "]" +shift.GetDriver().GetName() << setw(10) << shift.GetBusID() << endl;
	}
	cout << right;
}
