#ifndef __SHIFT_INCLUDED__
#define __SHIFT_INCLUDED__

#include "driver.h"
#include "bus.h"
#include "line.h"

class Shift {
	public:
		unsigned int GetDay() const;
		unsigned int GetStartHour() const;
		unsigned int GetEndHour() const;
		unsigned int GetDuration() const;
		const string& GetDriverID() const;
		const string& GetBusID() const;
		const string& GetLineID() const;
		// Construtor:
		Shift(unsigned int day, unsigned int startHour, unsigned int endHour, const string& DriverID, const string& BusID, const string& LineID);
		// "less than" operator overload. Used to order the intern set container of Shifts_Interface
		// Set order is defined by cronological order of the shifts.
		friend bool operator<(const Shift&, const Shift&);
	private:
		unsigned int day;
		unsigned int startHour;
		unsigned int endHour;
		string driverID;
		string busID;
		string lineID;
};


#endif