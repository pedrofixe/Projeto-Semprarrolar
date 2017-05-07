#include "bus_stop.h"

const string& Bus_Stop::GetName() const
{
	return name;
}

unsigned int Bus_Stop::GetLinesCount() const
{
	return linesAtStop.size();
}

void Bus_Stop::RemoveLineFromStop(const Line *ptr_Line )
{
	auto iterator = find(linesAtStop.cbegin(), linesAtStop.cend(), ptr_Line);
	if (iterator != linesAtStop.cend()) { // found
		linesAtStop.erase(iterator);
	}
	//if it doesn't exist do nothing
}

const vector<Line*>& Bus_Stop::GetLines() const
{
	return linesAtStop;
}

void Bus_Stop::AddLine(Line * ptr_Line)
{
	linesAtStop.push_back(ptr_Line);
}

void Bus_Stop::ShowSchedule() const
{

}