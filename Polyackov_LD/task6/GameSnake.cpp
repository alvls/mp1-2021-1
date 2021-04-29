
#include "main.hpp"
#include "GameSnake.hpp"

// Area

Area::Area(short _w, short _h) : width(_w), height(_h)
{
	for (short i = 0; i < width + 2; i++)
		widthstr += '@';
	widthstr += '\n';
	heightstr += '@';
	for (short j = 0; j < width; j++)
		heightstr += ' ';
	heightstr += "@\n";
}

void Area::ShowArea()
{
	cout << widthstr;
	for (short i = 0; i < height; i++)
		cout << heightstr;
	cout << widthstr;
}

// Snake

void Snake::ShowBody()
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | LIGHTGREEN));
	for (const auto& tmp : snake)
	{
		gotoxy(tmp);
		cout << 'o';
	}
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | BLACK));
}

void Snake::ShowHead()
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(snake[0]);
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | GREEN));
	cout << 'O';
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | BLACK));
}

Snake::Snake(Area* _pArea) : pArea(_pArea)
{
	for (short i = 0; i < INITIALSIZE; i++)
	{
		COORD tmppos = { pArea->GetWidth() / 2 + i, pArea->GetHeight() / 2 };
		snake.push_back(tmppos);
	}
}

void Snake::ShowSnake()
{
	ShowBody();
	ShowHead();
}

void Snake::ChangeForm(const short x, const short y, const bool AddUnit)
{
	COORD tmpcoord = { snake[0].X + x, snake[0].Y + y };
	if (!AddUnit)
	{
		snake.insert(snake.cbegin(), tmpcoord); // Теперь первый элемент - голова - сместилась
		snake.pop_back(); // Удаляется последнее звено у хвоста
	}
	else
		snake.push_back(tmpcoord);
}

void Snake::Move(const short code)
{
	switch (code)
	{
	case UP:
		ChangeForm(0, -1);
		break;
	case DOWN:
		ChangeForm(0, 1);
		break;
	case LEFT:
		ChangeForm(-1, 0);
		break;
	case RIGHT:
		ChangeForm(1, 0);
		break;
	}
}

bool Snake::CrossedItself()
{
	for (size_t i = 1; i < snake.size(); i++)
		if (snake[0].X == snake[i].X && snake[0].Y == snake[i].Y)
			return true;
	return false;
}

Snake::~Snake()
{
	// Сбрасываю на nullptr, чтобы случайно не уничтожить информацию, хранящую под указателем
	// Объект удалится сам с помощью своего деструктора в дальнейшем
	pArea = nullptr;
	// Не использую delete, так как не выделял динамическую память с помощью new
}

// Food

bool Food::unique()
{
	vector<COORD> SnakeCopy = pSnake->GetSnake();
	for (const auto& tmp : SnakeCopy)
		if (FoodsCoord.X == tmp.X && FoodsCoord.Y == tmp.Y)
			return false;
	return true;
}

Food::Food(Area* _pArea, Snake* _pSnake) : pArea(_pArea), pSnake(_pSnake)
{
	srand(time(NULL));
	GenerateFood();
}

void Food::GenerateFood()
{
	static short width = pArea->GetWidth();
	static short height = pArea->GetHeight();
	do
	{
		FoodsCoord = { rand() % width + 1, rand() % height + 1 };
	} while (!unique());
}

void Food::ShowFood()
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(FoodsCoord);
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | LIGHTRED));
	cout << '+';
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | BLACK));
}

Food::~Food()
{
	// Сбрасываю на nullptr, чтобы случайно не уничтожить информацию, хранящую под указателями
	// Те объекты удалятся сами с помощью своих деструкторов в дальнейшем
	pArea = nullptr;
	pSnake = nullptr;
	// Не использую delete, так как не выделял динамическую память с помощью new
}

// GameSnake

void GameSnake::Show()
{
	area.ShowArea();
	food.ShowFood();
	snake.ShowSnake();
	ShowGoal();
}

void GameSnake::ShowGoal()
{
	static COORD pos = { 1, area.GetHeight() + 3 };
	gotoxy(pos);
	cout << "Осталось съесть пищи: " << goal;
}

short GameSnake::GameStatus()
{
	COORD head = snake.GetHead();
	if (head.X == 0 || head.X == area.GetWidth() + 1 || head.Y == 0 || head.Y == area.GetHeight() + 1)
		return 0;
	if (snake.CrossedItself())
		return 0;
	if (head.X == food.GetCoord().X && head.Y == food.GetCoord().Y)
	{
		food.GenerateFood();
		snake.ChangeForm(0, 0, true);
		goal--;
	}
	if (goal == 0)
		return 1;
	return 2;
}

void GameSnake::Actions()
{
	static short code = 2;
	static char c = '0';
	if (_kbhit())
	{
		do
		{
			switch (c = _getch())
			{
			case -32:
				break;
			case'w': case'W': case UPARROW:
				if (code != DOWN)
					code = UP;
				break;
			case's': case'S': case DOWNARROW:
				if (code != UP)
					code = DOWN;
				break;
			case'a': case 'A': case LEFTARROW:
				if (code != RIGHT)
					code = LEFT;
				break;
			case'd': case'D': case RIGHTARROW:
				if (code != LEFT)
					code = RIGHT;
				break;
			}
		} while (c == -32);
	}
	snake.Move(code);
}

GameSnake::GameSnake(short _goal, short _w, short _h) : goal(_goal), area(_w, _h), snake(&area), food(&area, &snake)
{
	if (_w * _h - 5 < _goal || _w < 6 || _h < 2 || _goal == 0)
		throw exception("Игру с задаными параметрами невозможно выиграть!");
}

void GameSnake::LaunchGame()
{
	enum { GAMEOVER, GAMEWON, GAMECONTINUE };
	short status = GAMECONTINUE;
	while (status == GAMECONTINUE)
	{
		Hide();
		Actions();
		status = GameStatus();
		Show();
		Sleep(200);
	}
	if (status == GAMEOVER)
		cout << "\n\n К сожалению, Вы проиграли!\n\n";
	if (status == GAMEWON)
		cout << "\n\n Поздравляем! Вы выиграли!\n\n";
}
