#pragma once

class Date
{
private:
    int year;
    int month;
    int day;
    string event;
    int SumOfDays();
public:
    //�����������
    Date(int _day = 1, int _month = 1, int _year = 1, string _event = "�����\0") : day(_day), month(_month), year(_year), event(_event) {}

    //����������� �����������
    Date(const Date& other);

    //����� �� �����
    void PrintDate() { cout << " " << day << " " << MonthName[month - 1] << " " << year << " ����" << endl; }

    //�������
    int GetYear() { return year; }
    int GetMonth() { return month; }
    int GetDay() { return day; }
    string GetEvent() { return event; }

    //�������
    void SetYear(int year) { this->year = year; }
    void SetMonth(int month) { this->month = month; }
    void SetDay(int day) { this->day = day; }
    void SetEvent(string event) { this->event = event; }

    //������� ����� ������
    int DateDifference(Date& other) { return abs(SumOfDays() - other.SumOfDays()); }

    //���������
    bool operator== (const Date& other) { return (year == other.year) && (month == other.month) && (day == other.day); }
    bool operator!= (const Date& other) { return (year != other.year) && (month != other.month) && (day != other.day); }
    Date& operator= (const Date& other);
    Date operator+ (const int& otherday);
    Date operator- (const int& otherday);
    ~Date() {};
};
