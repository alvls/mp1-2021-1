
#include "all.h"

bool menu()
{
    static Tabulator tab;
    int choice = -1;
    cout << "\n Сейчас Вы находитесь в меню. Выберите, что нужно сделать:\n\t(1) Задать текущую функцию\n\t(2) Задать текущее число точек табулирования\n\t(3) Узнать текущее число точек табулирования\n\t(4) Задать отрезок табулирования\n\t(5) Узнать отрезок табулирования\n\t(6) Выполнить табулирование функции\n\t(7) Выдать результаты табулирования\n\t(8) Сохранить результаты табулирования в файл\n\t(0) Выйти из программы" << endl;
    choice = checking(0, 8);
    system("cls");
    if ((choice == 1) || (choice == 2) || (choice == 4))
        tab.DeleteTabData();
    try
    {
        switch (choice)
        {
        case 1:
            mode1(tab);
            break;
        case 2:
            mode2(tab);
            break;
        case 3:
            mode3(tab);
            break;
        case 4:
            mode4(tab);
            break;
        case 5:
            mode5(tab);
            break;
        case 6:
            mode6(tab);
            break;
        case 7:
            mode7(tab);
            break;
        case 8:
            mode8(tab);
            break;
        case 0:
            system("cls");
            return false;
        default:
            throw exception("Ошибка выбора действия в меню");
        }
    }
    catch (const exception &ex)
    {
        cout << endl << ex.what() << endl << endl;
    }
    system("pause");
    system("cls");
    return true;
}

void mode1(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Задать текущую функцию\"\n\n Перечень возможных функций:" << endl << endl;
    string NameOfFunc[NUMOFFUNC] = { "Синус", "Косинус", "Тангенс", "Арксинус", "Арккосинус", "Арктангенс", "Гиперболический синус", "Гиперболический косинус", "Гиперболический тангенс", "Ареасинус", "Ареакосинус", "Ареатангенс", "x в квадрате", "x в кубе", "Квадратный корень из x", "Кубический корень из x", "2 в степени x", "e в степени x ", "10 в степени x", "Двоичный логарифм", "Натуральный логарифм", "Десятичный логарифм", "Дробная часть числа", "Целая часть числа", "Модуль" };
    for (int i = 0; i < NUMOFFUNC; i++)
    {
        cout << " " << i + 1 << ") " << NameOfFunc[i] << endl;
        if (i > 10)
            gotoxy(29, i - 6);
    }
    gotoxy(0, 19);
    cout << " Выберите нужную функцию: ";
    int tmpnum = checking(1, NUMOFFUNC);
    tab.SetFunc(tmpnum);
    cout << "\n Вы успешно задали текущую функцию!\n" << endl;
}

void mode2(Tabulator& tab)
{
    int tmpnum = -1;
    cout << "\n Вы выбрали действие \"Задать текущее число точек табулирования\"\n\n Введите нужное количество точек табулирования (>=2): ";
    tmpnum = checking(2, INT_MAX);
    tab.SetPoints(tmpnum);
    cout << "\n Вы успешно задали число точек табулирования!\n\n";
}

void mode3(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Узнать текущее число точек табулирования\"" << endl; 
    if (tab.GetPoints() < 2)
        throw exception(" Ошибка получения информации!\n Измените число точек табулирования!");
    cout << "\n Заданное число точек : " << tab.GetPoints() << endl << endl;
}

void mode4(Tabulator& tab)
{
    double tmp;
    cout << "\n Вы выбрали действие \"Задать отрезок табулирования\"\n\n Знак \".\" используется в качестве разделителя для нецелых значений \n\n Введите значение левой границы отрезка: ";
    cin >> tmp;
    tab.SetLeftBound(tmp);
    tab.SetRightBound(tmp - 1);
    while (tab.GetLeftBound() >= tab.GetRightBound())
    {
        cout << "\n Введите значение правой границы отрезка: ";
        cleaner();
        cin >> tmp;
        tab.SetRightBound(tmp);
        if (tab.GetLeftBound() > tab.GetRightBound())
            cout << "\n Значение правой границы не может быть меньше значения левой границы! " << endl;
        if (tab.GetLeftBound() == tab.GetRightBound())
            cout << "\n Значение правой границы не может быть равно значению левой границы! " << endl;
    }
    cout << "\n Вы успешно задали отрезок табулирования" << endl << endl;
}

void mode5(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Узнать отрезок табулирования\"" << endl;
    if ((tab.GetLeftBound() == DBL_MIN) || (tab.GetRightBound() == DBL_MAX))
        throw exception(" Ошибка получения информации!\n Измените отрезок табулирования!");
    double* tmp = tab.GetBounds();
    cout << "\n Заданный отрезок табулирования : от " << tmp[0] << " до " << tmp[1] << endl << endl;
    delete[] tmp;
}

void mode6(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Выполнить табулирование функции\"" << endl;
    if (tab.GetFunc() == nullptr)
        throw exception(" Ошибка табулирования функции!\n Измените текущую функцию!");
    if (tab.GetPoints() < 2)
        throw exception(" Ошибка табулирования функции!\n Измените число точек табулирования!");
    if ((tab.GetLeftBound() == DBL_MIN) || (tab.GetRightBound() == DBL_MAX))
        throw exception(" Ошибка табулирования функции!\n Измените отрезок табулирования!");
    if (tab.TabDataExist())
        throw exception(" Повторное табулирование функции не требуется,\n так как параметры табулирования не изменились!");
    tab.TabFunc();
    cout << "\n Табулирование функции прошло успешно!" << endl << endl;
}

void mode7(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Выдать результаты табулирования\"" << endl;
    if (!tab.TabDataExist())
        throw exception(" Ошибка получения информации!\n Требуется предварительно протабулировать функцию!");
    if (tab.GetPoints() > MAXPOINTSFORPRINT)
    {
        tab.PrintData(MAXPOINTSFORPRINT);
        cout << "\n Количество точек табулирования больше " << MAXPOINTSFORPRINT << "\n Вывести на экран полный список?\n (может занять немного больше времени)\n 1) Да\n 2) Нет" << endl;
        int No = checking(1, 2) - 1;
        if (!No)
        {
            cout << "\n Вы выбрали действие \"Выдать результаты табулирования\"" << endl << endl;
            system("cls");
            tab.PrintData();
        }
    }
    else 
        tab.PrintData();
}

void mode8(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Cохранить результаты табулирования в файл\"" << endl;
    if (!tab.TabDataExist())
        throw exception(" Ошибка получения информации!\n Требуется предварительно протабулировать функцию!");
    tab.SaveData();
    cout << "\n Данные успешно успешно сохранены в папку с программой!" << endl << endl;
}
