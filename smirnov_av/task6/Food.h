#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

struct Coordinates
{
	int x;
	int y;
	bool operator==(Coordinates other)
	{
		if (x == other.x && y == other.y)
			return true;
		else
			return false;
	}

};

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class Food
{
protected:
	int worthScore;
	Coordinates coordFood;
	
public:
	Food(int _worthScore, Coordinates _coordFood) : worthScore{ _worthScore }, coordFood{ _coordFood }
	{

	}

	Food(int x, int y, int _worthScore)
	{
		coordFood.x = x;
		coordFood.y = y;
		worthScore = _worthScore;
	}

	void ShowFood();
	Coordinates GetCoordFood() { return coordFood; }
};

void gotoxy(int x, int y);