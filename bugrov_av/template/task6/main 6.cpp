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

/// getxy +
/// setships +
/// set_random_ships +
/// check +
/// show +

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
class table
{
	const int hit = 'x';
	const char miss = 149;
	const char empty = '~';
	const char ship = '+';
	const string header = "   А Б В Г Д Е Ж З И К";
	string list[10];
	//-----------------------------
	bool check(int x1, int y1, int x2, int y2, int* ship_amount);
	friend class game;
public:
	friend class menu;
	const int indent = 3;
	const int max = 10;
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
	void set_random_ships();
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

//===============================================

///Доделать play
/// доделать manual 
/// доделать playgame

///На будущее: 
/// Сделать три уровня сложности: 
/// новичок (рандомные выстрелы и рандомная установка кораблей);
/// любитель (рандомная с добиванием стрельба + не рандомные выстрелы)
/// профессионал ( верные выстрелы и "умная" установка кораблей)

//===============================================

enum mode
{
	oneplayer,
	twoplayers
};
class game
{
	const int indent = 3;
	mode var;
	table mine[2], enemy[2];//нулевой игрок ходит первым, первый - вторым
	int turn;
	//-------------------------------------------------------------------
	string shoot(int& letter, int& digit, bool& gamerepeat,bool& goodshoot);
	vector<int> random_shoot(bool& gamerepeat, bool& goodshoot);
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
	void show();
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
	bool goodshoot;
	if (var == oneplayer)
	{
		vector<int> ji;
		srand(time(0));
		mine[0].setships();
		mine[1].set_random_ships();
		while (gamerepeat)
		{
			turn = 0;
			show();
			do
			{
				cout << "\nВведите координаты выстрела ";
				getxy(letter, digit);
				cout << "\n" << shoot(letter, digit, gamerepeat, goodshoot) << "\n";
				if (goodshoot)
					cout << "Снова ваш ход";
			} while (goodshoot);
			if (!gamerepeat)
				break;
			cout << "Передать ход компьютеру - Enter, сдаться - Esc";
			int ans;
			bool garbage;
			do
			{
				ans = _getch();
				switch (ans)
				{
				case 13:
					system("cls");
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
			turn = 1;
			ji = random_shoot(gamerepeat, goodshoot);
			cout << "Противник выстрелил в клетку " << char(mine[0].header[ji[0]]) << (ji[1] + 1) << "\n";
			_getch();
		}
		if (turn % 2 == 0)
			cout << "Вы победили, поздравляем!\n";
		else
			cout << "Увы, победил компьютер\n";
		_getch();
	}
	else//Игра двух человек
	{
		turn = 1;
		mine[0].setships();
		mine[1].setships();
		while (gamerepeat)
		{
			turn = (turn + 1) % 2;
			show();
			do
			{
				cout << "\nВведите координаты выстрела ";
				getxy(letter, digit);
				cout << "\n" << shoot(letter, digit, gamerepeat, goodshoot) << "\n";
				if (goodshoot)
					cout << "Снова ваш ход";
			} while (goodshoot);
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
					cout << "Передайте ход сопернику\n";
					Sleep(1500);
					cout << "Если сейчас ваш ход, введите любой символ\n";
					_getch();
					cout << "Противник выстрелил в клетку " << char(mine[0].header[mine[0].indent + letter * 2]) << (digit + 1) << "\n";
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
		}
		cout << "Победа " << turn + 1 << "-го игрока! Поздравляем!";
		_getch();
	}
}
vector<int> game::random_shoot(bool& gamerepeat, bool& goodshoot)
{
	const int usernum = 0;
	vector<int> ji(2);//потом придумал передавать vector, и решил ничего не менять
	int& i = ji[1];
	int& j = ji[0];
	//const int begini = digit, beginj = indent + letter * 2;
	do
	{
		i = rand() % 10;
		j = indent + 2 * (rand() % 10);
	} while (mine[usernum][i][j] == mine[usernum].hit || mine[usernum][i][j] == mine[usernum].miss);
	if (mine[usernum][i][j] == mine[usernum].empty)
	{
		goodshoot = false;
		mine[usernum][i][j] = mine[usernum].miss;
		enemy[turn][i][j] = enemy[turn].miss;
		return ji;
	}
	else
	{
		mine[usernum][i][j] = mine[usernum].hit;
		enemy[turn][i][j] = enemy[turn].hit;
		goodshoot = true;
		for (int i = 0; i < mine[usernum].max; i++)
			for (j = 0; j < mine[usernum][i].size(); j++)
				if (mine[usernum][i][j] == mine[i].ship)
					return ji;
		gamerepeat = false;
		return ji;
	}
}
string game::shoot(int& letter, int& digit, bool& gamerepeat,bool& goodshoot)
{
	const int usernum = (turn + 1) % 2;
	const int begini = digit, beginj = indent + letter * 2;
	const string answer[3] = { "Попадание", "Мимо", "Уже был такой выстрел" };
	int quantity = 0;
	if (mine[usernum][begini][beginj] == mine[usernum].hit || mine[usernum][begini][beginj] == mine[usernum].miss)
	{
		goodshoot = false;
		return answer[2];
	}
	else
		if (mine[usernum][begini][beginj] == mine[usernum].empty)
		{
			goodshoot = false;
			mine[usernum][begini][beginj] = mine[usernum].miss;
			enemy[turn][begini][beginj] = enemy[turn].miss;
			return answer[1];
		}
		else
		{
			mine[usernum][begini][beginj] = mine[usernum].hit;
			enemy[turn][begini][beginj] = enemy[turn].hit;
			goodshoot = true;
			int i, j;
			for (i = 0; i < mine[usernum].max; i++)
				for (j = 0; j < mine[usernum][i].size(); j++)
					if (mine[usernum][i][j] == mine[i].ship)
					{
						mine[usernum][begini][beginj] = mine[usernum].hit;
						enemy[turn][begini][beginj] = enemy[turn].hit;
						return answer[0];
					}
			gamerepeat = false;
		}
			/*if (mine[usernum][begini][beginj] == mine[usernum].ship)
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
			}*/
}

//===============================================

class menu
{
	int pointer;
	enum choice
	{
		W_en = 87,
		W = 214,
		w_en = 119,
		w = 246,
		A_en = 65,
		A = 212,
		a_en = 97,
		a = 244,
		S_en = 83,
		S = 219,
		s_en = 115,
		s = 251,
		D_en = 68,
		D = 194,
		d_en = 100,
		d = 226,
		_n = 13,
		esc = 27
	};
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
	bool badsymb;
	int input;
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	menu()
	{
		pointer = 0;
		badsymb = true;
		input = 0;
	}
	void choose_item();
	void mainmenu();
	void playgame();
	void manual();
	bool exitmenu();
};
void menu::choose_item()
{
	bool exitgame = true;
	system("color E0");
	do 
	{
		mainmenu();
		switch (pointer)
		{
		case 0:
			playgame();
			break;
		case 1:
			manual();
			break;
		case 2:
			exitgame = exitmenu();
			break;
		}
	} while (exitgame);
}
void menu::mainmenu()
{
	int i;
	pointer = 0;
	badsymb = true;
	const vector<string>item{ "   Играть"," Инструкция", "   Выход" };
	const vector<string> header{ "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n","+Добро пожаловать в игру \"Морской бой\"+\n","+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n" };
	for (i = 0; i < header.size(); i++)
		cout << header[i];
	//(WORD)((Background << 4) | Text))
	do
	{
		for (i = 0; i < pointer; i++)
		{
			cout << item[i] << "\n";
		}
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | BLACK));
		cout << item[pointer] << "\n";
		i++;
		SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | BLACK));
		for (i; i < item.size(); i++)
		{
			cout << item[i] << "\n";
		}
		do
		{
			input = _getch();
			switch (input)
			{
			case w: case W: case w_en: case W_en:
				if (pointer > 0)
					pointer--;
				else
					pointer = item.size() - 1;
				badsymb = false;
				break;
			case S: case s: case S_en: case s_en:
				pointer = (pointer + 1) % item.size();
				badsymb = false;
				break;
			case _n:
				badsymb = false;
				break;
			default:
				badsymb = true;
			}
		} while (badsymb);
	} while (input != _n);
}
void menu::playgame()
{
	int i;
	pointer = 0;
	system("color E0");
	bool badsymb = true;
	int input;
	mode gamemod;
	//(WORD)((Background << 4) | Text))

	do
	{
		for (i = 0; i < pointer; i++)
		{
			cout << item[i] << "\n";
		}
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | BLACK));
		cout << item[pointer] << "\n";
		i++;
		SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | BLACK));
		for (i; i < item.size(); i++)
		{
			cout << item[i] << "\n";
		}
		do
		{
			input = _getch();
			switch (input)
			{
			case w: case W: case w_en: case W_en:
				if (pointer > 0)
					pointer--;
				else
					pointer = item.size() - 1;
				badsymb = false;
				break;
			case S: case s: case S_en: case s_en:
				pointer = (pointer + 1) % item.size();
				badsymb = false;
				break;
			case _n:
				badsymb = false;
				break;
			default:
				badsymb = true;
			}
		} while (badsymb);
	} while (input != _n);
}
void menu::manual()
{
	cout << "ДЕЙСТВИЯ ВО ВРЕМЯ ИГРЫ:\n";
	cout << "Играют два игрокa. Это могут быть два человека или человек и компьютер\n"; 
	cout << "Каждый по очереди вводит координаты клетки, в которую нужно выстрелить\n"; 
	cout << "Есть три варианта результата выстрела: попадание в корабль, промах, выстрел по клетке, в которую уже стреляли\n"; 
	cout << "Каждый вариант выдаётся игроку\n"; 
	cout << "Если игрок попал в корабль, ход остаётся у него, иначе переходит к сопернику\n"; 
	cout << "Выигрывает тот игрок, кто первым потопит все корабли противника\n";
	cout << "УСЛОВНЫЕ ОБОЗНАЧЕНИЯ: \n";
	table t;
	{
		int indent = t.indent;
		const char ship = t.ship;
		const char miss = t.miss;
		const char hit = t.hit;
		t[0][7 * 2 + indent] = hit;
		t[1][1 * 2 + indent] = ship;
		t[1][4 * 2 + indent] = ship;
		t[1][7 * 2 + indent] = ship;
		t[1][9 * 2 + indent] = ship;
		t[2][1 * 2 + indent] = ship;
		t[2][7 * 2 + indent] = hit;
		t[2][9 * 2 + indent] = ship;
		t[3][4 * 2 + indent] = hit;
		t[3][5 * 2 + indent] = hit;
		t[3][7 * 2 + indent] = miss;
		t[3][9 * 2 + indent] = ship;
		t[4][indent] = miss;
		t[4][2 * 2 + indent] = miss;
		t[4][6 * 2 + indent] = miss;
		t[4][7 * 2 + indent] = hit;
		t[4][8 * 2 + indent] = miss;
		t[4][9 * 2 + indent] = ship;
		t[5][2 * 2 + indent] = ship;
		t[5][5 * 2 + indent] = miss;
		t[5][7 * 2 + indent] = miss;
		t[6][2 * 2 + indent] = hit;
		t[6][3 * 2 + indent] = miss;
		t[6][4 * 2 + indent] = miss;
		t[7][2 * 2 + indent] = ship;
		t[7][3 * 2 + indent] = miss;
		t[8][2 * 2 + indent] = miss;
		t[8][3 * 2 + indent] = miss;
		t[8][4 * 2 + indent] = hit;
		t[8][5 * 2 + indent] = ship;
		t[8][8 * 2 + indent] = ship;
		t[9][indent] = ship;
		t.show();
		cout << t.empty << " - Если это ваши корабли, то здесь ничего нет. Если вражеские - может быть всё нижеперечисленное\n";
		cout << t.hit << " - Повреждение корабля. Возможно, он потоплен, возможно нет\n";
		cout << t.miss << " - Выстрел в клетку, где нет корабля\n";
		cout << t.ship << " - Клетка с вашим кораблём\n";
	}

	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n"; 
	cout << "\n";
	cout << "\n";
}
bool menu::exitmenu()
{
	bool yes = true;
	badsymb = true;
	do 
	{
		cout << "Вы точно хотите выйти из игры?" << "\n";
		if (yes)
		{
			cout << "         ";
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | BLACK));
			cout << "Да";
			cout << "\t";
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | BLACK));
			cout << "Нет\n";
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | BLACK));
		}
		else
		{
			cout << "         ";
			cout << "Да";
			cout << "\t";
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | BLACK));
			cout << "Нет\n";
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | BLACK));
		}
		do
		{
			input = _getch();
			switch (input)
			{
				switch (input)
				{
				case A: case a: case A_en: case a_en: case D: case d: case d_en: case D_en:
					yes = !yes;
					badsymb = false;
					break;
				case _n:
					badsymb = false;
					break;
				default:
					badsymb = true;
					break;
				}
			}
		} while (badsymb);
	} while (input != _n);
	return yes;
}

//===============================================

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menu m;
}