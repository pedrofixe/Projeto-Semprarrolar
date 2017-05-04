#include "line.h"


// bool line::LoadLines(string filename, vector<line> &LineSet) {

// 	ifstream lines_file(filename);

// 	if (lines_file.fail()) 
// 	{
// 		lines_file.close();
// 		return false;
// 	}

// 	// Load lines
// 	string tempstr;
// 	while (getline(lines_file, tempstr)) {
// 		// Take line from file to tempstr
// 		tempstr += ";";
// 		istringstream line_stream(tempstr);
// 		line templine;
// 		string newtempstr;
// 		vector<bus_stop> stop_vector;
// 		bus_stop tempstop;
// 		vector<int> time_vector;


// 		// Store line ID
// 		getline(line_stream, tempstr, ';');
// 		utilities::trimString(tempstr);
// 		templine.ID = stoi(tempstr);

// 		// Store line freq
// 		getline(line_stream, tempstr, ';');
// 		utilities::trimString(tempstr);
// 		templine.freq = stoi(tempstr);

// 		// Store line's stops
// 		getline(line_stream, tempstr, ';');
// 		utilities::trimString(tempstr);
// 		tempstr += ',';
// 		istringstream bus_stop_stream(tempstr);

// 		while (getline(bus_stop_stream, tempstr, ','))
// 		{
// 			utilities::trimString(tempstr);
// 			tempstop.name = tempstr;
// 			stop_vector.push_back(tempstop);

// 		}
// 		templine.stops = stop_vector;

// 		// Store line's time between stops
// 		getline(line_stream, tempstr, ';');
// 		utilities::trimString(tempstr);
// 		tempstr += ',';
// 		istringstream time_stream(tempstr);

// 		while (getline(time_stream, tempstr, ','))
// 		{
// 			utilities::trimString(tempstr);
// 			time_vector.push_back(stoi(tempstr));

// 		}
// 		templine.timebetweenstops = time_vector;

// 		LineSet.push_back(templine); // Add templine to lineSet
// 	}
// 	lines_file.close();
// 	return true;
// }

// void line::SaveLines(string filename, vector<line> &LineSet) {
// 	ofstream lines_file(filename);

// 	for (const line &templine : LineSet) {
// 		lines_file << templine.ID << " ; " << templine.freq << " ; ";
// 		for (int i = 0; i < templine.stops.size(); ++i)
// 		{
// 			lines_file << templine.stops[i].name;
// 			if (i < templine.stops.size() - 1)
// 				lines_file << ", ";
// 		}

// 		lines_file << " ; ";

// 		for (int i = 0; i < templine.timebetweenstops.size(); ++i)
// 		{
// 			lines_file << templine.timebetweenstops[i];
// 			if (i < templine.timebetweenstops.size() - 1)
// 				lines_file << ", ";
// 		}

// 		// Only write a newline if it's not the last line
// 		if (templine.ID != LineSet.back().ID)
// 			lines_file << "\n";
// 	}

// 	lines_file.close();
// }


void Line::EditID(const string& input)
{
	this.ID = input;
}

void Line::EditFreq(const int& input)
{
	this.freq = input;
}

void Line::EditBus_Stops(const vector<Bus_Stop>& input)
{
	this.bus_stops = input;
}

void SetTimeBetweenStops(const vector<int>& input)
{
	this.timebetweenstops = input;
}