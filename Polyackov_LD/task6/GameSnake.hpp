#pragma once

class Area
{
private:
	short width;
	short height;
	string widthstr;
	string heightstr;
public:
	Area(short _w, short _h);
	void ShowArea();
	short GetWidth() { return width; }
	short GetHeight() { return height; }
};

class Snake
{
private:
	enum { INITIALSIZE = 5 };
	COORD LastUnit;
	vector<COORD> snake;
	Area* pArea; // ”казатель будет присвоен, поэтому в деструкторе не нужно использовать delete

	void ShowBody();
	void ShowHead();
public:
	Snake(Area* _pArea);
	void ShowSnake();
	size_t GetSize() { return snake.size(); }
	COORD GetHead() { return snake[0]; }
	Area* GetpArea() { return pArea; }
	void ChangePosition(const short dx, const short dy);
	void AddLastUnit();
	void Move(const short code);
	bool CrossedItself();
	vector<COORD> GetSnake() { return snake; }
};

class Food
{
private:
	COORD FoodsCoord;
	Snake* pSnake; // ”казатель будет присвоен, поэтому в деструкторе не нужно использовать delete

	bool unique();
public:
	Food(Snake* _pSnake);
	void GenerateFood();
	void ShowFood();
	COORD GetCoord() { return FoodsCoord; }
};

class GameSnake
{
private:
	Area area;
	Snake snake;
	Food food;
	short direction;
	short SizeNeeded;
	short FoodsLeft;

	void Show();
	void ShowInfo();
	void Hide() { system("cls"); }
	short GameStatus();
	void Actions();
	void EndGame(const short code);
public:
	GameSnake(short _goal, short _w, short _h);
	void LaunchGame();
};
