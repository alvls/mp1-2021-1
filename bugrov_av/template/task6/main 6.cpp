//class myships
//{
//	//У каждого игрока имеются 4 «однопалубных» (из одной клетки) корабля, 3 «двухпалубных», 2 «трехпалубных» и 1 «четырехпалубный»
//	vector<int> y;
//	vector<int> x;
//	const int max = 10;
//	const char separator = '|';
//	bool check(int* pointer);
//public:
//	myships()
//	{
//		int tmp = -2;
//		for (int i = 0; i < max; i++)
//		{
//			x.push_back(tmp);
//			y.push_back(tmp);
//		}
//	}
//	void setxy();
//};

/*
* Разработать систему классов и реализовать с ее помощью игру Морской бой.

Требования (правила).
* Играют два игрока (человек и компьютер).
* У каждого игрока два поля 10x10 клеток. В левом поле игрок расставляет свои корабли. В правом игрок пытается потопить чужие корабли.
* У каждого игрока имеются 4 «однопалубных» (из одной клетки) корабля, 3 «двухпалубных», 2 «трехпалубных» и 1 «четырехпалубный» корабль.
* Многопалубные корабли могут располагаться только по горизонтали или вертикали.
* Корабли не могут располагаться в соседних клетках. Соседними для каждой клетки считаются 8 окружающих ее клеток.
* Игра состоит из поочередных ходов игроков.
* Первый ход выполняет человек.
* Каждый ход состоит из следующих действий:
* Игрок, выполняющий ход, «называет» выбранную клетку (координаты).
* Соперник проверяет «попадание» на своей доске. Если в названной клетке расположен корабль, соперник оглашает попадание, иначе промах.
* Игрок, выполняющий ход, ставит на своей правой доске по названным координатам отметку о результатах хода.
* Если игрок, выполняющий ход, попал в корабль, ход остается у него, иначе переходит к сопернику.
* Выигрывает тот игрок, кто первым потопит все корабли противника.
*/

#include "all.h"
void getxy(int& letter, int& digit)
{
	int input;
	char output;
	bool garbage;
setletter:
	do
	{
		input = _getch();
		if (224 <= input && input <= 232)
		{
			output = input;
			letter = input - 224;
			cout << output;
			garbage = false;
		}
		else
			if (192 <= input && input <= 200)
			{
				output = input;
				letter = input - 192;
				cout << output;
				garbage = false;
			}
			else
				if (234 == input)
				{
					output = input;
					letter = input - 225;
					cout << output;
					garbage = false;
				}
				else
					if (202 == input)
					{
						output = input;
						letter = input - 193;
						cout << output;
						garbage = false;
					}
					else
						garbage = true;
	} while (garbage);
setdigit:
	do
	{
		input = _getch();
	} while ((input < '1' || input>'9') && input != '\b');
	if (input == '\b')
	{
		cout << "\b \b";
		goto setletter;
	}
	else
	{
		output = input;
		cout << output;
		digit = input - '1';
	}
	do
	{
		input = _getch();
	} while (input != '0' && input != '\b' && input != 13 && input != ' ');
	if (input == '0')
	{
		cout << "0";
		digit = 9;
	}
	else
		if (input == '\b')
		{
			cout << "\b \b";
			goto setdigit;
		}
		else
			return;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color E0");
	cout << "Выберите режим игры: 1 - один игрок, 2 - два игрока\n";
	int input = _getch();
	while (input != '1' && input != '2')
	{
		input = _getch();
	}
	input -= '0';
	cout << input;
	input--;
	cout << "\nВведите любую клавишу, чтобы продолжить\n";
	_getch();
	game g(input);
	system("cls");
	g.play();
}
//===============================================

///Здесь было начертано многое, но создатель уничтожил это писание, дабы излишне не мудрствовать

//===============================================
