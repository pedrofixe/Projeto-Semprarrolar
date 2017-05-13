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
		const Driver& GetDriver() const;
		const string& GetBusID() const;
		const Line& GetLine() const;

		void SetDay(const unsigned int&);
		void SetStartHour(const unsigned int&);
		void SetEndHour(const unsigned int&);
		void SetDuration(const unsigned int&);
		void SetDriver(const Driver&);
		void 

		// Construtor:
		Shift(unsigned int day, unsigned int startHour, unsigned int endHour, const Driver*, const string& BusID, const Line*);
		// "less than" operator overload. Used to order the intern set container of Shifts_Interface
		// Set order is defined by cronological order of the shifts.
		friend bool operator<(const Shift&, const Shift&);
	private:
		unsigned int day;
		unsigned int startHour;
		unsigned int endHour;
		const Driver* driver;
		string BusID;
		const Line* line;
};


#endif