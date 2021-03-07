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
    //Конструктор
    Date(int _day = 1, int _month = 1, int _year = 1, string _event = "Пусто\0") : day(_day), month(_month), year(_year), event(_event) {}

    //Конструктор копирования
    Date(const Date& other);

    //Вывод на экран
    void PrintDate() { cout << " " << day << " " << MonthName[month - 1] << " " << year << " года" << endl; }

    //Геттеры
    int GetYear() { return year; }
    int GetMonth() { return month; }
    int GetDay() { return day; }
    string GetEvent() { return event; }

    //Сеттеры
    void SetYear(int year) { this->year = year; }
    void SetMonth(int month) { this->month = month; }
    void SetDay(int day) { this->day = day; }
    void SetEvent(string event) { this->event = event; }

    //Разница между датами
    int DateDifference(Date& other) { return abs(SumOfDays() - other.SumOfDays()); }

    //Операторы
    bool operator== (const Date& other) { return (year == other.year) && (month == other.month) && (day == other.day); }
    bool operator!= (const Date& other) { return (year != other.year) && (month != other.month) && (day != other.day); }
    Date& operator= (const Date& other);
    Date operator+ (const int& otherday);
    Date operator- (const int& otherday);
    ~Date() {};
};