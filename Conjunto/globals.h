#ifndef __GLOBALS_INCLUDED__
#define __GLOBALS_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "line.h"
#include "driver.h"
#include "bus_stop.h"

using namespace std;

class LinesClass {
	public:
		void AddBusLine(const Line&);
		bool RemoveBusLine(const Line&);
		bool RemoveBusLineByID(const string& Identifier);

		bool LoadFromFile(const string&);
		void SaveToFile(const string&) const;

		void PrintLinesNames() const;
		bool LineExists(const string& lineIdentifier) const;
		const vector<Line>& GetLines() const; // n sei se vai ser usado
	private:
		vector<Line> lines;

};

class DriversClass {
	public:
		bool AddDriver(const Driver&);
		bool RemoveDriver(const Driver&);
		bool RemoveDriverByID(const string&);

		bool LoadFromFile(const string&);
		void SaveToFile() const;

		void ListDrivers() const;	
		bool DriverExists(const string&) const;
		const vector<Driver>& GetDrivers() const; // n sei se vai ser usado
	private:
		vector<Driver> drivers;
};

class Bus_StopsClass {
	public:

	private:
		unordered_map<Bus_Stop, vector<Line*> > hashmap;
};

static LinesClass	 Lines;
static DriversClass	 Drivers;
static Bus_StopsClass Bus_Stops;

#endif