
#include "all.h"

void cleaner()
{
    while (getchar() != '\n');
    cin.clear();
}

int GetDigit(const char LeftBound, const char RightBound)
{
	char digit;
	do
	{
		digit = _getch();
	} while (digit < LeftBound || digit > RightBound);
	return digit - '0';
}

int GetNumber(const int NumberOfDigits, const int TypeOfRead)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int tmpdigit;
	int number = 0;
	int pow10 = 1;
	for (int i = 1; i < NumberOfDigits; i++)
		pow10 *= 10;
	for (int i = 0; i < NumberOfDigits; i++)
	{
		tmpdigit = GetDigit();
		number += tmpdigit * pow10;
		pow10 /= 10;
		if (TypeOfRead == 0)
			cout << tmpdigit;
		else
		{
			SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | 2)); // Green
			cout << "*";
			SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0)); // Black
		}
	}
	return number;
}

void gotoxy(const int x, const int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(Console, pos);
}
