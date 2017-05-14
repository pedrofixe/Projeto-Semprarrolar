#ifndef __GLOBALS_INCLUDED__
#define __GLOBALS_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include <sstream>
#include "driver.h"
#include "bus_stop.h"
#include "shift.h"
#include "utilities.h"
#include "line.h"

// The compiler was throwing a tantrum... Seems like the only way to please is to re-declare this classes here despite the corresponding
// header file being included just above. 
class Line;
class Bus_Stop;

#define SCHEDULE_START 8
#define SCHEDULE_END 22

using namespace std;

class LinesClass {
	public:
		void AddBusLine(const Line&);
		bool RemoveBusLine(const Line&);
		bool RemoveBusLineByID(const string&);

		bool LoadFromFile(const string&);
		void SaveToFile() const;

		void PrintLinesNames() const;
		bool LineExists(const string&) const;
		int SearchLine(const string&) const;
		Line* FindLine(const string&);
		vector<Line>& GetLines(); // cant be const because some methods from other classes only work with non const vectors
	private:
		string filename;
		vector<Line> lines;

};

class DriversClass {
	public:
		void AddDriver(const Driver&);
		bool RemoveDriver(const Driver&);
		bool RemoveDriverByID(const string&);

		bool CanAddShiftToDriver(const string& DriverID, const Shift&);
		void AddShiftToDriver(const string& DriverID, const Shift&);
		void RemoveShiftFromDriver(const string& DriverID, const Shift&);
		void RemoveAllShiftsWithLineID(const string& LineID);

		bool LoadFromFile(const string&);
		void SaveToFile() const;

		void ListDrivers() const;	
		bool DriverExists(const string&) const;

		Driver* FindDriver(const string& DriverID); // returns a pointer to the specified driver or nullptr if it doesnt exist

		const vector<Driver>& GetDrivers() const; // n sei se vai ser usado
	private:
		string filename;
		vector<Driver> drivers;
};

class Bus_StopsClass {
	// esta classe tem que ser seriamente repensada e re-escrita. OK FEITO
	public:
		void AddLineToBusStop(Line* ptr_Line, const string& Bus_Stop_Name);
		//void RemoveLineFromBusStop(Line* ptr_Line, const string& Bus_Stop_Name);
		//void RemoveLineFromALLBus_Stops(Line* ptr_Line);
		Bus_Stop* FindBus_StopByName(const string&); // returns a pointer to the specified bus stop or nullptr if it doesnt exist
		void PrintAllBus_Stops_Names() const;
		void RebuildBus_Stops(vector<Line>&);
		void RemoveBusStop(const string&);
	private:
		vector<Bus_Stop> vecBusStops;
};

class Buses_Class {
	public:
		bool LoadFromFile(const string&);
		void SaveToFile() const;
		void PrintBuses() const;
		bool InsertBus(const string& BusID); // These 2 methods will return false when the bus specified isnt valid
		bool RemoveBus(const string& BusID);
		const set<Shift>& GetShifts(const string& BusID) const;
		bool BusExists(const string& BusID);
		bool CanAddShift(const string& BusID, const Shift&) const;
		void AddShift(const string& BusID, const Shift&);
		void RemoveShift(const string& BusID, const Shift&);
		void RemoveShiftsByLineID(const string& LineID);
	private:
		string filename;
		map<string, set<Shift> > mapBusesIDs;
};

class Shifts_InterfaceClass {
	public:
		bool LoadFromFile(const string&);
		void SaveToFile() const;
		void InsertShift(const Shift&);
		const set<Shift>& GetShifts() const;
		void ListShifts() const;
		void RemoveShift(const Shift&);
		void RemoveLineShifts(const string& LineID);
		void RemoveBus_Shifts(const string& BusID);
	private:
		set<Shift> setShifts;
		string filename;
};

static LinesClass	 Lines;
static DriversClass	 Drivers;
static Bus_StopsClass	Bus_Stops;
static Buses_Class Buses;
static Shifts_InterfaceClass Shifts_Interface;

#endif