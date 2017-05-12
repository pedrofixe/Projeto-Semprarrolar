#include "ui.h"

void MainMenu()
{
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();

	ui_utilities::PrintBanner();

	cout << string(3, '\n');

}

void ui::StartMenu()
{
	MainMenu();
}

void ui::StartMenu(const string& filename)
{
	SetBannerFilename(filename);
	MainMenu();
}


bool ui::SetConsoleWidth(const int& Width)
{
	if (Width > 119 && Width < 241)
	{
		ConsoleWidth = Width;
		return true;
	}
	return false;
}

bool ui::SetConsoleHeight(const int& Height)
{
	if (Height > 29 && Height < 64)
	{
		ConsoleHeight = Height;
		return true;
	}
	return false;
}

bool ui::SetBannerFilename(const string& filename)
{
	ifstream bannerfile(filename);

	if (bannerfile.fail())
	{
		bannerfile.close();
		return false;
	}
	else
	{
		bannerfilename = filename;
		return true;
	}
}



int ui::GetConsoleWidth()
return ConsoleWidth;

int ui::GetConsoleHeight()
return ConsoleHeight;

int ui::GetBannerFilename()
return bannerfilename;