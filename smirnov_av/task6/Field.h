#pragma once
#include <iostream>
#include <Windows.h>
#include "Food.h"
#define WALLSIGN "#"

using namespace std;
class Field
{
private:
	int width;
	int height;
public:
	Field(int _width = 0, int _height = 0) : width{ _width }, height{ _height }
	{

	}

	void ShowWalls();
	int GetWidth() { return width; }
	int GetHeight() { return height; }
};

