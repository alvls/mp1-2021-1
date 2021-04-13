#pragma once
#include "Event.h"
#include <vector>

#define RAWS 10
#define SEATSINRAWS 10
struct hall
{
	int numberHall;
	int vipPrice;
	int defaultPrice;
};
class Session
{
private:
	Event dataAboutEvent;
	vector <vector<bool>> places;
public:
	Session(const Event& otherData)
	{
		dataAboutEvent = otherData;
		places.resize(RAWS);
		for (size_t i = 0; i < places.size(); i++)
		{
			places[i].resize(10);
		}
	}

	vector <vector<bool>> GetPlaces();

	bool operator==(Session otherSession)
	{
		if (dataAboutEvent == otherSession.dataAboutEvent)
			return true;
		return false;
	}


};

