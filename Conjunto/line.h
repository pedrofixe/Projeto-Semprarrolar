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
		void SetID(const string&);
		void SetFreq(const unsigned int&);
		void SetBus_Stops(const vector<Bus_Stop>&);
		void SetTimeBetweenStops(const vector<unsigned int>&);

	private:
		string ID;
		unsigned int freq;
		vector<Bus_Stop> bus_stops;
		vector<unsigned int> timebetweenstops;

};


#endif