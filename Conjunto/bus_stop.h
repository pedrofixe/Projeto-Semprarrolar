#ifndef __BUS_STOP_INCLUDED__
#define __BUS_STOP_INCLUDED__

#include <string>

using namespace std;

class Bus_Stop {

public:
	void ShowSchedule() const;
	void SetName(const string&)

private:
	std::string name;

};

#endif