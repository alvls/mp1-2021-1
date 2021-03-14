//2.1.��������� �������
//����������� ����� ��������� �������.
//����� ������ ��������� ��������� ���� �������� ������� � ������� : ���, �����, ����(� ��������� �� 1 ������ 1 ���� �� 31 ������� 2020 ����), 
//������������ �������.
//�� ������ ���� ����� ����������� ������ ���� �������.����� ����� ������� � �� ����� 30.
//����� ������ ������������� �������� : 1) ���������� �������, 2) ������ ���� ���������� �������, 
//3) ��������� ������� ����� �������� ����� � ����� �������(� �����, �������, ����), 
//4) ������������ ����� �������, ������� ��������� ������������ ������� �� �������� ��������(� �����, �������, ����) � ������� � � ������� �������.
//����� ������ ��������� ��� ����������� ������������, ����������, �������� ������������, � ����� ������� �������� ���� �� �������.

//�� ������������ ������������ 
//������ ���-�� ����

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

#define CONST_COUNT_MONTHS 13

int MonthDays[CONST_COUNT_MONTHS] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

class Calendarofevents
{
private:
	int age;
	int day;
	string nameevent;
	int month;
public:

	void GetNamesEvents()
	{
		cout << "\"" << nameevent << "\"" << endl;;
	}

	Calendarofevents()
	{
		age = 0;
		day = 0;
		month = 0;
		nameevent = "�����";
	}

	Calendarofevents(int agetemp,int daytemp,int monthtemp)
	{
		this->age = agetemp;
		this->day = daytemp;
		this->month = monthtemp;
	}
	
	void SetEvent(int agetemp, int daytemp, int monthtemp, string nameeventtemp)
	{
		age = agetemp;
		day = daytemp;
		month = monthtemp;
		nameevent = nameeventtemp;
		cout << "������� ������� �����������!" << endl;
	}

	void SetEvent(int agetemp, int daytemp, int monthtemp)
	{
		age = agetemp;
		day = daytemp;
		month = monthtemp;
	}

	void PrintEvent()
	{
		cout << "\t��������� ����������� ������ �������" << endl;
		cout << "(1) - ������������ ������ �������    " << "\"" << nameevent << "\"" << endl;;
		cout << "(2) - ���� ������ �������    " << "\"" << day << "\"" << endl;
		cout << "(3) - ����� ������ �������    " << "\"" << month << "\"" << endl;
		cout << "(4) - ��� ������ �������    " << "\"" << age << "\"" << endl;
	}
	
	void GetDataEvent()
	{
		//��������� ���� �������
		cout << "���� �������: " << day << ' ' << month << ' ' << age << endl;
	}

	void operator= (const Calendarofevents& other)
	{
		this->age = other.age;
		this->day = other.day;
		this->month = other.month;
		this->nameevent = other.nameevent;
	}

	void CoutingDaysDate(int & days,int & daysn,Calendarofevents & other ,int i = 0)
	{
		days = 365 * age;
		days += (day - 1);
		while (i != month)
		{
			days += MonthDays[i];
			i++;
		}
		i = 0;
		daysn = 365 * other.age;
		daysn += (other.day - 1);
		while (i != other.month)
		{
			daysn += MonthDays[i];
			i++;
		}
		int days1;
		days1 = days - daysn;
		if (days1 > 0)
		{
			cout << "�� ������� �������� " << days1 << "����" << endl;
		}
		else if (days1 < 0)
		{
			cout << "������� ����������� " << abs(days1) << "���� �����" << endl;
		}
		else
		{
			cout << "������� �������!" << endl;
		}
	}

	void AddationDays(int numday)
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
					age++;
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

	void SubtractionDays(int numday)
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
					age--;
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

//�������� ����������� ����������� ��� ���������� ������� �� ���� �������������. � ������� �������� ������ � ���������� ������ ����� � ������.
//��� ��� ����������� �������.

void Menu();
void PutZnInArr(Calendarofevents* arr, int count, int countpop);
void GetDataForClass(int& age, int& day, int& month, string& name);
void PrintElofClass(Calendarofevents* arr, int count);
void GetInfoNameEvent(Calendarofevents* arr, int count);
void FunFindEvent(int num, Calendarofevents* arr, int count);
Calendarofevents* FunSetEvent(Calendarofevents* arr, int countp);
void GetDataForNewDate(int& age, int& day, int& month);
void AddDays(Calendarofevents* arr, int countp, int numdays);
void SubtractDays(Calendarofevents* arr, int countp, int numdays);
void GetDaysOfMonth(int month, int& day);

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Calendarofevents* arrevent;
	Calendarofevents ndate;
	int countdaysn = 0, countdayse = 0;
	int countevent = 0, choicetem, numstr, countpop = 0;
	bool choiceret = true;
	arrevent = new Calendarofevents[countevent];
	while (choiceret)
	{
		Menu();
		cout << "������� ����� ������ ����, ������� ������ ���������" << endl;
		cin >> choicetem;
		switch (choicetem)
		{
		case 1:
			countpop++;
			arrevent = FunSetEvent(arrevent, countpop);
			PutZnInArr(arrevent, countpop, countpop);
			PrintElofClass(arrevent, countpop);
			system("pause");
			break;
		case 2:
			GetInfoNameEvent(arrevent, countpop);
			cout << "������� ����� ������� �� ������, ���� �������� ������ ������: ";
			//�������� �� ������
			cin >> numstr;
			FunFindEvent(numstr, arrevent, countpop);
			break;
		case 3:
			int nage, nday, nmonth;
			GetDataForNewDate(nage, nday, nmonth);
			ndate.SetEvent(nage, nday, nmonth);
			GetInfoNameEvent(arrevent, countpop);
			cout << "������� ����� ������� �� ������, �� �������� �� ����� ������� ���������� ����: ";
			//�������� �� ������
			cin >> numstr;
			arrevent[--numstr].CoutingDaysDate(countdayse,countdaysn,ndate,0);
			system("pause");
			break;
		case 4:
			int numdays, choice;
			cout << "� ���� ������ �� ����� ���������� ���� �������!" << endl;
			cout << "������� �����, ������� ������������� ��������:\n\t(1) ��������� ���\n\t(2) ������ ���" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "������� ���������� ����, �� ������� ������ ����������� ������� �����" << endl;
				cin >> numdays;
				GetInfoNameEvent(arrevent, countpop);
				cout << "������� ����� ������� �� ������, ���� �������� ������ ���������: ";
				cin >> numstr;
				AddDays(arrevent, numstr, numdays);
				arrevent[--numstr].GetDataEvent();
				system("pause");
				break;
			case 2:	
				cout << "������� ���������� ����, �� ������� ������ ����������� ������� �����" << endl;
				cin >> numdays;
				GetInfoNameEvent(arrevent, countpop);
				cout << "������� ����� ������� �� ������, ���� �������� ������ ���������: ";
				cin >> numstr;
				SubtractDays(arrevent, numstr, numdays);
				arrevent[--numstr].GetDataEvent();
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
	//� ��� ������������ ����� ��������� ������ �������� ������ �������? � ������ ��� � ������� ��� ������?
	system("pause");
	delete[] arrevent;
	//������� ������� ��������� �������
	return 0;
}

void Menu()
{
	cout << "  ������������, ��������� ������������, � ��������� �������� ��������� �����������:\n\t(1) ���������� �������.\n\t(2) ������ ���� ���������� �������.\n\t(3) ��������� ������� ����� �������� ����� � ����� �������(� �����, �������, ����).\n\t(4) ������������ ����� �������, ������� ��������� ������������ ������� �� �������� ��������(� �����, �������, ����) � ������� � � ������� ������.\n\t(0) ����� �� ���������.\n";
}

void PutZnInArr(Calendarofevents* arr, int count, int countpop)
{
	int ageu = 0, dayu = 0, monthu = 0, i;
	string nameu = "�����";
	for (i = (countpop - 1); i < count; i++)
	{
		cout << "\t������� ����� " << (i + 1) << endl;
		GetDataForClass(ageu, dayu, monthu, nameu);
		arr[i].SetEvent(ageu, dayu, monthu, nameu);
		system("pause");
		system("cls");
	}
}

void GetDataForClass(int &age,int &day,int &month, string &name)
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

void PrintElofClass(Calendarofevents* arr, int count)
{
	cout << "\t\t������ ������������� �������:" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << "���� �������  "<< (i+1) << endl;
		arr[i].PrintEvent();
	}
}

void GetInfoNameEvent(Calendarofevents* arr, int count)
{
	int i;
	cout << "\t\t������ ��������� �������:" << endl;
	for  (i = 0; i < count; i++)
	{
		cout << '(' << i + 1 << ')' << " ������� - ";
		arr[i].GetNamesEvents();
	}
}
//���������� ������� ������
void FunFindEvent(int num, Calendarofevents* arr, int count)
{
	int i;
	num--;
	for (i = 0; i < count; i++)
	{
		if (i == num)
		{
			arr[i].GetDataEvent();
			cout << endl;
			system("pause");
		}
	}
}

Calendarofevents* FunSetEvent(Calendarofevents* arr, int countp)
{
	int i;
	Calendarofevents* narr1 = 0;
	Calendarofevents* narr2 = 0;
	if (countp == 1)
	{
		narr1 = arr;
		narr2 = new Calendarofevents[countp];
		return narr2;
	}
	else
	{
		delete[] narr2;
		delete[] narr1;
		narr1 = arr;
		narr2 = new Calendarofevents[countp];
		for (i = 0; i < (countp-1); i++)
		{
			narr2[i] = narr1[i]; 
		}
		return narr2;
	}
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
	//������� ����� �����, ����� � �������� ����� ���� ���, � ���������� �����
	GetDaysOfMonth(month, day);	
}

void AddDays(Calendarofevents* arr, int countp, int numdays)
{
	countp--;
	arr[countp].AddationDays(numdays);
}

void SubtractDays(Calendarofevents* arr, int countp, int numdays)
{
	countp--;
	arr[countp].SubtractionDays(numdays);
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