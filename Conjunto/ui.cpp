#include "ui.h"

void ui::PreMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	string tempstr;

	PrintBanner();

	while(1)
	{
		cout <<"\n Insert lines filename (leave empty for default: linhas.txt): ";

		getline(cin, tempstr);
		if (tempstr == "")	tempstr = "linhas.txt";

		if (!Lines.LoadFromFile(tempstr)) {
			cout << "File doesn't exist!";
			continue;
		}
		break;
	}

	cout << "\n";

	while (1)
	{
		cout << "\n Insert drivers filename (leave empty for default: condutores.txt): ";

		getline(cin, tempstr);
		if (tempstr == "")	tempstr = "condutores.txt";

		if (!Drivers.LoadFromFile(tempstr)) {
			cout << "File doesn't exist!";
			continue;
		}
		break;
	}

	cout << '\n';

	while (1)
	{
		cout << "\n Insert buses filename (leave empty for default: autocarros.txt): ";

		getline(cin, tempstr);
		if (tempstr == "")	tempstr = "autocarros.txt";

		if (!Buses.LoadFromFile(tempstr)) {
			cout << "File doesn't exist!";
			continue;
		}
		break;
	}

	cout << '\n';

	while (1)
	{
		cout << "\n Insert shifts filename (leave empty for default: turnos.txt): ";

		getline(cin, tempstr);
		if (tempstr == "")	tempstr = "turnos.txt";

		if (!Shifts_Interface.LoadFromFile(tempstr)) {
			cout << "File doesn't exist!";
			continue;
		}
		break;
	}
	
	cout << "\n\n All files have been loaded with sucess. Press enter to continue...";
	getchar();

	MainMenu();
}

void ui::MainMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	PrintBanner();

	//   FUNCIONALIDADES QUE O PROJETO DEVE TER, RETIRADO DO PDF
	//1. Ler e guardar a informa?o de linhas e condutores armazenada em ficheiros;
	//2. Gerir os condutores : criar, alterar e remover um condutor;
	//3. Gerar e visualizar de modo formatado tabelas com hor?ios de uma paragem;
	//4. Visualizar o trabalho atribu?o a um condutor;
	//5. Visualizar a informa?o de um autocarro;
	//6. Visualizar a informa?o de uma linha, visualizando de modo formatado a tabela com o seu hor?io;
	//7. Inquirir sobre quais as linhas que incluem determinada paragem;
	//8. Calcular e visualizar um percurso e tempo de viagem entre duas quaisquer paragens indicadas pelo
	//	utilizador.Deve procurar a solu?o : na linha que cont? a paragem inicial ou; na linha que cont? a
	//	paragem inicial e numa das linhas que tenha paragens comuns com a ?linha inicial?.Havendo mais
	//	do que uma solu?o o programa deve apresentar todas as solu?es encontradas mas por ordem
	//		crescente de dist?cia.Se n? encontrar uma solu?o dentro das restri?es indicadas, o programa
	//		deve indicar que n? encontrou uma liga?o entre as duas paragens.
	//		9. Listar todos os per?dos de autocarros sem condutor atribu?o.
	//		10. Listar todos os per?dos de condutores sem o servi? completo atribu?o(que n? tenham atingido o
	//			limite m?imo semanal).
	//		11. Efetuar interactivamente a atribui?o de servi? a um condutor, permitindo ao utilizador ver as
	//		disponibilidades de servi? dos autocarros, pedindo ao utilizador informa?o sobre um novo turno e
	//		verificando a consist?cia dessa informa?o com as restri?es de hor?io do condutor e restantes
	//		dados existentes.

	cout << " 1- Line management\n";
	cout << " 2- Driver management\n";
	cout << " 3- Bus management\n";
	cout << " 4- Shift management\n";
	cout << " 5- Calculate shortest trip\n";
	cout << " 6- Visualize Schedules\n";
	cout << " 0- Quit\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Select an option: ";

		getline(cin, input);
		cout << "\n";

		if (input == "1")
		{
			LineManagementMenu();
			break;
		}

		if (input == "2")
		{
			DriverManagementMenu();
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

void ui::LineManagementMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	PrintBanner();

	cout << "1- Create line\n";
	cout << "2- Edit line\n";
	cout << "3- Remove line\n";
	cout << "9- Return to previous menu\n";
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
			CreateLineMenu();
			break;
		}

		if (input == "2")
		{
			//Menu1to2();
			break;
		}

		if (input == "3")
		{
			RemoveLineMenu();
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

void ui::CreateLineMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Line templine;

	while (1)
	{
		cout << "\nInsert line's ID:";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Lines.LineExists(tempstr))
			break;

		cout << "\nInvalid input!";
	}
	templine.SetID(tempstr);


	while (1)
	{
		cout << "\nInsert time between buses:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (utilities::isNumeric(tempstr))
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
			if (!utilities::isNumeric(tempstr))
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

void ui::RemoveLineMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	PrintBanner();


	string tempstr;

	while (1)
	{
		cout << "\nInsert line's ID:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Lines.RemoveBusLineByID(tempstr))
			break;

		cout << "\nLine not found!";
	}


	cout << "\nLine removed, Press any key to continue...";
	cin.get();

	return;
}


void ui::DriverManagementMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	PrintBanner();

	cout << "1- Create driver\n";
	cout << "2- Edit driver\n";
	cout << "3- Remove driver\n";
	cout << "9- Return to previous menu\n";
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
			CreateDriverMenu();
			break;
		}

		if (input == "2")
		{
			//Menu1to2();
			break;
		}

		if (input == "3")
		{
			RemoveDriverMenu();
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


void ui::CreateDriverMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	while (1)
	{
		cout << "\nInsert driver's ID:";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Drivers.DriverExists(tempstr))
			break;

		cout << "\nInvalid input!";
	}
	tempdriver.SetID(tempstr);


	while (1)
	{
		cout << "\nInsert driver's name:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		bool test = 1;

		for (int i = 0; i < tempstr.size(); ++i)
		{
			if (tempstr[i] >= '0' && tempstr[i] <= '9')
			{
				test = 0;
				break;
			}
		}

		if (test && tempstr.size() > 0)
			break;

		cout << "\nInvalid input!";
	}
	tempdriver.SetName(tempstr);

	while (1)
	{
		cout << "\nInsert driver's maximum hours per shift:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "\nInvalid input!";
	}
	tempdriver.SetMaxHoursShift(stoi(tempstr));


	while (1)
	{
		cout << "\nInsert driver's maximum hours per week:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "\nInvalid input!";
	}
	tempdriver.SetMaxHoursWeek(stoi(tempstr));


	while (1)
	{
		cout << "\nInsert driver's minimum rest hours:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "\nInvalid input!";
	}
	tempdriver.SetMinHoursRest(stoi(tempstr));

	cout << "\nDriver created, Press any key to continue...";
	cin.get();

	Drivers.AddDriver(tempdriver);

	return;
}

void ui::RemoveDriverMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	while (1)
	{
		cout << "\nInsert driver's ID:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Drivers.RemoveDriverByID(tempstr))
			break;

		cout << "\nLine not found!";
	}


	cout << "\nDriver removed, Press any key to continue...";
	cin.get();

	return;
}


void ui::StartMenu()
{
	PreMenu();
}

bool ui::StartMenu(const string& filename)
{
	if (SetBannerFilename(filename))
	{
		PreMenu();
		return true;
	}
	return false;
}

bool ui::StartMenu(const int& Width, const int& Height, const string& filename)
{
	if (SetConsoleWidth(Width) && SetConsoleHeight(Height) && SetBannerFilename(filename))
	{
		PreMenu();
		return true;
	}
	return false;
}


bool ui::SetConsoleWidth(const unsigned int& Width)
{
	//if (Width > 119 && Width < 241)
	//{
		ConsoleWidth = Width;
		return true;
	//}
	return false;
}

bool ui::SetConsoleHeight(const unsigned int& Height)
{
	// if (Height > 29 && Height < 64)
	// {
		ConsoleHeight = Height;
		return true;
	// }
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


void ui::PrintBanner()
{

	// static string Banner = "";
	// if (Banner == "") {
	// 	ifstream hBanner(bannerfilename);
	// 	if (hBanner.fail()) {
	// 		cout << "Error openning banner file." << endl;
	// 		hBanner.close();
	// 		return;
	// 	}
	// 	string asciiTemp;
	// 	while (getline(hBanner, asciiTemp))
	// 		Banner += string(((ConsoleWidth - asciiTemp.size()) / 2), ' ') + asciiTemp + "\n";
	// }

	// cout << endl << Banner;

	ifstream banner(bannerfilename);

	cout << "\n";
	string asciiTemp;

	while (getline(banner, asciiTemp))
		cout << string(((ConsoleWidth - asciiTemp.size()) / 2),' ') << asciiTemp << "\n";

	cout << "\n\n\n";

	cout << string(3,'\n');

}