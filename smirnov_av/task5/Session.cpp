#include "Session.h"

void Session::SetEvent(Event otherEvent)
{
	dataAboutEvent = otherEvent;
}

bool Session::CheckAvailability(int _countPlaces, bool _isVip)
{
	int freeSeats = 0;
	if (_isVip)
	{
		for (size_t i = 0; i < VIPRAWS; i++)
		{
			for (size_t j = 0; j < SEATSINRAWS; j++)
			{
				if (places[i][j] == 0)
					freeSeats++;
				if (freeSeats = _countPlaces)
					return true;
			}
		}
	}
	else
	{
		for (size_t i = VIPRAWS; i < RAWS; i++)
		{
			for (size_t j = 0; j < SEATSINRAWS; j++)
			{
				if (places[i][j] == 0)
					freeSeats++;
				if (freeSeats = _countPlaces)
					return true;
			}
		}
	}
	return false;
}


void Session::SetPlaces(int _countPlaces, bool _isVip, vector<int>& settedSeats)
{
	if (_isVip && CheckAvailability(_countPlaces, _isVip) )
	{
		for (int i = 0; i < VIPRAWS; i++)
		{
			for (int j = 0; j < SEATSINRAWS; j++)
			{
				if (places[i][j] == 0)
				{
					places[i][j] = 1;
				
					settedSeats.push_back(i * 10 + j); //номер места
					_countPlaces--;
				}
				if (_countPlaces == 0)
					return;
			}
		}
	}
	else if (CheckAvailability(_countPlaces, _isVip))
	{

		for (int i = VIPRAWS; i < RAWS; i++)
		{
			for (int j = 0; j < SEATSINRAWS; j++)
			{
				if (places[i][j] == 0)
				{
					settedSeats.push_back(i * 10 + j);//в i ряд записываю номер места
					places[i][j] = 1;
					_countPlaces--;
				}
				if (_countPlaces == 0)
					return;
			}
		}
	}
	throw string("Невозможно уместить столько человек!");
}

void Session::BackUpPlaces(vector<int>& settedSeats)
{
	for (size_t i = 0; i < settedSeats.size(); i++)
	{
		places[settedSeats[i] / 10][settedSeats[i]%10] = 0;
	}
}

Event Session::GetEvent()
{
	return dataAboutEvent;
}




