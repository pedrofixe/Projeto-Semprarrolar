#include <iostream>
#include <string>
#include <vector>
#include "driver.h"
#include "bus_stop.h"
#include "line.h"
#include "ui_utilities.h"
#include "utilities.h"

using namespace std;


int main()
{

	string horta = "   ola   ";
	cout << horta << "\n";

	utilities::trimString(horta);

	cout << horta;

	cout << "\n\n";
	return 0;
}