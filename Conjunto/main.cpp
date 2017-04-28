#include <iostream>
#include <string>
#include "ui_utilities.h"

using namespace std;

#define LINES_FILENAME "linhas"
#define DRIVERS_FILENAME "condutores"

template <class T>

//Swap the value of two integers
void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

// Remove spaces at the beginning and at the end of a string
void TrimString(string &input)
{
	while (input[0] == ' ')
		input.erase(input.begin());

	while (input.back() == ' ')
		input.erase(input.end() - 1);
}

// Caluclates the length of a string
int intsize(int input)
{
	int res = 0;

	while (input)
	{
		res++;
		input /= 10;
	}

	return res;
}




int main()
{

	ui_utilities::SetWindow(120,30);

	std::cout << "Hortaliças incoming ...";

	ui_utilities::ClearScreen();


	std::cout << "\n\n";
	return 0;
}