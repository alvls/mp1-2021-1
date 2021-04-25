#include "TicketOffice.h"
#include <iostream>
#include <string>
using namespace std;

string Films[] = {"Пираты Карибского Моря 1","Пираты Карибского Моря 2" , "Властелин колец", "Гарри Поттер 1", "Гарри Поттер 2", "Гарри Поттер 3" , "Гарри Поттер 4" , "Гарри Поттер 5" ,
"Гарри Поттер 6" , "Гарри Поттер 7" , "Пираты Карибского Моря 3", "Пираты Карибского Моря 4"};

void RandomEventsInDay(vector<Event>& eventsInDay)
{
	
	Event temp;
	Time delay = { 1,30 };
	Time startWork = { 10, 30 };
	int filledEvents = 0;
	for (size_t i = 0; i < COUNTHALLS * SESSIONSINHALLINDAY; i++)
	{
		temp.SetNameFilm(Films[rand() % 12]);
		if (filledEvents == SESSIONSINHALLINDAY - 1)
		{
			temp.SetTimeEvent(startWork + delay * filledEvents);
			filledEvents = 0;

		}
		else
		{
			temp.SetTimeEvent(startWork + delay * filledEvents);
			filledEvents++;
		}
		eventsInDay.push_back(temp);
	}
}

void main()
{
	setlocale(LC_ALL, "ru");
	vector<Event> eventsInDay;
	Cinema myCinema;
	
	Date date = { 10,4 };
	for (size_t i = 0; i < 30; i++)
	{
		RandomEventsInDay(eventsInDay);
		myCinema.SetSheduleInDay(i,eventsInDay);
	}
	myCinema.UpdateSession(date);
	myCinema.ShowSessions(date);
	date = { 11, 4 };
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ПОСЛЕ ИЗЕНЕНИЯ ДАТЫ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	myCinema.UpdateSession(date);
	myCinema.ShowSessions(date);
	system("Pause");
}