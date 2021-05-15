#ifndef __MYCOORDXY_H__
#define __MYCOORDXY_H__

struct MyCoordXY 
{
	int x, y;
	MyCoordXY(int _x = 0, int _y = 0) : x(_x), y(_y) {};
	MyCoordXY& operator +=(const MyCoordXY& change);
};

MyCoordXY operator +(const MyCoordXY& op1, const MyCoordXY& op2);
bool operator ==(const MyCoordXY& op1, const MyCoordXY& op2);

#endif __MYCOORDXY_H__
