#include "TicketOffice.h"
#include <iostream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

string Films[] = {"Пираты Карибского моря 1","Пираты Карибского моря 2" , "Властелин колец 1","Властелин колец 2", "Властелин колец 3", "Гарри Поттер 1",
"Гарри Поттер 2", "Гарри Поттер 3" , "Гарри Поттер 4" , "Гарри Поттер 5" ,"Гарри Поттер 6" , "Гарри Поттер 7" , "Пираты Карибского моря 3",
"Пираты Карибского моря 4" , "Властелин колец 2", "Властелин колец 3" };

void RandomEventsInDay(vector<Event>& eventsInDay)
{
	
	Event temp;
	Time delay = { 1,30 };
	Time startWork = { 10, 30 };
	int filledEvents = 0;
	for (size_t i = 0; i < COUNTHALLS * SESSIONSINHALLINDAY; i++)
	{
		temp.SetNameFilm(Films[rand() % 15]);
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

Time GetCurrentTime()
{
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	Time result = { 0 , 0 };
	result.hours = timeinfo->tm_hour;
	result.minutes = timeinfo->tm_min;
	return result;
}

Date GetCurrentDate()
{
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	Date result;
	result.day = timeinfo->tm_mday;
	result.mounth = timeinfo->tm_mon;
	return result;
}

void main()
{
	setlocale(LC_ALL, "ru");
	vector<Event> eventsInDay;
	Cinema myCinema;
	//создаем холлы 
	myCinema.SetDataHall(0, 400, 200);
	myCinema.SetDataHall(1, 500, 250);
	myCinema.SetDataHall(2, 300, 150);
	//заполняем расписание 
	for (size_t i = 0; i < 30; i++)
	{
		RandomEventsInDay(eventsInDay);
		myCinema.SetSheduleInDay(i,eventsInDay);
		eventsInDay.clear();
	}
	try
	{
		TicketOffice ticketOffice;
		ticketOffice.SetCinema(&myCinema);
		//используем хардкод, а не системное время, чтобы не зависило от даты проверки работы 
		Time currentTime = { 19, 19 };
		Date currentDate = { 26,04 };
		myCinema.UpdateSession(currentDate); //обновили расписание доступных сеансов в зависимости от даты 
		myCinema.ShowSessions(currentDate); // можно посмотреть все доступные сессии в пределах 3 дней от текущей даты 
		Date dateSession = { 27, 4 };
		Time timeSession = { 13,30 };
		bool _isVip = false;
		int _countSeats = 3;
		int hall = 2;
		ticketOffice.SetDataClient(dateSession, timeSession, "Пираты Карибского моря 3", hall, _isVip, _countSeats);
		//проверяем доступность
		ticketOffice.CheckAvailability();
		//резервируем 
		ticketOffice.Reserve(currentDate, currentTime);
		vector<Ticket>tickets(4);
		//получаем билеты 
		tickets = ticketOffice.GetTickets();
		//вывод билетов 
		for (size_t i = 0; i < tickets.size(); i++)
		{
			cout << tickets[i] << endl;
		}
		cout << "Итоговая цена: " << ticketOffice.GetTotalPrice() << "р"<< endl;
		
		//новый клиент
		dateSession = { 28, 4 };
		timeSession = { 19,30 };
		_isVip = true;
		_countSeats = 2;
		hall = 1;
		ticketOffice.SetDataClient(dateSession, timeSession, "Гарри Поттер 4", hall, _isVip, _countSeats);
		ticketOffice.CheckAvailability();
		ticketOffice.Reserve(currentDate, currentTime);
		//отменяем билеты, зарезервинованные выше
		ticketOffice.CancellationOrder();
	}
	catch (const string& ex)
	{
		cout << ex << endl;
	}
	
	system("Pause");
}