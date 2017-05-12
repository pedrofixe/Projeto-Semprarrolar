#ifndef __GLOBALS_INCLUDED__
#define __GLOBALS_INCLUDED__

#include <vector>
#include <string>
#include "line.h"
#include "driver.h"
#include "bus_stop.h"

using namespace std;

class LinesClass {
	public:
		void AddLine(const Line&);
		bool RemoveLine(const Line&);
		bool RemoveLine(const unsigned int&);

		bool LoadFromFile(const string&);
		void SaveToFile(const string&);

		void PrintLinesNames() const;
		int LineSearch(const Line&) const;
		const vector<Line>& GetLines() const; // n sei se vai ser usado
	private:
		vector<Line> Lines;

};

class DriversClass {
	public:
		void AddDriver(const Driver&);
		bool RemoveDriver(const Driver&);
		bool RemoveDriver(const unsigned int&);

		bool LoadFromFile(const string&);
		void SaveToFile(const string&) const;

		void ListDrivers() const;	
		int DriverSearch(const &Driver) const;
		const vector<Driver>& GetDrivers() const; // n sei se vai ser usado
	private:
		vector<Driver> Drivers;
};

class Bus_StopsClass {
	public:

	private:
		// implementar wrapper sobre hashmap
};

static LinesClass	 Lines;
static DriversClass	 Drivers;
static Bus_StopsClass Bus_Stops;

#endif