/*
    Разработать класс Календарь событий.

    Класс должен позволять сохранять даты заданных событий в формате: год, месяц, день, наименование события. 
    На каждый день может приходиться только одно событие. Общее число событий – не более 30.
    
    Класс должен предоставлять операции: 
    1) установить событие, 
    2) узнать дату выбранного события, 
    3) вычислить разницу между заданной датой и датой события (в днях), 
    4) сформировать новое событие, сдвинув выбранное существующее событие на заданное смещение (в днях) в меньшую и в большую сторону.
    
    Класс должен содержать все необходимые конструкторы, деструктор, оператор присваивания, а также «уметь» выводить себя на консоль.
*/

#ifndef MAX_EVENTS
    #define MAX_EVENTS 2
#endif // !MAX_EVENTS

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h> //Для setconsole...(1251). Нужно для правильной обработки названий событий, написанных по-русски
#include <string>
using namespace std;

int MonthDays(int month, int year)
{
    int Days[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((month==2)&&((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))))
        return Days[0];
    return Days[month];
}
const string MonthName[12] = { "января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря"};

class Date
{
private:
    int year;
    int month;
    int day;
    string event;
    int SumOfDays()
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
public:
    //Конструктор
    Date(int _day = 1, int _month = 1, int _year = 1, string _event = "Пусто\0") : day(_day), month(_month), year(_year), event(_event)
    {
        //cout << "Вызвался конструктор: " << this << endl;
    }
    //Конструктор копирования
    Date(const Date& other)
    {
        year = other.year;
        month = other.month;
        day = other.day;
        event = other.event;
        //cout << "Вызвался конструктор копирования: " << this << endl;
    }
    //Геттеры
    int GetYear()
    {
        return year;
    }
    int GetMonth()
    {
        return month;
    }
    int GetDay()
    {
        return day;
    }
    string GetEvent()
    {
        return event;
    }
    //Вывод на экран
    void PrintDate()
    {
        cout << " " << day << " " << MonthName[month-1] << " " << year << " года" << endl;
    }
    //Сеттеры
    void SetYear(int year)
    {
        this->year = year;
    }
    void SetMonth(int month)
    {
        this->month = month;
    }
    void SetDay(int day)
    {
        this->day = day;
    }
    void SetEvent(string event)
    {
        this->event = event;
    }
    //Разница между датами
    int DateDifference(Date& other)
    {
        return abs(SumOfDays() - other.SumOfDays());
    }
    //Операторы
    bool operator== (const Date& other)
    {
        return (year == other.year) && (month == other.month) && (day == other.day);
    }
    bool operator!= (const Date& other)
    {
        return (year != other.year) && (month != other.month) && (day != other.day);
    }
    Date& operator= (const Date& other)
    {
        if (this == &other)
            return *this;
        year = other.year;
        month = other.month;
        day = other.day;
        event = other.event;
        return *this;
    }
    Date operator+ (const int& otherday)
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
    Date operator- (const int& otherday)
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
        system("pause");
        return tmp;
    }
    //Деструктор
    ~Date()
    {
        //cout << "Вызвался деструктор: " << this << endl;
    }
};

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
    if (counter == 0)
    {
        cout << "\n К сожалению, у Вас нет установленных событий.\n" << endl;
        return -1;
    }
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
        cout << "\n К сожалению, дата последнего события получила неподдерживаемое значение.\n Программа удалила данное событие." << endl;
        Date tmp;
        arr[counter - 1] = tmp;
        counter--;
        return arr;
    }
    for (int i = 0; i < counter - 1; i++)
        if (arr[counter-1] == arr[i])
        {
            cout << "\n К сожалению, дата последнего события совпала с одной из существующих дат.\n Программа удалила данное событие." << endl;
            Date tmp;
            arr[counter - 1] = tmp;
            counter--;
            return arr;
        }
    return arr;
}

void rezhim3(Date* arr, int& counter)
{
    int tmpnum = -1;
    Date tmpDate;
    int tmpdays;
    cout << "\n Вы выбрали действие \n\t\"Вычислить разницу между заданной датой и датой события (в днях)\".\n\n Задайте дату.\n\n Введите год (>=1): " << endl;
    cout << "";
    tmpDate.SetYear(proverka(1, INT_MAX));
    cout << "\n Введите месяц (от 1 до 12): ";
    tmpDate.SetMonth(proverka(1, 12));
    tmpdays = MonthDays(tmpDate.GetMonth(), tmpDate.GetYear());
    cout << "\n Введите день (от 1 до " << tmpdays << "): ";
    tmpDate.SetDay(proverka(1, tmpdays));
    cout << "\n Теперь выберите нужное событие " << endl;
    tmpnum = SelectedEvent(counter, arr);
    cout << "\n Заданная дата: ";
    tmpDate.PrintDate();
    cout << "\n Разница между датой события и Вашей датой: " << arr[tmpnum].DateDifference(tmpDate) << " д." << endl << endl;
}

void rezhim4(Date* arr, int& counter)
{
    int tmpnum = -1;
    int vibor = -1;
    int tmpdays = -1;
    cout << "\n Вы выбрали действие \n\t\"Сформировать новое событие, сдвинув выбранное существующее\n\tсобытие на заданное смещение в меньшую или в большую сторону\"." << endl;
    tmpnum = SelectedEvent(counter, arr);
    cout << "\n На сколько дней Вы хотите передвинуть событие? (>=1)" << endl;
    tmpdays = proverka(1, INT_MAX);
    cout << "\n В какую сторону Вы хотите передвинуть выбранное событие?\n\t1) В большую сторону\n\t2) В меньшую сторону" << endl;
    vibor = proverka(1,2);
    if (vibor == 1)
        arr[counter++] = arr[tmpnum] + tmpdays;
    if (vibor == 2)
        arr[counter++] = arr[tmpnum] - tmpdays;
    system("cls");
    cout << "\n Вы сформировали событие \"" << arr[counter-1].GetEvent() << "\"\n Номер события: " << counter << endl << endl;
}

bool menu()
{
    int tmpnum = -1;
    static int counter = 0;
    static int size = MAX_EVENTS;
    static Date* arr = new Date[size]; //Для хранения событий
    int vibor = -1;
    cout << "\n Сейчас Вы находитесь в меню. Выберите, что нужно сделать :\n\t(1) Установить событие \n\t(2) Узнать дату выбранного события \n\t(3) Вычислить разницу между заданной датой и датой события \n\t(4) Сформировать новое событие, сдвинув выбранное существующее\n\tсобытие на заданное смещение в меньшую или в большую сторону\n\t(0) Выйти из программы" << endl;
    vibor = proverka(0,4);
    if ((counter == 0) && ((vibor == 2) || (vibor == 3) || (vibor == 4)))
    {
        cout << "\n Для работы режима (" << vibor << ") требуется хотя бы одно событие.\n К сожалению, у Вас нет установленных событий.\n" << endl;
        system("pause");
        system("cls");
        return true;
    }
    system("cls");
    switch (vibor)
    {
    case 1:
        cout << "\n Вы выбрали действие \n\t\"Установить событие\"." << endl;
        arr[counter++] = CreateNewDate();
        break;
    case 2:
        cout << "\n Вы выбрали действие \n\t\"Узнать дату выбранного события\"." << endl;;
        tmpnum = SelectedEvent(counter, arr);
        cout << "\n Дата выбранного события: ";
        arr[tmpnum].PrintDate();
        break; 
    case 3:
        // 3) вычислить разницу между заданной датой и датой события (в днях), 
        rezhim3(arr, counter);
        break;
    case 4:
        // 4) сформировать новое событие, сдвинув выбранное существующее событие на заданное смещение(в днях) в меньшую и в большую сторону.
        rezhim4(arr, counter);
        break;
    case 0:
        delete[]arr;
        arr = nullptr;
        return false;
        break; 
    default:
        cout << "Непредвиденная ошибка." << endl;
        delete[]arr;
        arr = nullptr;
        return false;
        break;
    }
    if (counter == size)
        arr = RecreateArr(arr, size, counter);
    ExistDate(arr, counter);
    system("pause");
    system("cls");
    return true;
}

void main()
{
    setlocale(LC_ALL, "Ru");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    cout << "\n Календарь событий!" << endl;
    while (menu()) {}
    system("pause");
}