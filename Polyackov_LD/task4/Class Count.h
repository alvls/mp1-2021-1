#pragma once

class Count
{
private:
	int steps;
	Time LeftBound;
	Time RightBound;
public:
	//Конструкторы
	Count(int _steps = 0);
	Count(Time _LeftBound, Time RightBound, int steps= 0);
	Count(const Count& other);

	//Геттеры
	int GetSteps() { return steps; }
	Time GetLeftBound() { return LeftBound; }
	Time GetRightBound() { return RightBound; }
	vector<Time> GetTimeBounds();
	
	//Сеттеры
	void SetSteps(int _steps) { steps = _steps; }
	void SetLeftBound(Time _LeftBound) { LeftBound = _LeftBound; }
	void SetRightBound(Time _RightBound) { RightBound = _RightBound; }

	//Вывести подсчёт на экран
	void PrintCount() { cout << setfill('0') << setw(2) << LeftBound.hour << ":" << setfill('0') << setw(2) << LeftBound.minutes << " - " << setfill('0') << setw(2) << RightBound.hour << ":" << setfill('0') << setw(2) << RightBound.minutes; }
	void PrintCountSteps() { cout << "\n Количество шагов: " << steps << "\n"; }

	//Операторы
	friend ostream& operator<< (ostream& os, const Count& count);
	friend istream& operator>> (istream& is, Count& count);
	Count& operator= (const Count& other);
};
