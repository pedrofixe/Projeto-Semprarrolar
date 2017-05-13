#ifndef __BUS_STOP_INCLUDED__
#define __BUS_STOP_INCLUDED__

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "line.h"

using namespace std;

class Bus_Stop {

	public:

		const string& GetName() const;
		unsigned int GetLinesCount() const;
		const vector< Line* >& GetLines() const;
		void RemoveLineFromStop(const Line*);
		void AddLine(Line*);

		void ShowSchedule() const; // falta implementar

		// Constructor:
		Bus_Stop(const string& argBus_StopName) : name(argBus_StopName) { };

	private:
		const string name;
		vector<Line*> linesAtStop;

};

#endif