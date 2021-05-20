#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <conio.h>

using namespace std;

void gotoxy(const COORD pos);

enum ConsoleColor 
{
	BLACK = 0,
	GREEN = 2,
	LIGHTGREEN = 10,
	LIGHTRED = 12,
};

enum Directions { UP, DOWN, LEFT, RIGHT };

enum ArrowKeys
{
	UPARROW = 72,
	LEFTARROW = 75,
	RIGHTARROW = 77,
	DOWNARROW = 80
};
