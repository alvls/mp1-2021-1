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
	Area* pArea;

	void ShowBody();
	void ShowHead();
public:
	Snake(Area* _pArea);
	void ShowSnake();
	size_t GetSize() { return snake.size(); }
	COORD GetHead() { return snake[0]; }
	Area* GetpArea() { return pArea; }
	void ChangePosition(const short x, const short y);
	void AddLastUnit();
	void Move(const short code);
	bool CrossedItself();
	vector<COORD> GetSnake() { return snake; }
	~Snake();
};

class Food
{
private:
	COORD FoodsCoord;
	Snake* pSnake;

	bool unique();
public:
	Food(Snake* _pSnake);
	void GenerateFood();
	void ShowFood();
	COORD GetCoord() { return FoodsCoord; }
	~Food();
};

class GameSnake
{
private:
	Area area;
	Snake snake;
	Food food;
	short direction;
	short SizeNeeded;
	short FruitsLeft;

	void Show();
	void ShowInfo();
	void Hide() { system("cls"); }
	short GameStatus();
	void Actions();
	void EndGame(const int code);
public:
	GameSnake(short _goal, short _w, short _h);
	void LaunchGame();
};
