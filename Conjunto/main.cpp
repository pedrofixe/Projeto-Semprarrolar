#include <iostream>
#include <string>
#include <vector>
#include "bus.h"
#include "bus_stop.h"
#include "driver.h"
#include "globals.h"
#include "line.h"
#include "shift.h"
#include "ui.h"
#include "ui_utilities.h"
#include "utilities.h"

using namespace std;


int main()
{
	ui menu;
	menu.StartMenu(120, 30, "asciibanner.txt");

	return 0;
}