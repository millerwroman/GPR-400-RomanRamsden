#include "GameOfLife.h"

void printGrid(bool gridOne[26][26])
{
	for (int i = 1; i < gridSize; ++i)
	{
		for (int j = 1; j < gridSize; ++j)
		{
			if (gridOne[i][j] == true)
			{
				std::cout << " O ";
			}
			else
			{
				std::cout << " . ";
			}
			if (j == gridSize - 1)
			{
				std::cout << std::endl;
			}
		}
	}
}

void compareGrid(bool gridOne[26][26], bool gridTwo[26][26])
{
	for (int i = 0; i < gridSize; ++i)
	{
		for (int j = 0; j < gridSize; ++j)
		{
			gridTwo[i][j] = gridOne[i][j];
		}
	}
}

void determineState(bool gridOne[gridSize + 1][gridSize + 1])
{
	bool gridTwo[gridSize + 1][gridSize + 1] = {};
	compareGrid(gridOne, gridTwo);

	for (int a = 1; a < gridSize; a++)
	{
		for (int b = 1; b < gridSize; b++)
		{
			int alive = 0;
			for (int c = -1; c < 2; c++)
			{
				for (int d = -1; d < 2; d++)
				{
					if (!(c == 0 && d == 0))
					{
						if (gridTwo[a + c][b + d])
						{
							++alive;
						}
					}
				}
			}
			if (alive < 2)
			{
				gridOne[a][b] = false;
			}
			else if (alive == 3)
			{
				gridOne[a][b] = true;
			}
			else if (alive > 3)
			{
				gridOne[a][b] = false;
			}
		}
	}
}
void clearScreen()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	if (hStdOut == INVALID_HANDLE_VALUE) return;

	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hStdOut, static_cast<TCHAR>(' '), cellCount, homeCoords, &count);

	FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);

	SetConsoleCursorPosition(hStdOut, homeCoords);
}
