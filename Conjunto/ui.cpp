#include "ui.h"

void MainMenu()
{
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();

	ui_utilities::PrintBanner();

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


bool SetConsoleWidth(const int& Width)
{
	if (Width > 119)
	{
		ConsoleWidth = Width;
		return true;
	}
	return false;
}

bool SetConsoleHeight(const int& Height)
{
	if (Height > 29)
	{
		ConsoleHeight = Height;
		return true;
	}
	return false;
}
