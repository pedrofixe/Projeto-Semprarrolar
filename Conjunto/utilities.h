#ifndef __UTILITIES_INCLUDED__
#define __UTILITIES_INCLUDED__

#include <string>

using namespace std;

class utilities{

public:
	template <class T>

	static void swap(T&, T&);
	static void trimstring(string&);
	static int intsize(int);
};


#endif