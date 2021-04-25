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
	userdata SetData();//получает данные о пользователе
					   //проверяет, можно ли вычесть из количества билетов, чтобы оно не стало отрицательным
	/// меняет также число свободных билетов.
	void GetTicket(userdata inf);//сформировать билет
	cashbox& operator=(cashbox& cash);/////////////////////////////////
	cashbox(cashbox& cash);////////////////////////////////////////////
	void change_database(userdata change, bool is_new);
public:
	void SetPlace();//полная обработка действий с билетами
	cashbox()
	{
		railway tmp_rail;
		for (int i = 0; i < 30; i++)/////сдесь нужно считывать из файла
		{
			toNN.push_back(tmp_rail);
			toMsk.push_back(tmp_rail);
		}
	}
};