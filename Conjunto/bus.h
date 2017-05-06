#ifndef __BUS_INCLUDED__
#define __BUS_INCLUDED__

#include "line.h"
#include "driver.h"
#include "shift.h"

class Bus {

	public:
		bool AddShift(const Shift&);
		const vector<Shift*>& GetShifts();
		Line GetLine();
		Driver GetDriver();
		unsigned int GetOrderNum();
	private:
		Line* line;
		unsigned int orderNum;
		Driver* driver;
		vector<Shift*> shifts;
};


#endif