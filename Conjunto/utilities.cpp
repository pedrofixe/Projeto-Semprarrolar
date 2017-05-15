#include "utilities.h"

template <class T>

//Swap the value of two integers
void utilities::swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

// Remove spaces at the beginning and at the end of a string
void utilities::trimString(string &input)
{
	if (input.length() < 2) return;
	while (input[0] == ' ')
		input.erase(input.begin());

	while (input.back() == ' ')
		input.erase(input.end() - 1);
}

// Caluclates the length of a string
int utilities::intSize(int input)
{
	int res = 0;

	while (input)
	{
		res++;
		input /= 10;
	}

	return res;
}

bool utilities::isNumeric(string input)
{
	utilities::trimString(input);

	if (input.size() == 0)
		return false;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}

string utilities::DayNumberToString(const unsigned int& num)
{
	static string daysArray[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	return daysArray[num];
}

int utilities::DayStringToNumber(const string& dayName)
{
	if (dayName == "monday") {
		return 0;
	}
	else if (dayName == "tuesday") {
		return 1;
	}
	else if (dayName == "wednesday") {
		return 2;
	}
	else if (dayName == "thursday") {
		return 3;
	}
	else if (dayName == "friday") {
		return 4;
	}
	else if (dayName == "saturday") {
		return 5;
	}
	else if (dayName == "sunday") {
		return 6;
	}
	else return -1;
}
