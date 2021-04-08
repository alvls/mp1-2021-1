
#include "all.h"

//������������

OneDay::OneDay()
{
	date = Date();
	StepsDay = 0;
	counts = vector<Count>();
}

OneDay::OneDay(Date _date)
{
	date = Date();
	StepsDay = 0;
	counts = vector<Count>();
}

//�������

void OneDay::SetStepsDay()
{
	StepsDay = 0;
	for (size_t i = 0; i < counts.size(); i++)
		StepsDay += counts[i].GetSteps();
}

//����� �� �����

void OneDay::PrintAllCounts()
{
	size_t SizeOfCounts = counts.size();
	for (size_t i = 0; i < SizeOfCounts; i++)
	{
		cout << i + 1 << ") ";
		counts[i].PrintCount();
		cout << "\n";
	}
}

void OneDay::PrintMonthOfDay()
{
	const string MonthName[12] = { "������", "�������", "����", "������", "���", "����", "����", "������", "��������", "�������", "������", "�������" };
	cout << MonthName[GetDate().GetMonth() - 1] << " " << GetDate().GetYear() << " ����\n";
}

//���������

ostream& operator<<(ostream& os, const OneDay& oneday)
{
	size_t SizeOfCounts = oneday.counts.size();
	os << oneday.date << " " << SizeOfCounts << "\n";
	for (size_t i = 0; i < SizeOfCounts; i++)
		os << oneday.counts[i] << "\n";
	os << oneday.StepsDay << "\n";
	return os;
}

istream& operator>>(istream& is, OneDay& oneday)
{
	is >> oneday.date;
	size_t NewSizeOfCounts;
	is >> NewSizeOfCounts;
	oneday.counts.clear();
	for (size_t i = 0; i < NewSizeOfCounts; i++)
	{
		Count tmpcount;
		is >> tmpcount;
		oneday.StepsDay += tmpcount.GetSteps();
		oneday.counts.push_back(tmpcount);
	}
	is >> oneday.StepsDay;
	return is;
}
