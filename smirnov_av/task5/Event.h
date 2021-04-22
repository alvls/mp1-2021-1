#pragma once
#include <string>

using namespace std;

struct Date
{
	int day;
	int mounth;

	bool operator==(Date otherDate)
	{
		if (this->day == otherDate.day && this->mounth == otherDate.mounth)
			return true;
		return false;
	}
};

struct Time
{
	int hours;
	int minutes;

	bool operator==(Time otherTime)
	{
		if (this->hours == otherTime.hours && this->minutes == otherTime.minutes)
		{
			return true;
		}
		return false;
	}
};




class Event
{
private:
	string nameFilm;
	Time timeSession;
public:
	Event()
	{
		nameFilm = "unknown";
		timeSession.hours = 0;
		timeSession.minutes = 0;
	}

	Event(string _nameFilm, Time timeSession) : nameFilm(_nameFilm), timeSession(timeSession)
	{
		
	}

	//сеттеры
	void SetNameFilm(string otherName);
	void SetTimeSession(Time otherTime);
	
	//геттеры
	string GetNameFilm();
	Time GetTimeSession();	

	//операторы
	bool operator==(Event otherEvent)
	{
		if (nameFilm == otherEvent.nameFilm && timeSession == otherEvent.timeSession)
		{
			return true;
		}
		return false;
	}
};

