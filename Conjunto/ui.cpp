#include "ui.h"

void ui::PreMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
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
	
	cout << "\n\n All files have been loaded with success. Press enter to continue...";
	getchar();

	MainMenu();
}

void ui::MainMenu()
{
	while (true) {

		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
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

		cout << "  - MAIN MENU -\n";
		cout << " 1- Line management\n";
		cout << " 2- Driver management\n";
		cout << " 3- Bus management\n";
		cout << " 4- Shift management\n";
		cout << " 5- Calculate shortest trip\n";
		cout << " 6- Visualize Schedules\n";
		cout << " 0- Quit\n";
		cout << "\n";

		string input;

		while (true)
		{
			cout << "Select an option: ";

			getline(cin, input);
			cout << "\n";

			if (input == "1")
			{
				LineManagementMenu();
				break;
			}

			else if (input == "2")
			{
				DriverManagementMenu();
				break;
			}

			else if (input == "3")
			{
				BusManagementMenu();
				break;
			}

			else if (input == "4")
			{
				cout << "Menu4";
				break;
			}

			else if (input == "5")
			{
				cout << "Menu5";
				break;
			}

			else if (input == "0")
				return;

			else
				cout << "Invalid input\n";

		}

	}
}

void ui::LineManagementMenu()
{
	while (true) {
		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << "  - LINE MANAGEMENT MENU -\n";
		cout << " Active bus lines:";
		Lines.PrintLinesNames();
		cout << endl << endl;
		cout << " 1- Create line\n";
		cout << " 2- Edit line [NOT FINISHED YET]\n";
		cout << " 3- Remove line\n";
		cout << " 9- Return to previous menu\n";
		cout << "\n";

		string input;

		while (true)
		{
			cout << "Select an option: ";

			getline(cin, input);
			cout << "\n";

			if (input == "1")
			{
				CreateLineMenu();
				break;
			}

			else if (input == "2")
			{
				EditLineMenu();
				break;
			}

			else if (input == "3")
			{
				RemoveLineMenu();
				break;
			}

			else if (input == "9")
			{
				return;
			}

			else 
				cout << "Invalid input\n";

		}

	}
}

void ui::CreateLineMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Line templine;

	cout << "\n - CREATE LINE MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert new Line's ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Lines.LineExists(tempstr)) {
			cout << "Sorry but that Line ID isn't valid! It seems that line already exists.";
			continue;
		}
		else if (tempstr.length() < 3) {
			cout << "Sorry but the ID you inserted is too short. Please try again!";
			continue;
		}

		break;
	}
	templine.SetID(tempstr);

	while (1)
	{
		cout << "\n Insert new Line's frequency of service (minutes): ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!utilities::isNumeric(tempstr)) {
			cout << "Sorry but it seems you didn't insert a number! Try again.";
			continue;
		}
		if (stoi(tempstr) > 300 || stoi(tempstr) <= 2) {
			cout << "Yeah... That doesn't seem about right. Try again";
			continue;
		}
		break;
	}

	templine.SetFreq(stoi(tempstr));

	vector<string> tempstops;

	cout << "\n Insert new Line's bus stops (press enter after you type each one and to stop insert 0):";
	cout << endl;
	while (getline(cin, tempstr)) {
		utilities::trimString(tempstr);
		if (tempstr == "0") break;
		if (tempstr.length() < 3) {
			cout << "Oops! That is too short... Try again!" << endl;
		}
		tempstops.push_back(tempstr);
	}

	vector<unsigned int> temptimebetweenstops;

	cout << "\n Perfect! Now please insert the time it takes to travel between the following stops (minutes): ";
	cout << endl;

	for (size_t i = 0; i < tempstops.size() - 1; i++) {
		cout << "-Travel time beetween " << tempstops[i] << " and " << tempstops[i + 1] << "? ";
		getline(cin, tempstr);

		if (!utilities::isNumeric(tempstr)) {
			cout << "Sorry but it seems you didn't insert a number! Try again.";
			i--;
			continue;
		}
		if (stoi(tempstr) > 300 || stoi(tempstr) <= 2) {
			cout << "Yeah... That doesn't seem about right. Try again";
			i--;
			continue;
		}

		temptimebetweenstops.push_back( stoi(tempstr) );
	}

	templine.SetBus_Stops(tempstops);
	templine.SetTimeBetweenStops(temptimebetweenstops);

	cout << "\n   Line created, Press any key to continue...";
	cin.get();

	Lines.AddBusLine(templine);

	return;
}

void ui::EditLineMenu() 
{
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << "\n - EDIT LINE MENU -"
		<< "\n Please select one of the following bus lines:";

	Lines.PrintLinesNames();
	cout << endl << endl;

	while (1)
	{
		cout << " Line: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "0") return;

		if (Lines.LineExists(tempstr))
			break;

		cout << "\nLine not found!";
		cout << "\nEnter 0 if you wish to go back to the previous menu.\n";
	}
}

void ui::RemoveLineMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << "\n - REMOVE LINE MENU -"
		<< "\n Please select one of the following bus lines:";

	Lines.PrintLinesNames();

	cout << "\n Keep in mind all the shifts associated with that line will be also deleted!";

	cout << endl << endl;

	while (1)
	{
		cout << " Line: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "0") return;

		if (Lines.RemoveBusLineByID(tempstr))
			break;

		cout << "\nLine not found!";
		cout << "\nEnter 0 if you wish to go back to the previous menu.\n";
	}


	cout << "\n  Line removed, Press any key to continue...";
	cin.get();

	return;
}


void ui::DriverManagementMenu()
{
	while (true) {

		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << " - MANAGE DRIVERS MENU -";
		cout << "\n Currently there are " << Drivers.GetDrivers().size() << " drivers employed at SEMPRARROLAR.";
		cout << endl << endl;
		cout << " 1- Create driver\n";
		cout << " 2- List drivers\n";
		cout << " 3- List driver shifts\n";
		cout << " 4- Edit driver [NOT DONE YET]\n";
		cout << " 5- Remove driver\n";
		cout << " 9- Return to previous menu\n";
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

			else if (input == "2")
			{
				ListDriversMenu();
				break;
			}

			else if (input == "3")
			{
				ListDriverShiftsMenu();
				break;
			}

			else if (input == "4")
			{
				//EditDriversMenu();
				break;
			}

			else if (input == "5")
			{
				RemoveDriverMenu();
				break;
			}

			else if (input == "9")
			{
				return;
			}
			else
				cout << "Invalid input\n";

		}

	}
}

void ui::CreateDriverMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - CREATE DRIVER MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert new driver's ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Drivers.DriverExists(tempstr)) {
			cout << "\nSorry but it seems there already exists a driver with that ID! Try again.";
			continue;
		}
		else if (tempstr.length() < 2) {
			cout << "\nSorry but the ID you entered is too short! Try again.";
			continue;
		}
		break;
	}
	tempdriver.SetID(tempstr);


	while (1)
	{
		cout << "\n Insert driver's name: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr.length() < 3) {
			cout << "Sorry but the name you entered is too short! Try again.";
			continue;
		}
		break;
	}
	tempdriver.SetName(tempstr);

	while (1)
	{
		cout << "\n Insert driver's maximum hours per shift:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "Invalid input!";
	}
	tempdriver.SetMaxHoursShift(stoi(tempstr));


	while (1)
	{
		cout << "\n Insert driver's maximum hours of work per week:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "Invalid input!";
	}
	tempdriver.SetMaxHoursWeek(stoi(tempstr));


	while (1)
	{
		cout << "\n Insert driver's minimum rest hours between shifts:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "Invalid input!";
	}

	tempdriver.SetMinHoursRest(stoi(tempstr));

	Drivers.AddDriver(tempdriver);
	cout << "\n    Driver created, Press any key to continue...";
	cin.get();

	return;
}

void ui::ListDriversMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();
	cout << endl << endl << " Listing Drivers: " << endl << endl;

	Drivers.ListDrivers();
	
	cout << "\n Press any key to continue...";
	cin.get();
}

void ui::ListDriverShiftsMenu() {

	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << " - LIST DRIVER SHIFTS MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert driver's ID:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Drivers.DriverExists(tempstr))
			break;

		cout << "\nDriver not found!";
	}
	Driver *driver = Drivers.FindDriver(tempstr);

	cout << endl;

	Shifts_InterfaceClass::ListShifts(driver->GetDriverShifts());

	cout << endl << endl << "\n       Press any key to continue...";
	cin.get();
}

void ui::RemoveDriverMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << " - REMOVE DRIVER MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert driver's ID:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Drivers.RemoveDriverByID(tempstr))
			break;

		cout << "\nDriver not found!";
	}


	cout << "\n         Driver removed, Press any key to continue...";
	cin.get();

	return;
}

void ui::BusManagementMenu() {
	while (true) {

		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << " - MANAGE BUSES MENU -";
		cout << "\n Currently there are " << Buses.GetNumberOfBuses() << " buses being used at SEMPRARROLAR.";
		cout << endl << endl;
		cout << " 1- Create bus\n";
		cout << " 2- List buses\n";
		cout << " 3- Remove bus\n";
		cout << " 9- Return to previous menu\n";
		cout << "\n";

		string input;

		while (1)
		{
			cout << "Select an option: ";

			getline(cin, input);
			cout << "\n";

			if (input == "1")
			{
				CreateBusMenu();
				break;
			}
			else if (input == "2")
			{
				ListBusesMenu();
				break;
			}
			else if (input == "3")
			{
				RemoveBusMenu();
				break;
			}
			else {
				cout << "\nInvalid Input";
			}
		}
	}
}

void ui::CreateBusMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - CREATE BUS MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert new Bus ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Buses.BusExists(tempstr)) {
			cout << "\nSorry but it seems there already exists a bus with that ID! Try again.";
			continue;
		}
		else if (tempstr.length() < 2) {
			cout << "\nSorry but the ID you entered is too short! Try again.";
			continue;
		}
		break;
	}
	Buses.InsertBus(tempstr);
	cout << "\n   Bus created, Press any key to continue...";
	cin.get();
	return;

}

void ui::ListBusesMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - LIST BUSES MENU -" << endl << endl;

	Buses.ListBuses();

	cout << "\n Press any key to continue...";
	cin.get();
	return;

}

void ui::RemoveBusMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - REMOVE BUS MENU -"
		<< "\n Please select one of the following buses:";

	Buses.ListBuses();

	cout << "\n Keep in mind all the shifts associated with that bus will be also deleted!";

	cout << endl << endl;

	while (1)
	{
		cout << "\n Insert Bus ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Buses.BusExists(tempstr)) {
			cout << "\nSorry but no Bus was found with that ID! Try again.";
			continue;
		}
		break;
	}
	Buses.RemoveBus(tempstr);
	cout << "\n   Bus removed, Press any key to continue...";
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

	 static string Banner = "";
	 if (Banner == "") {
	 	ifstream hBanner(bannerfilename);
	 	if (hBanner.fail()) {
	 		cout << "Error openning banner file." << endl;
	 		hBanner.close();
	 		return;
	 	}
	 	string asciiTemp;
	 	while (getline(hBanner, asciiTemp))
	 		Banner += string(((ConsoleWidth - asciiTemp.size()) / 2), ' ') + asciiTemp + "\n";
	 }

	 cout << endl << Banner << endl << endl;

	//ifstream banner(bannerfilename);

	//cout << "\n";
	//string asciiTemp;

	//while (getline(banner, asciiTemp))
	//	cout << string(((ConsoleWidth - asciiTemp.size()) / 2),' ') << asciiTemp << "\n";

	//cout << "\n\n\n";

	//cout << string(3,'\n');

}