#ifndef __DRIVER_INCLUDED__
#define __DRIVER_INCLUDED__

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "utilities.h"

using namespace std;

class driver{

public:
	unsigned int ID;
	string name;
	unsigned int MaxHoursShift;
	unsigned int MaxHoursWeek;
	unsigned int MinHoursBetwenShifts;

	static bool LoadDrivers(string, vector<driver>&);
	static void SaveDrivers(string, vector<driver>&);

};


#endif