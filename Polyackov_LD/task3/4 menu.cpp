
#include "all.h"

bool menu()
{
    static Tabulator tab;
    int vibor = -1;
    cout << "\n Сейчас Вы находитесь в меню. Выберите, что нужно сделать:\n\t(1) Задать текущую функцию\n\t(2) Задать текущее число точек табулирования\n\t(3) Узнать текущее число точек табулирования\n\t(4) Задать отрезок табулирования\n\t(5) Узнать отрезок табулирования\n\t(6) Выполнить табулирование функции\n\t(7) Выдать результаты табулирования\n\t(8) Сохранить результат табулирования в файл\n\t(0) Выйти из программы" << endl;
    vibor = proverka(0, 8);
    system("cls");
    if ((vibor == 1) || (vibor == 2) || (vibor == 4))
        tab.DeleteTabData();
    try
    {
        switch (vibor)
        {
        case 1:
            rezhim1(tab);
            break;
        case 2:
            rezhim2(tab);
            break;
        case 3:
            rezhim3(tab);
            break;
        case 4:
            rezhim4(tab);
            break;
        case 5:
            rezhim5(tab);
            break;
        case 6:
            rezhim6(tab);
            break;
        case 7:
            rezhim7(tab);
            break;
        case 8:
            rezhim8(tab);
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
        cout << endl << ex.what() << endl;
    }
    system("pause");
    system("cls");
    return true;
}

void rezhim1(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Задать текущую функцию\"\n\n Перечень возможных функций:" << endl << endl;
    string NameOfFunc[NUMOFFUNC] = { "x", "Синус", "Косинус", "Тангенс", "Котангенс", "Арксинус", "Арккосинус", "Арктангенс", "Арккотангенс", "Гиперболический синус", "Гиперболический косинус", "Гиперболический тангенс", "Гиперболический котангенс", "Ареасинус", "Ареакосинус", "Ареатангенс", "Ареакотангенс", "x в квадрате", "x в кубе", "Квадратный корень из x", "Кубический корень из x", "2 в степени x", "e в степени x ", "10 в степени x", "Двоичный логарифм", "Натуральный логарифм", "Десятичный логарифм", "Дробная часть числа", "Целая часть числа", "Модуль" };
    for (int i = 1; i < NUMOFFUNC; i++)
    {
        cout << " " << i << ") " << NameOfFunc[i] << endl;
        if ((i >= 12) && (i < 24))
            gotoxy(36, i - 7);
        if ((i >= 24) && (i < 29))
            gotoxy(76, i - 19);
    }
    gotoxy(0, 18);
    cout << " Выберите нужную функцию: ";
    int tmpnum = proverka(1, NUMOFFUNC);
    tab.SetFunc(tmpnum);
    cout << "\n Вы успешно задали текущую функцию!\n" << endl;
}

void rezhim2(Tabulator& tab)
{
    int tmpnum = -1;
    cout << "\n Вы выбрали действие \"Задать текущее число точек табулирования\"\n Введите нужное количество точек табулирования (>=2): " << endl;
    tmpnum = proverka(2, INT_MAX);
    tab.SetPoints(tmpnum);
    cout << "\n Вы успешно задали число точек табулирования!\n\n";
}

void rezhim3(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Узнать текущее число точек табулирования\"" << endl; 
    if (tab.GetPoints() < 2)
        throw exception(" Ошибка получения информации!\n Измените число точек табулирования!");
    cout << "\n Заданное число точек : " << tab.GetPoints() << endl;
}

void rezhim4(Tabulator& tab)
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
        if (tab.GetLeftBound() >= tab.GetRightBound())
            cout << " Значение правой границы не может быть меньше значения левой границы, либо быть равно значению левой границы! " << endl;
    }
}

void rezhim5(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Узнать отрезок табулирования\"" << endl;
    if ((tab.GetLeftBound() < DBL_MIN + 0, 1) || (tab.GetRightBound() > DBL_MAX - 0, 1))
        throw exception(" Ошибка получения информации!\n Измените границы табулирования!");
    double* tmp = tab.GetBounds();
    cout << "\n Заданный отрезок табулирования : от " << tmp[0] << " до " << tmp[1] << endl;
    delete[] tmp;
}

void rezhim6(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Выполнить табулирование функции\"" << endl;
    if (tab.GetFunc() == nullptr)
        throw exception(" Ошибка табулирования функции!\n Измените текущую функцию!");
    if (tab.GetPoints() < 2)
        throw exception(" Ошибка табулирования функции!\n Измените число точек табулирования!");
    if ((tab.GetLeftBound() < DBL_MIN + 0, 1) || (tab.GetRightBound() > DBL_MAX - 0, 1))
        throw exception(" Ошибка табулирования функции!\n Измените границы табулирования!");
    if (tab.GetTabData() != nullptr)
        throw exception(" Повторное табулирование функции не требуется, так как параметры табулирования не изменились!");
    tab.TabFunc();
    cout << "Табулирование функции прошло успешно!" << endl << endl;
}

void rezhim7(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Выдать результаты табулирования\"" << endl;
    if (tab.GetTabData() == nullptr)
        throw exception(" Ошибка получения информации!\n Требуется предварительно протабулировать функцию!");
    tab.PrintData();
}

void rezhim8(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Cохранить результат табулирования в файл\"" << endl;
    if (tab.GetTabData() == nullptr)
        throw exception(" Ошибка получения информации!\n Требуется предварительно протабулировать функцию!");
    tab.SaveData();
    cout << "Данные успешно успешно сохранены в папку с программой!" << endl << endl;
}
