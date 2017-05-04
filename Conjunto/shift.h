#ifndef __SHIFT_INCLUDED__
#define __SHIFT_INCLUDED__

#include "driver.h"
#include "bus.h"
#include "line.h"

class Shift {
	public:
		unsigned int GetStartHour();
		unsigned int GetEndHour();
		unsigned int GetDuration();
		const Driver& GetDriver();
		const Bus& GetBus();
		const Line& GetLine();
		// Construtor:
		Shift(unsigned int day, unsigned int startHour, unsigned int endHour, const Driver*, const Bus*, const Line*);
	private:
		unsigned int day;
		unsigned int startHour;
		unsigned int endHour;
		const Driver* Driver;
		const Bus* Bus;
		const Line* Line;
};


#endif