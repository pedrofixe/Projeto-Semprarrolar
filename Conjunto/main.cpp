#include <iostream>
#include <string>
#include <vector>
#include "driver.h"
#include "bus_stop.h"
#include "line.h"
#include "ui_utilities.h"
#include "utilities.h"

using namespace std;

#define LINES_FILENAME "linhas"
#define DRIVERS_FILENAME "condutores"


int main()
{

	// vector<line> horta;

	// line::LoadLines(LINES_FILENAME, horta);

	// line temp;

	// temp.ID = 1234;
	// temp.freq = 69;

	// bus_stop tempstop;
	// tempstop.name = "Casa";
	// temp.stops.push_back(tempstop);

	// tempstop.name = "Faculdade";
	// temp.stops.push_back(tempstop);

	// tempstop.name = "Pingo Doce";
	// temp.stops.push_back(tempstop);

	// tempstop.name = "Casa";
	// temp.stops.push_back(tempstop);

	// temp.timebetweenstops = {4,2,0};

	// horta.insert(horta.end(), temp);

	// line::SaveLines(LINES_FILENAME, horta);

	vector<driver> horta;

	driver::LoadDrivers(DRIVERS_FILENAME, horta);

	driver temp;

	temp.ID = 69420;
	temp.name = "ze das coibes";
	temp.MaxHoursShift = 42;
	temp.MaxHoursWeek = 32;
	temp.MinHoursBetwenShifts = 5;

	horta.push_back(temp);

	driver::SaveDrivers(DRIVERS_FILENAME, horta);

	cout << "\n\n";
	return 0;
}