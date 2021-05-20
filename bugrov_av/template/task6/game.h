#pragma once
#include "all.h"
class game
{
	enum mode
	{
		oneplayer,
		twoplayers
	};
	const int indent = 3;
	mode var;
	table mine[2], enemy[2];//нулевой игрок ходит первым, первый - вторым
	int turn;
	//-------------------------------------------------------------------
	int shoot(int& letter, int& digit, bool& gamerepeat, bool& goodshoot, vector<int>& digit_shoot, vector<char>& letter_shoot);
	void random_shoot(bool& gamerepeat, bool& goodshoot, vector<int>& digit_shoot, vector<char>& letter_shoot);
	game& operator=(const game& g);
	game(const game& g);
public:
	game(int _var)
	{
		turn = 0;
		table t_tmp;
		for (int i = 0; i < 2; i++)
			mine[i] = enemy[i] = t_tmp;
		if (_var % 2)
			var = twoplayers;
		else
			var = oneplayer;
	}
	void play();
	void show() const;
};