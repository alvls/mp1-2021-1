#include "Cinema.h"



int Cinema::FindIndexSession(int hallNumber, Session& neededSession)
{
	for (size_t i = 0; i < sessions[hallNumber].size(); i++)
	{
		if (sessions[hallNumber][i] == neededSession)
			return i;
		
	}
	throw string("Данного сеанса не существует!");
}

bool Cinema::CheckAvailability(int _countPlaces, bool _isVip, int _hallNumber, Event _neededSession)
{
	Session tempSession(_neededSession);
	int index = FindIndexSession(_hallNumber, tempSession);
	return sessions[_hallNumber][index].CheckAvailability(_countPlaces, _isVip);
}

void Cinema::AddHall(int numberHall, int _vipPrice, int _defaultPrice)
{
	hall tempHall;
	tempHall.vipPrice = _vipPrice;
	tempHall.defaultPrice = _defaultPrice;
	if (numberHall == halls.size())
	{
		halls.push_back(tempHall);
	}
	else
	{
		vector<hall>::const_iterator j = halls.begin();
		advance(j, numberHall);
		halls.insert(j, tempHall);
	}

}

void Cinema::SetDataHall(int numberHall, int _vipPrice, int _defaultPrice)
{
	halls[numberHall].defaultPrice = _defaultPrice;
	halls[numberHall].vipPrice = _vipPrice;
}

void Cinema::SetPlace(int countPlaces,bool _isVip, int hallNumber, Event neededEvent, vector<vector<int>>& settedSeats)
{
	Session tempSession(neededEvent);
	int index = FindIndexSession(hallNumber, tempSession);
	sessions[hallNumber][index].SetPlaces(countPlaces, _isVip, settedSeats);
}

void Cinema::SetSessionsInHall(int hall, vector<Session> otherSessions)
{
	if (hall > sessions.size())
	{
		throw string("Данного зала не существует!");
	}
	sessions[hall] = otherSessions;	
}

void Cinema::SetSheduleInDay(int day, vector<Event> events)
{
	sheduleDay[day] = events;
}

vector<Event> Cinema::GetEventsInDay(int day)
{
	return sheduleDay[day].GetEvents();
}
