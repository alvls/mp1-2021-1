#include "MySnake.h"

const char SNAKE_TAIL = 'o';
const char SNAKE_HEAD = 'O';

void MySnake::RestartSnake(MyCoordXY star_pos)
{
	snake.clear();
	snake.reserve(1000);
	for (int i = 0; i < 5; i++)
	{
		snake.push_back(star_pos);
	}
	for (int i = 1; i < 5; i++)
	{
		snake[i].x++;
	}	
}

void MySnake::DrawSnake(MyDisplay& console)
{
	console.SetColor(9, 0);
	console.GoAndDrawSymbol(snake[0].x, snake[0].y, SNAKE_HEAD);
	console.SetColor(6, 0);
	for (int i = 1; i < snake.size(); i++)
	{
		console.GoAndDrawSymbol(snake[i].x, snake[i].y, SNAKE_TAIL);
	}
	drawn = snake.size();
}

void MySnake::GrowSnake(int growsize)
{
	MyCoordXY temp = LastElement();
	for (int i = 0; i < growsize; i++)
	{
		snake.push_back(temp);
	}
}

MyCoordXY MySnake::LastElement()
{
	int size = snake.size();
	size--;
	return snake[size];
}

bool MySnake::IntoSnake(MyCoordXY& pos)
{
	for (unsigned int i = 0; i < snake.size(); i++)
	{
		if (snake[i].x == pos.x && snake[i].y == pos.y)
		{
			return true;
		}
	}
	return false;
}

void MySnake::MoveSnake(MyCoordXY& delta, MyDisplay& console)
{
	typedef vector<MyCoordXY> CoordVectortemp;
	CoordVectortemp tmpvector;
	int size = snake.size();
	tmpvector.reserve(size);
	for (int i = 0; i < size; i++)
	{
		tmpvector.push_back(snake[i]);
	}
	if (drawn == snake.size())
	{
		console.GoAndDrawSymbol(snake[size - 1].x, snake[size - 1].y, ' ');
	}
	else
	{
		drawn++;
	}
	snake[0] += delta;
	for (int i = 1; i < size; i++)
	{
		snake[i] = tmpvector[i - 1];
	}
	console.SetColor(9, 0);
	console.GoAndDrawSymbol(snake[0].x, snake[0].y, SNAKE_HEAD);
	console.SetColor(6, 0);
	console.GoAndDrawSymbol(snake[1].x, snake[1].y, SNAKE_TAIL);
}

MyCoordXY MySnake::Head()
{
	return snake[0];
}
