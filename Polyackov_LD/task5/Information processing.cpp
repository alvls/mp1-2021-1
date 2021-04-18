
#include "all.h"

void cleaner()
{
    while (getchar() != '\n');
    cin.clear();
}

int GetDigit(const char LeftBound, const char RightBound, const bool IsEnterActive, const bool IsBackspaceActive)
{
	char digit;
	do
	{
		digit = _getch();
		if ((digit == BACKSPACE && IsBackspaceActive) || (digit == ENTER && IsEnterActive)) // �������� �� IsBackspaceActive � IsEnterActive �����, ����� ����� ������� ����� ����� �����, �� �� ������� �� ��
			return digit - '0';
	} while (digit < LeftBound || digit > RightBound);
	return digit - '0';
}

int GetNumber(const int NumberOfDigits, const int TypeOfRead, const bool IsEnterActive)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int tmpdigit;
	int number = 0;
	int pow10 = 1;
	for (int i = 1; i < NumberOfDigits; i++)
		pow10 *= 10;
	for (int i = 0; i < NumberOfDigits; i++)
	{
		tmpdigit = GetDigit('0', '9', IsEnterActive, true);
		if (tmpdigit == (BACKSPACE - '0'))
			if (i != 0)
			{
				pow10 *= 10;
				number = number / (pow10 * 10) * pow10 * 10; // ������������� pow10 �������� �� 10, ����� ����� �� ����������� �������
				i -= 2; // 2 ������ ��� ���� i-- ������ �� ��, ����� ���������� ���� backspace, � ������ i-- �� ��, ����� ���������� ���� ���������� �����    
				cout << "\b \b";
				continue;
			}
			else
			{
				i--;
				continue;
			}
		if (tmpdigit == (ENTER - '0'))
			if (IsEnterActive == true && i != 0)
				return number;
			else
			{
				i--;
				continue;
			}
		number += tmpdigit * pow10;
		pow10 /= 10;
		if (TypeOfRead == 0)
			cout << tmpdigit;
		else
		{
			SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | GREEN)); 
			cout << "*";
			SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | BLACK)); 
		}
	}
	return number;
}

void gotoxy(const int x, const int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
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
	cout << "\n  _____________\n |\\  _________ \\\n | \\ \\        \\_\\\n |  \\ \\        \\_\\\n |   \\ \\________\\ \\\n |    \\____\\\\\\\\____\\\n |    |  ________  |\n |    | |________| |\n |    |            |\n |    |            |\n |    |  ��������  |\n |    |    24/7    |\n |____|____________|\n ";
}

void waiting()
{
	gotoxy(1, 15);
	system("pause");
	system("cls");
}

void PrintMenu()
{
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = 22;
	pos.Y = 2;
	string menustr[5] = { "��������, ��� ����� �������:", "(1) ����������� ��������� ����� �������", "(2) ������ ������� �������� (������ �������� ����� �� �����)", "(3) ������� �� ������� ��������", "(4) ������� ����� �������" };
	for (int i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(hConsole, pos);
		cout << menustr[i];
		pos.Y++;
	}
	pos.Y++;
	SetConsoleCursorPosition(hConsole, pos);
}
