#pragma once

class Date
{
private:
    int day;
    int month;
    int year;
    int weekday;
    int DaysFromZeroPoint(); //Количество дней, прошедших от 01.01.1900
    void SetWeekDay(); //Задать день недели (вс, пн, вт, ср, чт, пт, сб)
    int MonthDays(int _month); //Количество дней в выбранном месяце
    bool leap(); //Проверка на високосность
public:
    //Конструкторы
    Date(int _day = 1, int _month = 1, int _year = 1900) : day(_day), month(_month), year(_year) { SetWeekDay(); };
    Date(const Date& other);

    //Геттеры
    int GetYear() { return year; }
    int GetMonth() { return month; }
    int GetDay() { return day; }
    int GetWeekDay() { return weekday; }

    //Сеттеры
    void SetYear(int _year) { year = _year; }
    void SetMonth(int _month) { month = _month; }
    void SetDay(int _day) { day = _day; }

    //Вывести дату на экран
    void PrintDate();

    //Разница между датами
    int DateDifference(Date& other) { return abs(DaysFromZeroPoint() - other.DaysFromZeroPoint()); }

    //Операторы
    bool operator== (const Date& other) { return (year == other.year) && (month == other.month) && (day == other.day); }
    bool operator!= (const Date& other) { return (year != other.year) && (month != other.month) && (day != other.day); }
    bool operator< (const Date& other) { return (year <= other.year) && (month <= other.month) && (day < other.day); }
    bool operator> (const Date& other) { return (year >= other.year) && (month >= other.month) && (day > other.day); }
    friend ostream& operator<< (ostream& os, const Date& date);
    friend istream& operator>> (istream& is, Date& date);
    Date& operator= (const Date& other);
    Date operator+ (const int& otherday);
};
