
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
	LastUnit = snake[snake.size() - 1];
}

void Snake::ShowSnake()
{
	ShowBody();
	ShowHead();
}

void Snake::ChangePosition(const short dx, const short dy)
{
	LastUnit = snake[snake.size() - 1];
	COORD tmpcoord = { snake[0].X + dx, snake[0].Y + dy };
	snake.insert(snake.cbegin(), tmpcoord); // Теперь голова пересместилась
	snake.pop_back(); // Удаляется последнее звено у хвоста
}

void Snake::AddLastUnit()
{
	snake.push_back(LastUnit);
}

void Snake::Move(const short direction)
{
	switch (direction)
	{
	case UP:
		ChangePosition(0, -1);
		break;
	case DOWN:
		ChangePosition(0, 1);
		break;
	case LEFT:
		ChangePosition(-1, 0);
		break;
	case RIGHT:
		ChangePosition(1, 0);
		break;
	}
}

bool Snake::CrossedItself()
{
	COORD head = snake[0];
	for (size_t i = 1; i < snake.size(); i++)
		if (head.X == snake[i].X && head.Y == snake[i].Y)
			return true;
	return false;
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

Food::Food(Snake* _pSnake) : pSnake(_pSnake)
{
	srand(time(NULL));
	GenerateFood();
}

void Food::GenerateFood()
{
	short width = pSnake->GetpArea()->GetWidth();
	short height = pSnake->GetpArea()->GetHeight();
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

// GameSnake

void GameSnake::Show()
{
	area.ShowArea();
	food.ShowFood();
	snake.ShowSnake();
	ShowInfo();
}

void GameSnake::ShowInfo()
{
	COORD pos = { 1, area.GetHeight() + 3 };
	gotoxy(pos);
	cout << "Размер змейки: " << SizeNeeded - FoodsLeft << " из " << SizeNeeded << "\n\n Осталось съесть пищи: " << FoodsLeft;
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
		snake.AddLastUnit();
		FoodsLeft--;
		if (FoodsLeft == 0)
			return 1;
		food.GenerateFood();
	}
	return 2;
}

void GameSnake::Actions()
{
	if (_kbhit())
	{
		char c;
		do
		{
			switch (c = _getch())
			{
			case -32:
				break;
			case UPARROW:
				if (direction != DOWN)
					direction = UP;
				break;
			case DOWNARROW:
				if (direction != UP)
					direction = DOWN;
				break;
			case LEFTARROW:
				if (direction != RIGHT)
					direction = LEFT;
				break;
			case RIGHTARROW:
				if (direction != LEFT)
					direction = RIGHT;
				break;
			}
		} while (c == -32);
	}
	snake.Move(direction);
}

void GameSnake::EndGame(const short code)
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	enum { GAMEOVER, GAMEWON };
	if (code == GAMEOVER)
	{
		gotoxy(snake.GetHead());
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | LIGHTRED));
		cout << '!';
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | BLACK));
		COORD end = { 1, area.GetHeight() + 7 };
		gotoxy(end);
		cout << "К сожалению, Вы проиграли!\n\n";
	}
	if (code == GAMEWON)
	{
		Hide();
		Show();
		cout << "\n\n Поздравляем! Вы выиграли!\n\n";
	}
}

GameSnake::GameSnake(short _goal, short _w, short _h) : area(_w, _h), snake(&area), food(&snake)
{
	if (_goal < snake.GetSize() + 1)
		throw exception("Длина змейки, которую нужно достичь, должна быть больше изначальной длины змейки!");
	if (_w < snake.GetSize() + 2)
		throw exception("При данных параметрах змейка не убирается по ширине!");
	if (_h < 2)
		throw exception("При данных параметрах змейка не убирается по высоте!");
	if (_w * _h < _goal)
		throw exception("Змейка не сможет достичь заданной длины из-за нехватки свободного места!");
	direction = LEFT;
	SizeNeeded = _goal;
	FoodsLeft = _goal - short(snake.GetSize());
}

void GameSnake::LaunchGame()
{
	enum { GAMEOVER, GAMEWON, GAMECONTINUE, SPEED = 200 };
	short status = GAMECONTINUE;
	unsigned int time = clock();
	Hide();
	Show(); // Отрисовка начального положения
	time = clock() - time;
	if (SPEED > time)
		Sleep(SPEED - time);
	while (true)
	{
		time = clock();
		Actions();
		status = GameStatus();
		if (status != GAMECONTINUE)
			break;
		Hide();
		Show();
		time = clock() - time;
		if (SPEED > time)
			Sleep(SPEED - time);
	}
	EndGame(status);
}
