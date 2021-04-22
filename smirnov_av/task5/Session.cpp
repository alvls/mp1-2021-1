#include "Session.h"

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


void Session::SetPlaces(int _countPlaces, bool _isVip, vector<vector<int>>& settedSeats)
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
					settedSeats[i].push_back(j);
				}
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
					places[i][j] = 1;
					settedSeats[i].push_back(j);
				}
			}
		}
	}

	throw string("Ќевозможно уместить столько человек!");
}

Event Session::GetEvent()
{
	return dataAboutEvent;
}




