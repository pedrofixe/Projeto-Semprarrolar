#include <iostream>
#include <string>
#include <vector>
#include "bus_stop.h"
#include "driver.h"
#include "line.h"
#include "globals.h"
#include "ui.h"
#include "ui_utilities.h"
#include "utilities.h"

using namespace std;


int main()
{
	ui menu;

	menu.StartMenu(120, 30, "asciibanner.txt");

	cout << "\n\n";
	return 0;
}