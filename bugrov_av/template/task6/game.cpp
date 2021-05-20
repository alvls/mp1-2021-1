#include "all.h"
void game::show() const
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
	bool goodshoot = false;
	vector<int>digit_shoot;
	vector<char>letter_shoot;
	const string answer[3] = { "Попадание", "Мимо", "Уже был такой выстрел" };
	int ansnum;
	if (var == oneplayer)
	{
		srand(time(0));
		cout << "Игрок, выставляйте корабли\n";
		mine[0].setships();
		mine[1].set_random_ships();
		while (gamerepeat)
		{
			turn = 0;
			if (!digit_shoot.empty())
			{
				cout << "Противник сделал выстрел в координаты ";
				for (int i = 0; i < digit_shoot.size(); i++)
					cout << letter_shoot[i] << "-" << digit_shoot[i] << " ";
				cout << "\n";
			}
			show();
			digit_shoot.clear();
			letter_shoot.clear();
			do
			{
				if (goodshoot)
					cout << "Снова ваш ход\n";
				cout << "Введите координаты выстрела ";
				getxy(letter, digit);
				ansnum = shoot(letter, digit, gamerepeat, goodshoot, digit_shoot, letter_shoot);
				if (ansnum > 0)
					cout << "\n" << answer[ansnum] << "\n";
				if (goodshoot)
				{
					system("cls");
					show();
					cout << "Попадание\n";
				}
			} while (goodshoot && gamerepeat);
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
					turn = 1;
					garbage = false;
					break;
				default:
					garbage = true;
					break;
				}
			} while (garbage);
			turn = 1;
			digit_shoot.clear();
			letter_shoot.clear();
			do
			{
				random_shoot(gamerepeat, goodshoot, digit_shoot, letter_shoot);
			} while (goodshoot && gamerepeat);
		}
	onewin:		
		if (turn % 2 == 0)
			cout << "Вы победили, поздравляем!\n";
		else
			cout << "Увы, победил компьютер\n";
		_getch();
	}
	else//Игра двух человек
	{
		turn = 1;
		cout << "Первый игрок, выставляйте корабли\n";
		mine[0].setships();
		cout << "Теперь передайте возможность выставить корабли второму игроку, нажав любую клавишу\n";
		_getch();
		system("cls");
		cout << "Второй игрок, выставляйте корабли\n";
		mine[1].setships();
		cout << "Второй игрок, передайте право сделать выстрел первому игроку, нажав любую клавишу\n";
		_getch();
		system("cls");
		while (gamerepeat)
		{
			turn = (turn + 1) % 2;
			if (!digit_shoot.empty())
			{
				cout << "Противник сделал выстрел в координаты ";
				for (int i = 0; i < digit_shoot.size(); i++)
					cout << letter_shoot[i] << "-" << digit_shoot[i] << " ";
				cout << "\n";
			}
			show();
			digit_shoot.clear();
			letter_shoot.clear();
			do
			{
				if (goodshoot)
					cout << "Снова ваш ход\n";
				cout << "Введите координаты выстрела ";
				getxy(letter, digit);
				ansnum = shoot(letter, digit, gamerepeat, goodshoot, digit_shoot, letter_shoot);
				if (ansnum > 0)
					cout << "\n" << answer[ansnum] << "\n";
				if (goodshoot)
				{
					system("cls");
					show();
					cout << "Попадание\n";
				}
			} while (goodshoot && gamerepeat);
			if (!gamerepeat)
				break;
			cout << "Передать ход сопернику - Enter, сдаться - Esc\n";
			int ans;
			bool garbage;
			do
			{
				ans = _getch();
				switch (ans)
				{
				case 13:
					system("cls");
					cout << "Если сейчас ход " << (turn + 1) % 2 + 1 << "-го игрока, введите любой символ\n";
					_getch();
					system("cls");
					garbage = false;
					break;
				case 27:
					gamerepeat = false;
					turn = (turn + 1) % 2;
					garbage = false;
					break;
				default:
					garbage = true;
					break;
				}
			} while (garbage);
		}
		cout << "Победа " << (turn + 1) << "-го игрока! Поздравляем!";
		_getch();
	}
}
void game::random_shoot(bool& gamerepeat, bool& goodshoot, vector<int>& digit_shoot, vector<char>& letter_shoot)
{
	const int usernum = 0;
	int i;
	int j;
	do
	{
		i = rand() % 10;
		j = indent + 2 * (rand() % 10);
	} while (mine[usernum][i][j] == mine[usernum].hit || mine[usernum][i][j] == mine[usernum].miss);
	digit_shoot.push_back(i + 1);
	letter_shoot.push_back(mine->header[j]);
	if (mine[usernum][i][j] == mine[usernum].empty)
	{
		goodshoot = false;
		mine[usernum][i][j] = mine[usernum].miss;
		enemy[turn][i][j] = enemy[turn].miss;
		return;
	}
	else
	{
		mine[usernum][i][j] = mine[usernum].hit;
		enemy[turn][i][j] = enemy[turn].hit;
		goodshoot = true;
		for (int i = 0; i < mine[usernum].max; i++)
			for (j = indent; j < mine[usernum][i].size(); j += 2)
				if (mine[usernum][i][j] == mine->ship)
					return;
		gamerepeat = false;
		return;
	}
}
int game::shoot(int& letter, int& digit, bool& gamerepeat, bool& goodshoot, vector<int>& digit_shoot, vector<char>& letter_shoot)
{
	const int usernum = (turn + 1) % 2;
	const int begini = digit, beginj = indent + letter * 2;
	digit_shoot.push_back(begini + 1);
	letter_shoot.push_back(mine->header[beginj]);
	//const string answer[3] = { "Попадание", "Мимо", "Уже был такой выстрел" };
	//int quantity = 0;
	if (mine[usernum][begini][beginj] == mine[usernum].hit || mine[usernum][begini][beginj] == mine[usernum].miss)
	{
		goodshoot = false;
		return 2;
	}
	else
		if (mine[usernum][begini][beginj] == mine[usernum].empty)
		{
			goodshoot = false;
			mine[usernum][begini][beginj] = mine[usernum].miss;
			enemy[turn][begini][beginj] = enemy[turn].miss;
			return 1;
		}
		else
		{
			mine[usernum][begini][beginj] = mine[usernum].hit;
			enemy[turn][begini][beginj] = enemy[turn].hit;
			goodshoot = true;
			int i, j;
			for (i = 0; i < mine[usernum].max; i++)
				for (j = indent; j < mine[usernum][i].size(); j += 2)
					if (mine[usernum][i][j] == mine->ship)
						return 0;
			gamerepeat = false;
			return 0;
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