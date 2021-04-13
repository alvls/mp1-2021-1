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
	Date dateSession;
	Time timeSession;
public:
	Event()
	{
		nameFilm = "unknown";
		dateSession.day = 0;
		dateSession.mounth = 0;
		timeSession.hours = 0;
		timeSession.minutes = 0;
	}

	Event(string _nameFilm, Date _dateSession, Time timeSession) : nameFilm(_nameFilm), dateSession(_dateSession), timeSession(timeSession)
	{
		
	}

	//сеттеры
	void SetNameFilm(string otherName);
	void SetDateSession(Date otherDate);
	void SetTimeSession(Time otherTime);
	
	//геттеры
	string GetNameFilm();
	Date GetDateSession();
	Time GetTimeSession();	

	//операторы
	bool operator==(Event otherEvent)
	{
		if (nameFilm == otherEvent.nameFilm && dateSession == otherEvent.dateSession && timeSession == otherEvent.timeSession)
		{
			return true;
		}
		return false;
	}
};

