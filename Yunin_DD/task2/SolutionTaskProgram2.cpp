	//�������� �������:
//2.1.��������� �������
//����������� ����� ��������� �������.
//����� ������ ��������� ��������� ���� �������� ������� � ������� : ���, �����, ����(� ��������� �� 1 ������ 1 ���� �� 31 ������� 2020 ����), 
//������������ �������.
//�� ������ ���� ����� ����������� ������ ���� �������.����� ����� ������� � �� ����� 30.
//����� ������ ������������� �������� : 1) ���������� �������, 2) ������ ���� ���������� �������, 
//3) ��������� ������� ����� �������� ����� � ����� �������(� �����, �������, ����), 
//4) ������������ ����� �������, ������� ��������� ������������ ������� �� �������� ��������(� �����, �������, ����) � ������� � � ������� �������.
//����� ������ ��������� ��� ����������� ������������, ����������, �������� ������������, � ����� ������� �������� ���� �� �������.

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
		nameevent = "�����";
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
		//��������� ���� �������
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
	int counter = 0;
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
	void SetArrEvent(Event& nevent)
	{
		int i;
		for (i = (counter - 1); i < counter ; i++)
		{
			arrevents[i] = nevent;
		}
	}
	void PrintElemArr()
	{
		for (int i = 0; i < counter; i++)
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
			cout << "������� ����������� " << days1 << " ���� �����" << endl;
		}
		else if (days1 < 0)
		{
			cout << "������� ����� ����� " << abs(days1) << " ����" << endl;
		}
		else
		{
			cout << "������� �������!" << endl;
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
	void CountigCounter()
	{
		counter++;
	}
};



void Menu();
void PutZnInArr(Calendarofevents& calen, Event& nevent);
void GetDataForClassEvent(int& age, int& day, int& month, string& name);
void GetDaysOfMonth(int month, int& day);
void GetInfoNameEvent(Calendarofevents& calen);
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
	int choicetem, numdays, countdayse = 0, countdaysn = 0;;
	while (choiceret)
	{
		Menu();
		cout << "������� ����� ������ ����, ������� ������ ���������" << endl;
		cin >> choicetem;
		switch (choicetem)
		{
		case 1:
			calendar.CountigCounter();
			PutZnInArr(calendar, nevent);
			system("pause");
			break;
		case 2:
			int choice1;
			GetInfoNameEvent(calendar);
			cout << "������� ����� ������� �� ������, ���� �������� ������ ������: ";
			cin >> choice1;
			FunFindEvent(calendar, choice1);
			system("pause");
			break;
		case 3:
			int nage, nday, nmonth,choice2;
			GetDataForNewDate(nage, nday, nmonth);
			nevent.SetEvent(nage, nday, nmonth);
			GetInfoNameEvent(calendar);
			cout << "������� ����� ������� �� ������, ���� �������� ������ ������: ";
			cin >> choice2;
			FunChoiceEvent3(calendar,nevent,choice2,countdayse,countdaysn);
			system("pause");
			break;
		case 4:
			int choice,choicenum;
			cout << "� ���� ������ �� ����� ���������� ���� �������!" << endl;
			cout << "������� �����, ������� ������������� ��������:\n\t(1) ��������� ������� �� �����-�� ����� ���� �����\n\t(2) ��������� ������� �� �����-�� ����� ���� �����" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "������� ���������� ����, �� ������� ������ ����������� ������� �����" << endl;
				cin >> numdays;
				GetInfoNameEvent(calendar);
				cout << "������� ����� ������� �� ������, ���� �������� ������ ���������: ";
				cin >> choicenum;
				FAddDays(calendar, choicenum, numdays);
				FunFindEvent(calendar, choicenum);
				system("pause");
				break;
			case 2:
				cout << "������� ���������� ����, �� ������� ������ ����������� ������� �����" << endl;
				cin >> numdays;
				GetInfoNameEvent(calendar);
				cout << "������� ����� ������� �� ������, ���� �������� ������ ���������: ";
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
			cout << "��� �������, ���� ���� ��� ������.����� �������!" << endl;
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
	cout << "  ������������, ��������� ������������, � ��������� �������� ��������� �����������:\n\t(1) ���������� ������� (��������� ����� ������� �� ����� 30).\n\t(2) ������ ���� ���������� �������.\n\t(3) ��������� ������� ����� �������� ����� � ����� �������(� �����, �������, ����).\n\t(4) ������������ ����� �������, ������� ��������� ������������ ������� �� �������� ��������(� �����, �������, ����) � ������� � � ������� ������.\n\t(0) ����� �� ���������.\n";
}

void PutZnInArr(Calendarofevents& calen, Event& nevent)
{
	int ageu = 0, dayu = 0, monthu = 0;
	string nameu = "�����";
	GetDataForClassEvent(ageu, dayu, monthu, nameu);
	nevent.SetEvent(ageu, dayu, monthu, nameu);
	calen.SetArrEvent(nevent);
	cout << "������� ������� �����������!" << endl;
	system("pause");
	system("cls");
}

void GetDataForClassEvent(int& age, int& day, int& month, string& name)
{
	age = 0, day = 0, month = 0;
	cout << "(1) ����� ���, ��������, \"2000\"\n";
	while ((age > 2020) || (age < 1))
	{
		cout << "������� ��� �������, ��������� �������� �� \"1\" �� \"2020\"" << endl;
		cin >> age;
		if ((age > 2020) || (age < 1))
		{
			cout << "������!��������� ����!";
		}
	}

	cout << "(2) ����� �����, ������� �������, ��� \"������\" - \"1\", \"�������\" - \"2\" � �.�.\n";
	while ((month > 12) || (month < 1))
	{
		cout << "������� ����� �������, ��������� �������� �� \"1\" �� \"12\"" << endl;
		cin >> month;
		if ((month > 12) || (month < 1))
		{
			cout << "������!��������� ����!";
		}
	}
	//������� ����� �����, ����� � �������� ����� ���� ���, � ���������� �����
	GetDaysOfMonth(month, day);
	//������� ������� ���������� ��������� �����, ����� ����� ���� �������� �������.
	cout << "������� �������� �������" << endl;
	while (getchar() != '\n');
	getline(cin, name);
}

void GetDaysOfMonth(int month, int& day)
{
	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
	{
		cout << "(3) ����� ����, ��������, \"15\"\n";
		while ((day > 31) || (day < 1))
		{
			cout << "������� ���� �������, ��������� �������� �� \"1\" �� \"31\"" << endl;
			cin >> day;
			if ((day > 31) || (day < 1))
			{
				cout << "������!��������� ����!";
			}
		}
	}
	else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
	{
		cout << "(3) ����� ����, ��������, \"15\"\n";
		while ((day > 30) || (day < 1))
		{
			cout << "������� ���� �������, ��������� �������� �� \"1\" �� \"30\"" << endl;
			cin >> day;
			if ((day > 30) || (day < 1))
			{
				cout << "������!��������� ����!";
			}
		}
	}
	else
	{
		cout << "(3) ����� ����, ��������, \"15\"\n";
		while ((day > 28) || (day < 1))
		{
			cout << "������� ���� �������, ��������� �������� �� \"1\" �� \"28\"" << endl;
			cin >> day;
			if ((day > 28) || (day < 1))
			{
				cout << "������!��������� ����!";
			}
		}
	}
}

void GetInfoNameEvent(Calendarofevents& calen)
{
	cout << "\t\t������ ��������� �������:" << endl;
	calen.PrintElemArr();
}

void FunFindEvent(Calendarofevents& calen,int choice)
{
	choice--;
	string date;
	date = calen.FindDateEvent(choice);
	cout << "���� �������: " << date << endl;		
}

void GetDataForNewDate(int& age, int& day, int& month)
{
	age = 0, day = 0, month = 0;
	cout << "(1) ����� ���, ��������, \"2000\"\n";
	while ((age > 2020) || (age < 1))
	{
		cout << "������� ��� �������, ��������� �������� �� \"1\" �� \"2020\"" << endl;
		cin >> age;
		if ((age > 2020) || (age < 1))
		{
			cout << "������!��������� ����!";
		}
	}

	cout << "(2) ����� �����, ������� �������, ��� \"������\" - \"1\", \"�������\" - \"2\" � �.�.\n";
	while ((month > 12) || (month < 1))
	{
		cout << "������� ����� �������, ��������� �������� �� \"1\" �� \"12\"" << endl;
		cin >> month;
		if ((month > 12) || (month < 1))
		{
			cout << "������!��������� ����!";
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