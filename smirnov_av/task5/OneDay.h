#pragma once
#include "Session.h"
#include <vector>
#define ROWS 10
#define PLACESINROW 10
#define COUNTHALLS 3
using namespace std;

struct hall
{
	int numberHall;
	int vipPrice;
	int defaultPrice;
	bool places[][];
};

class OneDay
{
private:
	vector<Event> sessionsPerDay;
	hall hallSession;
	bool places[COUNTHALLS][ROWS][PLACESINROW];
public:
	OneDay(vector <Event> other)
	{
		sessionsPerDay = other;
		InitializationArray();
	}

	void InitializationArray()
	{
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			for (size_t j = 0; j < ROWS; j++)
			{
				for (size_t k = 0; k < PLACESINROW; k++)
				{
					places[i][j][k] = 0;
				}
			}
		}
	}

	bool CheckAvailability(int countPlaces, int hall, )
	{

	}

	void SetSessionsInHall(int numberHall, vector <Event> other);

};

