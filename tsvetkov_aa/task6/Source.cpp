#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <cstring>
#include <time.h>	
#include <tchar.h>
#include <stdio.h>
#include<ctime>
using namespace std;

void position(int x, int y)//перемещение курсора в консоли
{
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;									// Установка координаты X
	position.Y = y;									// Установка координаты Y
	SetConsoleCursorPosition(hConsole, position);
}

class deck//класс палуба, для однопалубных кораблей, и так же потомок для многопалубных
{
protected:
	int x1;
	int y1;
	int health;
public:
	deck(int _health = 1)//конструктор
	{
		x1 = 0;
		y1 = 0;
		health = _health;
	}
	int minushealth()//уменьшение значения здоровья при попадании
	{
		health--;
		return health;
	}
	virtual int gethealth(int x, int y)//возврат значение здоровья корабля, если промах то возвращается 0
	{
		if ((x1 == x) && (y1 == y))
			return health;
		else return 0;
	}
	virtual void mask(int k, int pozpc[10][10])//в процессе необходимо будет "обводить корабли" различными знаками
	{
		if (y1 - 1 >= 0)
		{
			if (x1 + 1 <= 9)
			{
				pozpc[x1 + 1][y1 - 1] = k;
				pozpc[x1 + 1][y1] = k;
			}
			if (x1 - 1 >= 0)
			{
				pozpc[x1 - 1][y1 - 1] = k;
				pozpc[x1 - 1][y1] = k;
			}
			pozpc[x1][y1 - 1] = k;
		}
		if (y1 + 1 <= 9)
		{
			if (x1 + 1 <= 9)
			{
				pozpc[x1 + 1][y1 + 1] = k;
				pozpc[x1 + 1][y1] = k;
			}
			if (x1 - 1 >= 0)
			{
				pozpc[x1 - 1][y1 + 1] = k;
				pozpc[x1 - 1][y1] = k;
			}
			pozpc[x1][y1 + 1] = k;
		}
		return;
	}
	virtual void robot(int pozpc[10][10])//установка корабля на поле для компьютера
	{
		do {
			x1 = rand() % 10;
			y1 = rand() % 10;
		} while (pozpc[x1][y1] != 0);
		pozpc[x1][y1] = 1;
		mask(2, pozpc);
	}
	virtual void move(string pol[], int poz[10][10])//установка корабля для игрока
	{
		int i, xpol, ypol, tmp;
		ypol = 1; xpol = 3;
		x1 = 0; y1 = 0;
		if (poz[x1][y1] != 1)
			pol[ypol][xpol] = '#';
		else
			pol[ypol][xpol] = 'X';
		for (i = 0; i < 11; i++)
			cout << pol[i];
		char symbol = _getch();
	u:		while ((symbol = _getch()))
	{
		switch (symbol) {
		case 72:
			//cout << "Вверх\n";
			if (ypol != 1)
			{
				y1 -= 1;
				tmp = ypol;
				ypol -= 1;
				if (pol[tmp][xpol] == 'X')
					pol[tmp][xpol] = '#';
				else
					pol[tmp][xpol] = '_';
				if (poz[x1][y1] != 1)
					pol[ypol][xpol] = '#';
				else
					pol[ypol][xpol] = 'X';
			}
			break;
		case 75:
			//std::cout << "Влево\n";
			if (xpol != 3)
			{
				x1 -= 1;
				tmp = xpol;
				xpol -= 2;
				if (pol[ypol][tmp] == 'X')
					pol[ypol][tmp] = '#';
				else
					pol[ypol][tmp] = '_';
				if (poz[x1][y1] != 1)
					pol[ypol][xpol] = '#';
				else
					pol[ypol][xpol] = 'X';
			}
			break;
		case 77:
			//std::cout << "Вправо\n";
			if (xpol != 21)
			{
				x1 += 1;
				tmp = xpol;
				xpol += 2;
				if (pol[ypol][tmp] == 'X')
					pol[ypol][tmp] = '#';
				else
					pol[ypol][tmp] = '_';
				if (poz[x1][y1] != 1)
					pol[ypol][xpol] = '#';
				else
					pol[ypol][xpol] = 'X';
			}
			break;
		case 80:
			//std::cout << "Вниз\n";
			if (ypol != 10)
			{
				y1 += 1;
				tmp = ypol;
				ypol += 1;
				if (pol[tmp][xpol] == 'X')
					pol[tmp][xpol] = '#';
				else
					pol[tmp][xpol] = '_';
				if (poz[x1][y1] != 1)
					pol[ypol][xpol] = '#';
				else
					pol[ypol][xpol] = 'X';
			}
			break;
		case 13:
			if (poz[x1][y1] == 0)
			{
				poz[x1][y1] = 1;
				mask(2, poz);
				cout << "Корабль успешно установлен";
				Sleep(500);
				system("cls");
				return;
			}
			cout << "Невозможно разместить корабль!" << endl;
			goto u;
			break;
		}
		system("cls");
		for (i = 0; i < 11; i++)
			cout << pol[i];
	}
	}
};

class manydeck :public deck//все функции аналогичны функциям класса deck, только выполняются для многопалубных кораблей
{
protected:
	int x2;
	int y2;
public:
	manydeck(int health) : deck(health), x2(0), y2(0) {};
	virtual void mask(int k, int pozpc[10][10])
	{
		int tmp;
		if (x1 == x2)
		{

			if (y1 - 1 >= 0)
			{
				pozpc[x1][y1 - 1] = k;
				if (x1 + 1 <= 9)
					for (tmp = y1 - 1; tmp <= y2; tmp++)
						pozpc[x1 + 1][tmp] = k;
				if (x1 - 1 >= 0)
					for (tmp = y1 - 1; tmp <= y2; tmp++)
						pozpc[x1 - 1][tmp] = k;
			}
			if (y2 + 1 <= 9)
			{
				pozpc[x1][y2 + 1] = k;
				if (x1 + 1 <= 9)
					for (tmp = y1; tmp <= y2 + 1; tmp++)
						pozpc[x1 + 1][tmp] = k;
				if (x1 - 1 >= 0)
					for (tmp = y1; tmp <= y2 + 1; tmp++)
						pozpc[x1 - 1][tmp] = k;

			}
			return;
		}
		else
		{

			if (x1 - 1 >= 0)
			{
				pozpc[x1 - 1][y1] = k;
				if (y1 - 1 >= 0)
					for (tmp = x1 - 1; tmp <= x2; tmp++)
						pozpc[tmp][y1 - 1] = k;
				if (y1 + 1 <= 9)
					for (tmp = x1 - 1; tmp <= x2; tmp++)
						pozpc[tmp][y1 + 1] = k;

			}
			if (x2 + 1 <= 9)
			{
				pozpc[x2 + 1][y1] = k;
				if (y1 - 1 >= 0)
					for (tmp = x1; tmp <= x2 + 1; tmp++)
						pozpc[tmp][y1 - 1] = k;
				if (y1 + 1 <= 9)
					for (tmp = x1; tmp <= x2 + 1; tmp++)
						pozpc[tmp][y1 + 1] = k;

			}
			return;
		}
	}
	virtual void robot(int pozpc[10][10])
	{
		int tmp, p;
		p = rand() % 2 + 1;
	p:		do {
		x1 = rand() % 10;
		y1 = rand() % 10;
	} while (pozpc[x1][y1] != 0);
	tmp = 1;
	if (p == 1)
	{
		while (tmp < health)
		{
			if ((pozpc[x1][y1 + tmp] == 0) && (y1 + tmp <= 9))
				tmp++;
			else
				break;
		}
		if (tmp == health)
		{
			x2 = x1;
			y2 = y1 + tmp - 1;
		}
		if (tmp != health)
		{
			tmp = 1;
			while (tmp < health)
			{
				if ((pozpc[x1][y1 - tmp] == 0) && (y1 - tmp >= 0))
					tmp++;
				else
					break;
			}
			if (tmp == health)
			{
				x2 = x1;
				y2 = y1;
				y1 = y1 - tmp + 1;
			}
		}
		if (tmp != health)
			goto p;
	}
	if (p == 2)
	{
		while (tmp < health)
		{
			if ((pozpc[x1 + tmp][y1] == 0) && (x1 + tmp <= 9))
				tmp++;
			else
				break;
		}
		if (tmp == health)
		{
			y2 = y1;
			x2 = x1 + tmp - 1;
		}
		if (tmp != health)
		{
			tmp = 1;
			while (tmp < health)
			{
				if ((pozpc[x1 - tmp][y1] == 0) && (x1 - tmp >= 0))
					tmp++;
				else
					break;
			}
			if (tmp == health)
			{
				y2 = y1;
				x2 = x1;
				x1 = x1 - tmp + 1;
			}
		}
		if (tmp != health)
			goto p;
	}
	if (x1 == x2)
	{
		for (tmp = y1; tmp <= y2; tmp++)
			pozpc[x1][tmp] = 1;
		mask(2, pozpc);
		return;
	}
	else
	{
		for (tmp = x1; tmp <= x2; tmp++)
		{
			pozpc[tmp][y1] = 1;
		}
		mask(2, pozpc);

		return;
	}
	}
	virtual void move(string pol[], int poz[10][10])
	{
		int i, xpol1, ypol1, xpol2, ypol2, tmp, tmp2;
		ypol1 = 1; xpol1 = 3; xpol2 = 3;
		x1 = 0; y1 = 0; x2 = 0; y2 = y1 + health - 1;
		ypol2 = ypol1 + health - 1;
		tmp = y1; tmp2 = ypol1;
		while (tmp <= y2)
		{
			if (poz[x1][tmp] != 1)
				pol[tmp2][xpol1] = '#';
			else
			{
				pol[tmp2][xpol1] = 'X';
			}
			tmp++;
			tmp2 += 1;
		}
		for (i = 0; i < 11; i++)
			cout << pol[i];
		char symbol = _getch();
	p:		while ((symbol = _getch()))
	{
		switch (symbol) {
		case 72:
			//"Вверх\n";
			if (ypol1 != 1)
			{
				y1 -= 1;
				y2 -= 1;
				tmp = ypol1;
				ypol1 -= 1;
				ypol2 -= 1;
				if (x1 == x2)
				{
					while (tmp <= ypol2 + 1)
					{
						if (pol[tmp][xpol1] == 'X')
							pol[tmp][xpol1] = '#';
						else
							pol[tmp][xpol1] = '_';
						tmp++;
					}
					tmp = y1; tmp2 = ypol1;
					while (tmp <= y2)
					{
						if (poz[x1][tmp] != 1)
							pol[tmp2][xpol1] = '#';
						else
						{
							pol[tmp2][xpol1] = 'X';
						}
						tmp++;
						tmp2++;
					}
				}
				else
				{
					tmp = xpol1;
					while (tmp <= xpol2)
					{
						if (pol[ypol1 + 1][tmp] == 'X')
							pol[ypol1 + 1][tmp] = '#';
						else
							pol[ypol1 + 1][tmp] = '_';
						tmp += 2;
					}
					tmp = x1; tmp2 = xpol1;
					while (tmp <= x2)
					{
						if (poz[tmp][y1] != 1)
							pol[ypol1][tmp2] = '#';
						else
						{
							pol[ypol1][tmp2] = 'X';
						}
						tmp++;
						tmp2 += 2;
					}
				}
			}
			break;
		case 75:
			// "Влево\n";
			if (xpol1 != 3)
			{
				x1 -= 1;
				x2 -= 1;
				xpol1 -= 2;
				xpol2 -= 2;
				if (x1 == x2)
				{
					tmp2 = ypol1;
					while (tmp2 <= ypol2)
					{
						if (pol[tmp2][xpol1 + 2] == 'X')
							pol[tmp2][xpol1 + 2] = '#';
						else
							pol[tmp2][xpol1 + 2] = '_';
						tmp2 += 1;
					}
					tmp = y1; tmp2 = ypol1;
					while (tmp <= y2)
					{
						if (poz[x1][tmp] != 1)
							pol[tmp2][xpol1] = '#';
						else
						{
							pol[tmp2][xpol1] = 'X';
						}
						tmp++;
						tmp2 += 1;
					}
				}
				else
				{
					tmp = xpol1 + 2;
					while (tmp <= xpol2 + 2)
					{
						if (pol[ypol1][tmp] == 'X')
							pol[ypol1][tmp] = '#';
						else
							pol[ypol1][tmp] = '_';
						tmp += 2;
					}
					tmp = x1; tmp2 = xpol1;
					while (tmp <= x2)
					{
						if (poz[tmp][y1] != 1)
							pol[ypol1][tmp2] = '#';
						else
						{
							pol[ypol1][tmp2] = 'X';
						}
						tmp++;
						tmp2 += 2;
					}
				}
			}
			break;
		case 77:
			// "Вправо\n";
			if (xpol2 != 21)
			{
				x1 += 1;
				x2 += 1;
				xpol1 += 2;
				xpol2 += 2;
				if (x1 == x2)
				{
					tmp2 = ypol1;
					while (tmp2 <= ypol2)
					{
						if (pol[tmp2][xpol1 - 2] == 'X')
							pol[tmp2][xpol1 - 2] = '#';
						else
							pol[tmp2][xpol1 - 2] = '_';
						tmp2 += 1;
					}
					tmp = y1; tmp2 = ypol1;
					while (tmp <= y2)
					{
						if (poz[x1][tmp] != 1)
							pol[tmp2][xpol1] = '#';
						else
						{
							pol[tmp2][xpol1] = 'X';
						}
						tmp++;
						tmp2 += 1;
					}
				}
				else
				{
					tmp = xpol1 - 2;
					while (tmp <= xpol2 - 2)
					{
						if (pol[ypol1][tmp] == 'X')
							pol[ypol1][tmp] = '#';
						else
							pol[ypol1][tmp] = '_';
						tmp += 2;
					}
					tmp = x1; tmp2 = xpol1;
					while (tmp <= x2)
					{
						if (poz[tmp][y1] != 1)
							pol[ypol1][tmp2] = '#';
						else
						{
							pol[ypol1][tmp2] = 'X';
						}
						tmp++;
						tmp2 += 2;
					}
				}
			}
			break;
		case 80:
			// "Вниз\n";
			if (ypol2 != 10)
			{
				y1 += 1;
				y2 += 1;
				tmp = ypol1;
				ypol1 += 1;
				ypol2 += 1;
				if (x1 == x2)
				{
					while (tmp <= ypol2 - 1)
					{
						if (pol[tmp][xpol1] == 'X')
							pol[tmp][xpol1] = '#';
						else
							pol[tmp][xpol1] = '_';
						tmp++;
					}
					tmp = y1; tmp2 = ypol1;
					while (tmp <= y2)
					{
						if (poz[x1][tmp] != 1)
							pol[tmp2][xpol1] = '#';
						else
						{
							pol[tmp2][xpol1] = 'X';
						}
						tmp++;
						tmp2++;
					}
				}
				else
				{
					tmp = xpol1;
					while (tmp <= xpol2)
					{
						if (pol[ypol1 - 1][tmp] == 'X')
							pol[ypol1 - 1][tmp] = '#';
						else
							pol[ypol1 - 1][tmp] = '_';
						tmp += 2;
					}
					tmp = x1; tmp2 = xpol1;
					while (tmp <= x2)
					{
						if (poz[tmp][y1] != 1)
							pol[ypol1][tmp2] = '#';
						else
						{
							pol[ypol1][tmp2] = 'X';
						}
						tmp++;
						tmp2 += 2;
					}
				}
			}
			break;
		case 32:
			// Пробел
			if (x1 == x2)
			{
				tmp = ypol1;
				while (tmp <= ypol2)
				{
					if (pol[tmp][xpol1] == 'X')
						pol[tmp][xpol1] = '#';
					else
						pol[tmp][xpol1] = '_';
					tmp++;
				}
				x2 = x1 + health - 1;
				xpol2 = xpol1 + (health - 1) * 2;
				ypol2 = ypol1;
				y2 = y1;
				while (x2 > 9)
				{
					x1--;
					x2--;
					xpol1 -= 2;
					xpol2 -= 2;
				}
				tmp = x1; tmp2 = xpol1;
				while (tmp <= x2)
				{
					if (poz[tmp][y1] != 1)
						pol[ypol1][tmp2] = '#';
					else
					{
						pol[ypol1][tmp2] = 'X';
					}
					tmp++;
					tmp2 += 2;
				}
			}
			else
			{
				tmp = xpol1;
				while (tmp <= xpol2)
				{
					if (pol[ypol1][tmp] == 'X')
						pol[ypol1][tmp] = '#';
					else
						pol[ypol1][tmp] = '_';
					tmp += 2;
				}
				x2 = x1;
				xpol2 = xpol1;
				y2 = y1 + health - 1;
				ypol2 = ypol1 + health - 1;
				while (y2 > 9)
				{
					y1--;
					y2--;
					ypol1--;
					ypol2--;
				}
				tmp = y1; tmp2 = ypol1;
				while (tmp <= y2)
				{
					if (poz[x1][tmp] != 1)
						pol[tmp2][xpol1] = '#';
					else
					{
						pol[tmp2][xpol1] = 'X';
					}
					tmp++;
					tmp2++;
				}
			}
			break;
		case 13:
			//Enter
			if (x1 == x2)
			{
				tmp = y1;
				while (tmp <= y2)
				{
					if (poz[x1][tmp] != 0)
						break;
					tmp++;
				}
				if (tmp == y2 + 1)
				{
					for (tmp = y1; tmp <= y2; tmp++)
						poz[x1][tmp] = 1;
					mask(2, poz);
					cout << "Корабль успешно установлен";
					Sleep(500);
					system("cls");
					return;
				}
			}
			else
			{
				tmp = x1;
				while (tmp <= x2)
				{
					if (poz[tmp][y1] != 0)
						break;
					tmp++;
				}
				if (tmp == x2 + 1)
				{
					for (tmp = x1; tmp <= x2; tmp++)
					{
						poz[tmp][y1] = 1;
					}
					mask(2, poz);
					cout << "Корабль успешно установлен";
					Sleep(500);
					system("cls");
					return;
				}
			}
			cout << "Невозможно разместить корабль!" << endl;
			goto p;
			break;
		}
		system("cls");
		for (i = 0; i < 11; i++)
			cout << pol[i];

	}
	}
	virtual int gethealth(int x, int y)
	{
		int tmp;
		if (x1 == x2)
		{
			for (tmp = y1; tmp <= y2; tmp++)
				if ((x1 == x) && (tmp == y))
					return health;
		}
		if (y1 == y2)
		{
			for (tmp = x1; tmp <= x2; tmp++)
				if ((tmp == x) && (y1 == y))
					return health;
		}
		return 0;
	}
};

class Playing
{
protected:
	int pozpc[10][10] = { 0 };
	int poz[10][10] = { 0 };
	string pc[11] = { "__|A_Б_В_Г_Д_Е_Ж_З_И_К_\n","1 |_|_|_|_|_|_|_|_|_|_|\n","2 |_|_|_|_|_|_|_|_|_|_|\n","3 |_|_|_|_|_|_|_|_|_|_|\n","4 |_|_|_|_|_|_|_|_|_|_|\n","5 |_|_|_|_|_|_|_|_|_|_|\n",
"6 |_|_|_|_|_|_|_|_|_|_|\n","7 |_|_|_|_|_|_|_|_|_|_|\n","8 |_|_|_|_|_|_|_|_|_|_|\n","9 |_|_|_|_|_|_|_|_|_|_|\n","10|_|_|_|_|_|_|_|_|_|_|\n" };
	string player[11] = { "__|A_Б_В_Г_Д_Е_Ж_З_И_К_\n","1 |_|_|_|_|_|_|_|_|_|_|\n","2 |_|_|_|_|_|_|_|_|_|_|\n","3 |_|_|_|_|_|_|_|_|_|_|\n","4 |_|_|_|_|_|_|_|_|_|_|\n","5 |_|_|_|_|_|_|_|_|_|_|\n",
"6 |_|_|_|_|_|_|_|_|_|_|\n","7 |_|_|_|_|_|_|_|_|_|_|\n","8 |_|_|_|_|_|_|_|_|_|_|\n","9 |_|_|_|_|_|_|_|_|_|_|\n","10|_|_|_|_|_|_|_|_|_|_|\n" };
	deck* kplayer[10] = { new deck, new deck, new deck, new deck, new manydeck(2),new manydeck(2),new manydeck(2), new manydeck(3), new manydeck(3) ,new manydeck(4) };
	deck* kpc[10] = { new deck, new deck, new deck, new deck, new manydeck(2),new manydeck(2),new manydeck(2), new manydeck(3), new manydeck(3) ,new manydeck(4) };
	int countplayer = 10;//количество кораблей
	int countpc = 10;
public:
	void setrobot()//размещение кораблей компьютером
	{
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			kpc[i]->robot(pozpc);
		}
	}
	void fieldplayer()//размещение кораблей игроком
	{
		int i = 0;
		cout << "Разместите свои корабли на игровом поле" << endl;
		cout << "Используйте  клавиши \"стрелки\" для перемещения корабля по полю" << endl;
		cout << "Используйте клавишу \"Пробел\" для изменениея ориентации корабля" << endl;
		cout << "Используйте клавишу \"Enter\" для установки корабля" << endl;
		for (i = 0; i < 10; i++)
		{
			kplayer[i]->move(player,poz);
		}
	}
	void printplay()//вывод на консоль игрового поля
	{
		system("cls");
		int i = 0;
		position(22, 1);
		cout << "Бой!" << endl;
		position(0, 2);
		cout << "Ваше поле";
		position(25, 2);
		cout << "Вражеское поле" << endl;
		position(0, 3);
		for (i = 0; i < 11; i++)
			cout << player[i];
		for (i = 0; i < 11; i++)
		{
			position(25, i + 3);
			cout << pc[i];
		}
		cout << "Осталось кораблей: " << countplayer << setw(24) << "Осталось кораблей: " << countpc << endl;
		cout << "Выберите клетку для выстрела,перемещая \"X\" по вражескому полю, " << endl << "затем нажмите клавишу \"Enter\" для выстрела" << endl;
		cout << "Обозначения клеток:" << endl << "0-пустая клетка" << endl << "#-попадание по вражескому кораблю" << endl;
	}
	int pcplay(int p)//алгоритм работы робота при выстреле
	{
		static int h, n;
		static int x, y;
		int tmp, i;
		if (p != 0)
			goto l;

	j:	x = rand() % 10;
		y = rand() % 10;
		if ((poz[x][y] == 2) || (poz[x][y] == 0))
		{
			poz[x][y] = 3;
			player[y + 1][2 * x + 3] = 'X';
			return 0;
		}
		if (poz[x][y] == 3)
			goto j;
		if (poz[x][y] == 1)
		{
			i = 0;
			h = 0;
			while ((h < 1) && (i < 10))
			{
				h = kplayer[i]->gethealth(x, y);
				if (h > 0) n = i;
				i++;
			}
			poz[x][y] = 3;
			player[y + 1][2 * x + 3] = 'X';
			h--;
			if (h == 0)
			{
				kplayer[n]->mask(3, poz);
				countplayer--;
				return 0;
			}

			p = rand() % 4 + 1;

		l:			switch (p)
		{
		case(1):
			tmp = x - 1;
			if (tmp < 0)
			{
				while (p == 1)
					p = rand() % 4 + 1;
				goto l;
			}
			if (poz[tmp][y] != 1)
			{
				while (p == 1)
					p = rand() % 4 + 1;
				if (poz[tmp][y] == 3)
					goto l;
				if (poz[tmp][y] != 3)
				{
					player[y + 1][2 * tmp + 3] = 'X';
					poz[tmp][y] = 3;
				}
				return p;
			}

			while ((poz[tmp][y] == 1) && (tmp >= 0))
			{
				h--;
				player[y + 1][2 * tmp + 3] = 'X';
				poz[tmp][y] = 3;
				tmp--;
			}
			if (h != 0)
			{
				if (tmp >= 0)
				{
					player[y + 1][2 * tmp + 3] = 'X';
					poz[tmp][y] = 3;
				}
				if (tmp < 0)
				{
					p = 2;
					goto l;
				}
				p = 2;
				return p;
			}
			else
			{
				kplayer[n]->mask(3, poz);
				countplayer--;
				return 0;
			}
			break;
		case(2):
			tmp = x + 1;
			if (tmp > 9)
			{
				while (p == 2)
					p = rand() % 4 + 1;
				goto l;
			}
			if (poz[tmp][y] != 1)
			{
				while (p == 2)
					p = rand() % 4 + 1;
				if (poz[tmp][y] == 3)
					goto l;
				if (poz[tmp][y] != 3)
				{
					player[y + 1][2 * tmp + 3] = 'X';
					poz[tmp][y] = 3;
				}

				return p;
			}

			while ((poz[tmp][y] == 1) && (tmp <= 9))
			{
				h--;
				player[y + 1][2 * tmp + 3] = 'X';
				poz[tmp][y] = 3;
				tmp++;
			}
			if (h != 0)
			{
				if (tmp <= 9)
				{
					player[y + 1][2 * tmp + 3] = 'X';
					poz[tmp][y] = 3;
				}
				if (tmp > 9)
				{
					p = 1; 
					goto l;
				}
				p = 1;
				return p;
			}
			else
			{
				kplayer[n]->mask(3, poz);
				countplayer--;
				return 0;
			}
			break;
		case 3:
			tmp = y + 1;
			if (tmp > 9)
			{
				while (p == 3)
					p = rand() % 4 + 1;
				goto l;
			}
			if (poz[x][tmp] != 1)
			{
				while (p == 3)
					p = rand() % 4 + 1;
				if (poz[x][tmp] == 3)
					goto l;
				if (poz[x][tmp] != 3)
				{
					player[tmp + 1][2 * x + 3] = 'X';
					poz[x][tmp] = 3;
				}
				return p;
			}

			while ((poz[x][tmp] == 1) && (tmp <= 9))
			{
				h--;
				player[tmp + 1][2 * x + 3] = 'X';
				poz[x][tmp] = 3;
				tmp++;
			}
			if (h != 0)
			{
				if (tmp <= 9)
				{
					player[tmp + 1][2 * x + 3] = 'X';
					poz[x][tmp] = 3;
				}
				if (tmp > 9)
				{
					p = 4;
					goto l;
				}
				p = 4;
				return p;
			}
			else
			{
				kplayer[n]->mask(3, poz);
				countplayer--;
				return 0;
			}
			break;
		case 4:
			tmp = y - 1;
			if (tmp < 0)
			{
				while (p == 4)
					p = rand() % 4 + 1;
				goto l;
			}
			if (poz[x][tmp] != 1)
			{
				while (p == 4)
					p = rand() % 4 + 1;
				if (poz[x][tmp] == 3)
					goto l;
				if (poz[x][tmp] != 3)
				{
					player[tmp + 1][2 * x + 3] = 'X';
					poz[x][tmp] = 3;
				}
				return p;
			}

			while ((poz[x][tmp] == 1) && (tmp >= 0))
			{
				h--;
				player[tmp + 1][2 * x + 3] = 'X';
				poz[x][tmp] = 3;
				tmp--;
			}
			if (h != 0)
			{
				if (tmp >= 0)
				{
					player[tmp + 1][2 * x + 3] = 'X';
					poz[x][tmp] = 3;
				}
				if (tmp < 0)
				{
					p = 3;
					goto l;
				}
				p = 3;
				return p;
			}
			else
			{
				kplayer[n]->mask(3, poz);
				countplayer--;
				return 0;
			}
			break;
		}
		}

	}
	int playerplay()//обработка хода игрока(выбор цели, выстрел)
	{
		int i, j, xpol, ypol, tmp;
	m:	ypol = 1; xpol = 3;
		int x = 0, y = 0, h, n;
		pc[ypol][xpol] = 'X';
		printplay();

		char symbol = _getch();
		while ((symbol = _getch()))
		{
			switch (symbol) {
			case 72:
				// "Вверх\n";
				if (ypol != 1)
				{
					y -= 1;
					tmp = ypol;
					ypol -= 1;
					if (pozpc[x][y + 1] == 3)
						pc[tmp][xpol] = '#';
					else
						if (pozpc[x][y + 1] == 4)
							pc[tmp][xpol] = '0';
						else
							pc[tmp][xpol] = '_';

					pc[ypol][xpol] = 'X';
				}
				break;
			case 75:
				//  "Влевоо\n";
				if (xpol != 3)
				{
					x -= 1;
					tmp = xpol;
					xpol -= 2;
					if (pozpc[x + 1][y] == 3)
						pc[ypol][tmp] = '#';
					else
						if (pozpc[x + 1][y] == 4)
							pc[ypol][tmp] = '0';
						else
							pc[ypol][tmp] = '_';
					pc[ypol][xpol] = 'X';
				}
				break;
			case 77:
				// "Вправо\n";
				if (xpol != 21)
				{
					x += 1;
					tmp = xpol;
					xpol += 2;
					if (pozpc[x - 1][y] == 3)
						pc[ypol][tmp] = '#';
					else
						if (pozpc[x - 1][y] == 4)
							pc[ypol][tmp] = '0';
						else
							pc[ypol][tmp] = '_';
					pc[ypol][xpol] = 'X';
				}
				break;
			case 80:
				// "Вниз\n";
				if (ypol != 10)
				{
					y += 1;
					tmp = ypol;
					ypol += 1;
					if (pozpc[x][y - 1] == 3)
						pc[tmp][xpol] = '#';
					else
						if (pozpc[x][y - 1] == 4)
							pc[tmp][xpol] = '0';
						else
							pc[tmp][xpol] = '_';
					pc[ypol][xpol] = 'X';
				}
				break;
			case 13:
				// "Enter\n"
				if ((pozpc[x][y] != 1) && (pozpc[x][y] != 3))
				{
					pc[ypol][xpol] = '0';
					pozpc[x][y] = 4;
					return 0;
				}
				else
				{
					h = 0;
					i = 0;
					while ((h < 1) && (i < 10))
					{
						h = kpc[i]->gethealth(x, y);
						if (h > 0) n = i;
						i++;
					}
					pc[ypol][xpol] = '#';
					pozpc[x][y] = 3;
					h = kpc[n]->minushealth();
					if (h == 0)
					{
						countpc--;
						kpc[n]->mask(4, pozpc);
						for (j = 0; j < 10; j++)
						{
							for (int i = 0; i < 10; i++)
								if (pozpc[i][j] == 4)
									pc[j + 1][2 * i + 3] = '0';
						}
						return 1;
					}
				}
				system("cls");
				goto m;
				break;
			}
			system("cls");
			printplay();

		}
	}
	void gameprocess()
	{
		int p = 0, k = 0;
		int tmpcount;
		fieldplayer();
		setrobot();
		printplay();
		while ((countplayer > 0) && (countpc > 0))
		{
			do
			{
				k = playerplay();
			} while ((k == 1) && (countpc > 0));
			if ((k != 1) && (countpc != 0))
			{
			r: tmpcount = countplayer;
				p = pcplay(p);
				printplay();
				if ((tmpcount != countplayer) && (countplayer != 0))
					goto r;
			}
		}
		if (countplayer == 0)
			cout << "Вы проиграли!" << endl;
		else
			cout << "Поздравляем, вы выиграли!" << endl;
	}
};

int  menu()
{
	int m;
	string label[] = { "_____________________________________________$$\n","$$___$$__$$$$__$$$$$___$$$$__$$__$$__$$$$__$$__$$\n","$$$_$$$_$$__$$_$$__$$_$$__$$_$$_$$__$$__$$_$$__$$\n","$$_$_$$_$$__$$_$$$$$$_$$_____$$$$___$$__$$_$$_$$$\n","$$___$$_$$__$$_$$_____$$__$$_$$_$$__$$__$$_$$$_$$\n",
			"$$___$$__$$$$__$$______$$$$__$$__$$__$$$$__$$__$$\n","________________$$\n","$$$$$___$$$$__$$__$$\n","$$_____$$__$$_$$__$$\n","$$$$$__$$__$$_$$_$$$\n","$$__$$_$$__$$_$$$_$$\n","$$$$$___$$$$__$$__$$\n" };
	for (int i = 0; i < 12; i++)
	{
		cout << label[i];
		Sleep(150);
	}
	cout << endl << endl;
	cout << "1.Новая Игра\n" << "0.Выход\n";
	cin >> m;
	return m;
}


void main()
{
	srand(time(NULL));
	int m;
	std::locale current_locale("");
	std::locale::global(current_locale);
	std::ios::sync_with_stdio(false);
	system("mode con cols=80 lines=25");
	Playing play;
	m = menu();
	if (m == 1)
	{
		system("cls");
		play.gameprocess();
	}
	else return;
	system("pause");
}
