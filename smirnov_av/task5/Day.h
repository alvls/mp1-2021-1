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

	//�������
	vector<Event> GetEvents();
	Event GetEvent(int index);
	//�������
	void SetEventInd(int index, Event _event);
	void SetEventBack(Event _event);

	friend class Cinema; 

};

