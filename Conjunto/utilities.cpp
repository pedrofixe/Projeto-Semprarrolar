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
void utilities::trimString(std::string &input)
{
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

string utilities::DayNumberToString(const unsigned int &num)
{
	static string daysArray[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	return daysArray[num];
}