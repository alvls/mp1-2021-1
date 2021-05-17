#include "all.h"
void table::setships()
{
	int ship_amount[4] = { 4,3,2,1 };
	int x1, y1, x2, y2;
	do
	{
		show();
		cout << "Введите координаты начала нового корабля ";
		getxy(x1, y1);
		cout << "\n";
		cout << "Введите координаты конца нового корабля ";
		getxy(x2, y2);
		cout << "\n";
		if (check(x1, y1, x2, y2, ship_amount))
			cout << "Успешно!\n";
		else
			cout << "Неверный ввод\n";
		cout << "Введите любой символ, чтобы продолжить ";
		_getch();
		system("cls");
	} while (ship_amount[0] > 0 || ship_amount[1] > 0 || ship_amount[2] > 0 || ship_amount[3] > 0);
}
void table::show() const
{
	enum color
	{
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		BROWN = 6,
		LIGHTGRAY = 7,
		DARKGRAY = 8,
		LIGHTBLUE = 9,
		LIGHTGREEN = 10,
		LIGHTCYAN = 11,
		LIGHTRED = 12,
		LIGHTMAGENTA = 13,
		YELLOW = 14,
		WHITE = 15
	};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << header << "\n";
	int i, j;
	for (i = 0; i < max; i++)
	{
		cout << list[i][0];
		cout << list[i][1];
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | BLACK));
		for (j = 2; j < list[i].size(); j++)
			cout << list[i][j];
		cout << "\n";
		SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | BLACK));
	}
}
bool table::check(int x1, int y1, int x2, int y2, int* ship_amount)
{
	int distance;
	int buf_ymin, buf_ymax, buf_xmin, buf_xmax;//координаты буфера
	int tmp_ymin, tmp_ymax, tmp_xmin, tmp_xmax;//координаты корабля
	if (x1 != x2)
	{
		//y= const
		if (y1 != y2)
			return false;
		else
		{
			distance = abs(x1 - x2);
			if (distance > 3)
				return false;
			else
				if (ship_amount[distance] == 0)
					return false;
			if (x1 > x2)
			{
				tmp_xmax = indent + x1 * 2;
				tmp_xmin = indent + x2 * 2;
				//------------------------
				if (x1 < 9)
					buf_xmax = 2 * x1 + 2;
				else
					buf_xmax = 2 * x1;
				if (x2 > 0)
					buf_xmin = 2 * x2 - 2;
				else
					buf_xmin = x2;
			}
			else
			{
				tmp_xmax = indent + x2 * 2;
				tmp_xmin = indent + x1 * 2;
				//------------------------
				if (x2 < 9)
					buf_xmax = 2 * x2 + 2;
				else
					buf_xmax = 2 * x2;
				if (x1 > 0)
					buf_xmin = 2 * x1 - 2;
				else
					buf_xmin = x1;
			}
		}
		if (y1 > 0)
			buf_ymin = y1 - 1;
		else
			buf_ymin = y1;
		if (y1 < 9)
			buf_ymax = y1 + 1;
		else
			buf_ymax = y1;
		tmp_ymin = tmp_ymax = y1;
	}
	else
	{
		//x=const
		distance = abs(y1 - y2);
		if (distance > 3)
			return false;
		else
			if (ship_amount[distance] == 0)
				return false;
		if (y1 > y2)
		{
			tmp_ymax = y1;
			tmp_ymin = y2;
			//------------------------
			if (y1 < 9)
				buf_ymax = y1 + 1;
			else
				buf_ymax = y1;
			if (y2 > 0)
				buf_ymin = y2 - 1;
			else
				buf_ymin = y2;
		}
		else
		{
			tmp_ymax = y2;
			tmp_ymin = y1;
			//------------------------
			if (y2 < 9)
				buf_ymax = y2 + 1;
			else
				buf_ymax = y2;
			if (y1 > 0)
				buf_ymin = y1 - 1;
			else
				buf_ymin = y1;
		}
		if (x1 > 0)
			buf_xmin = 2 * x1 - 2;
		else
			buf_xmin = 2 * x1;
		if (x1 < 9)
			buf_xmax = 2 * x1 + 2;
		else
			buf_xmax = 2 * x1;
		tmp_xmin = tmp_xmax = x1 * 2 + indent;
	}
	//cout << xmin <<" "<< ymin << "\n";//////////////////////////////////////////////
	//cout << xmax <<" "<< ymax << "\n";///////////////////////////////////////////////
	for (int i = buf_ymin; i <= buf_ymax; i++)
		for (int j = indent + buf_xmin; j <= indent + buf_xmax; j += 2)
			if (list[i][j] == ship)
				return false;
	ship_amount[distance]--;
	for (int i = tmp_ymin; i <= tmp_ymax; i++)
		for (int j = tmp_xmin; j <= tmp_xmax; j += 2)
			list[i][j] = ship;
	return true;
}
void table::set_random_ships()
{
	/*
	1. Выбор рандомной точки.
	2. Выбор изменения по i(y), или по j(x).
	3. Выбор положительного или отрицательного изменения.
	4. Получение конечной координаты.
	5. Если какая - то координата отрицательна или больше 18, перейти к пункту 1.
	6. Функция check для table.
	*/
	int ship_amount[4] = { 4,3,2,1 };//число кораблей
	int letter1, digit1;//первая координата
	int letter2, digit2;//вторая координата
	int direction;//направление
	int change;//изменение координаты
	while (ship_amount[0] > 0 || ship_amount[1] > 0 || ship_amount[2] > 0 || ship_amount[3] > 0)
	{
		digit1 = rand() % 10;
		letter1 = rand() % 10;
		direction = rand() % 6;
		change = rand() % 4;
		switch (direction)
		{
			//Условно идём против часовой стрелки
		case 0:
			letter2 = letter1;
			digit2 = digit1;
			check(letter1, digit1, letter2, digit2, ship_amount);
			break;
		case 1:
			//letter2 > letter1;
			letter2 = letter1 + change;
			digit2 = digit1;
			if (letter2 < 10)
				check(letter1, digit1, letter2, digit2, ship_amount);
			break;
		case 2:
			//digit2 > digit1;
			letter2 = letter1;
			digit2 = digit1 + change;
			if (digit2 < 10)
				check(letter1, digit1, letter2, digit2, ship_amount);
			break;
		case 3:
			//letter2 < letter1;
			letter2 = letter1 - change;
			digit2 = digit1;
			if (letter2 > -1)
				check(letter1, digit1, letter2, digit2, ship_amount);
			break;
		case 4:
			//digit2 < digit1;
			letter2 = letter1;
			digit2 = digit1 - change;
			if (digit2 > -1)
				check(letter1, digit1, letter2, digit2, ship_amount);
			break;
		}
	}
}
table::table()
{
	char tmp;
	for (int i = 0; i < max; i++)
	{
		if (i < 9)
		{
			tmp = i + '1';
			list[i].push_back(tmp);
			list[i].push_back(' ');
		}
		else
		{
			list[i].push_back('1');
			list[i].push_back('0');
		}
		list[i].push_back('|');
		for (int j = 0; j < max; j++)
		{
			list[i].push_back(empty);
			list[i].push_back('|');
		}
	}
}
table::table(const table& t)
{
	for (int i = 0; i < max; i++)
		list[i] = t.list[i];
}
table& table:: operator=(const table& t)
{
	for (int i = 0; i < max; i++)
		list[i] = t.list[i];
	return *this;
}
string& table::operator[](const int number)
{
	return list[number];
}