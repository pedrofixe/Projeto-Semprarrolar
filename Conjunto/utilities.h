#ifndef __UTILITIES_INCLUDED__
#define __UTILITIES_INCLUDED__

#include <string>

using namespace std;

namespace utilities{

	template <class T>

	void swap(T&, T&);
	void trimString(string&);
	int intSize(int);
	bool isNumeric(string);
	string DayNumberToString(const unsigned int&);
	int DayStringToNumber(const string&);
};


#endif