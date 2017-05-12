#ifndef __UI_UTILITIES_INCLUDED__
#define __UI_UTILITIES_INCLUDED__

#include <iostream>
#include <string>

using namespace std;

class ui_utilities{

public:
	
	static void ClearScreen();
	static bool SetWindow(int, int);
	static void PrintBanner(string, int);

};


#endif