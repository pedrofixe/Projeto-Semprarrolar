#ifndef __DRIVER_INCLUDED__
#define __DRIVER_INCLUDED__

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "utilities.h"

using namespace std;

class Driver{

public:
	void SetID(const string&);
	void SetName(const string&);
	void SetMaxHoursShift(const unsigned int&);
	void SetMaxHoursWeek(const unsigned int&);
	void SetMinHoursRest(const unsigned int&);

private:
	string ID;
	string name;
	unsigned int maxhoursshift;
	unsigned int maxhoursweek;
	unsigned int minhoursrest;


};


#endif