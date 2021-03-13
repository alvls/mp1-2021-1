	//Описание задания:
//2.1.Календарь событий
//Разработать класс Календарь событий.
//Класс должен позволять сохранять даты заданных событий в формате : год, месяц, день(в диапазоне от 1 января 1 года до 31 декабря 2020 года), 
//наименование события.
//На каждый день может приходиться только одно событие.Общее число событий – не более 30.
//Класс должен предоставлять операции : 1) установить событие, 2) узнать дату выбранного события, 
//3) вычислить разницу между заданной датой и датой события(в годах, месяцах, днях), 
//4) сформировать новое событие, сдвинув выбранное существующее событие на заданное смещение(в годах, месяцах, днях) в меньшую и в большую сторону.
//Класс должен содержать все необходимые конструкторы, деструктор, оператор присваивания, а также «уметь» выводить себя на консоль.

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

#define CONST_COUNT_MONTHS 13
#define CONST_COUNTING_EVENTS 30

int MonthDays[CONST_COUNT_MONTHS] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

class Event
{
private:
	int year;
	int day;
	string nameevent;
	int month;
public:
	Event()
	{
		year = 0;
		day = 0;
		month = 0;
		nameevent = "Пусто";
	}
	void operator= (const Event& other)
	{
		this->year = other.year;
		this->day = other.day;
		this->month = other.month;
		this->nameevent = other.nameevent;
	}
	void SetEvent(int yeartemp, int daytemp, int monthtemp, string nameeventtemp)
	{
		year = yeartemp;
		day = daytemp;
		month = monthtemp;
		nameevent = nameeventtemp;
	}
	void SetEvent(int yeartemp, int daytemp, int monthtemp)
	{
		year = yeartemp;
		day = daytemp;
		month = monthtemp;
	}
	void GetNameEvent()
	{
		cout << "\"" << nameevent << "\"" << endl;;
	}
	string GetDateEvent()
	{
		//Выводится дата события
		string date,days,months,years;
		days = to_string(day);
		months = to_string(month);
		years = to_string(year);
		date = days + '.' + months + '.' + years;
		return date;
	}
	int CountDays()
	{
		int days,i = 0;
		days = 365 * year;
		days += (day - 1);
		while (i != month)
		{
			days += MonthDays[i];
			i++;
		}
		return days;
	}
	void ChangeAddDays(int numday)
	{
		while (numday != 0)
		{
			if ((month == 1)||(month == 3)||(month == 5)||(month == 7)||(month == 8)||(month == 10)||(month == 12))
			{
				while (day < 32)
				{
					day++;
					numday--;
					if (numday == 0)
					{
						break;
					}
				}
				if (numday != 0)
				{
					month++;
					day = 1;
				}
				if (month == 13)
				{
					month = 1;
				year++;
				}
			}
			else if (month == 2)
			{
				while (day < 29)
				{
					day++;
					numday--;
					if (numday == 0)
					{
						break;
					}
				}
				if (numday != 0)
				{
					month++;
					day = 1;
				}
			}
			else if ((month == 4)||(month == 6)||(month == 9)||(month == 11))
			{
				while (day < 31)
				{
					day++;
					numday--;
					if (numday == 0)
					{
						break;
					}
				}
				if (numday != 0)
				{
					month++;
					day = 1;
				}
			}
		}
	}
	void ChangeSubtractDays(int numday)
	{
		while (numday != 0)
		{
			if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
			{
				while (day > 0)
				{
					day--;
					numday--;
					if (numday == 0)
					{
						break;
					}
				}
				if ((numday == 0) && (day == 0))
				{
					month--;
					if (month == 2)
					{
						day = 28;
					}
					else if (month == 7)
					{
						day = 31;
					}
					else
					{
						day = 30;
					}
				}
				if (numday != 0)
				{
					month--;
					if (month == 2)
					{
						day = 28;
					}
					else if (month == 7)
					{
						day = 31;
					}
					else
					{
						day = 30;
					}
				}
				if (month == 0)
				{
					month = 12;
					year--;
					day = 31;
				}
			}
			else if (month == 2)
			{
				while (day > 0)
				{
					day--;
					numday--;
					if (numday == 0)
					{
						break;
					}
				}
				if ((numday == 0) && (day == 0))
				{
					month--;
					day = 31;
				}
				if (numday != 0)
				{
					month--;
					day = 31;
				}
			}
			else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
			{
				while (day > 0)
				{
					day--;
					numday--;
					if (numday == 0)
					{
						break;
					}
				}
				if ((numday == 0) && (day == 0))
				{
					month--;
					day = 30;
				}
				if (numday != 0)
				{
					month--;
					day = 31;
				}
			}
		}
	}
};

class Calendarofevents
{
private:
	Event* arrevents;
	void Create()
	{
		arrevents = new Event[CONST_COUNTING_EVENTS];
	}
public:
	void CreateArrEvents()
	{
		Create();
	}
	~Calendarofevents()
	{
		delete[] arrevents;
	}
	void SetArrEvent(int index, Event& nevent)
	{
		int i;
		for (i = (index - 1); i < index ; i++)
		{
			arrevents[i] = nevent;
		}
	}
	void PrintElemArr(int count)
	{
		for (int i = 0; i < count; i++)
		{
			cout << "(" << i + 1 << ")"; 
			arrevents[i].GetNameEvent();
		}
	}
	string FindDateEvent(int index)
	{
		string date;
		date = arrevents[index].GetDateEvent();
		return date;
	}
	void CountDaysDate(Event& ndate, int& days, int& daysn, int& choice)
	{
		days = arrevents[choice].CountDays();
		daysn = ndate.CountDays();
		int days1;
		days1 = days - daysn;
		if (days1 > 0)
		{
			cout << "Событие завершилось " << days1 << " дней назад" << endl;
		}
		else if (days1 < 0)
		{
			cout << "Событие будет через " << abs(days1) << " дней" << endl;
		}
		else
		{
			cout << "Событие сегодня!" << endl;
		}
	}
	void AddDays(int index,int numdays)
	{
		arrevents[index].ChangeAddDays(numdays);
	}
	void SubtractDays(int index, int numdays)
	{
		arrevents[index].ChangeSubtractDays(numdays);
	}
};



void Menu();
void PutZnInArr(Calendarofevents& calen, Event& nevent, int countpop);
void GetDataForClassEvent(int& age, int& day, int& month, string& name);
void GetDaysOfMonth(int month, int& day);
void GetInfoNameEvent(Calendarofevents& calen, int count);
void FunFindEvent(Calendarofevents& calen, int choice);
void GetDataForNewDate(int& age, int& day, int& month);
void FunChoiceEvent3(Calendarofevents& calen, Event& nevent, int choice, int& countdayse, int& countdaysn);
void FAddDays(Calendarofevents& calen, int countind, int numdays);
void FSubtractDays(Calendarofevents& calen, int countind, int numdays);

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	bool choiceret = true;
	Calendarofevents calendar;
	calendar.CreateArrEvents();
	Event nevent;
	int choicetem, countindex = 0, numdays, countdayse = 0, countdaysn = 0;;
	while (choiceret)
	{
		Menu();
		cout << "Введите номер пункта меню, который хотите выполнить" << endl;
		cin >> choicetem;
		switch (choicetem)
		{
		case 1:
			countindex++;
			PutZnInArr(calendar, nevent,countindex);
			system("pause");
			break;
		case 2:
			int choice1;
			GetInfoNameEvent(calendar, countindex);
			cout << "Введите номер события из списка, дату которого хотите узнать: ";
			cin >> choice1;
			FunFindEvent(calendar, choice1);
			system("pause");
			break;
		case 3:
			int nage, nday, nmonth,choice2;
			GetDataForNewDate(nage, nday, nmonth);
			nevent.SetEvent(nage, nday, nmonth);
			GetInfoNameEvent(calendar, countindex);
			cout << "Введите номер события из списка, дату которого хотите узнать: ";
			cin >> choice2;
			FunChoiceEvent3(calendar,nevent,choice2,countdayse,countdaysn);
			system("pause");
			break;
		case 4:
			int choice,choicenum;
			cout << "В этом режиме мы будем переносить дату события!" << endl;
			cout << "Введите номер, которой соответствует операции:\n\t(1) Перенести событие на какое-то число дней вперёд\n\t(2) Перенести событие на какое-то число дней назад" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Введите количество дней, на которое хотите переместить событие вперёд" << endl;
				cin >> numdays;
				GetInfoNameEvent(calendar, countindex);
				cout << "Введите номер события из списка, дату которого хотите перенести: ";
				cin >> choicenum;
				FAddDays(calendar, choicenum, numdays);
				FunFindEvent(calendar, choicenum);
				system("pause");
				break;
			case 2:
				cout << "Введите количество дней, на которое хотите переместить событие назад" << endl;
				cin >> numdays;
				GetInfoNameEvent(calendar, countindex);
				cout << "Введите номер события из списка, дату которого хотите перенести: ";
				cin >> choicenum;
				FSubtractDays(calendar, choicenum, numdays);
				FunFindEvent(calendar, choicenum);
				system("pause");
				break;
			default:
				break;
			}
			break;
		case 0:
			cout << "Уже уходите, были рады вас видеть.Всего доброго!" << endl;
			system("pause");
			choiceret = false;
			break;
		default:
			break;
		}
		system("cls");
	}
}

void Menu()
{
	cout << "  Здравствуйте, уважаемый пользователь, в программе доступны следующие возможности:\n\t(1) Установить событие (Доступное число событий не более 30).\n\t(2) Узнать дату выбранного события.\n\t(3) Вычислить разницу между заданной датой и датой события(в годах, месяцах, днях).\n\t(4) Сформировать новое событие, сдвинув выбранное существующее событие на заданное смещение(в годах, месяцах, днях) в меньшую и в большую сторон.\n\t(0) Выход из программы.\n";
}

void PutZnInArr(Calendarofevents& calen, Event& nevent, int countpop)
{
	int ageu = 0, dayu = 0, monthu = 0;
	string nameu = "Пусто";
	GetDataForClassEvent(ageu, dayu, monthu, nameu);
	nevent.SetEvent(ageu, dayu, monthu, nameu);
	calen.SetArrEvent(countpop, nevent);
	cout << "Событие успешно установлено!" << endl;
	system("pause");
	system("cls");
	
}

void GetDataForClassEvent(int& age, int& day, int& month, string& name)
{
	age = 0, day = 0, month = 0;
	cout << "(1) Введём год, например, \"2000\"\n";
	while ((age > 2020) || (age < 1))
	{
		cout << "Введите год события, возможный диапазон от \"1\" до \"2020\"" << endl;
		cin >> age;
		if ((age > 2020) || (age < 1))
		{
			cout << "Ошибка!Повторите ввод!";
		}
	}

	cout << "(2) Введём месяц, вводить числами, где \"Январь\" - \"1\", \"Февраль\" - \"2\" и т.д.\n";
	while ((month > 12) || (month < 1))
	{
		cout << "Введите месяц события, возможный диапазон от \"1\" до \"12\"" << endl;
		cin >> month;
		if ((month > 12) || (month < 1))
		{
			cout << "Ошибка!Повторите ввод!";
		}
	}
	//сначала введи месяц, затем в качестве учёта дней дни, с обработкой этого
	GetDaysOfMonth(month, day);
	//Функция которая объединяет несколько строк, чтобы можно было называть события.
	cout << "Введите название события" << endl;
	while (getchar() != '\n');
	getline(cin, name);
}

void GetDaysOfMonth(int month, int& day)
{
	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
	{
		cout << "(3) Введём день, например, \"15\"\n";
		while ((day > 31) || (day < 1))
		{
			cout << "Введите день события, возможный диапазон от \"1\" до \"31\"" << endl;
			cin >> day;
			if ((day > 31) || (day < 1))
			{
				cout << "Ошибка!Повторите ввод!";
			}
		}
	}
	else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
	{
		cout << "(3) Введём день, например, \"15\"\n";
		while ((day > 30) || (day < 1))
		{
			cout << "Введите день события, возможный диапазон от \"1\" до \"30\"" << endl;
			cin >> day;
			if ((day > 30) || (day < 1))
			{
				cout << "Ошибка!Повторите ввод!";
			}
		}
	}
	else
	{
		cout << "(3) Введём день, например, \"15\"\n";
		while ((day > 28) || (day < 1))
		{
			cout << "Введите день события, возможный диапазон от \"1\" до \"28\"" << endl;
			cin >> day;
			if ((day > 28) || (day < 1))
			{
				cout << "Ошибка!Повторите ввод!";
			}
		}
	}
}

void GetInfoNameEvent(Calendarofevents& calen, int count)
{
	cout << "\t\tСписок доступных событий:" << endl;
	calen.PrintElemArr(count);
}

void FunFindEvent(Calendarofevents& calen,int choice)
{
	choice--;
	string date;
	date = calen.FindDateEvent(choice);
	cout << "Дата события: " << date << endl;		
}

void GetDataForNewDate(int& age, int& day, int& month)
{
	age = 0, day = 0, month = 0;
	cout << "(1) Введём год, например, \"2000\"\n";
	while ((age > 2020) || (age < 1))
	{
		cout << "Введите год события, возможный диапазон от \"1\" до \"2020\"" << endl;
		cin >> age;
		if ((age > 2020) || (age < 1))
		{
			cout << "Ошибка!Повторите ввод!";
		}
	}

	cout << "(2) Введём месяц, вводить числами, где \"Январь\" - \"1\", \"Февраль\" - \"2\" и т.д.\n";
	while ((month > 12) || (month < 1))
	{
		cout << "Введите месяц события, возможный диапазон от \"1\" до \"12\"" << endl;
		cin >> month;
		if ((month > 12) || (month < 1))
		{
			cout << "Ошибка!Повторите ввод!";
		}
	}
	GetDaysOfMonth(month, day);
}

void FunChoiceEvent3(Calendarofevents& calen, Event& nevent, int choice, int& countdayse, int& countdaysn)
{
	choice--;
	calen.CountDaysDate(nevent, countdayse, countdaysn, choice);
}

void FAddDays(Calendarofevents& calen, int countind, int numdays)
{
	countind--;
	calen.AddDays(countind, numdays);
}

void FSubtractDays(Calendarofevents& calen, int countind, int numdays)
{
	countind--;
	calen.SubtractDays(countind, numdays);
}