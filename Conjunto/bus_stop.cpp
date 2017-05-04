#include "bus_stop.h"

void Bus_Stop::SetName(const string& input)
{
	this->name = input;
}

string Bus_Stop::GetName()
{
	return this->name;
}