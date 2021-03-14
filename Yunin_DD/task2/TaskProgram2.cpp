//2.1.Календарь событий
//Разработать класс Календарь событий.
//Класс должен позволять сохранять даты заданных событий в формате : год, месяц, день(в диапазоне от 1 января 1 года до 31 декабря 2020 года), 
//наименование события.
//На каждый день может приходиться только одно событие.Общее число событий – не более 30.
//Класс должен предоставлять операции : 1) установить событие, 2) узнать дату выбранного события, 
//3) вычислить разницу между заданной датой и датой события(в годах, месяцах, днях), 
//4) сформировать новое событие, сдвинув выбранное существующее событие на заданное смещение(в годах, месяцах, днях) в меньшую и в большую сторону.
//Класс должен содержать все необходимые конструкторы, деструктор, оператор присваивания, а также «уметь» выводить себя на консоль.

//Не использовать високосность 
//Учесть кол-во дней

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
		nameevent = "Пусто";
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
		cout << "Событие успешно установлено!" << endl;
	}

	void SetEvent(int agetemp, int daytemp, int monthtemp)
	{
		age = agetemp;
		day = daytemp;
		month = monthtemp;
	}

	void PrintEvent()
	{
		cout << "\tНебольшая презентация вашего события" << endl;
		cout << "(1) - Наименование вашего события    " << "\"" << nameevent << "\"" << endl;;
		cout << "(2) - День вашего события    " << "\"" << day << "\"" << endl;
		cout << "(3) - Месяц вашего события    " << "\"" << month << "\"" << endl;
		cout << "(4) - Год вышего события    " << "\"" << age << "\"" << endl;
	}
	
	void GetDataEvent()
	{
		//Выводится дата события
		cout << "Дата события: " << day << ' ' << month << ' ' << age << endl;
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
			cout << "До события осталось " << days1 << "дней" << endl;
		}
		else if (days1 < 0)
		{
			cout << "Событие завершилось " << abs(days1) << "дней назад" << endl;
		}
		else
		{
			cout << "Событие сегодня!" << endl;
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

//Оператор копирования понадобится для добавления события по мере необходимости. С помощью зачистки памяти и объявления нового места в памяти.
//Как для Копирования массива.

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
		cout << "Введите номер пункта меню, который хотите выполнить" << endl;
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
			cout << "Введите номер события из списка, дату которого хотите узнать: ";
			//Проверка на ошибку
			cin >> numstr;
			FunFindEvent(numstr, arrevent, countpop);
			break;
		case 3:
			int nage, nday, nmonth;
			GetDataForNewDate(nage, nday, nmonth);
			ndate.SetEvent(nage, nday, nmonth);
			GetInfoNameEvent(arrevent, countpop);
			cout << "Введите номер события из списка, до которого мы будем считать количество дней: ";
			//Проверка на ошибку
			cin >> numstr;
			arrevent[--numstr].CoutingDaysDate(countdayse,countdaysn,ndate,0);
			system("pause");
			break;
		case 4:
			int numdays, choice;
			cout << "В этом режиме мы будем переносить дату события!" << endl;
			cout << "Введите номер, которой соответствует операции:\n\t(1) Прибавить дни\n\t(2) Отнять дни" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Введите количество дней, на которое хотите переместить событие вперёд" << endl;
				cin >> numdays;
				GetInfoNameEvent(arrevent, countpop);
				cout << "Введите номер события из списка, дату которого хотите перенести: ";
				cin >> numstr;
				AddDays(arrevent, numstr, numdays);
				arrevent[--numstr].GetDataEvent();
				system("pause");
				break;
			case 2:	
				cout << "Введите количество дней, на которое хотите переместить событие назад" << endl;
				cin >> numdays;
				GetInfoNameEvent(arrevent, countpop);
				cout << "Введите номер события из списка, дату которого хотите перенести: ";
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
			cout << "Уже уходите, были рады вас видеть.Всего доброго!" << endl;
			system("pause");
			choiceret = false;
			break;
		default:
			break;
		}
		system("cls");
	}
	//А где пользователю будет правильно ввести название своего события? В классе или в функции вне класса?
	system("pause");
	delete[] arrevent;
	//Функция выводит доступные события
	return 0;
}

void Menu()
{
	cout << "  Здравствуйте, уважаемый пользователь, в программе доступны следующие возможности:\n\t(1) Установить событие.\n\t(2) Узнать дату выбранного события.\n\t(3) Вычислить разницу между заданной датой и датой события(в годах, месяцах, днях).\n\t(4) Сформировать новое событие, сдвинув выбранное существующее событие на заданное смещение(в годах, месяцах, днях) в меньшую и в большую сторон.\n\t(0) Выход из программы.\n";
}

void PutZnInArr(Calendarofevents* arr, int count, int countpop)
{
	int ageu = 0, dayu = 0, monthu = 0, i;
	string nameu = "Пусто";
	for (i = (countpop - 1); i < count; i++)
	{
		cout << "\tСобытие номер " << (i + 1) << endl;
		GetDataForClass(ageu, dayu, monthu, nameu);
		arr[i].SetEvent(ageu, dayu, monthu, nameu);
		system("pause");
		system("cls");
	}
}

void GetDataForClass(int &age,int &day,int &month, string &name)
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

void PrintElofClass(Calendarofevents* arr, int count)
{
	cout << "\t\tСписок установленных событий:" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << "Ваше событие  "<< (i+1) << endl;
		arr[i].PrintEvent();
	}
}

void GetInfoNameEvent(Calendarofevents* arr, int count)
{
	int i;
	cout << "\t\tСписок доступных событий:" << endl;
	for  (i = 0; i < count; i++)
	{
		cout << '(' << i + 1 << ')' << " Событие - ";
		arr[i].GetNamesEvents();
	}
}
//Вызывается функция поиска
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