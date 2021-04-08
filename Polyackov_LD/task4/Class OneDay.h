#pragma once

class OneDay
{
private:
	Date date;
	int StepsDay;
	vector<Count> counts;
public:
	//Конструкторы
	OneDay();
	OneDay(Date _date);

	//Геттеры
	Date GetDate() { return date; }
	int GetStepsDay() { return StepsDay; }
	vector<Count> GetCounts() { return counts; }
	Count GetCountAtInd(const int index) { return counts.at(index); }
	size_t GetCountSize() { return counts.size(); }

	//Сеттеры
	void SetDate(Date _date) { date = _date; }
	void SetStepsDay();
	void SetOneCount(Count _count) { counts.push_back(_count); }

	//Вывод на экран
	void PrintDateOfDay() { date.PrintDate(); }
	void PrintAllCounts();
	void PrintMonthOfDay();

	//Операторы
	friend ostream& operator<<(ostream& os, const OneDay& oneday);
	friend istream& operator>>(istream& is, OneDay& oneday);
};
