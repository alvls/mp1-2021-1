
#include "all.h"

//Конструкторы

Count::Count(int _steps)
{
	LeftBound.hour = 0;
	RightBound.hour = 1;
	LeftBound.minutes = 0;
	RightBound.minutes = 1;
	steps = _steps;
}

Count::Count(Time _LeftBound, Time _RightBound, int _steps)
{
	LeftBound = _LeftBound;
	RightBound = _RightBound;
	steps = _steps;
}

Count::Count(const Count& other)
{
	LeftBound = other.LeftBound;
	RightBound = other.RightBound;
	steps = other.steps;
}

//Геттеры

vector<Time> Count::GetTimeBounds()
{
	vector<Time> tmpvec(2);
	tmpvec.push_back(LeftBound);
	tmpvec.push_back(RightBound);
	return tmpvec;
}

//Операторы

ostream& operator<<(ostream& os, const Count& count)
{
	os << count.LeftBound.hour << " " << count.LeftBound.minutes << " " << count.RightBound.hour << " " << count.RightBound.minutes << " " << count.steps;
	return os;
}

istream& operator>>(istream& is, Count& count)
{
	is >> count.LeftBound.hour;
	is >> count.LeftBound.minutes;
	is >> count.RightBound.hour;
	is >> count.RightBound.minutes;
	is >> count.steps;
	return is;
}

Count& Count::operator= (const Count& other)
{
	if (this == &other)
		return *this;
	LeftBound = other.LeftBound;
	RightBound = other.RightBound;
	steps = other.steps;
	return *this;
}
