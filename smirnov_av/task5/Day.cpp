#include "Day.h"

vector<Event> Day::GetEvents()
{
    return eventsInThisDay;
}

Event Day::GetEvent(int index)
{
	return eventsInThisDay[index];
}

void Day::SetEventInd(int index, Event _event)
{
	vector<Event>::const_iterator i = eventsInThisDay.begin();
	advance(i, index);
	eventsInThisDay.insert(i, _event);
}

void Day::SetEventBack(Event _event)
{
	eventsInThisDay.push_back(_event);
}
