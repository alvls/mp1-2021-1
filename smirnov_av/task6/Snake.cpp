#include "Snake.h"


void Snake::ChangeSnakePos(int deltaX, int deltaY)
{
	Coordinates LastUnit = snake[snake.size() - 1];;
	Coordinates temp = { snake[0].x + deltaX, snake[0].y + deltaY };
	snake.insert(snake.begin(), temp); 
	snake.pop_back(); 
}

void Snake::SnakeShow(const int& width, const int& height)
{
	bool exit = false;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t y = 1; y < height + 1; y++)
	{		
		for (size_t x = 1; x < width + 1; x++)
		{
			if (snake[0].x == x && snake[0].y == y)
			{
				gotoxy(x, y);			
				SetConsoleTextAttribute(hConsole, (WORD)((White << 4) |Red));
				cout << "0";
				continue;
			}		
			for (size_t i = 1; i < snake.size(); i++)
			{
				if (snake[i].x == x && snake[i].y == y)
				{
					gotoxy(x, y);
					SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | Green));
					cout << "î";					
				}					
			}					
		}	
	}
	SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | Black));
}

void Snake::SnakeMove()
{
	switch (snakeDir)
	{
	case LEFT:
		this->ChangeSnakePos(-1, 0);
		break;
	case RIGHT:
		this->ChangeSnakePos(1, 0);
		break;		
	case DOWN:
		this->ChangeSnakePos(0, 1);
		break;
	case UP:
		this->ChangeSnakePos(0, -1);
		break;
	}
}

void Snake::SnakeHide(const int& width, const int& height)
{	
	for (size_t y = 1; y < height + 1; y++)
	{
		for (size_t x = 1; x < width + 1; x++)
		{
			for (size_t i = 1; i < snake.size(); i++)
			{
				if (snake[i].x == x && snake[i].y == y)
				{
					gotoxy(x, y);
					cout << " ";
				}
			}
		}
	}
}

void Snake::SetSnakeDir(Direction _dir)
{
	snakeDir = _dir;
}

vector<Coordinates> Snake::GetSnake()
{
	return snake;
}

void Snake::PushLastPart(Coordinates lastPart)
{
	snake.push_back(lastPart);
}
