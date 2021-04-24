#include "TicketOffice.h"
#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "ru");
	//заполнение кинотеатра
	vector <ticket> tickets;
	Time jda = { 19,30 };
	Date date = { 12,3 };
	Cinema myCinema;
	Cinema* dada = &myCinema;
	TicketOffice ticketOffice;
	ticketOffice.SetCinema(dada);
	myCinema.AddHall(0, 400, 200);
	Event temp;
	temp.SetNameFilm("HELP");
	temp.SetTimeEvent(12, 0);
	Session a;
	a.SetEvent(temp);
	Session b;
	temp.SetNameFilm("сумерки");
	temp.SetTimeEvent(19, 30);
	b.SetEvent(temp);
	
	vector <Session> sessions;
	sessions.push_back(a);
	sessions.push_back(b);

	myCinema.SetSessionsInHall(0, sessions);


	ticketOffice.SetDataClient(date, jda, "сумерки", 0, false, 3);
	cout <<"Проверка на доступность:" << ticketOffice.CheckAvailability() << endl;
	ticketOffice.Reserve();
	tickets = ticketOffice.GetTickets();
	cout << endl;
	for (size_t i = 0; i < tickets.size(); i++)
	{
		cout << tickets[i] << endl;
	}
	cout << "totalPrice = " << ticketOffice.GetTotalPrice();
	system("Pause");
}