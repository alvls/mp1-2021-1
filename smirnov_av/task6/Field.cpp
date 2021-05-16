#include "Field.h"

void Field::ShowWalls()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | Blue));
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			if (i == 0 || i == height - 1)
				cout << WALLSIGN;
			else if (j == 0 || j == width - 1)
				cout << WALLSIGN;
			else
				cout << " ";
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | Black));
}
