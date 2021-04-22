#pragma once
#include "Event.h"
#include <vector>
class Day
{
private:
	vector <Event> eventsInThisDay;
public:
	Day(vector<Event> _eventsInThisDay)
	{
		eventsInThisDay = _eventsInThisDay;
	}
	Day()
	{

	}

	//геттеры
	vector<Event> GetEvents();
	
	//сеттеры
	void SetEventInd(int index, Event _event);
	void SetEventBack(Event _event);

};

