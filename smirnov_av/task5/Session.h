#pragma once
#include <iostream>
#include <string>
using namespace std;

struct _time
{
	int hours;
	int minutes;
};

struct date
{
	int day;
	int mounth;
	int year;
};

class Session
{
private:
	date sessionDate;
	_time startSession;
	string nameFilm;
	int hallNumber;
	int regularPrice;
	int vipPrice;
public:
	Session(date _sessionDate, _time _startSession, string _nameFilm, int _hallNumber, int _regularPrice, int _vipPrice) : sessionDate(_sessionDate), startSession(_startSession), nameFilm(_nameFilm),
		hallNumber(_hallNumber), regularPrice(_regularPrice), vipPrice(_vipPrice)
	{

	}

};

