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

void Cinema::SetPlace(int countPlaces, bool _isVip, int hallNumber, Event neededEvent, vector<int>& settedSeats)
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

void Cinema::GetPriceFromHall(int hall, int& defaultPrice, int& vipPrice)
{
	defaultPrice = halls[hall].defaultPrice;
	vipPrice = halls[hall].vipPrice;
}

vector<Event> Cinema::GetEventsInDay(int day)
{
	return sheduleDay[day].GetEvents();
}

void Cinema::BackUpSeats(int hallNumber, Event neededEvent, vector<int>& settedSeats)
{
	Session tempSession(neededEvent);
	int index = FindIndexSession(hallNumber, tempSession);
	sessions[hallNumber][index].BackUpPlaces(settedSeats);
}

void Cinema::UpdateSession(Date _date)
{
	int day = _date.day;
	Date temp(_date);
	if (savedDays.empty()) //можно убрать 
	{
		FillSessions(temp);
		savedDays[0] = temp.day;

		
		FillSessions(temp + 1);
		savedDays[1] = temp.day;

	
		FillSessions(temp + 2);
		savedDays[2] = temp.day;
	}

	if (day == savedDays[0]) //обновление не нужно
		return;
	else if (day == savedDays[1])		//нужно обновить 1 день 
	{
		savedDays[0] = savedDays[1];
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			for (size_t j = 0; j < SESSIONSINHALLINDAY; j++)
			{
				sessions[i][j] = sessions[i][j + SESSIONSINHALLINDAY];
				sessions[i][j].SetDay(_date);
			}
		}
		
		savedDays[1] = savedDays[2];
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			for (size_t j = SESSIONSINHALLINDAY; j < 2 * SESSIONSINHALLINDAY; j++)
			{
				sessions[i][j] = sessions[i][j + SESSIONSINHALLINDAY];
				sessions[i][j].SetDay(_date + 1);
			}
		}

		FillSessions(_date + 2);
		savedDays[2] = temp.day + 1;
	}
	else if (day == savedDays[2])
	{
		savedDays[0] = savedDays[2];
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			for (size_t j = 0; j < SESSIONSINHALLINDAY; j++)
			{
				sessions[i][j] = sessions[i][j + 2 * SESSIONSINHALLINDAY]; 
				sessions[i][j].SetDay(_date);
			}
		}
	}
	else
	{
		FillSessions(temp);
		savedDays[0] = temp.day;

		
		FillSessions(temp + 1);
		savedDays[1] = temp.day + 1;

		FillSessions(temp + 2);
		savedDays[2] = temp.day + 2;
	}
}

//считаем, что в массиве расписания при составлении массива
void Cinema::FillSessions(Date _date)
{

	//заполнение первого зала в _date.day день 
	for (size_t i = 0; i < SESSIONSINHALLINDAY ; i++)
	{
		Session temp(sheduleDay[_date.day].eventsInThisDay[i]);
		sessions[0].push_back(temp);
		sessions[0][sessions[0].size() - 1].SetDay(_date);
	}
	//заполнение второго зала _date.day день 
	for (size_t i = 0; i < SESSIONSINHALLINDAY; i++)
	{
		Session temp(sheduleDay[_date.day].eventsInThisDay[i+SESSIONSINHALLINDAY]);
		sessions[1].push_back(temp);
		sessions[1][sessions[1].size() - 1].SetDay(_date);
	}
	//заполнение третьего зала в _date.day день 
	for (size_t i = 0; i < SESSIONSINHALLINDAY; i++)
	{
		Session temp(sheduleDay[_date.day].eventsInThisDay[i + 2 * SESSIONSINHALLINDAY]);
		sessions[2].push_back(temp);
		sessions[2][sessions[2].size() - 1].SetDay(_date);
	}

}

void Cinema::ShowSessions(Date _date)
{
	cout << _date << endl;
	for (size_t i = 0; i < COUNTHALLS; i++)
	{
		for (size_t j = 0; j < SESSIONSINHALLINDAY; j++)
		{
			cout << sessions[i][j];
		}
	}
	cout << _date + 1 << endl;
	for (size_t i = 0; i < COUNTHALLS; i++)
	{
		for (size_t j = SESSIONSINHALLINDAY; j < 2 * SESSIONSINHALLINDAY; j++)
		{
			cout << sessions[i][j];
		}
	}
	cout << _date + 2 << endl;
	for (size_t i = 0; i < COUNTHALLS; i++)
	{
		for (size_t j = 2 * SESSIONSINHALLINDAY; j < 3 * SESSIONSINHALLINDAY; j++)
		{
			cout << sessions[i][j];
		}
	}
}
