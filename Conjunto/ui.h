#ifndef __UI_INCLUDED__
#define __UI_INCLUDED__

#include <string>
#include <fstream>
#include "ui_utilities.h"

using namespace std;

class ui{

public:
	void StartMenu();
	bool StartMenu(const string&);
	bool StartMenu(const int&, const int&, const string&);

	bool SetConsoleWidth(const int&);
	bool SetConsoleHeight(const int&);
	bool SetBannerFilename(const string&);

	int GetConsoleWidth() const;
	int GetConsoleHeight() const;
	int GetBannerFilename() const;

private:
	int ConsoleWidth = 150;
	int ConsoleHeight = 40;

	string bannerfilename = "asciibanner.txt";

}

#endif