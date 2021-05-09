#include "Cinema.h"

int Cinema::FindIndexSession(int hallNumber, Session& neededSession)
{
	for (size_t i = 0; i < sessions[hallNumber].size(); i++)
	{
		if (sessions[hallNumber][i] == neededSession)
			return i;
	}
	throw string("������� ������ �� ����������!");
}

void Cinema::SetFirstDaySession(Date _date)
{
	for (size_t i = 0; i < COUNTHALLS; i++)
	{
		for (size_t j = 0; j < SESSIONSINHALLINDAY; j++)
		{
			Session temp(sheduleDay[_date.day].GetEvent(j));
			sessions[i][j] = temp;
			sessions[i][j].SetDate(_date);
		}
	}
}

void Cinema::SetSecondtDaySession(Date _date)
{
	for (size_t i = 0; i < COUNTHALLS; i++)
	{
		for (size_t j = SESSIONSINHALLINDAY; j < 2 * SESSIONSINHALLINDAY; j++)
		{
			Session temp(sheduleDay[_date.day].GetEvent(j));
			sessions[i][j] = temp;
			sessions[i][j].SetDate(_date);
		}
	}
}

void Cinema::SetThirdDaySession(Date _date)
{
	for (size_t i = 0; i < COUNTHALLS; i++)
	{
		for (size_t j = 2 * SESSIONSINHALLINDAY; j < 3 * SESSIONSINHALLINDAY; j++)
		{
			Session temp(sheduleDay[_date.day].GetEvent(j));
			sessions[i][j] = temp;
			sessions[i][j].SetDate(_date);
		}
	}
}

bool Cinema::CheckAvailability(int _countPlaces, bool _isVip, int _hallNumber, Session _neededSession)
{
	int index = FindIndexSession(_hallNumber, _neededSession);
	return sessions[_hallNumber][index].CheckAvailability(_countPlaces, _isVip);
}

void Cinema::AddHall(int numberHall, int _vipPrice, int _defaultPrice)
{
	hall tempHall = { _vipPrice, _defaultPrice };
	if (numberHall == halls.size())
	{
		halls.push_back(tempHall);
	}
	else
	{
		vector<hall>::const_iterator j = halls.begin();
		advance(j, numberHall);
		halls.insert(j, tempHall);
	}

}

void Cinema::SetDataHall(int numberHall, int _vipPrice, int _defaultPrice)
{
	halls[numberHall].defaultPrice = _defaultPrice;
	halls[numberHall].vipPrice = _vipPrice;
}

void Cinema::SetPlace(int countPlaces, bool _isVip, int hallNumber, Session neededSession, vector<int>& settedSeats)
{
	int index = FindIndexSession(hallNumber, neededSession);
	sessions[hallNumber][index].SetPlaces(countPlaces, _isVip, settedSeats);
}

void Cinema::SetSessionsInHall(int hall, vector<Session> otherSessions)
{
	if (hall > sessions.size())
	{
		throw string("������� ���� �� ����������!");
	}
	sessions[hall] = otherSessions;
}

void Cinema::SetSheduleInDay(int day, vector<Event> events)
{
	sheduleDay[day] = events;
}

void Cinema::GetPriceFromHall(int hall, int& defaultPrice, int& vipPrice)
{
	defaultPrice = halls[hall].defaultPrice;
	vipPrice = halls[hall].vipPrice;
}

vector<Event> Cinema::GetEventsInDay(int day)
{
	return sheduleDay[day].GetEvents();
}

void Cinema::BackUpSeats(int hallNumber, Session neededSession, vector<int>& settedSeats)
{
	int index = FindIndexSession(hallNumber, neededSession);
	sessions[hallNumber][index].BackUpPlaces(settedSeats);
}

void Cinema::UpdateSession(Date _date)
{
	int day = _date.day;
	Date temp(_date);
	
	if (day == savedDays[0]) //���������� �� �����
		return;
	else if (day == savedDays[1])		//����� �������� 1 ���� 
	{
		savedDays[0] = savedDays[1];
		//����������� ���������� ������� 2-�� ��� � 1-� ����
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			for (size_t j = 0; j < SESSIONSINHALLINDAY; j++)
			{
				sessions[i][j] = sessions[i][j + SESSIONSINHALLINDAY];
				sessions[i][j].SetDate(_date);
			}
		}
		//����������� ���������� ������� 3-�� ��� �� 2-� ����
		savedDays[1] = savedDays[2];
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			for (size_t j = SESSIONSINHALLINDAY; j < 2 * SESSIONSINHALLINDAY; j++)
			{
				sessions[i][j] = sessions[i][j + SESSIONSINHALLINDAY];
				sessions[i][j].SetDate(_date + 1);
			}
		}

		//���������� 3-�� ��� �� ������� ����������
		SetThirdDaySession(_date + 10);
		savedDays[2] = temp.day + 2;
	}
	else if (day == savedDays[2])
	{
		//����������� ���������� �� ������� 3 - �� ��� � ����� 1-��
		savedDays[0] = savedDays[2];
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			for (size_t j = 0; j < SESSIONSINHALLINDAY; j++)
			{
				sessions[i][j] = sessions[i][j + 2 * SESSIONSINHALLINDAY]; 
				sessions[i][j].SetDate(_date);
			}
		}
		//���������� ������ 2-�� ���
		SetSecondtDaySession(_date + 1);
		//���������� ������ 3-�� ��� 
		SetThirdDaySession(_date + 2);
	}
	else
	{
		//���������� ������� ���
		SetFirstDaySession(_date);
		savedDays[0] = temp.day;

		//���������� ������� ���
		SetSecondtDaySession(_date + 1);
		savedDays[1] = temp.day + 1;

		//���������� �������� ���
		SetThirdDaySession(_date + 2);
		savedDays[2] = temp.day + 2;
	}
}


void Cinema::ShowSessions(Date _date)
{

	for (size_t k = 0; k < COUNTHALLS; k++)
	{
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			for (size_t j = k*SESSIONSINHALLINDAY; j < (k+1) * SESSIONSINHALLINDAY; j++)
			{
				cout << sessions[i][j] << " \n���: " << i << endl << endl;
			}
		}
	}
}
