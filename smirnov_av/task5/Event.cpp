#include "Event.h"

void Event::SetNameFilm(string otherName)
{
	nameFilm = otherName;
}

void Event::SetTimeSession(Time otherTime)
{
	timeSession = otherTime;
}

string Event::GetNameFilm()
{
	return nameFilm;
}

Time Event::GetTimeSession()
{
	return timeSession;
}


