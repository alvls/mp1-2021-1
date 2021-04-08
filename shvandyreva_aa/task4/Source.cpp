/*
Разработать класс Термометр.
Класс должен хранить историю наблюдений за температурой в течение одного календарного (не високосного) года.
Наблюдения описываются датой (день, месяц, год) и временем (в часах).
При поступлении нового наблюдения для уже существующих даты и времени старое наблюдение заменяется.
Температура задается в градусах Цельсия.
Класс должен содержать необходимые служебные методы.
Класс должен предоставлять следующие операции:
1) установить начальные дату и время наблюдений,
2) узнать начальные дату и время наблюдений,
3) задать наблюдение,
4) узнать температуру в выбранном наблюдении,
5) задать серию наблюдений для выбранной даты,
6) найти среднюю температуру для выбранной даты, выбранного месяца, за всю историю наблюдений,
7) найти среднюю дневную или ночную температуру для выбранного месяца,
8) сохранить историю наблюдений в файл,
9) считать историю наблюдений из файла.
*/
#include <iostream>
#include <Windows.h>
#include <fstream> //для работы с файлами
#include <sstream> //для рабрты с файлами
using namespace std;

struct Observation
{
	int day, month, year;
	int hour;
	int temperature;
};

class Thertometer
{
private:
	Observation referenceDay;
	Observation observationDay[24][365];
	int sizeMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
public:
	Thertometer(string file)
	{
		ifstream in(file);
		string line;
		int day, month, year, hour;
		double temperature;
		char str[]("Погода.txt");
		if (!in.is_open())
		{
			throw "Невозможно открыть файл 'Погода.txt'.Создайте его!";
		}
		//catch (char* str)
		//{
		//	cout << "Невозможно открыть файл " << str << ". Создайте его!" << endl;
		//	system("pause");
		//	exit(1);
		//}
		int i = 1, j = 0;
		if (in.peek() == EOF)
		{
			referenceDay.day = -1;
			referenceDay.month = -1;
			referenceDay.year = -1;
			referenceDay.hour = -1;
			referenceDay.temperature = -1;
		}
		else
		{
			getline(in, line);
			istringstream ist(line);
			ist >> day;
			ist >> month;
			ist >> year;
			ist >> hour;
			ist >> temperature;
			referenceDay.day = day;
			referenceDay.month = month;
			referenceDay.year = year;
			referenceDay.hour = hour;
			referenceDay.temperature = temperature;
		}
		while (getline(in, line))
		{
			istringstream ist(line);
			ist >> day;
			ist >> month;
			ist >> year;
			ist >> hour;
			ist >> temperature;
			observationDay[i][j].day = day;
			observationDay[i][j].month = month;
			observationDay[i][j].year = year;
			observationDay[i][j].temperature = temperature;
			j++;
			i++;
			if (i == 24)
				i = 1;
			if (j == 365)
				j = 0;
		}
	}
	Thertometer(const Thertometer& now)
	{
		referenceDay = now.referenceDay;
		for (int j = 0; j < 365; j++)
			for (int i = 0; i < 24; i++)
			{
				observationDay[i][j] = now.observationDay[i][j];
			}
	}
	Thertometer& operator=(const Thertometer& now)
	{
		if (this == &now)
		{
			return *this;
		}
		referenceDay = now.referenceDay;
		for (int j = 0; j < 365; j++)
			for (int i = 0; i < 24; i++)
			{
				observationDay[i][j] = now.observationDay[i][j];
			}
		return *this;
	}
	void setReferenceDay(int day, int month, int year, int hour)
	{
		referenceDay.day = day;
		referenceDay.month = month;
		referenceDay.year = year;
		referenceDay.hour = hour;
		referenceDay.temperature = 0;
	}
	Observation getReferenceDay()
	{
		return referenceDay;
	}
	void setObservation(int day, int month, int year, int hour, int temperature)
	{
		Observation temp;
		temp.day = day;
		temp.month = month;
		temp.year = year;
		temp.hour = hour;
		temp.temperature = temperature;
		int d1 = referenceDay.year * 365 + sumOfDays(referenceDay.month) + referenceDay.day;
		int d2 = year * 365 + sumOfDays(month) + day;
		observationDay[hour - 1][d2 - d1] = temp;
	}

	int getTemperature(int day, int month, int year, int hour)
	{
		int d1 = referenceDay.year * 365 + sumOfDays(referenceDay.month) + referenceDay.day;
		int d2 = year * 365 + sumOfDays(month) + day;
		Observation temp = observationDay[hour - 1][d2 - d1];
		return temp.temperature;
	}

	void newFile(const char* name)
	{
		FILE* out;
		fopen_s(&out, name, "w");
		int countDay = 0; //365 дней
		int month = referenceDay.month;
		int day = referenceDay.day;
		int hour = referenceDay.hour + 1;
		int year = referenceDay.year;
		bool end = false;
		int r;
		r = sumOfDays(referenceDay.month) + referenceDay.day;
		while (countDay < 365)
		{
			for (; month < 13; month++) //месяц
			{
				for (; day < sizeMonth[month - 1] + 1; day++) //день
				{
					for (; hour < 25; hour++) //час
					{
						fprintf(out, "%d %d %d %d %d\n", day, month, year, hour - 1, 0);
						if ((countDay == 365) && (hour == referenceDay.hour))
						{
							end = true;
							break;
						}
					}
					hour = 1;
					countDay++;
					r++;
					if (r == 365)
						year++;
					if (end)
						break;
				}
				day = 1;
				if (month == 12)
					month = 0;
				if (end)
					break;
			}
		}
		fclose(out);
	}
	void saveFile(const char* name)
	{
		FILE* out;
		fopen_s(&out, name, "w");
		for (int j = 0; j < 365; j++)
			for (int i = 0; i < 24; i++)
			{
				fprintf(out, "%d %d %d %d %d\n", observationDay[i][j].day,
					observationDay[i][j].month, observationDay[i][j].year,
					observationDay[i][j].hour, observationDay[i][j].temperature);
			}
		fclose(out);
	}
	void readFile(const char* name)
	{
		FILE* in;
		errno_t err = fopen_s(&in, name, "r");
		if (in == NULL)
		{
			return;
		}
		char r[100];
		int j = 0, i = 0;
		while (fgets(r, 100, in))
		{
			r[strlen(r) - 1] = 0;
			sscanf_s(r, "%d %d %d %d %d", &observationDay[i][j].day, &observationDay[i][j].month, &observationDay[i][j].year,
				&observationDay[i][j].hour, &observationDay[i][j].temperature);
			i++;
			if (i == 24)
			{
				i = 0;
				j++;
			}
		}
		fclose(in);
	}
	void setSeries(int day, int month, int year, int from, int to, int* temp)
	{
		for (int h = from; h <= to; h++)
		{
			setObservation(day, month, year, h, temp[h - from]);
		}
	}

	double averageTemperatureForYear() //средняя температура за год
	{
		double sum = 0;
		int days = 0;
		for (int i = 0; i < 365 * 24; i++)
		{
			if (observationDay[i % 24][i / 24].year == 0)
				continue;
			sum += observationDay[i % 24][i / 24].temperature;;
			days++;
		}
		return (sum / days);
	}
	double averageTemperatureForMonth(int month, int year) //средняя температура за месяц
	{
		double sum = 0;
		int count = 0;
		if (referenceDay.month == month && referenceDay.year == year) 
		{ 
			for (int d = referenceDay.day; d <= sizeMonth[month - 1];)
			{
				if (count == 0) 
				{
					for (int k = referenceDay.hour; k <= 24; k++)
					{
						sum += getTemperature(referenceDay.day, month, year, k);
					}
					count++;
				}
				d++;
				for (int h = 1; h <= 24; h++) 
				{
					sum += getTemperature(d, month, year, h);
				}
			}
			double a = (sum / (24*(sizeMonth[month - 1] - referenceDay.day)));
			return (a);
		}
		count = 0;
		if (referenceDay.month == month && ((referenceDay.year + 1) == year)) 
		{
			for (int d = 1; d < referenceDay.day; d++)
			{
				if (count == 0) 
				{
					//для последнего дня
					for (int j = 1; j < referenceDay.hour; j++) 
					{
						sum += getTemperature(referenceDay.day, month, year, j);
					}
					count++;
				}
				for (int h = 1; h <= 24; h++) 
				{
					sum += getTemperature(d, month, year, h);
				}
			}
			double a = (sum / (24*referenceDay.day));
			return (a);
		}
		else 
		{
			for (int d = 1; d <= sizeMonth[month - 1]; d++)
			{
				for (int h = 1; h <= 24; h++)
					sum += getTemperature(d, month, year, h);
			}
			return (sum / (24*sizeMonth[month - 1]));
		}
	}

	double averageTemperatureForDay(int day, int month, int year) //средняя температура за день
	{
		double sum = 0;
		for (int h = 0; h < 24; h++)
		{
			sum += getTemperature(day, month, year, h);
		}
		return (sum / 24);
	}

	double averageTemperatureForInterval(int month, int year, int from, int to) //средняя температура за интервал времени
	{
		double sum = 0;
		for (int d = 1; d <= sizeMonth[month - 1]; d++)
		{
			for (int h = from; h <= to; h++)
				sum += getTemperature(d, month, year, h);
		}
		return (sum / sizeMonth[month - 1]);
	}

	int sumOfDays(int month)
	{
		int sum = 0;
		for (int i = 0; i < month - 1; i++)
		{
			sum += sizeMonth[i];
		}
		return sum;
	}

	~Thertometer()
	{

	}
};
int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Thertometer objThertometer("Погода.txt");
	try
	{
		objThertometer.readFile("Погода.txt");
	}
	catch (char* str)
	{
		cout << str << endl;
		system("pause");
		return 404;
	}
	Observation start = objThertometer.getReferenceDay();
	cout << "Добро пожаловать в программу 'Термометр'!\nСчитывание из файла происходит при запуске, не забудьте сохранить данные в файл по окончании работы." << endl;
	if (start.day < 0)
		cout << "Дата начала наблюдений ещё не задана." << endl;
	else
	{
		cout << "Дата начала наблюдений: " << start.day << '.' << start.month << '.' << start.year << endl;
		cout << "Время: " << start.hour << ".00" << endl;
	}
	int day, month, year, hour, temperature, from, to;
	int* series = new int[25];//для серии наблюдений 
	int r;
	int choice_operation; //номер операции
	while (1)
	{
		cout << "\nСписок операций:" << endl;
		cout << "1) установить начальные дату и время наблюдений," << endl;
		cout << "2) узнать начальные дату и время наблюдений," << endl;
		cout << "3) задать наблюдение," << endl;
		cout << "4) узнать температуру в выбранном наблюдении," << endl;
		cout << "5) задать серию наблюдений для выбранной даты," << endl;
		cout << "6) найти среднюю температуру для выбранной даты, выбранного месяца, за всю историю наблюдений," << endl;
		cout << "7) найти среднюю дневную или ночную температуру для выбранного месяца," << endl;
		cout << "8) сохранить историю наблюдений в файл," << endl;
		cout << "9) Выход" << endl;
		cin >> choice_operation;
		while (choice_operation < 1 || choice_operation > 10)
		{
			cout << " Операции с таким номером нет. Пожалуйста, введите нужный номер ещё раз: ";
			cin >> choice_operation;
		}
		switch (choice_operation)
		{
		case 1: //установить начальные дату и время наблюдений
		{
			int a;
			cout << "При обновлении начальной даты и времени старые наблюдения будут утеряны, хотите установить новую дату? \n 1. да \n 2. нет" << endl;
			cin >> a;
			if (a == 1)
			{
				cout << "Введите день начала наблюдений: " << endl;
				cin >> day;
				cout << "Введите месяц начала наблюдений: " << endl;
				cin >> month;
				cout << "Введите год начала наблюдений: " << endl;
				cin >> year;
				cout << "Введите час начала наблюдений: " << endl;
				cin >> hour;
				objThertometer.setReferenceDay(day, month, year, hour);
				start = objThertometer.getReferenceDay();
				objThertometer.newFile("Погода.txt");
				objThertometer.readFile("Погода.txt"); //считать новый файл, чтобы дальше с ним работать 
			}
			break;
		}
		case 2: //узнать начальные дату и время наблюдений
		{
			if (start.day < 0)
				cout << "Дата начала наблюдений ещё не задана." << endl;
			else
			{
				cout << "Дата начала наблюдений: " << start.day << '.' << start.month << '.' << start.year << endl;
				cout << "Время: " << start.hour << ".00" << endl;
			}
			break;
		}
		case 3: //задать наблюдение 
		{
			if (start.day < 0)
				cout << "Дата начала наблюдений ещё не задана." << endl;
			else
			{
				cout << "Добавление нового наблюдения. " << endl;
				cout << "Введите день: " << endl;
				cin >> day;
				cout << "Введите месяц: " << endl;
				cin >> month;
				cout << "Введите год: " << endl;
				cin >> year;
				cout << "Введите час: " << endl;
				cin >> hour;
				cout << "Введите температуру: " << endl;
				cin >> temperature;
				int d1 = start.year * 365 + objThertometer.sumOfDays(start.month) + start.day;
				int d2 = year * 365 + objThertometer.sumOfDays(month) + day;
				if (d2 < d1)
				{
					cout << "Не удалось задать новое наблюдение, так как указанная дата раньше начала наблюдения. " << endl;
				}
				if (d2 > d1 + 365)
				{
					cout << "Не удалось задать новое наблюдение, так как указанная дата позже начала наблюдения. " << endl;
				}
				else
				{
					objThertometer.setObservation(day, month, year, hour, temperature);
					cout << "Новое наблюдение успешно добавлено. " << endl;
				}
			}
			break;
		}
		case 4: //узнать температуру в выбранном наблюдении
		{
			if (start.day < 0)
				cout << "Дата начала наблюдений ещё не задана." << endl;
			else
			{
				cout << "Чтобы узнать температуру, введите: " << endl;
				cout << "День: " << endl;
				cin >> day;
				cout << "Месяц: " << endl;
				cin >> month;
				cout << "Год: " << endl;
				cin >> year;
				cout << "Час: " << endl;
				cin >> hour;
				cout << "Заданная температура: " << objThertometer.getTemperature(day, month, year, hour) << endl;
			}
			break;
		}
		case 5: //задать серию наблюдений для выбранной даты 
		{
			if (start.day < 0)
				cout << "Дата начала наблюдений ещё не задана." << endl;
			else
			{
				cout << "Чтобы задать серию наблюдений введите: " << endl;
				cout << "День: " << endl;
				cin >> day;
				cout << "Месяц: " << endl;
				cin >> month;
				cout << "Год: " << endl;
				cin >> year;
				cout << "Час начала: " << endl;
				cin >> from;
				cout << "Час конца серии наблюдений: " << endl;
				cin >> to;
				for (int i = 0; i < to - from + 1; i++)
				{
					cout << "Введите температуру для " << from + i << ".00: ";
					cin >> series[i];
				}
				objThertometer.setSeries(day, month, year, from, to, series);
			}
			break;
		}
		case 6: //найти среднюю температуру для выбранной даты, выбранного месяца, за всю историю наблюдений
		{
			if (start.day < 0)
				cout << "Дата начала наблюдений ещё не задана." << endl;
			else
			{
				int operation;
				cout << "Выберите нужный вам пункт:" << endl;
				cout << "1. Найти среднюю температуру для выбранной даты" << endl;
				cout << "2. Найти среднюю температуру для выбранного месяца" << endl;
				cout << "3. Найти среднюю температуру за всю историю наблюдений" << endl;
				cin >> operation;
				switch (operation)
				{
				case 1:
				{
					cout << "Чтобы узнать среднюю температуру, введите: " << endl;
					cout << "День: " << endl;
					cin >> day;
					cout << "Месяц: " << endl;
					cin >> month;
					cout << "Год: " << endl;
					cin >> year;
					cout << "Cpедняя температура за указанную дату: " << objThertometer.averageTemperatureForDay(day, month, year) << endl;
					break;
				}
				case 2:
				{
					cout << "Введите номер месяца и года, за который хотите узнать среднюю температуру: ";
					cin >> month >> year;
					cout << "Средняя температура за выбранный мeсяц: " << objThertometer.averageTemperatureForMonth(month, year) << endl;
					break;
				}
				case 3:
				{
					cout << "Средняя температура за год: " << objThertometer.averageTemperatureForYear() << endl;
					break;
				}
				}
			}
			break;
		}
		case 7: //найти среднюю дневную или ночную температуру для выбранного месяца
		{
			if (start.day < 0)
				cout << "Дата начала наблюдений ещё не задана." << endl;
			else
			{
				cout << "Введите номер месяца и года, за который хотите узнать среднюю дневную и ночную температуру: ";
				cin >> month >> year;
				cout << "Средняя дневная температура за выбранный мeсяц: " << objThertometer.averageTemperatureForInterval(month, year, 11, 16) << endl;
				cout << "Средняя ночная температура за выбранный мeсяц: " << objThertometer.averageTemperatureForInterval(month, year, 0, 6) << endl;
			}
			break;
		}
		case 8: //сохранить историю наблюдений в файл
		{
			objThertometer.saveFile("Погода.txt");
			break;
		}
		case 9:
		{
			return 0;
		}
		}
	}
}