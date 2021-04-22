#include "TicketOffice.h"
#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "ru");
	//заполнение кинотеатра
	Cinema myCinema;
	Cinema* dada = &myCinema;
	myCinema.AddHall(0, 400, 200);
	vector <Day> shedule;
	vector <Session> sessionssss;
	vector <Event> ev;
	vector <Event> pa;
	Time tempS;
	tempS.hours = 12;
	tempS.minutes = 30;
	Event temp("Сумерки", tempS);
	ev.push_back(temp);
	Session papa(temp);
	temp.SetNameFilm("Гангстеры");
	ev.push_back(temp);
	sessionssss.push_back(papa);
	myCinema.SetSheduleInDay(2, ev);
	myCinema.SetSessionsInHall(1, sessionssss);
	cout << myCinema.CheckAvailability(3, false, 1, papa);
	pa = myCinema.GetEventsInDay(2);
	cout << pa[0].GetNameFilm();
	cout << pa[1].GetNameFilm();

	TicketOffice a(dada);
	
	system("Pause");
}