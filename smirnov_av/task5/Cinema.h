#pragma once
#include <vector>
#include "Day.h"
#include "Session.h"
#include <string>
#include <iostream>
using namespace std;

#define COUNTHALLS 3
#define SESSIONSINHALLINDAY 8


struct hall
{
	int vipPrice;
	int defaultPrice;
};

class Cinema
{
private:
	vector<Day> sheduleDay; //расписание на 30 дней без информации по залу                       
	vector <vector <Session>> sessions; // все сеансы в пределах 3 дней с информацией по залу       
	vector <int> savedDays; //хранит дни, которые сохранены в sessions
	vector<hall> halls; //информация о ценах на билеты в залах  
	int FindIndexSession(int hallNumber, Session& neededSession);
	void SetFirstDaySession(Date _date);
	void SetSecondtDaySession(Date _date);
	void SetThirdDaySession(Date _date);
public:
	Cinema()
	{
		sheduleDay.resize(30);
		sessions.resize(COUNTHALLS);
		savedDays.resize(3);
		halls.resize(COUNTHALLS);
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			sessions[i].resize(SESSIONSINHALLINDAY * 3);
		}
	}

	//проверка доступности данного количества мест в данной зоне на данном сеансе
	bool CheckAvailability(int countPlaces, bool isVip, int hallNumber, Session neededSession);
	//добавить зал
	void AddHall(int numberHall, int _vipPrice = 0, int _defaultPrice = 0 );
	//установить цену в зале
	void SetDataHall(int numberHall, int _vipPrice, int _defaultPrice);
	//занять места на данном сеансе
	void SetPlace(int countPlaces,bool _isVip, int hallNumber, Session neededSession, vector<int>& settedSeats);
	//установить сеансы в данном холе
	void SetSessionsInHall(int hall, vector <Session> otherSessions);
	//установить расписание на день
	void SetSheduleInDay(int day,vector <Event> events);
	//получить цену билетов в данном зале
	void GetPriceFromHall(int hall, int& defaultPrice, int& vipPrice);
	//получить все события в данный день
	vector<Event> GetEventsInDay(int day);
	//отмена посадочных мест в последней транзакции
	void BackUpSeats(int hallNumber, Session neededSession, vector<int>& settedSeats);
	//обновление расписания в зависимости от введенной даты пользователем
	void UpdateSession(Date _date);
	//показать расписание на 3 дня с залами 
	void ShowSessions(Date _date);

};

