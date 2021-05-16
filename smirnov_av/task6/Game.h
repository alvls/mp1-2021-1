#pragma once
#include "Field.h"
#include "Snake.h"
#include <conio.h>
#define SCOREONEFOOD 10

class Game
{
private:
	Field field;
	Snake snake;
	vector <Food> allFood;
	int indexFood;
	int score;
	int needScore;
	bool isWin;
	int speed;

	bool CheckCollision();
	bool CheckBounds(const int& width, const int& height);
	void EatFood();
	void ShowFood();
public:
	Game(int _needScore,int _speed,int _width, int _height): needScore{ _needScore }, speed{_speed}
	{
		Field tempField(_width, _height);
		field = tempField;
		Snake tempSnake(field.GetWidth()/ 2 - 3, field.GetHeight() / 2);
		snake = tempSnake;
		isWin = false;
		score = 0;
	}
	
	int GetScore() { return score; }
	void NewTry() { score = 0; }

	void StartGame();
	bool GetResult();
};

