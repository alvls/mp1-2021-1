#pragma once

class Pedometer
{
private:
	Date StartDate;
	vector<OneDay> VecOfDays;
	//Получить вектор из первых дней всех месяцев
	//Нужно, чтобы пользователь мог выбрать месяц
	vector<OneDay> GetVecOfFirstDaysInMonths();
	vector<OneDay> GetMonth(size_t pos);
public:
	//Конструкторы
	Pedometer();
	Pedometer(Date date);

	//Геттеры
	vector<OneDay> GetVecOfDays() { return VecOfDays; };
	size_t GetSize() { return VecOfDays.size(); }
	Date GetStartDate() { return StartDate; }

	//Сеттеры
	void SetStartDate(Date _date) { StartDate = _date; }
	void SetOneDay(OneDay _oneday) { VecOfDays.push_back(_oneday); }

	//Вывод на экран 
	void PrintStartDate() { StartDate.PrintDate(); }
	void PrintPedometer(int type = 0);
	size_t PrintMonths();

	//Обработка "интересной" информации
	double AverageInMonth(size_t pos);
	double AverageInAllHistory();
	double AverageInWeekDay(int selectedweekday);
	OneDay MaxInMonth(size_t pos);
	OneDay MaxInDay();

	//Работа с файлами
	void SaveInFile();
	void ReadFromFile();

	//Операторы
	OneDay& operator[] (const int index) { return VecOfDays.at(index); }
	friend ostream& operator<<(ostream& os, const Pedometer& pedometer);
	friend istream& operator>>(istream& is, Pedometer& pedometer);

	//Random Generator
	void RandomGenerator(size_t value);
};
