#pragma once
#include "Event.h"
#include <vector>

#define RAWS 10
#define SEATSINRAWS 10
#define VIPRAWS 2

class Session
{
private:
	Event dataAboutEvent;
	Date dateSession;
	vector <vector<bool>> places;
public:
	Session(const Event& otherData)
	{
		dataAboutEvent = otherData;
		places.resize(RAWS);
		for (size_t i = 0; i < RAWS; i++)
		{
			places[i].resize(SEATSINRAWS);
			for (size_t j = 0; j < SEATSINRAWS; j++)
			{
				places[i][j] = 0;
			}
		}
	}

	Session()
	{
		places.resize(RAWS);
		for (size_t i = 0; i < RAWS; i++)
		{
			places[i].resize(SEATSINRAWS);
			for (size_t j = 0; j < SEATSINRAWS; j++)
			{
				places[i][j] = 0;
			}
		}
	}

	~Session()
	{
	}

	void SetEvent(Event otherEvent);
	bool CheckAvailability(int _countPlaces, bool _isVip);
	void SetPlaces(int _countPlaces, bool _isVip, vector<int>& settedSeats);
	void BackUpPlaces(vector<int>& settedSeats);
	Event GetEvent();
	void SetDate(Date _otherDate);
	bool operator==(Session& otherSession)
	{
		if (dataAboutEvent == otherSession.dataAboutEvent && dateSession == otherSession.dateSession)
			return true;
		return false;
	}

	friend ostream& operator<<(ostream& out, const Session& otherSession);
};

