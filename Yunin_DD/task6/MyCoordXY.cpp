#include "MyCoordXY.h"

MyCoordXY& MyCoordXY::operator +=(const MyCoordXY& change) 
{
    x += change.x;
    y += change.y;
    return *this;
}

MyCoordXY operator +(const MyCoordXY& change1, const MyCoordXY& change2) 
{
    MyCoordXY temp;
    temp.x = change1.x + change2.x;
    temp.y = change1.y + change2.y;
    return temp;
}

bool operator ==(const MyCoordXY& change1, const MyCoordXY& change2)
{
    return change1.x == change2.x && change1.y == change2.y;
}
