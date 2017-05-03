#ifndef __GLOBALS_INCLUDED__
#define __GLOBALS_INCLUDED__

#include <vector>
#include "line.h"
#include "driver.h"

class LinesClass {
	public:
		void AddBusLine(Line&);
		void RemoveBusLine(Line&);
		void LoadFromFile();
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
		void LoadFromFile();
		void SaveToFile() const;
		void ListDrivers() const;	
		bool DriverExists(string&) const;
		const vector<Driver>& GetDrivers() const; // n sei se vai ser usado
	private:
		vector<Driver> Drivers;
};

class BusStopsClass {
	public:

	private:
		// implementar wrapper sobre hashmap
};

static LinesClass	 Lines;
static DriversClass	 Drivers;
static BusStopsClass BusStops;

#endif