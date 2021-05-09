#pragma once
#include "all.h"
//----------------------------------------------------------
void setstr(string& s);
int getdate();
void updown(int& pointer, const int lim, bool& notEnter);
void setwtype(const int pointer, userdata& data);
int leftright(const string* var, int maxvar, string message);
//----------------------------------------------------------
class cashbox
{
	//���� � ���: 1 - ���������; 3 - ������; 5,7,9 - ��������
	//���� � ��: 2 - ���������; 4 - ������; 6,8,10 - ��������
	vector<railway> toNN, toMsk;
	int sum;
	userdata SetData();//�������� ������ � ������������
	//���������, ����� �� ������� �� ���������� �������, ����� ��� �� ����� �������������
	/// ������ ����� ����� ��������� �������.
	void GetTicket(userdata inf);//������������ �����
	//cashbox& operator=(const cashbox& cash);/////////////////////////////////
	cashbox(const cashbox& cash);////////////////////////////////////////////
	void change_database(userdata change, bool is_new);
	bool disagree(userdata& data);
	void do_repeat(bool& repeat);
	friend ostream& operator<<(ostream& place, const cashbox& c);
	friend istream& operator>>(istream& place, cashbox& c);
public:
	void calculate(const userdata& data);
	void SetPlace(bool& repeat);//������ ��������� �������� � ��������
	cashbox() : sum(0)
	{
		ifstream fin;
		if (fin.peek() == EOF)
		{
			railway null_rail;
			for (int i = 0; i < 30; i++)/////����� ����� ��������� �� �����
			{
				toNN.push_back(null_rail);
				toMsk.push_back(null_rail);
			}
		}
		else
			fin >> (*this);
		ofstream fout;
		fout.open("Ticket.txt", ios_base::out | ios_base::trunc);
	}
};