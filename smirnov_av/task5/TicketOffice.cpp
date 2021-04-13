#include "TicketOffice.h"

void TicketOffice::GetDataBuyer(Date _date, Time _timeSession, string _nameFilm, int _hallNumber, bool _isVip, int _countSeats)
{
	dataFromClient.date = _date;
	dataFromClient.timeSession = _timeSession;
	dataFromClient.nameFilm = _nameFilm;
	dataFromClient.hallNumber = _hallNumber;
	dataFromClient.isVip = _isVip;
	dataFromClient.countSeats = _countSeats;
	isInitilize = true;
}
