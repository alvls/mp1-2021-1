#pragma once
#include "Cinema.h"
#include <vector>


struct ticket
{

};

struct DataBuyer
{
	Date date;
	Time timeSession;
	string nameFilm;
	int hallNumber;
	bool isVip;
	int countSeats;
};

struct hall
{
	int vipPrice;
	int defaultPrice;
};

class TicketOffice
{
private:
	vector<hall> halls; //?
	Cinema* cinema;
	//vector <DataBuyer> arrayInformations;
	DataBuyer dataFromClient;
	bool isInitilize;
	bool isEnd;
public:
	TicketOffice(Cinema* otherCinema)
	{
		cinema = otherCinema;
	}

	void GetDataBuyer(Date _date, Time _timeSession, string _nameFilm, int _hallNumber, bool _isVip, int _countSeats);
	bool CheckAvailability();
	void Reserve();
	int GetTotalPrice();
	void CancellationOrder();
	vector<ticket> GetTickets();
	void SetHallDefaultPrice(int numberHall, int price);
	
};

