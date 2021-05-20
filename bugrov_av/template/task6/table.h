#pragma once
#include "all.h"
class table
{
	const char hit = 'x';
	const char miss = 149;
	const char empty = '~';
	const char ship = '+';
	const string header = "   � � � � � � � � � �";
	string list[10];
	//-----------------------------
	bool check(int x1, int y1, int x2, int y2, int* ship_amount);
	friend class game;
public:
	friend class menu;
	const int indent = 3;
	const int max = 10;
	table();
	void show() const;
	void set_random_ships();
	void setships();
	table(const table& t);
	table& operator=(const table& t);
	string& operator[](const int number);
};