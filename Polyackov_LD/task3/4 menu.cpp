
#include "all.h"

bool menu()
{
    static Tabulator tab;
    int vibor = -1;
    cout << "\n Сейчас Вы находитесь в меню. Выберите, что нужно сделать:\n\t(1) Задать текущую функцию\n\t(2) Задать текущее число точек табулирования\n\t(3) Узнать текущее число точек табулирования\n\t(4) Задать отрезок табулирования\n\t(5) Узнать отрезок табулирования\n\t(6) Выполнить табулирование функции\n\t    и выдать результаты табулирования\n\t(7) Выполнить табулирование функции\n\t    и сохранить результат табулирования в файл\n\t(0) Выйти из программы" << endl;
    vibor = proverka(0, 7);
    system("cls");
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
    case 0:
        system("cls");
        return false;
    default:
        cout << "Непредвиденная ошибка." << endl;
        return false;
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
        cout << " " << i << ") " << NameOfFunc[i];
        if ((i==4)||(i==8)||(i==12)||(i==16)||(i==20)||(i==23)||(i==26)||(i==29))
            cout << endl << endl;
    }
    cout << " Выберите нужную функцию: ";
    int tmpnum = proverka(1, NUMOFFUNC);
    tab.SetFunc(tmpnum);
    cout << "Вы успешно задали текущую функцию!" << endl;
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
    cout << "\n Вы выбрали действие \"Узнать текущее число точек табулирования\"\n Заданное число точек: " << tab.GetPoints() << endl;
}

void rezhim4(Tabulator& tab)
{
    double tmp;
    cout << "\n Вы выбрали действие \"Задать отрезок табулирования\"\n\n Знак \".\" используется в качестве разделителя для нецелых значений \n\n Введите значение левой границы отрезка: ";
    cin >> tmp;
    tab.SetLeftBound(tmp);
    tab.SetRightBound(tmp - 1);
    while (tab.GetLeftBound() > tab.GetRightBound())
    {
        cout << "\n Введите значение правой границы отрезка: ";
        cleaner();
        cin >> tmp;
        tab.SetRightBound(tmp);
    }
}

void rezhim5(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Узнать отрезок табулирования\"\n Заданный отрезок табулирования: от " << tab.GetLeftBound() << " до " << tab.GetRightBound() << endl;
}

void rezhim6(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Выполнить табулирование функции\n\t\t      и выдать результаты табулирования\"" << endl;
    double** temp;
    Function* func = tab.GetFunc();
    temp = tab.TabFunc(func);
    cout << endl;
    for (int i = 0; i < tab.GetPoints(); i++)
        cout << " x = " << temp[i][0] << " ; y = " << temp[i][1] << endl;
    for (int i = 0; i < 2; i++)
        delete[]temp[i];
    delete[] temp;
}

void rezhim7(Tabulator& tab)
{
    cout << "\n Вы выбрали действие \"Выполнить табулирование функции\n\t    и сохранить результат табулирования в файл\"" << endl;
    char* tmpstr = new char[MAX_SYMB];
    time_t seconds = time(NULL);
    strftime(tmpstr, MAX_SYMB, "tabfunction (%H.%M.%S).txt", localtime(&seconds)); //%H - часы, %M - минуты, %S - секунды
    Function* func = tab.GetFunc();
    ofstream fout;
    fout.open(tmpstr);
    if (!fout.is_open())
        cout << "\n Ошибка открытия файла!\n\n";
    else
    {
        double** temp = tab.TabFunc(func);
        fout << endl;
        for (int i = 0; i < tab.GetPoints(); i++)
            fout << " x = " << temp[i][0] << " ; y = " << temp[i][1] << endl;
        for (int i = 0; i < 2; i++)
            delete[]temp[i];
        delete[] temp;
    }
    fout.close();
    cout << "\n Табулирование функции прошло успешно!\n Данные были сохранены в файл\n \"" << tmpstr << "\",\n находящийся в папке с программой.\n\n";
    delete[]tmpstr;
    tmpstr = nullptr;

}
