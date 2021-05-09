#pragma once
#include "Cinema.h"
#include <vector>
#include <iostream>
#include <string>
#define MORNINGHOURS 12
#define EVENINGHOURS 18
#define MORNINGPRICE 0.75
#define EVENINGPRICE 1.5


using namespace std;
/*����������� ������ �������� ����� � ���������.
����� �������� ����� ������ ����������� ������ ����� �� ������� ������� �� ���������� � ������������ ����������. �������, ��� ������� ������� ���������� 
�� ������ � �������� ���� ���� �� ������� ����.
������ ����� ����������� �����, �������� ������ ������, ��������� ������, ������� ����, ���������� ������ � ����������� �� ���� (VIP � �������).
��� ��������� �������, ��� ���������� ��������� ��� ����
� ��������� ����� �������, � ����� ���������� ������ ������������� (��� ������� ���������).
���������� ����� � ������ ���� ����������� ������� ���� � ������� � ����. ��� ��������� �������, ��� ����� ����
�� ���� ����� � ����� ���� ���������. ������� ������� �� ����� ������������ ����� 10 ����� ����� ������ ������.

���������� � ���� ������� �� ��������� 30 ���� ������� �������� � ������ ���������. ��� ������� ���� ����������� ������� ��������� �������
(�� ������� ������ � �� 12.00 �� 18.00).
��������� ������� �� �������� ������ (�� 12.00) ���������� 75% �� �������, ��������� ������� �� �������� ������ (����� 18.00) � 150% �� �������. 
���������� � ���������� ������ (��������/������) � ������ ���� �� ������ ������ ����� �������� � ������ ���������.

����� �������� ����� ������ ������������� ��������� ��������:
1) ������� ������ ����������: ����, ����� ������, �������� ������, ����� ����, ��� ����, ����� ����
2) ��������� ������� ���������� ���������� ��������� ���� � ��������� ����,
3) ��������������� ��������� ���������� ����,
4) ���������� ����� ��������� �������, 
5) �������� ����� �������
6) ������������ ������ (������ ����� ��������: ����, ����� ������, �������� ������, ����� ����, ����� ����, ����� ����� � ����).
����� ��������� ������ �������������� ��� ��������� ������ ������ �������� ����� � ����� ���� ���������� � ����������-����������� ��������. 
*/

struct Ticket
{
	Date dateSession;
	Time timeEvent;
	string nameFilm = "unknown";
	int hallNumber = 0;
	int rowNumber = 0;
	int seat = 0;
};

std::ostream& operator << (std::ostream& out, const Ticket& _ticket);

struct DataClient
{
	Date date = { 0 , 0 };
	Session neededSession;
	int hallNumber = 0;
	bool isVip = false;
	int countSeats = 0;
};


class TicketOffice
{
private:
	Cinema* cinema;
	DataClient dataFromClient;
	bool isInitilize = false; //true - ���� ��������� ������ ����������
	vector<int> historySeats; //������� ���������� ���� � ��������� ���������� 
	int GetPrice(int hall, int _countSeats, bool _isVip); 
public:
	TicketOffice(Cinema* otherCinema)
	{
		cinema = otherCinema;
	}
	TicketOffice()
	{
		cinema = nullptr;
	}

	//���������� ����� � ������ �����������
	void SetCinema(Cinema* otherCinema); 
	//�������� ������ �������
	void SetDataClient(Date _date, Time _timeSession, string _nameFilm, int _hallNumber, bool _isVip, int _countSeats); 
	//��������� ����������� ������� ���������� ���� � ������ ���� 
	bool CheckAvailability();  
	//����������� ����� 
	void Reserve(Date currnetDate, Time currentTime); 
	//�������� ���� ������� 
	int GetTotalPrice(); 
	//������ ������� 
	void CancellationOrder(); 
	//��������� ������� 
	vector<Ticket> GetTickets(); 
	//���������, �������� �� ������ ������� 
	void CheckInitilize(); 
	// �������� �� ��������� 
	void CheckGetLate(Date currentDate, Time currentTime); 
};

