#ifndef __SHIFT_INCLUDED__
#define __SHIFT_INCLUDED__

#include "driver.h"

class Shift {
	public:
		unsigned int GetStartHour();
		unsigned int GetEndHour();
		unsigned int GetDuration();
		const Driver GetDriver();
		const Bus GetBus();
		const Line GetLine();
		// Construtor:
		Shift(unsigned int day, unsigned int startHour, unsigned int endHour, const Driver* , const Bus*, const Line*);
	private:
		unsigned int day;
		unsigned int startHour;
		unsigned int endHour;
		const Driver * const Driver;
		const Bus * const Bus;
		const Line * const Line;

};


#endif