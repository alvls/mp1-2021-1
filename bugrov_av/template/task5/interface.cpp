#include "all.h"
//---------------------------------------------------
void setstr(string& s)
{//не успел сделать через _getch()
	s.clear();
	cout << " Количество символов не более 32\n";
	char get;
	for (int i = 0; i < 32; i++)
	{
		get = getchar();
		if (get == '\0' || get == '\n' || get == '\r' || get == ' ')
			break;
		s.push_back(get);
	}
}
int getdate()
{
	int n;
	int res;
	do
	{
		res = 0;
	first_digit:	do
	{
		n = _getch() - '0';
	} while (n < 0 || n>9);
	cout << n;
	res += n * 10;
	do
	{
		n = _getch() - '0';
		if (n == '\b' - '0')
		{
			res = 0;
			cout << "\b \b";
			goto first_digit;
		}
	} while ((n < 0 || n>9) && n != 13 - '0');
	if (n != 13 - '0')
	{
		cout << n << "\n";
		res += n;
	}
	else
	{
		res /= 10;
		cout << "\n";
	}
	if (res > 30 || res < 1)
		cout << "Неверные данные\n";
	} while (res > 30 || res < 1);
	return res;
}
void updown(int& pointer, const int lim, bool& notEnter)
{
	bool repeat = true;
	int input;
	enum choice
	{
		W_en = 87,
		W = 214,
		w_en = 119,
		w = 246,
		A_en = 65,
		A = 212,
		a_en = 97,
		a = 244,
		S_en = 83,
		S = 219,
		s_en = 115,
		s = 251,
		D_en = 68,
		D = 194,
		d_en = 100,
		d = 226,
		_n = 13,
		esc = 27
	};
	while (repeat)
	{
		input = _getch();
		switch (input)
		{
		case w: case W: case w_en: case W_en:
			if (pointer > 0)
				pointer--;
			else
				pointer = lim - 1;
			notEnter = true;
			repeat = false;
			break;
		case S: case s: case S_en: case s_en:
			if (pointer < lim - 1)
				pointer++;
			else
				pointer = 0;
			notEnter = true;
			repeat = false;
			break;
		case _n:
			notEnter = false;
			repeat = false;
			break;
		}
	}
}
int leftright(const string* var, int maxvar, string message)
{
	bool repeat = true;
	int input;
	int pointer = 0;
	int i;
	string separator = "\t";
	enum choice
	{
		W_en = 87,
		W = 214,
		w_en = 119,
		w = 246,
		A_en = 65,
		A = 212,
		a_en = 97,
		a = 244,
		S_en = 83,
		S = 219,
		s_en = 115,
		s = 251,
		D_en = 68,
		D = 194,
		d_en = 100,
		d = 226,
		_n = 13,
		esc = 27
	};
	enum color
	{
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		BROWN = 6,
		LIGHTGRAY = 7,
		DARKGRAY = 8,
		LIGHTBLUE = 9,
		LIGHTGREEN = 10,
		LIGHTCYAN = 11,
		LIGHTRED = 12,
		LIGHTMAGENTA = 13,
		YELLOW = 14,
		WHITE = 15
	};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("color B2");//LIGHTCYAN GREEN	
	do
	{
		system("cls");
		cout << message;
		repeat = true;
		for (i = 0; i < pointer; i++)
			cout << var[i] << separator;
		if (pointer < maxvar)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | GREEN));
			cout << var[pointer] << separator;
			i++;
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | GREEN));
			for (i; i < maxvar; i++)
				cout << var[i] << separator;;
		}
		while (repeat)
		{
			input = _getch();
			switch (input)
			{
			case A: case a: case A_en: case a_en:
				if (pointer > 0)
					pointer--;
				else
					pointer = maxvar - 1;
				repeat = false;
				break;
			case D: case d: case d_en: case D_en:
				if (pointer < maxvar - 1)
					pointer++;
				else
					pointer = 0;
				repeat = false;
				break;
			case _n:
				repeat = false;
				break;
			}
		}
	} while (input != _n);
	system("cls");
	return pointer;
}
void setwtype(const int pointer, userdata& data)
{
	switch (pointer)
	{
	case 0:
		data.Wtype = wagonType::down_c;
		break;
	case 1:
		data.Wtype = wagonType::up_c;
		break;
	case 2:
		data.Wtype = wagonType::down_r;
		break;
	case 3:
		data.Wtype = wagonType::up_r;
		break;
	case 4:
		data.Wtype = wagonType::sleep;
		break;
	}
}
bool cashbox::disagree(userdata& data)
{
	system("cls");
	system("color B2");
	cout << "Удостоверьтесь, что ваши данные введены правильно:\n\n";
	cout << "Отправление:\n";
	if (data.tnumber)
	{
		cout << "Москва. Курский вокзал\n";
		cout << "Прибытие:\nНижний Новгород. Московский вокзал\n";
	}
	else
	{
		cout << "Нижний Новгород. Московский вокзал\n";
		cout << "Прибытие:\nМосква. Курский вокзал\n";
	}
	cout << "Дата: " << data.date << "-й день\n";
	cout << "ФИО пассажира:\n";
	cout << data.surname << "\n";
	cout << data.name << "\n";
	cout << data.patronymic << "\n";
	switch (data.Ttype)
	{
	case trainType::firm:
		cout << "Фирменный поезд\n";
		switch (data.Wtype)
		{
		case wagonType::down_c:
			cout << "Купе. Нижнее место\n";
			break;
		case wagonType::down_r:
			cout << "Плацкарт. Нижнее место\n";
			break;
		case wagonType::sleep:
			cout << "Спальный вагон\n";
			break;
		case wagonType::up_c:
			cout << "Купе. Верхнее место\n";
			break;
		case wagonType::up_r:
			cout << "Плацкарт. Верхнее место\n";
			break;
		}
		break;
	case trainType::speed:
		cout << "Скорый поезд\n";
		switch (data.Wtype)
		{
		case wagonType::down_c:
			cout << "Купе. Нижнее место\n";
			break;
		case wagonType::down_r:
			cout << "Плацкарт. Нижнее место\n";
			break;
		case wagonType::up_c:
			cout << "Купе. Верхнее место\n";
			break;
		case wagonType::up_r:
			cout << "Плацкарт. Верхнее место\n";
			break;
		}
		break;
	case trainType::swallow:
		cout << "Поезд \"Ласточка\"\n";
		cout << "Номер поезда: " << data.tnumber << "\n";
		break;
	}
	cout << "\nЕсли какие-либо данные оказались неверны, нажмите esc. Если всё верно, нажмите Enter. Если вы отзываете билет, нажмите Backspace\n";
	int ans;
	do
	{
		ans = _getch();
		switch (ans)
		{
		case 13:
			system("cls");
			cout << "Заказ отправлен на обработку\n";
			_getch();
			return false;
		case 27:
			system("cls");
			cout << "Введите снова все необходимые данные\n";
			_getch();
			return true;
		case '\b':
			cout << "Вы отменили заказ билета\n";
			_getch();
			system("cls");
			data.date = 0;
			return false;
		}
	} while (1);
}
//---------------------------------------------------
userdata cashbox::SetData()
{
	enum color
	{
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		BROWN = 6,
		LIGHTGRAY = 7,
		DARKGRAY = 8,
		LIGHTBLUE = 9,
		LIGHTGREEN = 10,
		LIGHTCYAN = 11,
		LIGHTRED = 12,
		LIGHTMAGENTA = 13,
		YELLOW = 14,
		WHITE = 15
	};
	//
	//едут в Мск: 1 - фирменный; 3 - скорый; 5,7,9 - ласточка
	//едут в НН: 2 - фирменный; 4 - скорый; 6,8,10 - ласточка
	//
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	userdata data;
	system("color B2");//LIGHTCYAN GREEN
	do {
		cout << "Введите дату отправления поезда. Первый день - сегодня (26.04.21), последний день - 30-й\n";
		data.date = getdate();
		string message = "Выберите направление. Вокзал в Нижнем Новгороде - Московский, в Москве - Курский\n\n";
		{
			string var[2] = { "Москва - Нижний Новгород", "Нижний Новгород - Москва" };
			data.tnumber = leftright(var, 2, message);
		}
		cout << "Введите фамилию без пробелов и разделителей.";
		setstr(data.surname);
		cout << "Введите имя без пробелов и разделителей.";
		setstr(data.name);
		cout << "Введите отчество. Если его нет, нажмите пробел, затем Enter.";
		setstr(data.patronymic);
		system("cls");
		const string trains[3] = { "\"Ласточка\"","Фирменный поезд","Скорый поезд" };
		int pointer = 0;
		int input;
		int i;
		bool notEnter;
		do
		{
			i = 0;
			system("cls");
			cout << "Выберите тип поезда:\n\n";
			for (i; i < pointer; i++)
				cout << trains[i] << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | GREEN));
			cout << trains[i] << endl;
			i++;
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | GREEN));
			for (i; i < 3; i++)
				cout << trains[i] << endl;
			updown(pointer, 3, notEnter);
		} while (notEnter);
		switch (pointer)
		{
		case 0:
			data.Ttype = trainType::swallow;
			
			break;
		case 1:
			data.Ttype = trainType::firm;
			break;
		case 2:
			data.Ttype = trainType::speed;
		}
		system("cls");
		const int firmmax = 5;
		const int speedmax = firmmax - 1;
		string fwagtype[firmmax] = { "Купе (нижние места) 2650 руб", "Купе (верхние места) 3762 руб", "Плацкарт (нижние места) 1315 руб", "Плацкарт (верхние места) 1603 руб", "СВ 6748 руб" };
		string swagtype[speedmax]= { "Купе (нижние места) 3026 руб", "Купе (верхние места) 4186 руб", "Плацкарт (нижние места) 1589 руб", "Плацкарт (верхние места) 1791 руб"};
		switch (data.Ttype)
		{
		case trainType::swallow:
			message = "Выберите номер поезда. Цена 1193 руб\n";
			if (!data.tnumber)
			{
				string var[3] = { "№6 (4:30)", "№8 (11:00)", "№10 (17:30)" };
				data.tnumber = leftright(var, 3, message);
				switch (data.tnumber)
				{
				case 0:
					data.tnumber = 6;
					break;
				case 1:
					data.tnumber = 8;
					break;
				case 2:
					data.tnumber = 10;
					break;
				}
			}
			else
			{
				string var[3] = { "№5 (4:30)", "№7 (11:00)", "№9 (17:30)" };
				data.tnumber = leftright(var, 3, message);
				switch (data.tnumber)
				{
				case 0:
					data.tnumber = 5;
					break;
				case 1:
					data.tnumber = 7;
					break;
				case 2:
					data.tnumber = 9;
					break;
				}
			}
			break;
		case trainType::firm:
			pointer = 0;
			input = 0;
			do
			{
				system("cls");
				cout << "Выберите тип места:\n\n";
				bool repeat = true;
				for (i = 0; i < pointer; i++)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | GREEN));
					cout << fwagtype[i] << "\n";
				}
				if (pointer < firmmax)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | GREEN));
					cout << fwagtype[pointer] << "\n";
					SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | GREEN));
					i++;
				}
				for (i; i < firmmax; i++)
					cout << fwagtype[i] << "\n";
				updown(pointer, firmmax, notEnter);
			} while (notEnter);
			if (data.tnumber)
				data.tnumber = 1;
			else
				data.tnumber = 2;
			setwtype(pointer, data);
			break;
		case trainType::speed:
			pointer = 0;
			input = 0;
			do
			{
				system("cls");
				cout << "Выберите тип места: \n\n";
				bool repeat = true;
				for (i = 0; i < pointer; i++)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | GREEN));
					cout << swagtype[i] << "\n";
				}
				if (pointer < speedmax)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | GREEN));
					cout << swagtype[pointer] << "\n";
					SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | GREEN));
					i++;
				}
				for (i; i < speedmax; i++)
					cout << swagtype[i] << "\n";
				updown(pointer, speedmax, notEnter);
			} while (notEnter);
			if (data.tnumber)
				data.tnumber = 3;
			else
				data.tnumber = 4;
			setwtype(pointer, data);
			break;
		default:
			break;
		}
	} while (disagree(data));
	return data;
}