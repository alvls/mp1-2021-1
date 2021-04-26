#include "all.h"

void cashbox::SetPlace(bool& repeat)
{
	userdata information = SetData();
	system("color B2");
	if (information.tnumber % 2)
		if (toMsk[information.date-1].check(information))
		{
			calculate(information);
			GetTicket(information);
		}
		else
			cout << "Недостаточно свободных мест\n";
	else
		if (toNN[information.date-1].check(information))
		{
			calculate(information);
			GetTicket(information);
		}
		else
			cout << "Недостаточно свободных мест\n";
	ofstream fout;
	fout.open("Reserved.txt");
	fout << (*this);
	do_repeat(repeat);
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
void cashbox::do_repeat(bool& repeat)
{
	system("color B2");
	cout << "Будете ли вы заказывать ещё билеты? Enter - да, Esc - нет\n";
	int ans;
	bool badsymb;
	do
	{
		ans = _getch();
		switch (ans)
		{
		case 13:
			repeat = true;
			badsymb = false;
			break;
		case 27:
			repeat = false;
			badsymb = false;
			break;
		default:
			badsymb = true;
		}
	} while (badsymb);
}
//cashbox::cashbox(const cashbox& cash):toNN(cash.toNN), toMsk(cash.toMsk), sum(cash.sum)
//{
//
//}

ostream& operator<<(ostream& place, const cashbox& c)
{
	for (int i = 0; i < c.toMsk.size(); i++)
	{
		int j;
		for (j = 0; j < 6; j++)
			place << c.toMsk[i].ftrain.up_coupe[j] << "\n";
		for (j = 0; j < 6; j++)
			place << c.toMsk[i].ftrain.down_coupe[j] << "\n";
		for (j = 0; j < 4; j++)
			place << c.toMsk[i].ftrain.up_reserved[j] << "\n";
		for (j = 0; j < 4; j++)
			place << c.toMsk[i].ftrain.down_reserved[j] << "\n";
		for (j = 0; j < 2; j++)
			place << c.toMsk[i].ftrain.sleeping[j] << "\n";
		//==================================================
		for (j = 0; j < 4; j++)
			place << c.toMsk[i].strain.up_coupe[j] << "\n";
		for (j = 0; j < 4; j++)
			place << c.toMsk[i].strain.down_coupe[j] << "\n";
		for (j = 0; j < 8; j++)
			place << c.toMsk[i].strain.up_reserved[j] << "\n";
		for (j = 0; j < 8; j++)
			place << c.toMsk[i].strain.down_reserved[j] << "\n";
		//==================================================
		for (j = 0; j < 8; j++)
			place << c.toMsk[i].swtrain[0].wagon[j] << "\n";
		for (j = 0; j < 8; j++)
			place << c.toMsk[i].swtrain[1].wagon[j] << "\n";
		for (j = 0; j < 8; j++)
			place << c.toMsk[i].swtrain[2].wagon[j] << "\n";

	}
	for (int i = 0; i < c.toNN.size(); i++)
	{
		int j;
		for (j = 0; j < 6; j++)
			place << c.toNN[i].ftrain.up_coupe[j] << "\n";
		for (j = 0; j < 6; j++)
			place << c.toNN[i].ftrain.down_coupe[j] << "\n";
		for (j = 0; j < 4; j++)
			place << c.toNN[i].ftrain.up_reserved[j] << "\n";
		for (j = 0; j < 4; j++)
			place << c.toNN[i].ftrain.down_reserved[j] << "\n";
		for (j = 0; j < 2; j++)
			place << c.toNN[i].ftrain.sleeping[j] << "\n";
		//==================================================
		for (j = 0; j < 4; j++)
			place << c.toNN[i].strain.up_coupe[j] << "\n";
		for (j = 0; j < 4; j++)
			place << c.toNN[i].strain.down_coupe[j] << "\n";
		for (j = 0; j < 8; j++)
			place << c.toNN[i].strain.up_reserved[j] << "\n";
		for (j = 0; j < 8; j++)
			place << c.toNN[i].strain.down_reserved[j] << "\n";
		//==================================================
		for (j = 0; j < 8; j++)
			place << c.toNN[i].swtrain[0].wagon[j] << "\n";
		for (j = 0; j < 8; j++)
			place << c.toNN[i].swtrain[1].wagon[j] << "\n";
		for (j = 0; j < 8; j++)
			place << c.toNN[i].swtrain[2].wagon[j] << "\n";
	}
	return place;
}
istream& operator>>(istream& place, cashbox& c)
{
	place.get();
	for (int i = 0; i < c.toMsk.size(); i++)
	{
		int j;
		string str;
		for (j = 0; j < 6; j++)
		{
			getline(place, str); 
			c.toMsk[i].ftrain.up_coupe[j] = stoi(str);
		}
		for (j = 0; j < 6; j++) 
		{
			getline(place, str);
			c.toMsk[i].ftrain.down_coupe[j] = stoi(str);
		}
		for (j = 0; j < 4; j++)
		{
			getline(place, str);
			c.toMsk[i].ftrain.up_reserved[j] = stoi(str);
		}
		for (j = 0; j < 4; j++)
		{
			getline(place, str);
			c.toMsk[i].ftrain.down_reserved[j] = stoi(str);
		}
		for (j = 0; j < 2; j++)
		{
			getline(place, str);
			c.toMsk[i].ftrain.sleeping[j] = stoi(str);
		}
		//==================================================
		for (j = 0; j < 4; j++)
		{
			getline(place, str);
			c.toMsk[i].strain.up_coupe[j] = stoi(str);
		}
		for (j = 0; j < 4; j++)
		{
			getline(place, str);
			c.toMsk[i].strain.down_coupe[j] = stoi(str);
		}
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toMsk[i].strain.up_reserved[j] = stoi(str);
		}
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toMsk[i].strain.down_reserved[j] = stoi(str);
		}
		//==================================================
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toMsk[i].swtrain[0].wagon[j] = stoi(str);
		}
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toMsk[i].swtrain[1].wagon[j] = stoi(str);
		}
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toMsk[i].swtrain[2].wagon[j] = stoi(str);
		}
	}
	for (int i = 0; i < c.toNN.size(); i++)
	{
		int j;
		string str;
		for (j = 0; j < 6; j++)
		{
			getline(place, str);
			c.toNN[i].ftrain.up_coupe[j] = stoi(str);
		}
		for (j = 0; j < 6; j++)
		{
			getline(place, str);
			c.toNN[i].ftrain.down_coupe[j] = stoi(str);
		}
		for (j = 0; j < 4; j++)
		{
			getline(place, str);
			c.toNN[i].ftrain.up_reserved[j] = stoi(str);
		}
		for (j = 0; j < 4; j++)
		{
			getline(place, str);
			c.toNN[i].ftrain.down_reserved[j] = stoi(str);
		}
		for (j = 0; j < 2; j++)
		{
			getline(place, str);
			c.toNN[i].ftrain.sleeping[j] = stoi(str);
		}
		//==================================================
		for (j = 0; j < 4; j++)
		{
			getline(place, str);
			c.toNN[i].strain.up_coupe[j] = stoi(str);
		}
		for (j = 0; j < 4; j++)
		{
			getline(place, str);
			c.toNN[i].strain.down_coupe[j] = stoi(str);
		}
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toNN[i].strain.up_reserved[j] = stoi(str);
		}
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toNN[i].strain.down_reserved[j] = stoi(str);
		}
		//==================================================
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toNN[i].swtrain[0].wagon[j] = stoi(str);
		}
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toNN[i].swtrain[1].wagon[j] = stoi(str);
		}
		for (j = 0; j < 8; j++)
		{
			getline(place, str);
			c.toNN[i].swtrain[2].wagon[j] = stoi(str);
		}
	}
	return place;
}