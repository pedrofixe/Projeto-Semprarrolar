#ifndef __GLOBALS_INCLUDED__
#define __GLOBALS_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <set>
#include "line.h"
#include "driver.h"
#include "bus_stop.h"
#include "shift.h"

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
		void SaveToFile(const string&) const;

		void ListDrivers() const;	
		bool DriverExists(const string&) const;
		const vector<Driver>& GetDrivers() const; // n sei se vai ser usado
	private:
		vector<Driver> drivers;
};

class Bus_StopsClass {
	public:
		void AddLineToBusStop(Line* ptr_Line, const string& Bus_Stop_Name);
		void RemoveLineFromBusStop(Line* ptr_Line, const string& Bus_Stop_Name);
		void RemoveLineFromALLBus_Stops(Line* ptr_Line);
		Bus_Stop* FindBus_StopByName(const string&);
		void PrintAllBus_Stops_Names() const;
		void RemoveBusStop(const string&);
	private:
		vector<Bus_Stop> vecBusStops;
};

class Shifts_InterfaceClass {
public:
	void InsertShift(const Shift&);
	const set<Shift>& GetShifts() const;
	void ListShifts() const;
private:
	set<Shift> setShifts;
	string DayNumberToString(const unsigned int&) const;
};

static LinesClass	 Lines;
static DriversClass	 Drivers;
static Bus_StopsClass	Bus_Stops;
static Shifts_InterfaceClass Shifts_Interface;

#endif