#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#define number 12//число символов в номере телефона
#define date 8//число символов в дате рождения
using namespace std;
enum choice
{
	W = 150,
	w = 230,
	A = 148,
	a = 228,
	S = 155,
	s = 235,
	D = 130,
	d = 162,
	_n = 13,
	esc = 27
};
enum TColor
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
const string month[12] = { "января", "февраля", "марта", "апреля", "мая", "июня", "августа", "сентября", "октября", "ноября", "декабря" };