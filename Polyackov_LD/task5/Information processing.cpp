
#include "all.h"

int GetDigit()
{
	char digit;
	do
	{
		digit = _getch();
		if (digit == BACKSPACE || digit == ENTER)
			return digit - '0';
	} while (digit < '0' || digit > '9');
	return digit - '0';
}

int GetNumber(const int NumberOfDigits, const bool IsEnterActive, const int TypeOfWrite)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int tmpdigit;
	int number = 0;
	for (int i = 0; i <= NumberOfDigits; i++)
	{
		tmpdigit = GetDigit();
		if (tmpdigit == (BACKSPACE - '0'))
		{
			if (i != 0)
			{
				number /= 10;
				i--; // Пропустить ввод предыдущей цифры
				cout << "\b \b";
			}
			i--;
			continue;
		}
		if (tmpdigit == (ENTER - '0'))
		{
			if ((IsEnterActive && i != 0) || i == NumberOfDigits)
				return number;
			i--;
			continue;
		}
		if (i != NumberOfDigits)
		{
			number *= 10;
			number += tmpdigit;
			if (TypeOfWrite == 0)
				cout << tmpdigit;
			else
			{
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | GREEN));
				cout << "*";
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | BLACK));
			}
		}
		else
			i--;
	}
	return number;
}

void gotoxy(const int x, const int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void PrintStatus(const int type)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(7, 4);
	if (type == 0)
	{
		cout << "        ";
	}
	if (type == 1)
	{
		SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | LIGHTRED));
		cout << "  Error ";
	}
	if (type == 2)
	{
		SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | GREEN));
		cout << "Verified";
	}
	if (type == 3)
	{
		SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | CYAN));
		cout << " Waiting";
	}
	SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | BLACK));
}

void PrintCashMachine() 
{ 
	cout << "\n  _____________\n |\\  _________ \\\n | \\ \\        \\_\\\n |  \\ \\        \\_\\\n |   \\ \\________\\ \\\n |    \\____\\\\\\\\____\\\n |    |  ________  |\n |    | |________| |\n |    |            |\n |    |            |\n |    |  Банкомат  |\n |    |    24/7    |\n |____|____________|\n ";
}

void waiting()
{
	gotoxy(1,15);
	system("pause");
	system("cls");
}

void PrintMenu()
{
	string menustr[5] = { "Выберите, что нужно сделать:", "(1) Узнать баланс", "(2) Снять наличные (до 200 000)", "(3) Внести наличные", "(4) Вернуть карту" };
	cout << "\n ";
	for (auto const& tmpstr : menustr)
		cout << tmpstr << "\n ";
	cout << "\n ";
}
