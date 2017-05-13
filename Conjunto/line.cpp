#include "line.h"

void Line::SetID(const string& input)
{
	ID = input;
}

void Line::SetFreq(const unsigned int& input)
{
	freq = input;
}

void Line::SetBus_Stops(const vector<Bus_Stop>& input)
{
	bus_stops = input;
}

void Line::SetTimeBetweenStops(const vector<unsigned int>& input)
{
	timeBetweenStops = input;
}


string Line::GetID() const
{
	return ID;
}

unsigned int Line::GetFreq() const
{
	return freq;
}

vector<Bus_Stop> Line::GetBus_Stops() const
{
	return bus_stops;
}

vector<unsigned int> Line::GetTimeBetweenStops() const
{
	return timeBetweenStops;
}

void Line::ShowSchedule() const
{

}