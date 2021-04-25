#include "all.h"

void cashbox::SetPlace()
{
	userdata information = SetData();
	if (information.tnumber % 2)
		if (toMsk[information.date-1].check(information))
		{
			//меняем Reserved.txt дозапись: std::ios::app
			GetTicket(information);
		}
		else
			cout << "Недостаточно свободных мест\n";
	else
		if (toNN[information.date-1].check(information))
		{
			//меняем Reserved.txt дозапись: std::ios::app
			GetTicket(information);
		}
		else
			cout << "Недостаточно свободных мест\n";
}
void cashbox::GetTicket(userdata inf)
{
	ofstream fout;
	fout.open("Ticket.txt");
	//Здесь должна быть функция подсчёта общей стоимости билетов. Написать её (в неё скидывать только тип места)
	if (fout.is_open())
	{
		//Выводы в файл пунктов билета
	}
	fout.close();
}
void cashbox::change_database(userdata change, bool is_new)
{
	ofstream os;
	if (is_new)
	{
		os.open("Reserved.txt", ios_base::app);
		if (os.is_open())
			;/////////////////////////////////////////////
		os.close();
	}
}