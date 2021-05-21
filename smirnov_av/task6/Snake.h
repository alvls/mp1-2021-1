#pragma once
#include <iostream>
#include <vector>
#include "Food.h"
#include "Field.h"
#include <Windows.h>

#define HEADSNAKE "0"
#define STARTSIZE 5

using namespace std;

enum Direction
{
	LEFT = 75,RIGHT = 77,DOWN = 80,UP = 72
};

class Snake
{
private:
	vector<Coordinates> snake;
	Direction snakeDir;
	void ChangeSnakePos(int deltaX, int deltaY);

public:
	Snake(int x = 0, int y = 0): snakeDir{LEFT}
	{
		Coordinates temp = { x,y };
		for (size_t i = 0; i < STARTSIZE; i++)
		{	
			if (snake.empty())
				snake.push_back(temp);
			else
				snake.push_back(temp);
			temp.x = temp.x + 1;
		}
	}
	
	void SnakeShow();
	void SnakeMove();
	void SnakeHide();
	
	Coordinates GetCoordHead() { return snake[0]; }
	void SetSnakeDir(Direction _dir);
	Direction GetSnakeDir() { return snakeDir; }
	vector<Coordinates> GetSnake();
	void PushLastPart(Coordinates lastPart);
};

