#include "TicketOffice.h"

void TicketOffice::SetDataBuyer(Date _date, Time _timeSession, string _nameFilm, int _hallNumber, bool _isVip, int _countSeats)
{
	dataFromClient.date = _date;
	dataFromClient.dataEvent.SetNameFilm(_nameFilm);
	dataFromClient.dataEvent.SetTimeSession(_timeSession);
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

void TicketOffice::CheckInitilize()
{
	if (!isInitilize)
		throw string("Нет информации о клиенте!");
}
