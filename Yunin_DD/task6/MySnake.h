#ifndef __MYSNAKE_H__
#define __MYSNAKE_H__

#include <vector>

#include "MyCoordXY.h"
#include "MyDisplay.h"

using namespace std;

typedef vector<MyCoordXY> CoordVector;

class MySnake
{
private:
	CoordVector snake;
	int drawn;
public:
	MySnake() { drawn = 0; }
	void RestartSnake(MyCoordXY star_pos);
	void DrawSnake(MyDisplay& console);
	void GrowSnake(int growsize);
	MyCoordXY LastElement();
	MyCoordXY Head();
	bool IntoSnake(MyCoordXY& pos);
	void MoveSnake(MyCoordXY& delta, MyDisplay& console);
	int Size() { return snake.size(); }
};
#endif __MYSNAKE_H__
