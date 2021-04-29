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
	vector<COORD> snake;
	Area* pArea;

	void ShowBody();
	void ShowHead();
public:
	Snake(Area* _pArea);
	void ShowSnake();
	size_t GetSize() { return snake.size(); }
	COORD GetHead() { return snake[0]; }
	void ChangeForm(const short x, const short y, const bool AddUnit = false);
	void Move(const short code);
	bool CrossedItself();
	vector<COORD> GetSnake() { return snake; }
	~Snake();
};

class Food
{
private:
	COORD FoodsCoord;
	Area* pArea;
	Snake* pSnake;

	bool unique();
public:
	Food(Area* _pArea, Snake* _pSnake);
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
	short goal;

	void Show();
	void ShowGoal();
	void Hide() { system("cls"); }
	short GameStatus();
	void Actions();
public:
	GameSnake(short _goal, short _w, short _h);
	void LaunchGame();
};
