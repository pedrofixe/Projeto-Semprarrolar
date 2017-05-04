#ifndef __LINE_INCLUDED__
#define __LINE_INCLUDED__

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "bus_stop.h"
#include "utilities.h"

using namespace std;

class Line {
	public:
		void ShowSchedule() const;
		void EditID();
		void EditFreq();
		void EditBus_Stops();
		void EditTimeBetweenStops();
	private:
		string ID;
		unsigned int freq;
		vector<Bus_Stop> Bus_Stops;
		vector<unsigned int> timeBetweenStops;

};


#endif