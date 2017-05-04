#include "globals.h"


bool LinesClass::LoadFromFile(const string& filename)
{
	ifstream lines_file(filename);

	if (lines_file.fail()) 
	{
		lines_file.close();
		return false;
	}

	// Load lines
	string tempstr;
	while (getline(lines_file, tempstr)) {
		// Take line from file to tempstr
		tempstr += ";";
		istringstream line_stream(tempstr);
		Line templine;
		string newtempstr;
		vector<Bus_Stop> stop_vector;
		Bus_Stop tempstop;
		vector<unsigned int> time_vector;


		// Store line ID
		getline(line_stream, tempstr, ';');
		utilities::trimString(tempstr);
		templine.SetID(tempstr);

		// Store line freq
		getline(line_stream, tempstr, ';');
		utilities::trimString(tempstr);
		templine.SetFreq(stoi(tempstr));

		// Store line's stops
		getline(line_stream, tempstr, ';');
		utilities::trimString(tempstr);
		tempstr += ',';
		istringstream Bus_Stop_stream(tempstr);

		while (getline(Bus_Stop_stream, tempstr, ','))
		{
			utilities::trimString(tempstr);
			tempstop.SetName(tempstr);
			stop_vector.push_back(tempstop);

		}
		templine.SetBus_Stops(stop_vector);

		// Store line's time between stops
		getline(line_stream, tempstr, ';');
		utilities::trimString(tempstr);
		tempstr += ',';
		istringstream time_stream(tempstr);

		while (getline(time_stream, tempstr, ','))
		{
			utilities::trimString(tempstr);
			time_vector.push_back(stoi(tempstr));

		}
		templine.SetTimeBetweenStops(time_vector);

		Lines.push_back(templine); // Add templine to global line vector
	}
	lines_file.close();
	return true;
}


