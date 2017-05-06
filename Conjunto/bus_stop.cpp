#include "bus_stop.h"

void Bus_Stop::SetName(const string& input)
{
	name = input;
}

string Bus_Stop::GetName()
{
	return name;
}