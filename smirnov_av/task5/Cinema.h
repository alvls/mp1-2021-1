#pragma once
#include <vector>
#include "Day.h"
#include "Session.h"
#include <string>
#include <iostream>
using namespace std;
#define COUNTHALLS 3
#define SESSIONSINHALLINDAY 5

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
	vector<hall> halls; //информаци€ о ценах на билеты в залах  
	int FindIndexSession(int hallNumber, Session& neededSession);
public:
	Cinema()
	{
		sheduleDay.resize(30);
		sessions.resize(COUNTHALLS);
	}


	//проверка доступности данного количества мест в данной зоне на данном сеансе
	bool CheckAvailability(int countPlaces, bool isVip, int hallNumber, Event neededEvent);
	//добавить зал
	void AddHall(int numberHall, int _vipPrice = 0, int _defaultPrice = 0 );
	//установить цену в зале
	void SetDataHall(int numberHall, int _vipPrice, int _defaultPrice);
	//зан€ть места на данном сеансе
	void SetPlace(int countPlaces,bool _isVip, int hallNumber, Event neededEvent, vector<int>& settedSeats);
	//установить сеансы в данном холе
	void SetSessionsInHall(int hall, vector <Session> otherSessions);
	//установить расписание на день
	void SetSheduleInDay(int day,vector <Event> events);
	//получить цену билетов в данном зале
	void GetPriceFromHall(int hall, int& defaultPrice, int& vipPrice);
	//получить все событи€ в данный день
	vector<Event> GetEventsInDay(int day);
	//отмена посадочных мест в последней транзакции
	void BackUpSeats(int hallNumber, Event neededEvent, vector<int>& settedSeats);
	//обновление расписани€ в зависимости от введенной даты пользователем
	void UpdateSession(Date _date);

	
};

