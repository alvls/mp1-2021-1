#include "Event.h"


unsigned int daysInMounth[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void Event::SetNameFilm(string otherName)
{
	nameFilm = otherName;
}

void Event::SetTimeEvent(Time otherTime)
{
	timeSession = otherTime;
}

void Event::SetTimeEvent(int hours, int minutes)
{
	timeSession.hours = hours;
	timeSession.minutes = minutes;
}

string Event::GetNameFilm()
{
	return nameFilm;
}

Time Event::GetTimeEvent()
{
	return timeSession;
}

ostream& operator<<(ostream& out, const Date& date)
{
	if (date.mounth < 10)
	{
		return out << "День:" << date.day << " Месяц:" << "0" <<date.mounth;
	}
	else
		return out << "День:" << date.day << " Месяц:" <<  date.mounth;
}

ostream& operator<<(ostream& out, const Time& time)
{
	if (time.minutes == 0)
	{
		return out << time.hours << ":" << time.minutes << "0";
	}
	return out << time.hours << ":" << time.minutes;
}

ostream& operator<<(ostream& out, const Event& otherEvent)
{
	return out << "Название фильма:" << otherEvent.nameFilm << endl << "Время:" << otherEvent.timeSession << endl;
}

Time Time::operator+(Time otherTime)
{
	Time temp(*this);
	temp.hours += otherTime.hours;
	temp.minutes += otherTime.minutes;
	if (temp.minutes == 60)
	{ 
		temp.hours++;
		temp.minutes = 0;
	}
		
	return temp;
}

Time Time::operator*(int value)
{
	Time temp(*this);
	temp.hours *= value;
	temp.minutes *= value;
	while (temp.minutes / 60 != 0)
	{
		temp.hours++;
		temp.minutes -= 60;
	}
	return temp;
}

Date Date::operator+(int otherDay)
{
	Date temp;
	temp.day = this->day;
	temp.mounth = this->mounth;
	temp.day += otherDay;
	if (temp.day > daysInMounth[temp.mounth])
	{
		temp.mounth += 1;
		if (temp.mounth == 12)
		{
			temp.mounth = 0;
			temp.day -= daysInMounth[11];
		}
		temp.day -= daysInMounth[temp.mounth - 1];
	}
	return temp;
}
