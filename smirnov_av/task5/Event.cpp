#include "Event.h"

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
	return out << date.day << " " << date.mounth;
}

ostream& operator<<(ostream& out, const Time& time)
{
	return out << time.hours << ":" << time.minutes;
}
