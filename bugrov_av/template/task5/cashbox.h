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
	//едут в Мск: 1 - фирменный; 3 - скорый; 5,7,9 - ласточка
	//едут в НН: 2 - фирменный; 4 - скорый; 6,8,10 - ласточка
	vector<railway> toNN, toMsk;
	int sum;
	userdata SetData();//получает данные о пользователе
	//проверяет, можно ли вычесть из количества билетов, чтобы оно не стало отрицательным
	/// меняет также число свободных билетов.
	void GetTicket(userdata inf);//сформировать билет
	//cashbox& operator=(const cashbox& cash);/////////////////////////////////
	void change_database(userdata change, bool is_new);
	bool agree(const userdata& data);
	void do_repeat(bool& repeat);
public:
	cashbox(const cashbox& cash);////////////////////////////////////////////
	void calculate(const userdata& data);
	void SetPlace(bool& repeat);//полная обработка действий с билетами
	cashbox() : sum(0)
	{
		railway null_rail;
		for (int i = 0; i < 30; i++)/////здесь нужно считывать из файла
		{
			toNN.push_back(null_rail);
			toMsk.push_back(null_rail);
		}
	}
};