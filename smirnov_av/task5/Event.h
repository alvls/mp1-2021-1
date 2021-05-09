#pragma once
#include <string>
#include <iostream>
using namespace std;

extern unsigned int daysInMounth[12];

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

	bool operator >=(Date otherDate);
	Date operator+(int otherDay);	
};

ostream& operator << (ostream& out, const Date& date);

struct Time
{
	int hours;
	int minutes;

	bool operator==(Time otherTime)
	{
		if (this->hours == otherTime.hours && (this->minutes == otherTime.minutes))
		{
			return true;
		}
		return false;
	}
	Time operator+(Time otherTime);
	Time operator*(int value);
	bool operator<=(Time otherTime);
	bool CheckLate(Time otherTime);
};

ostream& operator << (ostream& out, const Time& time);

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

	//�������
	void SetNameFilm(string otherName);
	void SetTimeEvent(Time otherTime);
	void SetTimeEvent(int hours, int minutes);
	//�������
	string GetNameFilm();
	Time GetTimeEvent();	

	//���������
	bool operator==(Event otherEvent)
	{
		if (nameFilm == otherEvent.nameFilm && timeSession == otherEvent.timeSession)
		{
			return true;
		}
		return false;
	}
	friend ostream& operator<<(ostream& out, const Event& otherEvent);
};


