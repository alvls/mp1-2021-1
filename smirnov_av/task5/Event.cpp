#include "Event.h"

void Event::SetNameFilm(string otherName)
{
	nameFilm = otherName;
}

void Event::SetDateSession(Date otherDate)
{
	dateSession = otherDate;
}

void Event::SetTimeSession(Time otherTime)
{
	timeSession = otherTime;
}

string Event::GetNameFilm()
{
	return nameFilm;
}

Date Event::GetDateSession()
{
	return dateSession;
}

Time Event::GetTimeSession()
{
	return timeSession;
}


