#ifndef __LINE_INCLUDED__
#define __LINE_INCLUDED__

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "bus_stop.h"
#include "utilities.h"

using namespace std;

class line{

public:
	unsigned int ID;
	unsigned int freq;
	vector<bus_stop> stops;
	vector<int> timebetweenstops;

	static bool LoadLines(string, vector<line>&);
	static void SaveLines(string, vector<line>&);

};


#endif