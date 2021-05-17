#include "Field.h"
#include "Food.h"
#include "Snake.h"
#include <conio.h>
#include "Game.h"


bool Game::CheckCollision()
{
	vector<Coordinates> temp = snake.GetSnake();
	for (size_t i = 1; i < temp.size(); i++)
	{
		if (temp[0] == temp[i])
			return true;
	}
	return false;
}

bool Game::CheckBounds(const int& width, const int& height)
{
	Coordinates temp = snake.GetCoordHead();
	if (temp.x < 1 || temp.x > width - 2 || temp.y < 1 || temp.y > height - 2)
		return true;
	else
		return false;
}

void Game::EatFood()
{
	vector<Coordinates> temp = snake.GetSnake();
	if (allFood[indexFood].GetCoordFood() == temp[0])
	{
		Direction tempDir = snake.GetSnakeDir();
		Coordinates lastPart = temp[temp.size() - 1];
		switch (tempDir)
		{
		case LEFT:
			lastPart.x += 1;
			break;
		case RIGHT:
			lastPart.x -= 1;
			break;
		case UP:
			lastPart.y += 1;
			break;
		case DOWN:
			lastPart.y -= 1;
			break;
		}
		score += SCOREONEFOOD;
		snake.PushLastPart(lastPart);
		indexFood = rand() % allFood.size();
		this->ShowFood();
		gotoxy(0, this->field.GetHeight() + 1);
		cout << "Score: " << score << endl;
	}

}

void Game::ShowFood()
{
	vector<Coordinates> temp = snake.GetSnake();
	bool exit = true;
	while (true)
	{
		for (size_t i = 0; i < temp.size(); i++)
		{
			if (allFood[indexFood].GetCoordFood() == temp[i])
			{
				indexFood = rand() % allFood.size();
				exit = false;
				break;
			}
		}
		if (exit == true)
			break;
		exit = true;
	}
	allFood[indexFood].ShowFood();	
}

void Game::StartGame()
{
	setlocale(LC_ALL, "ru");

	int width = field.GetWidth();
	int height= field.GetHeight();


	int key = 0;

	srand(time(NULL));

	//при запуске, создаем пул объектов, а потом выводим на экран при необходимости
	for (size_t i = 0; i < needScore + 2; i++)
	{
		Food temp = { rand() % (width - 3) + 1, rand() % (height -3 ) + 1, SCOREONEFOOD };
		allFood.push_back(temp);
	}

	//рисование стен
	field.ShowWalls();
	cout << endl;
	//вывод счета в начале игры
	cout << "Score: " << score << endl;
	cout << "NeededScore: " << SCOREONEFOOD * needScore << endl;

	snake.SnakeShow();
	this->ShowFood();
	snake.SnakeHide();

	while (true)
	{
		while (!_kbhit())
		{
			this->EatFood();

			if (score == needScore * SCOREONEFOOD)
			{
				isWin = true;
				return;
			}

			if (this->CheckBounds(width, height))
				return;

			if(this->CheckCollision())
				return;

			snake.SnakeMove();

			snake.SnakeShow();

			Sleep(speed);

			snake.SnakeHide();
		}

		key = _getch();
		if (key == 224)
			key = _getch();

		switch (key)
		{
		case RIGHT:
			if (snake.GetSnakeDir() != LEFT)
			{
				snake.SetSnakeDir(RIGHT);
			}
			break;
		case DOWN:
			if (snake.GetSnakeDir() != UP)
			{
				snake.SetSnakeDir(DOWN);

			}
			break;
		case LEFT:
			if (snake.GetSnakeDir() != RIGHT)
			{
				snake.SetSnakeDir(LEFT);

			}
			break;
		case UP:
			if (snake.GetSnakeDir() != DOWN)
			{
				snake.SetSnakeDir(UP);
			}
			break;
		}
	}
}

bool Game::GetResult()
{
	return isWin;
}



