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
//==============================================

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
	} while (input < '1' && input>'9' && input != '\b');
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
class table
{
	const int hit = 'x';
	const char miss = 149;
	const char empty = '~';
	const char ship = '+';
	const string header = "   А Б В Г Д Е Ж З И К";
	string list[10];
	const int indent = 3;
	const int max = 10;
	int flotilla[4] = { 4,3,2,1 };
	//-----------------------------
	bool check(int x1, int y1, int x2, int y2, int* ship_amount);
	friend class user;
	friend class game;
public:
	table()
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
	void show();
	void setships();
	table(const table& t)
	{
		for (int i = 0; i < max; i++)
			list[i] = t.list[i];
	}
	table& operator=(const table& t)
	{
		for (int i = 0; i < max; i++)
			list[i] = t.list[i];
		return *this;
	}
	string& operator[](const int number)
	{
		return list[number];
	}
};
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
void table::show()
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
	system("color E0");
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
				if (x1 < 18)
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
				if (x2 < 18)
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
		if (x1 < 18)
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

//===============================================

//Реализовать ходы компьютера - play + другие функции
//При выстреле сделать изменения в досках стреляющего (вражеские корабли) и атакуемого (ваши корабли)
//Сделать создание кораблей для компьютера
//Сделать установку кораблей в play

//===============================================

class game
{
	enum mode
	{
		oneplayer,
		twoplayers
	};
	const int indent = 3;
	mode var;
	table mine[2], enemy[2];//нулевой игрок ходит первым, первый - вторым
	int turn;
	void show();
	string shoot(int& letter, int& digit);
	void play();
	game& operator=(const game& g);
	game(const game& g);
public:
	game(int _var)
	{
		turn = 0;
		table t_tmp;
		for (int i = 0; i < 2; i++)
			mine[i] = enemy[i] = t_tmp;
		if (_var % 2)
			var = twoplayers;
		else
			var = oneplayer;
	}
};
void game::show()
{
	if (turn % 2)
		if (var == oneplayer)
			return;
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
	const char* gap = "\t\t\t";
	system("color E0");
	cout << "      ";
	cout << "Ваши корабли";
	cout << gap << "    ";
	cout << "Вражеские корабли" << "\n";
	cout << mine[turn].header;
	cout << gap;
	cout << enemy[turn].header << "\n";
	unsigned i, j;
	unsigned max = 10;
	for (i = 0; i < max; i++)
	{
		cout << mine[turn].list[i][0];
		cout << mine[turn].list[i][1];
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | BLACK));
		for (j = 2; j < mine[turn].list[i].size(); j++)
			cout << mine[turn].list[i][j];
		SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | BLACK));
		cout << gap;
		cout << enemy[turn].list[i][0];
		cout << enemy[turn].list[i][1];
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | BLACK));
		for (j = 2; j < enemy[turn].list[i].size(); j++)
			cout << enemy[turn].list[i][j];
		cout << "\n";
		SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | BLACK));
	}
}
void game::play()
{
	int letter, digit;
	bool gamerepeat = true;
	const bool oneplayer = (var == oneplayer);
	system("color E0");
	while (gamerepeat)
	{
		show();
		cout << "\nВведите координаты выстрела ";
		getxy(letter, digit);
		cout << "\n" << shoot(letter, digit) << "\n";
		cout << "Передать ход сопернику - Enter, сдаться - Esc";
		int ans;
		bool garbage;
		enum class s
		{
			n = 13,
			_esc = 27
		};
		do
		{
			ans = _getch();
			switch (ans)
			{
			case 13:
				system("cls");
				if (var == twoplayers)
				{
					cout << "Передайте ход сопернику\n";
					Sleep(1500);
					cout << "Если вам только что передали ход, введите любой символ\n";
					_getch();
				}
				garbage = false;
				break;
			case 27:
				gamerepeat = false;
				garbage = false;
				break;
			default:
				garbage = true;
				break;
			}
		} while (garbage);
		turn = (turn + 1) % 2;
		if (turn > 0 && oneplayer)
		{
			//реализовать ход компьютера
		}
	}
	if (turn > 0)
		turn = 1;
	else
		turn = 2;
	cout << "Победа " << turn << "-го игрока! Поздравляем!";
	_getch();
}
string game::shoot(int& letter, int& digit)
{
	const int usernum = (turn + 1) % 2;
	const int begini = digit, beginj = indent + letter * 2;
	const string answer[4] = { "Ранен", "Убит", "Мимо", "Уже был такой выстрел" };
	int i = begini, j = beginj;
	int quantity = 0;
	if (mine[usernum][begini][beginj] == mine[usernum].hit || mine[usernum][begini][beginj] == mine[usernum].miss)
		return answer[3];
	else
		if (mine[usernum][begini][beginj] == mine[usernum].empty)
			return answer[2];
		else
			if (mine[usernum][begini][beginj] == mine[usernum].ship)
			{
				mine[usernum][begini][beginj] = 'x';
				for (i, j, quantity; (j <= beginj + 6) && j <= 18; j += 2)
					if (mine[usernum][i][j] == mine[usernum].hit)
						quantity++;
					else
						if (mine[usernum][i][j] == mine[usernum].miss || mine[usernum][i][j] == mine[usernum].empty)
							break;
						else
							if (mine[usernum][i][j] == mine[usernum].ship)
								return answer[0];
				for (i = begini, j = beginj; (j >= beginj - 6) && j >= 0; j -= 2)
					if (mine[usernum][i][j] == mine[usernum].hit)
						quantity++;
					else
						if (mine[usernum][i][j] == mine[usernum].miss || mine[usernum][i][j] == mine[usernum].empty)
							break;
						else
							if (mine[usernum][i][j] == mine[usernum].ship)
								return answer[0];
				quantity = 0;
				for (i = begini, j = beginj; (i <= begini + 3) && i < 9; i++)
					if (mine[usernum][i][j] == mine[usernum].hit)
						quantity++;
					else
						if (mine[usernum][i][j] == mine[usernum].miss || mine[usernum][i][j] == mine[usernum].empty)
							break;
						else
							if (mine[usernum][i][j] == mine[usernum].ship)
								return answer[0];
				for (i = begini, j = beginj; (i >= begini - 3) && i > -1; i--)
					if (mine[usernum][i][j] == mine[usernum].hit)
						quantity++;
					else
						if (mine[usernum][i][j] == mine[usernum].miss || mine[usernum][i][j] == mine[usernum].empty)
							break;
						else
							if (mine[usernum][i][j] == mine[usernum].ship)
								return answer[0];
			}
	mine[usernum].flotilla[quantity - 1]--;
	if (mine[usernum].flotilla[0] < 1 && mine[usernum].flotilla[1] < 1 && mine[usernum].flotilla[2] < 1 && mine[usernum].flotilla[3] < 1)
		;
	else
		return answer[1];
}
