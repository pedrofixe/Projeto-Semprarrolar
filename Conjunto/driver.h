#ifndef __DRIVER_INCLUDED__
#define __DRIVER_INCLUDED__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class driver{

public:
	unsigned int ID;
	std::string name;
	unsigned int MaxHousShift;
	unsigned int MaxHoursWeek;
	unsigned int MinHoursBetwwenShifts;

	static void LoadDrivers(std::string);
	static bool SaveDrivers(std::string);

};


#endif