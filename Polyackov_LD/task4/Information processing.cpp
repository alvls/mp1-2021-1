
#include "all.h"

int check(int a, int b)
{
    int choice = INT_MIN;
    while ((choice < a) || (choice > b))
    {
        cin >> choice;
        if ((choice < a) || (choice > b))
        {
            cout << "Введено неверное число. Попробуйте ввести снова." << endl;
            cleaner();
        }
    }
    return choice;
}

size_t check(size_t a, size_t b)
{
    size_t choice = INT_MIN;
    while ((choice < a) || (choice > b))
    {
        cin >> choice;
        if ((choice < a) || (choice > b))
        {
            cout << "Введено неверное число. Попробуйте ввести снова." << endl;
            cleaner();
        }
    }
    return choice;
}

void cleaner()
{
    while (getchar() != '\n');
    cin.clear();
}

bool leap(int month, int year)
{
    if ((((year % 4 == 0) && (year % 100 != 0))) || (year % 400 == 0))
        return true;
    return false;
}

int MonthDays(int month, int year)
{
    int Days[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((month == 2) && leap(month, year))
        return Days[0];
    return Days[month];
}

OneDay CreateNewOneDay()
{
    cout << " Задайте дату подсчёта:" << endl;
    OneDay tmponeday;
    tmponeday.SetDate(CreateNewDate());
    system("cls");
    while (true)
    {
        tmponeday.SetOneCount(CreateNewCount());
        cout << " Продолжить ввод?\n 1) Да\n 2) Нет\n";
        if (check(1,2) == 2)
            break;
        system("cls");
    }
    tmponeday.SetStepsDay();
    return tmponeday;
}

Date CreateNewDate()
{
    cout << "\n Введите год (>=1900): ";
    int tmpyear = check(1900, INT_MAX);
    cout << "\n Введите месяц (от 1 до 12): ";
    int tmpmonth = check(1, 12);
    int tmpdays = MonthDays(tmpmonth, tmpyear);
    cout << "\n Введите день (от 1 до " << tmpdays << "): ";
    tmpdays = check(1, tmpdays);
    return Date(tmpdays, tmpmonth, tmpyear);
}

Count CreateNewCount()
{
    cout << "\n Задайте время подсчёта:\n\n Левая граница:";
    Time tmpLeftB = CreateTimeBound();
    cout << "\n Правая граница:";
    Time tmpRightB = CreateTimeBound();
    cout << "\n Задайте количество шагов: ";
    int tmpSteps = check(0, INT_MAX);
    cout << "\n";
    return Count(tmpLeftB, tmpRightB, tmpSteps);
}

Time CreateTimeBound()
{
    Time tmp;
    cout << "\n Введите час (от 0 до 23): ";
    tmp.hour = check(0, 23);
    cout << "\n Введите минуту (от 0 до 59): ";
    tmp.minutes = check(0, 59);
    return tmp;
}
