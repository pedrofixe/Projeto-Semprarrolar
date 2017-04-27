// Alterar as variaveis GlobalWidth e GlobalHeight para o valor pretendido
// Se nao pretender alterar o tamanho da janela alterar a variavel ChangeWindowSize para 0

#include <iostream>
#include <string>
#include "ui_utilities.h"

//int GlobalWidth = 130; // 120 ate 240
//int GlobalHeight = 30; // 30 ate 63
bool ChangeWindowSize = 1;

#ifdef _WIN32

#include <windows.h>

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
		if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
			)) return;

	/* Move the cursor home */
			SetConsoleCursorPosition(hStdOut, homeCoords);
	}

	bool SetWindow(int Width, int Height)
	{
		if (ChangeWindowSize)
		{
			_COORD coord;
			coord.X = Width;
			coord.Y = Height;

			_SMALL_RECT Rect;
			Rect.Top = 0;
			Rect.Left = 0;
			Rect.Bottom = Height - 1;
			Rect.Right = Width - 1;

		// Get handle of the standard output 
			HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
			if (Handle == NULL)
			{
				cout << "Failure in getting the handle\n" << GetLastError();
				return FALSE;
			}

		// Set screen buffer size to that specified in coord 
			if (!SetConsoleScreenBufferSize(Handle, coord))
			{
				cout << "Failure in setting buffer size\n" << GetLastError();
				return FALSE;
			}

		// Set the window size to that specified in Rect 
			if (!SetConsoleWindowInfo(Handle, TRUE, &Rect))
			{
				cout << "Failure in setting window size\n" << GetLastError();
				return FALSE;
			}
		}
		return TRUE;

	}

#else

	void ClearScreen()
	{
		std::cout << "\033[2J\033[1;1H";
		std::cout << "\033[2J\033[1;1H";
	}

	bool SetWindow(int width, int height)
	{
		if (ChangeWindowSize)
		{
			std::string res = "\e[8;";
			res += std::to_string(height);
			res += ";";
			res += std::to_string(width);
			res += "t";
			std::cout << res;

		}
		return true;
	}

#endif