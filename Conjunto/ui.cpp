#include "ui.h"

void PreMenu()
{
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	string temp;

	while(1)
	{
		cout <<"\nInsert lines filename:";

		getline(cin, temp);
		cout << "\n";

		ifstream linesfile(temp);

		if (!linesfile.fail())
			break;

		cout << "Invalid input";
	}

	LinesClass::LoadFromFile(temp);

	cout << "\n";

	while(1)
	{
		cout <<"\nInsert drivers filename:";

		getline(cin, temp);
		cout << "\n";

		ifstream driversfile(temp);

		if (!driversfile.fail())
			break;

		cout << "Invalid input";
	}

	DriversClass::LoadFromFile(temp);

	cout << '\n';

	// while(1)
	// {
	// 	cout <<"\nInsert shifts filename:";

	// 	getline(cin, temp);
	// 	cout << "\n";

	// 	ifstream shiftsfile(temp);

	// 	if (!shiftsfile.fail())
	// 		break;

	// 	cout << "Invalid input";
	// }

	// cout << '\n';

	while(1)
	{
		cout <<"\nInsert bus filename:";

		getline(cin, temp);
		cout << "\n";

		ifstream busfile(temp);

		if (!busfile.fail())
			break;

		cout << "Invalid input";
	}

	Buses_Class::LoadFromFile(temp);
}

void MainMenu()
{
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();

	ui_utilities::PrintBanner();

	cout << string(3, '\n');


	cout << "1- Line management\n";
	cout << "2- Driver management\n";
	cout << "3- Shift management\n";
	cout << "4- Bus management\n";
	cout << "5- Program trip\n";
	cout << "0- Quit\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Selecione uma opcao: ";

		getline(cin, input);
		cout << "\n";

		if (input == "1")
		{
			cout << "Menu1" //Menu1();
			break;
		}

		if (input == "2")
		{
			cout << "Menu2";
			break;
		}

		if (input == "3")
		{
			cout << "Menu3";
			break;
		}

		if (input == "4")
		{
			cout << "Menu4";
			break;
		}

		if (input == "0")
			exit(0);

		cout << "Invalid input\n";

	}

}

void ui::StartMenu()
{
	MainMenu();
}

bool ui::StartMenu(const string& filename)
{
	if (SetBannerFilename(filename))
		MainMenu();
}

bool ui::StartMenu(const int& Width, const int& Height, const string& filename)
{
	if (SetConsoleWidth(Width) && SetConsoleHeight(Height) && SetBannerFilename(filename))
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