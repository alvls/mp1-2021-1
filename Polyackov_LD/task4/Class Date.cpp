
#include "all.h"

//private 

int Date::DaysFromZeroPoint()
{
    int sum = 0;
    for (int i = 1900; i < year; i++)
    {
        sum += 365;
        if ((i % 400 == 0) || ((i % 4 == 0) && (i % 100 != 0)))
            sum += 1;
    }
    for (int i = 1; i < month; i++)
        sum += MonthDays(i);
    sum += day;
    return sum;
}

void Date::SetWeekDay()
{
    int daysbtw = DaysFromZeroPoint(); //days between *this и 01.01.1900 (нулевая точка отсчёта для шагомера, понедельник) 
    weekday = daysbtw - (daysbtw / 7) * 7;
}

int Date::MonthDays(int _month)
{
    int Days[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((_month == 2) && leap())
        return Days[0];
    return Days[_month];
}

bool Date::leap()
{
    if ((((year % 4 == 0) && (year % 100 != 0))) || (year % 400 == 0))
        return true;
    return false;
}

//Конструктор копирования

Date::Date(const Date& other) {
    year = other.year;
    month = other.month;
    day = other.day;
    weekday = other.weekday;
}

//Вывести дату на экран

void Date::PrintDate()
{
    const string MonthName[12] = { "января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря" };
    const string WeekDayName[7] = { "(воскресенье)", "(понедельник)", "(вторник)", "(среда)", "(четверг)", "(пятница)", "(суббота)" };
    cout << day << " " << MonthName[month - 1] << " " << year << " года " << WeekDayName[weekday];
}

//Операторы

ostream& operator<<(ostream& os, const Date& date)
{
    os << date.day << " " << date.month <<  " " << date.year << " " << date.weekday;
    return os;
}

istream& operator>>(istream& is, Date& date)
{
    is >> date.day;
    is >> date.month;
    is >> date.year;
    is >> date.weekday;
    return is;
}

Date& Date::operator= (const Date& other)
{
    if (this == &other)
        return *this;
    year = other.year;
    month = other.month;
    day = other.day;
    weekday = other.weekday;
    return *this;
}

Date Date::operator+ (const int& otherday)
{
    Date tmp;
    tmp.year = year;
    tmp.month = month;
    tmp.day = day + otherday;
    while (tmp.day > MonthDays(tmp.month))
    {
        tmp.day -= MonthDays(tmp.month);
        tmp.month++;
        if (tmp.month == 13)
        {
            tmp.month = 1;
            tmp.year++;
        }
    }
    tmp.SetWeekDay();
    return tmp;
}
