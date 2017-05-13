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

	MainMenu();
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
	cout << "5- Calculate shortest trip\n";
	cout << "0- Quit\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Select an option: ";

		getline(cin, input);
		cout << "\n";

		if (input == "1")
		{
			Menu1();
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

		if (input == "5")
		{
			cout << "Menu5";
			break;
		}

		if (input == "0")
			exit(0);

		cout << "Invalid input\n";

	}

}

void Menu1()
{
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	ui_utilities::PrintBanner();

	cout << string(3, '\n');

	cout << "1- Create line\n";
	cout << "2- Edit line\n";
	cout << "3- Remove line\n";
	cout << "9- Return\n";
	cout << "0- Quit\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Select an option: ";

		getline(cin, input);
		cout << "\n";

		if (input == "1")
		{
			Menu1to1();
			break;
		}

		if (input == "2")
		{
			Menu1to2();
			break;
		}

		if (input == "3")
		{
			Menu1to3();
			break;
		}

		if (input == "9")
		{
			return;
		}

		if (input == "0")
			exit(0);

		cout << "Invalid input\n";

	}

}

void Menu1to1()
{
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	ui_utilities::PrintBanner();

	cout << string(3, '\n');

	while (1)
	{
		cout << "\nInsert line's ID:";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!LinesClass::LineExists(tempstr))
			break;

		cout << "\nInvalid input!";
	}
	templine.SetID(tempstr);


	while (1)
	{
		cout << "\nInsert time between buses:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (utilities::is_numeric(tempstr))
			break;

		cout << "\nInvalid input!";
	}
	templine.SetFreq(stoi(tempstr));

	vector<string> tempstops;

	while (1)
	{
		tempstops.clear();

		cout << "\nInsert bus stops between commas:";
		getline(cin, tempstr);
		tempstr += ',';

		stringstream ss1(tempstr);
		while (getline(ss1, tempstr, ','))
		{
			utilities::trimString(tempstr);

			tempstops.push_back(tempstr);
		}

		// Condition to continue program
		if (tempstops.size() > 1)
			break;

		cout << "\nInvalid input!";
	}
	templine.SetBus_Stops(tempstops);

	vector<unsigned int> temptimebetweenstops;

	while (1)
	{
		temptimebetweenstops.clear();

		cout << "\nInsert time between stops, between commas:";
		getline(cin, tempstr);
		tempstr += ',';

		bool test = 1;

		stringstream ss1(tempstr);
		while (getline(ss1, tempstr, ','))
		{
			if (!is_numeric(tempstr))
			{
				test = 0;
				break;
			}
			temptimebetweenstops.push_back(stoi(tempstr));
		}

		// The number of times between stops must be equal to the number of stops minus 1
		if (test && temptimebetweenstops.size() == tempstops.size() - 1)
			break;

		cout << "\nInvalid input!";
	}

	cout << "\nLine created, Press any key to continue...";
	cin.get();

	Lines.AddBusLine(templine);

	return;
}

void Menu1to3()
{
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	ui_utilities::PrintBanner();

	cout << string(3, '\n');

	string tempstr;

	while (1)
	{
		cout << "\nInsert line's ID:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (LinesClass::RemoveBusLineByID(tempstr))
			break;

		cout << "\nLine not found!";
	}


	cout << "\nLine removed, Press any key to continue...";
	cin.get();

	return;
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


bool ui::SetConsoleWidth(const unsigned int& Width)
{
	if (Width > 119 && Width < 241)
	{
		ConsoleWidth = Width;
		return true;
	}
	return false;
}

bool ui::SetConsoleHeight(const unsigned int& Height)
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



unsigned int ui::GetConsoleWidth()
{
	return ConsoleWidth;
}

unsigned int ui::GetConsoleHeight()
{
	return ConsoleHeight;
}

string ui::GetBannerFilename()
{
	return bannerfilename;
}