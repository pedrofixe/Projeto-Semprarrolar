#include <iostream>
#include <string>
#include <vector>
//#include "ui_utilities.h"
#include "driver.h"
#include "utilities.h"

using namespace std;

#define LINES_FILENAME "linhas"
#define DRIVERS_FILENAME "condutores"



int main()
{

	vector<driver> horta;

	driver::LoadDrivers(DRIVERS_FILENAME, horta);

	driver temp;

	temp.ID = 1234;
	temp.name = "coisas 2e";
	temp.MaxHoursShift = 69;
	temp.MaxHoursWeek = 420;
	temp.MinHoursBetwenShifts = 5;
	horta.insert(horta.end(), temp);

	driver::SaveDrivers(DRIVERS_FILENAME, horta);

	cout << "\n\n";
	return 0;
}