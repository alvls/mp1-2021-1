#pragma once

class Pedometer
{
private:
	Date StartDate;
	vector<OneDay> VecOfDays;
	//�������� ������ �� ������ ���� ���� �������
	//�����, ����� ������������ ��� ������� �����
	vector<OneDay> GetVecOfFirstDaysInMonths();
	vector<OneDay> GetMonth(size_t pos);
public:
	//������������
	Pedometer();
	Pedometer(Date date);

	//�������
	vector<OneDay> GetVecOfDays() { return VecOfDays; };
	size_t GetSize() { return VecOfDays.size(); }
	Date GetStartDate() { return StartDate; }

	//�������
	void SetStartDate(Date _date) { StartDate = _date; }
	void SetOneDay(OneDay _oneday) { VecOfDays.push_back(_oneday); }

	//����� �� ����� 
	void PrintStartDate() { StartDate.PrintDate(); }
	void PrintPedometer(int type = 0);
	size_t PrintMonths();

	//��������� "����������" ����������
	double AverageInMonth(size_t pos);
	double AverageInAllHistory();
	double AverageInWeekDay(int selectedweekday);
	OneDay MaxInMonth(size_t pos);
	OneDay MaxInDay();

	//������ � �������
	void SaveInFile();
	void ReadFromFile();

	//���������
	OneDay& operator[] (const int index) { return VecOfDays.at(index); }
	friend ostream& operator<<(ostream& os, const Pedometer& pedometer);
	friend istream& operator>>(istream& is, Pedometer& pedometer);

	//Random Generator
	void RandomGenerator(size_t value);
};
