#include "Food.h"

void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hConsole, pos);
}

void Food::ShowFood()
{
	gotoxy(coordFood.x, coordFood.y);
	cout << "*";
}


