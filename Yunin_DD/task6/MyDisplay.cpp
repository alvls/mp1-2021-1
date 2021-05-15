#include "MyDisplay.h"
#include <conio.h>

MyDisplay::MyDisplay()
{
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.bVisible = true;
}

void MyDisplay::ShowCursor()
{
	GetConsoleCursorInfo(console, &cursor);
	cursor.bVisible = true;
	SetConsoleCursorInfo(console, &cursor);
}

void MyDisplay::HideCursor()
{
	GetConsoleCursorInfo(console, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(console, &cursor);
}

void MyDisplay::ClsConsole()
{
	system("cls");
}

void MyDisplay::PauseConsole()
{
	system("pause");
}

void MyDisplay::ChangePosCursor(int x, int y)
{
	COORD position;
	position.X = static_cast<SHORT>(x); //Установка координаты X, static_cast<SHORT> - мы явно говорим, что приводим переданный int x к short.	
	position.Y = static_cast<SHORT>(y); //Установка координаты Y, static_cast<SHORT> - мы явно говорим, что приводим переданный int y к short.	
	SetConsoleCursorPosition(console, position); // Устанавливаем Курсор в определённом месте в консоле.
}

void MyDisplay::GoAndDrawSymbol(int x, int y, char symbol)
{		
	ChangePosCursor(x, y);
	_putch(symbol);
}

void MyDisplay::SetColor(int color_text, int color_back_ground) 
{
	SetConsoleTextAttribute(console, (WORD)((color_back_ground << 4) | color_text));
}

MyDisplay::~MyDisplay() {}
