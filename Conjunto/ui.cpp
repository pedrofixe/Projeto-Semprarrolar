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

	Line templine;

	while (1)
	{
		cout << "\nInsert ID:";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (LineExists(tempstr))
			templine.SetID(tempstr);



	// Se nao for um numero, pedir novo input
		while (1)
		{
			cout << "\nInsira a frequencia da linha:";
			getline(cin, tempstr);

		// Condicao para a continuacao do programa
			if (is_numeric(tempstr))
				break;

			cout << "\nInput invalido!";
		}
		templinha.freq = stoi(tempstr);


	// Se existir algum numero na sequencia, pedir novo input
		while (1)
		{
			paragens.resize(0);

			cout << "\nInsira as paragens separadas por virgulas:";
			getline(cin, tempstr);
			tempstr += ',';

			bool test = 1;

			stringstream ss1(tempstr);
			while (getline(ss1, newtempstr, ','))
			{
				if (is_numeric(newtempstr))
				{
					test = 0;
					break;
				}
				paragens.push_back(newtempstr);
			}

		// Condicao para a continuacao do programa
			if (test && paragens.size() > 1)
				break;
			cout << "\nInput invalido!";
		}
		templinha.paragens = paragens;


	// Se existirem caracteres nao numericos, pedir novo input
		while (1)
		{
			tempoviagem.resize(0);

			cout << "\nInsira os tempos entre paragens, entre virgulas:";
			getline(cin, tempstr);
			tempstr += ',';

			bool test = 1;

			stringstream ss2(tempstr);
			while (getline(ss2, newtempstr, ','))
			{
				if (!is_numeric(newtempstr))
				{
					test = 0;
					break;
				}
				tempoviagem.push_back(stoi(newtempstr));
			}

		// Condicao para a continuacao do programa
			if (test && newtempstr.size() == 0 && tempoviagem.size() == paragens.size() - 1)
				break;

			cout << "\nInput invalido!";
		}

		templinha.tempoviagem = tempoviagem;

		LinhasGlobais.push_back(templinha);

		SaveLinhas();

		cout << "\nLinha Criada, Pressione qualquer tecla para continuar...";

		cin.get();
		Menu1();
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