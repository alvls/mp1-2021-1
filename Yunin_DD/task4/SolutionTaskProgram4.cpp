//Разработать класс Шагомер.
//Класс должен хранить историю подсчета шагов владельца.
//Каждый подсчет описывается датой(день, месяц, год) и интервалом времени(час, минута начала движения, час, минута окончания движения).
//Подсчет ведется в шагах с точностью до единицы.
//Класс должен содержать необходимые служебные методы.
//Класс должен предоставлять следующие операции : 1) установить дату начала подсчетов, 2) узнать дату начала подсчетов, 
//3) задать подсчет, 4) получить информацию о выбранном подсчете, 5) найти среднее число шагов в выбранном месяце или за всю историю наблюдений, 
//6) найти среднее число шагов в выбранный день недели за всю историю наблюдений, 
//7) найти максимальное число шагов в день в выбранном месяце или за всю историю наблюдений и дату, когда оно было достигнуто, 
//8) сохранить историю подсчетов в файл, 9) считать историю подсчетов из файла.

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <cstdlib> // для использования функции exit()

using namespace std;

struct DateandMaxSteps
{
	int maxsteps;
	string date_day;
};

struct Date
{
	int day, month, year;
	
};

struct NumDayCounter
{
	int numelem;
	int quantitycounters;
};

struct Counter
{
	int lefthour,leftminute, righthour, rightminute, countersteps;
};

ostream& operator<<(ostream& out, const Counter& counter)
{
	out << "Время - " << counter.lefthour << ":" << counter.leftminute << " - " << counter.righthour << ":" << counter.rightminute << "\n" << "Количество шагов - " << counter.countersteps << endl;;
	return out;
}

ostream& operator<<(ostream& out, const Date& date)
{
	out << "Дата - " << date.day << "." << date.month << "." << date.year;
	return out;
}

class Day
{
private:
	Date nday;
	Counter* arrcounters;
	int steps, numcounters;

	void CreateArrCounters() 
	{
		arrcounters = new Counter[numcounters + 1];
	}

	void DeleteArrCounters()
	{
		delete[] arrcounters;
		arrcounters = nullptr;
	}

	void IncreaseArrCounters()
	{
		Counter* temp;
		temp = new Counter[numcounters];
		for (int i = 0; i < numcounters; i++)
		{
			temp[i] = arrcounters[i];
		}
		DeleteArrCounters();
		CreateArrCounters();
		for (int i = 0; i < numcounters; i++)
		{
			arrcounters[i] = temp[i];
		}
		delete[] temp;
	}

public:
	Day() :nday{ 18,5,2002 }, arrcounters(nullptr), steps(0),numcounters(0)
	{
		CreateArrCounters();
	}

	void SetDate(int s_day, int s_month, int s_year)
	{
		nday.day = s_day;
		nday.month = s_month;
		nday.year = s_year;
	}

	void SetDate(Date s_date)
	{
		nday.day = s_date.day;
		nday.month = s_date.month;
		nday.year = s_date.year;
	}

	void SetCounter(int s_lefthour, int s_leftminute, int s_righthour, int s_rightminute, int s_countersteps)
	{
		arrcounters[numcounters].lefthour = s_lefthour;
		arrcounters[numcounters].leftminute = s_leftminute;
		arrcounters[numcounters].righthour = s_righthour;
		arrcounters[numcounters].rightminute = s_rightminute;
		arrcounters[numcounters].countersteps = s_countersteps;
		numcounters++;
		IncreaseArrCounters();
	}

	void SetCounter(Counter s_counter)
	{
		arrcounters[numcounters].lefthour = s_counter.lefthour;
		arrcounters[numcounters].leftminute = s_counter.leftminute;
		arrcounters[numcounters].righthour = s_counter.righthour;
		arrcounters[numcounters].rightminute = s_counter.rightminute;
		arrcounters[numcounters].countersteps = s_counter.countersteps;
		numcounters++;
		IncreaseArrCounters();
	}

	int GetNumCounters()
	{
		return numcounters;
	}

	Date GetDate()
	{
		return nday;
	}

	int GetNumSteps()
	{
		steps = 0;
		CountNumStepsPerDay();
		return steps;
	}

	int GetMonthOfDate()
	{
		return nday.month;
	}

	int GetYearOfDate()
	{
		return nday.year;
	}

	int GetDayOfDate()
	{
		return nday.day;
	}

	Counter GetInfoCounter(int countc)
	{
		return arrcounters[countc];
	}

	int GetCodeOfYear()
	{
		int code;
		CountCodeOfYear(code);
		return code;
	}

	int GetCodeMonth()
	{
		int code;
		CountCodeMonth(code);
		return code;
	}
	
	void PrintDates(int count)
	{
		cout << "Ваша дата запись (" << count + 1 << "): " << nday.day << "." << nday.month << "." << nday.year << endl;
	}

	void PrintDate()
	{
		cout << "Ваша начальная дата: " << nday.day << "." << nday.month << "." << nday.year << endl;
	}

	void PrintInfoCounters()
	{
		for (int i = 0; i < numcounters; i++)
		{
			cout << "Подсчёт (" << i + 1 << ")" << endl;
		}
	}

	void CountNumStepsPerDay()
	{
		for (int i = 0; i < numcounters; i++)
		{
			steps += arrcounters[i].countersteps;
		}
	}

	void CountCodeMonth(int& code)
	{
		if ((nday.month == 1) || (nday.month == 10))
		{
			code = 1;
		}
		else if ((nday.month == 4) || (nday.month == 7))
		{
			code = 0;
		}
		else if (nday.month == 5)
		{
			code = 2;
		}
		else if (nday.month == 8)
		{
			code = 3;
		}
		else if ((nday.month == 2) || (nday.month == 3) || (nday.month == 11))
		{
			code = 4;
		}
		else if (nday.month == 6)
		{
			code = 5;
		}
		else if ((nday.month == 9) || (nday.month == 12))
		{
			code = 6;
		}
	}

	void CountCodeOfYear(int& code)
	{
		int centuary,codecentuary,lastnum;
		centuary = nday.year / 100;
		if (centuary == 19)
		{
			codecentuary = 0;
		}
		else if (centuary == 20)
		{
			codecentuary = 6;
		}
		else
		{
			codecentuary = 4;
		}
		lastnum = nday.year % 100;
		code = (codecentuary + lastnum + (lastnum / 4)) % 7;
	}
	
	Day& operator= (const Day& t_day)
	{
		nday = t_day.nday;
		for (int i = 0; i < numcounters; i++)
		{
			arrcounters[i] = t_day.arrcounters[i];
		}
		steps = t_day.steps;
		return *this;
	}

};

class Pedometer
{
private:
	Day* arrdays;//Пусть начальная дата - нулевой элемент массива, 
	int countd;
	int numd;

	void CreateArrDays()
	{
		arrdays = new Day[countd + 1];
	}

	void DeleteArrDays()
	{
		delete[] arrdays;
		arrdays = nullptr;
	}

	void IncreaseArrDays()
	{
		Day* temp;
		temp = new Day[countd];
		for (int i = 0; i < countd; i++)
		{
			temp[i] = arrdays[i];
		}
		DeleteArrDays();
		CreateArrDays();
		for (int i = 0; i < countd; i++)
		{
			arrdays[i] = temp[i];
		}
		delete[] temp;
	}

	Counter GetCounterFromStr(string& str)
	{
		Counter tem = { 0,0,0,0,0 };
		int res, k = 0;
		size_t len;
		len = str.length();
		string temp = "Пустая строка";
		for (int i = 0, j = 0; i < len; i++, j++)
		{
			if (str[i] == ' ')
			{
				res = stoi(temp);
				if (k == 0)
				{
					tem.lefthour = res;
				}
				else if (k == 1)
				{
					tem.leftminute = res;
				}
				else if (k == 2)
				{
					tem.righthour = res;
				}
				else if (k == 3)
				{
					tem.rightminute = res;
				}
				else if (k == 4)
				{
					tem.countersteps = res;
				}
				temp = "Пустая строка";
				k++;
				j = 0;
				i++;
			}
			temp[j] = str[i];
		}
		return tem;
	}

	int CountWhiteSymbols(string str)
	{
		int num = 0;
		size_t len;
		len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (str[i] == ' ')
			{
				num++;
			}
		}
		return num;
	}

	Date GetDateFromStr(string& str)
	{
		int k = 0;
		size_t len;
		Date tem = { 0,0,0 };
		string temp = "Пустая строка";
		len = str.length();
		for (int i = 0, j = 0; i <= len; i++, j++)
		{
			if (str[i] == ' ')
			{
				int res = stoi(temp);
				if (k == 0)
				{
					tem.day = res;
				}
				else if (k == 1)
				{
					tem.month = res;
				}
				else
				{
					tem.year = res;
				}
				temp = "Пустая строка";
				j = 0;
				k++;
				i++;
			}
			temp[j] = str[i];
		}
		return tem;
	}

	NumDayCounter GetNumFromStr(string& str)
	{
		int res, k = 0;
		size_t len;
		string temp = "Пустая строка";
		NumDayCounter tem = { 0,0 };
		len = str.length();
		for (int i = 0, j = 0; i < len; i++, j++)
		{
			if (str[i] == ' ')
			{
				res = stoi(temp);
				if (k == 0)
				{
					tem.numelem = res;
				}
				else
				{
					tem.quantitycounters = res;
				}
				temp = "Пустая строка";
				k++;
				j = 0;
				i++;
			}
			temp[j] = str[i];
		}
		return tem;
	}

public:

	Pedometer(int d_coutd = 0) :arrdays(nullptr), countd(d_coutd), numd(0)
	{ 
		CreateArrDays();
	}

	void SetDayDate(int s_day, int s_month, int s_year)
	{
		arrdays[countd].SetDate(s_day, s_month, s_year);
		countd++;
		IncreaseArrDays();
	}

	void SetDayDate(Date s_date)
	{
		arrdays[countd].SetDate(s_date);
		countd++;
		IncreaseArrDays();
	}

	void SetNumOfDay(int num)
	{
		numd = num;
	}

	void SetDayCounter(int s_lefthour, int s_leftminute, int s_righthour, int s_rightminute, int s_countersteps)
	{
		arrdays[numd - 1].SetCounter(s_lefthour, s_leftminute, s_righthour, s_rightminute, s_countersteps);
	}

	void SetDayCounter(Counter s_counter, NumDayCounter s_num)
	{
		arrdays[s_num.numelem].SetCounter(s_counter);
	}

	Date GetStartDayDate()
	{
		Date temp;
		temp = arrdays[0].GetDate();
		return temp;
	}

	void PrintDaysDate()
	{
		for (int i = 0; i < countd; i++)
		{
			arrdays[i].PrintDates(i);
		}
	}

	void PrintStartDayDate()
	{
		arrdays[0].PrintDate();
	}

	void PrintDayCounter()
	{
		arrdays[numd - 1].PrintInfoCounters();
	}
	
	Counter GetInfoAboutCounter(int i)
	{
		Counter temp;
		temp = arrdays[numd -1].GetInfoCounter(i - 1);
		return temp;
	}

	int FindAverageNumofMonth(int month,int year)
	{
		int month_day, year_day;
		int avernum = 0,j = 0,numsteps = 0;
		for (int i = 0; i < countd; i++)
		{
			month_day = arrdays[i].GetMonthOfDate();
			year_day = arrdays[i].GetYearOfDate();
			if ((month == month_day)&&(year == year_day))
			{
				numsteps = arrdays[i].GetNumSteps();
				avernum += numsteps;
				j++;
			}
		}
		if (j != 0)
		{
			avernum = avernum / j;
			return avernum;
		}
		else
		{
			return avernum;
		}
	}

	int FindAveNumStepsOfAllTime()
	{
		int avernum = 0, j = 0, numsteps = 0;
		for (int i = 0; i < countd; i++)
		{
			numsteps = arrdays[i].GetNumSteps();
			avernum += numsteps;
			j++;
		}
		if (j != 0)
		{
			avernum = avernum / j;
			return avernum;
		}
		else
		{
			return avernum;
		}
	}

	int ConvertNumIntoCode(int num_day)
	{
		int codeday = -1;
		if (num_day == 1)
		{
			codeday = 2;
		}
		if (num_day == 2)
		{
			codeday = 3;
		}
		if (num_day == 3)
		{
			codeday = 4;
		}
		if (num_day == 4)
		{
			codeday = 5;
		}
		if (num_day == 5)
		{
			codeday = 6;
		}
		if (num_day == 6)
		{
			codeday = 0;
		}
		if (num_day == 7)
		{
			codeday = 1;
		}
		return codeday;
	}

	int FindAveNumStepsInDayOfWeek(int num_day)
	{
		int codeday,numsteps = 0,j = 0,averagenum = 0,year,month;
		codeday = ConvertNumIntoCode(num_day);
		for (int i = 0; i < countd; i++)
		{
			month = arrdays[i].GetMonthOfDate();
			year = arrdays[i].GetYearOfDate();
			int numday,codemonth,codeyear,code;
			numday = arrdays[i].GetDayOfDate();
			codemonth = arrdays[i].GetCodeMonth();
			codeyear = arrdays[i].GetCodeOfYear();
			code = (numday + codemonth + codeyear) % 7;
			if ((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 100 == 0 && year % 400 == 0))
			{
				if ((month == 1)||(month == 2))
				{
					code--;
				}
			}
			if (code == codeday)
			{
				numsteps = arrdays[i].GetNumSteps();
				averagenum += numsteps;
				j++;
			}
		}
		if (j != 0)
		{
			averagenum = averagenum / j;
			return averagenum;
		}
		else
		{
			return averagenum;
		}
	}

	DateandMaxSteps FindMaxNumStepsInMonth(int month, int year)
	{
		DateandMaxSteps temp;
		int month_day, year_day,day_day;
		int maxnumsteps = 0, numsteps = 0;
		string name;
		for (int i = 0; i < countd; i++)
		{
			day_day = arrdays[i].GetDayOfDate();
			month_day = arrdays[i].GetMonthOfDate();
			year_day = arrdays[i].GetYearOfDate();
			if ((month == month_day) && (year == year_day))
			{
				numsteps = arrdays[i].GetNumSteps();
				if (numsteps > maxnumsteps)
				{
					maxnumsteps = numsteps;
					temp.maxsteps = maxnumsteps;
					name = to_string(day_day) + "." + to_string(month_day) + "." + to_string(year_day);
					temp.date_day = name;
				}
			}
		}
		return temp;
	}

	DateandMaxSteps FindMaxNumStepsAllTime()
	{
		DateandMaxSteps temp;
		int month_day, year_day, day_day;
		int maxnumsteps = 0, numsteps = 0;
		string name;
		for (int i = 0; i < countd; i++)
		{
			day_day = arrdays[i].GetDayOfDate();
			month_day = arrdays[i].GetMonthOfDate();
			year_day = arrdays[i].GetYearOfDate();
			numsteps = arrdays[i].GetNumSteps();
			if (numsteps > maxnumsteps)
			{
				maxnumsteps = numsteps;
				temp.maxsteps = maxnumsteps;
				name = to_string(day_day) + "." + to_string(month_day) + "." + to_string(year_day);
				temp.date_day = name;
			}
		}
		return temp;
	}

	void ReadHisOfCountersIntoFail()
	{
		int countpr = 0;
		Date date1 = { 0,0,0 };
		NumDayCounter dayc;
		Counter counterf;
		// Попытаемся прочитать содержимое файла SomeText.txt
		ifstream inf("SomeText.txt");
		if (!inf)
		{
			// то выводим следующее сообщение об ошибке и выполняем функцию exit()
			cerr << "Uh oh, SomeText.txt could not be opened for reading!" << endl;
			exit(1);
		}
		// Пока есть, что читать,
		while (inf)
		{
			//пробежаться прежде по строке, определить сколько пробелов, чтобы определить, что делать 
			// то перемещаем то, что можем прочитать, в строку, а затем выводим эту строку на экран
			string strInput;
			Date date1;
			getline(inf, strInput);
			countpr = CountWhiteSymbols(strInput);
			if (countpr == 2)
			{
				dayc = GetNumFromStr(strInput);
			}
			else if (countpr == 3)
			{
				date1 = GetDateFromStr(strInput);
				SetDayDate(date1);
			}
			else if (countpr == 5)
			{
				counterf = GetCounterFromStr(strInput);
				SetDayCounter(counterf, dayc);
			}
			//cout << strInput << endl;
		}
		//Первая строка - дата начала, затем следующая дата, число строк что будет выделено для дат файла, строки с датами
		//номер записи в которую хочу поместить подсчёты, их число, данные подсчётов
	}

	void SaveInFile()
	{
		string a;
		Date date1;
		int numel;
		Counter counter1;
		ofstream fout("РезультатыПодсчётов.txt");
		if (!fout)
		{
			cout << "Случилась непредвиденная ошибка!" << endl;
			exit(1);
		}
		else
		{
			fout << "\t\tРезультаты подсчётов:\n\n";
			for (int i = 0; i < countd; i++)
			{
				date1 = arrdays[i].GetDate();
				fout << date1;
				numel = arrdays[i].GetNumCounters();
				for (int j = 0; j < numel; j++)
				{
					counter1 = arrdays[i].GetInfoCounter(j);
					fout << "\t\t" << counter1;
				}
				fout << endl;
			}
			fout.close();
		}
	}

	~Pedometer()
	{
		delete[] arrdays;
	}
};

void GetDaysOfMonth(int month, int& day, bool checkv);
void Menu();
void GetDate(int& year, int& day, int& month);

int main()
{
	Pedometer pedom;
	Counter counter;
	Date date;
	int dayofweek;
	DateandMaxSteps dmax;
	int day, month, year, choice, number;
	int year1, month1;
	int lefth, leftmin, righth, rightmin, numsteps;
	bool exit1 = true;
	int chnumday;
	setlocale(LC_ALL, "Rus");
	cout << "\n\t\tЗдравствуйте, уважаемый пользователь, вас приветствует программа \"Шагомер\".\n Давайте начнём работу.Введите дату начала пользования.\n";
	GetDate(year, day, month);
	pedom.SetDayDate(day, month, year);
	while (exit1)
	{
		Menu();
		cout << "Введите номер режима, который вы хотите выбрать: " << endl;
		choice = -1;
		while ((choice < 0) || (choice > 11))
		{
			cin >> choice;
			if ((choice < 0) || (choice > 11))
			{
				cout << "Вы ввели неверный номер, повторите ввод!" << endl;
			}
		}
		switch (choice)
		{
		case 1:
			date = pedom.GetStartDayDate();
			pedom.PrintStartDayDate();
			break;
		case 2:
			pedom.PrintDaysDate();
			cout << "Введите номер выбранного дня:" << endl;
			cin >> chnumday;
			pedom.SetNumOfDay(chnumday);
			cout << "Введите данные для подсчёта: \"Час начала подсчёта\" \"Минута начала подсчёта\":\"Час окончания подсчёта \" \"Минута окончания подсчёта \" \"Количество шагов\"" << endl;
			cin >> lefth >> leftmin >> righth >> rightmin >> numsteps;
			pedom.SetDayCounter(lefth, leftmin, righth, rightmin, numsteps);
			cout << "Подсчёт успешно установлен" << endl;
			break;
		case 3:
			pedom.PrintDaysDate();
			cout << "Введите номер выбранного дня:" << endl;
			cin >> chnumday;
			pedom.SetNumOfDay(chnumday);
			pedom.PrintDayCounter();
			cout << "Введите номер выбранного подсчёта:" << endl;
			cin >> chnumday;
			counter = pedom.GetInfoAboutCounter(chnumday);
			cout << counter << endl;
			break;
		case 4:
			cout << "Введите месяц и год, за который хотите узнвть статистику: " << endl;
			cin >> month1 >> year1;
			number = pedom.FindAverageNumofMonth(month1, year1);
			cout << "Ваше среднее число шагов за выбранный месяц = " << number << endl;
			break;
		case 5:
			number = pedom.FindAveNumStepsOfAllTime();
			cout << "Ваше среднее число шагов за весь период = " << number << endl;
			break;
		case 6:
			cout << "Введите номер дня недели, за который хотите найти среднее число шагов:" << endl;
			cin >> dayofweek;
			number = pedom.FindAveNumStepsInDayOfWeek(dayofweek);
			cout << "Ваше среднее число шагов за выбранный день недели = " << number << endl;
			break;
		case 7:
			cout << "Введите месяц и год, за который хотите узнвть статистику: " << endl;
			cin >> month1 >> year1;
			dmax = pedom.FindMaxNumStepsInMonth(month1, year1);
			cout << "Ваше максимальное число шагов за выбранный месяц = " << dmax.maxsteps << endl << "Дата этого дня: " << dmax.date_day << endl;
			break;
		case 8:
			dmax = pedom.FindMaxNumStepsAllTime();
			cout << "Ваше максимальное число шагов за всё время = " << dmax.maxsteps << endl << "Дата этого дня: " << dmax.date_day << endl;
			break;
		case 9:
			pedom.SaveInFile();
			cout << "Запись в файл произошла успешно!" << endl;
			break;
		case 10:
			pedom.ReadHisOfCountersIntoFail();
			break;
		case 11:
			GetDate(year, day, month);
			pedom.SetDayDate(day,month,year);
			cout << "Дата успешно добавлена" << endl;
			break;
		default:
			cout << "Программа завершила свою работа. Всего хорошего, досвидания!" << endl;
			system("pause");
			exit1 = false;
			break;
		}
		system("pause");
		system("cls");
	}
	//Перегрузить << для а
	system("pause");
	return 0;
}

void GetDate(int& year, int& day, int& month)
{
	bool checkv = false;//Проверка на високосность.
	year = 0, day = 0, month = 0;
	cout << "(1) Введём год, например, \"2000\"\n";
	while ((year > 2121) || (year < 1921))
	{
		cout << "Введите год события, возможный диапазон от \"1921\" до \"2121\"" << endl;
		cin >> year;
		if ((year > 2121) || (year < 1921))
		{
			cout << "Ошибка!Повторите ввод!";
		}
	}
	if ((year % 4 == 0 && year % 100 != 0)||(year % 4 == 0 && year % 100 == 0 && year % 400 == 0))
	{
		checkv = true;
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
	GetDaysOfMonth(month, day, checkv);
}

void Menu()
{
	cout << "  Здравствуйте, уважаемый пользователь, в программе доступны следующие возможности:\n\t(1) Узнать дату начала подсчетов.\n\t(2) Задать подсчет.\n\t(3) Получить информацию о выбранном подсчете.\n\t(4) Найти среднее число шагов в выбранном месяце.\n\t(5) Найти среднее число шагов за всю историю наблюдений.\n\t(6) Найти среднее число шагов в выбранный день недели за всю историю наблюдений.\n\t(7) Найти максимальное число шагов в день в выбранном месяце и дату, когда оно было достигнуто.\n\t(8) Найти максимальное число шагов в день за всю историю наблюдений и дату, когда оно было достигнуто.\n\t(9) Сохранить историю подсчетов в файл.\n\t(10) Считать историю подсчетов из файла.\n\t(11) Добавить ещё новый день.\n\t(0) Выход из программы.\n";
}

void GetDaysOfMonth(int month, int& day, bool checkv)
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
		if (checkv)
		{
			while ((day > 29) || (day < 1))
			{
				cout << "Введите день события, возможный диапазон от \"1\" до \"28\"" << endl;
				cin >> day;
				if ((day > 29) || (day < 1))
				{
					cout << "Ошибка!Повторите ввод!";
				}
			}
		}
		else
		{
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
}
