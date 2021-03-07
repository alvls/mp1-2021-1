
#include "all.h"
#pragma warning(disable : 4996)

int Date::SumOfDays()
{
    int sum = 0;
    for (int i = 1; i < year; i++)
    {
        sum += 365;
        if ((i % 400 == 0) || ((i % 4 == 0) && (i % 100 != 0)))
            sum += 1;
    }
    for (int i = 1; i < month; i++)
        sum += MonthDays(i, year);
    sum += day;
    return sum;
}

//Конструктор копирования
Date::Date(const Date& other) {
    year = other.year;
    month = other.month;
    day = other.day;
    event = other.event;
}

Date& Date::operator= (const Date& other)
{
    if (this == &other)
        return *this;
    year = other.year;
    month = other.month;
    day = other.day;
    event = other.event;
    return *this;
}

Date Date::operator+ (const int& otherday)
{
    Date tmp;
    tmp.year = year;
    tmp.month = month;
    tmp.day = day + otherday;
    char* days = new char[11];
    _itoa(otherday, days, 10);
    tmp.event = event + " (+" + days + " д.)";
    delete[]days;
    //Конвертер
    while (tmp.day > MonthDays(tmp.month, tmp.year))
    {
        tmp.day -= MonthDays(tmp.month, tmp.year);
        tmp.month++;
        if (tmp.month == 13)
        {
            tmp.month = 1;
            tmp.year++;
        }
    }
    return tmp;
}

Date Date::operator- (const int& otherday)
{
    Date tmp;
    tmp.year = year;
    tmp.month = month;
    char* days = new char[11];
    _itoa(otherday, days, 10);
    tmp.event = event + " (-" + days + " д.)";
    delete[]days;
    //Конвертер
    if (day > otherday)
    {
        tmp.day = day - otherday;
        return tmp;
    }
    if (day == otherday)
    {
        tmp.month--;
        if (tmp.month == 0)
            tmp.month = 12;
        tmp.day = MonthDays(tmp.month, tmp.year);
        return tmp;
    }
    if (day < otherday)
    {
        tmp.month--;
        if (tmp.month == 0)
        {
            tmp.month = 12;
            tmp.year--;
        }
        tmp.day = otherday - day;
        while (tmp.day >= MonthDays(tmp.month, tmp.year))
        {
            tmp.day -= MonthDays(tmp.month, tmp.year);
            tmp.month--;
            if (tmp.month == 0)
            {
                tmp.month = 12;
                tmp.year--;
            }
        }
        tmp.day = MonthDays(tmp.month, tmp.year) - tmp.day;
    }
    return tmp;
}
