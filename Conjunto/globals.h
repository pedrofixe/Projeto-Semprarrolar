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
		void AddBusLine(Line&);
		void RemoveBusLine(Line&);
		bool LoadFromFile(const string&);
		void SaveToFile() const;
		void PrintLinesNames() const;
		bool LineExists() const;
		const vector<Line>& GetLines() const; // n sei se vai ser usado
	private:
		vector<Line> Lines;

};

class DriversClass {
	public:
		void AddDriver(Driver&);
		void RemoveDriver(Driver&);
		bool LoadFromFile(const string&);
		void SaveToFile() const;
		void ListDrivers() const;	
		bool DriverExists(string&) const;
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