#ifndef __UI_INCLUDED__
#define __UI_INCLUDED__

#include <string>
#include <fstream>
#include "ui_utilities.h"
#include "globals.h"

using namespace std;

class ui{

public:
	void StartMenu();
	bool StartMenu(const string&);
	bool StartMenu(const int&, const int&, const string&);

	bool SetConsoleWidth(const unsigned int&);
	bool SetConsoleHeight(const unsigned int&);
	bool SetBannerFilename(const string&);

	unsigned int GetConsoleWidth();
	unsigned int GetConsoleHeight();
	string GetBannerFilename();

private:
	unsigned int ConsoleWidth = 150;
	unsigned int ConsoleHeight = 40;

	string bannerfilename = "asciibanner.txt";

}

#endif