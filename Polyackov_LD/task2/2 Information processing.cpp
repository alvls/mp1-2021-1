
#include "all.h"

int MonthDays(int month, int year)
{
    int Days[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((month == 2) && ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))))
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

int SelectedEvent(int counter, Date* arr)
{
    int tmpnum = -1;
    cout << "\n Перечень событий: " << endl;
    for (int i = 0; i < counter; i++)
        cout << i + 1 << ") " << arr[i].GetEvent() << endl;
    cout << "\n Выберите нужное Вам событие: " << endl;
    tmpnum = proverka(1, counter);
    tmpnum--;
    system("cls");
    cout << "\n Выбранное событие: " << tmpnum + 1 << ") " << arr[tmpnum].GetEvent() << endl;
    return tmpnum;
}

Date* RecreateArr(Date* arr, int& size, int counter)
{
    Date* tmparr = new Date[counter];
    for (int i = 0; i < counter; i++)
        tmparr[i] = arr[i];
    size *= 2;
    delete[]arr;
    arr = nullptr;
    arr = new Date[size];
    for (int i = 0; i < counter; i++)
        arr[i] = tmparr[i];
    delete[]tmparr;
    tmparr = nullptr;
    return arr;
}

Date* ExistDate(Date* arr, int& counter)
{
    if (arr[counter - 1].GetYear() <= 0)
    {
        cout << "\n К сожалению, дата последнего события получила неподдерживаемое значение.\n Программа удалила данное событие.\n" << endl;
        Date tmp;
        arr[counter - 1] = tmp;
        counter--;
        return arr;
    }
    for (int i = 0; i < counter - 1; i++)
        if (arr[counter - 1] == arr[i])
        {
            cout << "\n К сожалению, дата последнего события совпала с одной из существующих дат.\n Программа удалила данное событие.\n" << endl;
            Date tmp;
            arr[counter - 1] = tmp;
            counter--;
            return arr;
        }
    return arr;
}
