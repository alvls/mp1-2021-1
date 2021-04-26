#include "all.h"

void cashbox::SetPlace(bool& repeat)
{
	userdata information = SetData();
	if (information.tnumber % 2)
		if (toMsk[information.date-1].check(information))
		{
			//мен€ем Reserved.txt дозапись: std::ios::app
			calculate(information);
			GetTicket(information);
		}
		else
			cout << "Ќедостаточно свободных мест\n";
	else
		if (toNN[information.date-1].check(information))
		{
			//мен€ем Reserved.txt дозапись: std::ios::app
			GetTicket(information);
		}
		else
			cout << "Ќедостаточно свободных мест\n";
	
}
void cashbox::GetTicket(userdata inf)
{
	ofstream fout;
	fout.open("Ticket.txt");
	if (fout.is_open())
	{
		calculate(inf);
		fout << inf;
		fout.close();
	}
}
void cashbox::change_database(userdata change, bool is_new)
{
	fstream file;
	if (is_new)
	{
		file.open("Reserved.txt");
		if (file.is_open())
			;
		file.close();
	}
}
void cashbox:: calculate(const userdata& data)
{
	enum class price
	{
		swallow = 1193,
		firm_down_r = 1315,
		firm_down_c = 2650,
		firm_up_r = 1603,
		firm_up_c = 3762,
		firm_sleep = 6748,
		speed_down_r = 1589,
		speed_down_c = 3026,
		speed_up_r = 1791,
		speed_up_c = 4186
	};
	switch (data.Ttype)
	{
	case trainType::firm:
		switch (data.Wtype)
		{
		case wagonType::down_c:
			sum += static_cast<int>(price::firm_down_c);
			break;
		case wagonType::down_r:
			sum += static_cast<int>(price::firm_down_r);
			break;
		case wagonType::sleep:
			sum += static_cast<int>(price::firm_sleep);
			break;
		case wagonType::up_c:
			sum += static_cast<int>(price::firm_up_c);
			break;
		case wagonType::up_r:
			sum += static_cast<int>(price::firm_up_r);
			break;
		}
		break;
	case trainType::speed:
		switch (data.Wtype)
		{
		case wagonType::down_c:
			sum += static_cast<int>(price::speed_down_c);
			break;
		case wagonType::down_r:
			sum += static_cast<int>(price::speed_down_r);
			break;
		case wagonType::up_c:
			sum += static_cast<int>(price::speed_up_c);
			break;
		case wagonType::up_r:
			sum += static_cast<int>(price::speed_up_r);
			break;
		}
		break;
	case trainType::swallow:
		sum += static_cast<int>(price::swallow);
		break;
	}
}
cashbox::cashbox(const cashbox& cash):toNN(cash.toNN), toMsk(cash.toMsk), sum(cash.sum)
{

}