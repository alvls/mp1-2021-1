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
	dataFromClient.date = _date;
	dataFromClient.dataEvent.SetNameFilm(_nameFilm);
	dataFromClient.dataEvent.SetTimeEvent(_timeSession);
	dataFromClient.hallNumber = _hallNumber;
	dataFromClient.isVip = _isVip;
	dataFromClient.countSeats = _countSeats;
	isInitilize = true;
}

bool TicketOffice::CheckAvailability()
{
	CheckInitilize();
	return cinema->CheckAvailability(dataFromClient.countSeats, dataFromClient.isVip, dataFromClient.hallNumber, dataFromClient.dataEvent);		
}

void TicketOffice::Reserve()
{
	CheckInitilize();
	cinema->SetPlace(dataFromClient.countSeats, dataFromClient.isVip, dataFromClient.hallNumber, dataFromClient.dataEvent, historySeats);
}

int TicketOffice::GetTotalPrice()
{
	if (dataFromClient.dataEvent.GetTimeEvent().hours < MORNINGHOURS)
		return MORNINGPRICE * this->GetPrice(dataFromClient.hallNumber, dataFromClient.countSeats, dataFromClient.isVip);
	else if (dataFromClient.dataEvent.GetTimeEvent().hours >= EVENINGHOURS)
		return EVENINGPRICE * this->GetPrice(dataFromClient.hallNumber, dataFromClient.countSeats, dataFromClient.isVip);
	else
		return this->GetPrice(dataFromClient.hallNumber, dataFromClient.countSeats, dataFromClient.isVip);
}

void TicketOffice::CancellationOrder()
{
	CheckInitilize();
	cinema->BackUpSeats(dataFromClient.hallNumber, dataFromClient.dataEvent, historySeats);
}

vector<ticket> TicketOffice::GetTickets()
{
	vector <ticket> results(dataFromClient.countSeats);
	for (size_t i = 0; i < dataFromClient.countSeats; i++)
	{
		results[i].dateSession = dataFromClient.date;
		results[i].hallNumber = dataFromClient.hallNumber;
		results[i].nameFilm = dataFromClient.dataEvent.GetNameFilm();
		if (historySeats[i] != 0)
		{
			results[i].rowNumber = historySeats[i] / 10;;
			results[i].seat = historySeats[i] % 10;
		}
		results[i].timeEvent = dataFromClient.dataEvent.GetTimeEvent();		
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

std::ostream& operator<<(std::ostream& out, const ticket& _ticket)
{
	return out << "Дата:" << _ticket.dateSession << endl << "Время:" << _ticket.timeEvent << endl << "Название фильма:" << _ticket.nameFilm << endl << "Зал:" << _ticket.hallNumber << endl
		<< "Ряд:" << _ticket.rowNumber << endl << "Место:" << _ticket.seat << endl;
}
