#pragma once
#include <vector>
#include "Day.h"
#include "Session.h"
#include <string>
#include <iostream>
using namespace std;

#define COUNTHALLS 3
#define SESSIONSINHALLINDAY 8


struct hall
{
	int vipPrice;
	int defaultPrice;
};

class Cinema
{
private:
	vector<Day> sheduleDay; //���������� �� 30 ���� ��� ���������� �� ����                       
	vector <vector <Session>> sessions; // ��� ������ � �������� 3 ���� � ����������� �� ����       
	vector <int> savedDays; //������ ���, ������� ��������� � sessions
	vector<hall> halls; //���������� � ����� �� ������ � �����  
	int FindIndexSession(int hallNumber, Session& neededSession);
	void SetFirstDaySession(Date _date); 
	void SetSecondtDaySession(Date _date);
	void SetThirdDaySession(Date _date);
public:
	Cinema()
	{
		sheduleDay.resize(30);
		sessions.resize(COUNTHALLS);
		savedDays.resize(3); 
		halls.resize(COUNTHALLS);
		for (size_t i = 0; i < COUNTHALLS; i++)
		{
			sessions[i].resize(SESSIONSINHALLINDAY * 3);
		}
	}

	//�������� ����������� ������� ���������� ���� � ������ ���� �� ������ ������
	bool CheckAvailability(int countPlaces, bool isVip, int hallNumber, Session neededSession);
	//�������� ���
	void AddHall(int numberHall, int _vipPrice = 0, int _defaultPrice = 0 );
	//���������� ���� � ����
	void SetDataHall(int numberHall, int _vipPrice, int _defaultPrice);
	//������ ����� �� ������ ������
	void SetPlace(int countPlaces,bool _isVip, int hallNumber, Session neededSession, vector<int>& settedSeats);
	//���������� ������ � ������ ����
	void SetSessionsInHall(int hall, vector <Session> otherSessions);
	//���������� ���������� �� ����
	void SetSheduleInDay(int day,vector <Event> events);
	//�������� ���� ������� � ������ ����
	void GetPriceFromHall(int hall, int& defaultPrice, int& vipPrice);
	//�������� ��� ������� � ������ ����
	vector<Event> GetEventsInDay(int day);
	//������ ���������� ���� � ��������� ����������
	void BackUpSeats(int hallNumber, Session neededSession, vector<int>& settedSeats);
	//���������� ���������� � ����������� �� ��������� ���� �������������
	void UpdateSession(Date _date);
	//�������� ���������� �� 3 ��� � ������ 
	void ShowSessions(Date _date);

};

