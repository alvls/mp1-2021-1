
#include "all.h"

int MonthDays(int month, int year)
{
    int Days[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((month == 2) && (((year % 4 == 0) && (year % 100 != 0))) || (year % 400 == 0))
        return Days[0];
    return Days[month];
}

int proverka(int a, int b)
{
    int vibor = -1;
    while ((vibor < a) || (vibor > b))
    {
        cin >> vibor;
        if ((vibor < a) || (vibor > b))
        {
            cout << "Введено неверное число. Попробуйте ввести снова." << endl;
            while (getchar() != '\n');
            cin.clear();
        }
    }
    return vibor;
}

Date CreateNewDate()
{
    Date tmpDate;
    string tmpStr; //Для ввода информации
    int tmpdays;
    cout << "\n Введите год (>=1): ";
    tmpDate.SetYear(proverka(1, INT_MAX));
    cout << "\n Введите месяц (от 1 до 12): ";
    tmpDate.SetMonth(proverka(1, 12));
    tmpdays = MonthDays(tmpDate.GetMonth(), tmpDate.GetYear());
    cout << "\n Введите день (от 1 до " << tmpdays << "): ";
    tmpDate.SetDay(proverka(1, tmpdays));
    cout << "\n Введите событие: ";
    while (getchar() != '\n');
    cin.clear();
    getline(cin, tmpStr);
    tmpDate.SetEvent(tmpStr);
    return tmpDate;
}

int SelectedEvent(Calendar& list)
{
    int tmpnum = -1;
    list.PrintCalendar();
    cout << "\n Выберите нужное Вам событие: ";
    tmpnum = proverka(1, list.GetCounter()) - 1;
    system("cls");
    cout << "\n Выбранное событие: " << tmpnum + 1 << ") " << list[tmpnum].GetEvent() << endl;
    return tmpnum;
}
