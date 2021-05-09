#include "TicketOffice.h"

int TicketOffice::GetPrice(int hall, int _countSeats, bool _isVip)
{
	int defaultPrice;
	int vipPrice;
	cinema->GetPriceFromHall(hall, defaultPrice, vipPrice);
	if (_isVip)
		return vipPrice * _countSeats;
	else
		return defaultPrice * _countSeats;
}

void TicketOffice::SetCinema(Cinema* otherCinema)
{
	cinema = otherCinema;
}

void TicketOffice::SetDataClient(Date _date, Time _timeSession, string _nameFilm, int _hallNumber, bool _isVip, int _countSeats)
{
	Event temp;
	temp.SetNameFilm(_nameFilm);
	temp.SetTimeEvent(_timeSession);
	dataFromClient.date = _date;
	dataFromClient.neededSession.SetEvent(temp);
	dataFromClient.neededSession.SetDate(_date);
	dataFromClient.hallNumber = _hallNumber;
	dataFromClient.isVip = _isVip;
	dataFromClient.countSeats = _countSeats;
	isInitilize = true;
}

bool TicketOffice::CheckAvailability()
{
	CheckInitilize();
	return cinema->CheckAvailability(dataFromClient.countSeats, dataFromClient.isVip, dataFromClient.hallNumber, dataFromClient.neededSession);		
}

void TicketOffice::Reserve(Date currnetDate, Time currentTime)
{
	CheckInitilize();
	CheckGetLate(currnetDate,currentTime);
	if (dataFromClient.date >= currnetDate + 3)
		throw string("Билеты на сеансы можно заказывать в пределах трех дней!");
	cinema->SetPlace(dataFromClient.countSeats, dataFromClient.isVip, dataFromClient.hallNumber, dataFromClient.neededSession, historySeats);
}

int TicketOffice::GetTotalPrice()
{
	if (dataFromClient.neededSession.GetEvent().GetTimeEvent().hours < MORNINGHOURS)
		return MORNINGPRICE * this->GetPrice(dataFromClient.hallNumber, dataFromClient.countSeats, dataFromClient.isVip);
	else if (dataFromClient.neededSession.GetEvent().GetTimeEvent().hours >= EVENINGHOURS)
		return EVENINGPRICE * this->GetPrice(dataFromClient.hallNumber, dataFromClient.countSeats, dataFromClient.isVip);
	else
		return this->GetPrice(dataFromClient.hallNumber, dataFromClient.countSeats, dataFromClient.isVip);
}

void TicketOffice::CancellationOrder()
{
	CheckInitilize();
	cinema->BackUpSeats(dataFromClient.hallNumber, dataFromClient.neededSession, historySeats);
	isInitilize = false;
}

vector<Ticket> TicketOffice::GetTickets()
{
	CheckInitilize();
	vector <Ticket> results(dataFromClient.countSeats);
	for (size_t i = 0; i < dataFromClient.countSeats; i++)
	{
		results[i].dateSession = dataFromClient.date;
		results[i].hallNumber = dataFromClient.hallNumber;
		results[i].nameFilm = dataFromClient.neededSession.GetEvent().GetNameFilm();
		if (historySeats[i] != 0)
		{
			results[i].rowNumber = historySeats[i] / 10;;
			results[i].seat = historySeats[i] % 10;
		}
		results[i].timeEvent = dataFromClient.neededSession.GetEvent().GetTimeEvent();
	}
	historySeats.clear();
	isInitilize = false;
	return results;
}

void TicketOffice::CheckInitilize()
{
	if (!isInitilize)
		throw string("Нет информации о клиенте!");
}

void TicketOffice::CheckGetLate(Date currentDate, Time currentTime )
{
	CheckInitilize();
	Time delay = { 0, 10};
	if (currentDate == dataFromClient.date)
	{
		if (currentTime <= dataFromClient.neededSession.GetEvent().GetTimeEvent() + delay)
			return;
		else
			throw string("Сеанс начался больше, чем 10 минут назад, вы не можете попасть на сеанс!");
	}	
}

std::ostream& operator<<(std::ostream& out, const Ticket& _ticket)
{
	return out << "Дата:" << _ticket.dateSession << endl << "Время:" << _ticket.timeEvent << endl << "Название фильма:" << _ticket.nameFilm << endl << "Зал:" << _ticket.hallNumber << endl
		<< "Ряд:" << _ticket.rowNumber << endl << "Место:" << _ticket.seat << endl;
}
