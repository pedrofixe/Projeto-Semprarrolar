#include "globals.h"

void LinesClass::AddBusLine(const Line& inputLine)
{
	Lines.insert(inputLine);
}

bool LinesClass::RemoveBusLine(const Line& inputLine)
{
	for (int i = 0; i < Lines.size(); ++i)
	{
		if (Lines[i].GetID() == inputLine.GetID())
		{
			Lines.erase(Lines.begin() + i);
			return true;
		}
	}

	return false;
}

bool LinesClass::RemoveBusLine(const unsigned int& input)
{
	if (input < Lines.size())
	{
		Lines.erase(Lines.begin() + input);
		return true;
	}

	return false;
}

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


void LinesClass::SaveToFile(const string& filename) {
	ofstream lines_file(filename);

	vector<Bus_Stop> stop_vector;
	vector<unsigned int> timebetweenstops;

	for (const line &templine : Lines) {
		lines_file <<  templine.GetID() << " ; " << templine.GetFreq() << " ; ";

		stop_vector = templine.GetBus_Stops();
		for (int i = 0; i < stop_vector.size(); ++i)
		{
			lines_file << stop_vector[i].GetName();
			if (i < stop_vector.size() - 1)
				lines_file << ", ";
		}

		lines_file << " ; ";

		timebetweenstops = templine.GetTimeBetweenStops();
		for (int i = 0; i < timebetweenstops.size(); ++i)
		{
			lines_file << timebetweenstops[i];
			if (i < timebetweenstops.size() - 1)
				lines_file << ", ";
		}

		// Only write a newline if it's not the last line
		if (templine.GetID() != Lines.back().GetID())
			lines_file << "\n";
	}

	lines_file.close();
}

