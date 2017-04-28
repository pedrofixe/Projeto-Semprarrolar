#include "ui.h"

// Prints ASCII banner from filename
void ui::PrintBanner(std::string filename, int ConsoleWidth)
{
	ifstream banner(filename, fstream::in);

	cout << "\n";
	string asciiTemp;

	while (getline(banner, asciiTemp))
		cout << string(((ConsoleWidth - asciiTemp.size()) / 2), '\n') << asciiTemp << "\n";

	cout << "\n\n\n";
}