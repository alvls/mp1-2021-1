
#include "all.h"

bool menu(Pedometer& pedometer)
{
    int choice = -1;
    cout << "\n Сейчас Вы находитесь в меню. Выберите, что нужно сделать:\n\t(1) Узнать дату начала подсчетов\n\t(2) Задать подсчеты\n\t(3) Получить информацию о выбранном подсчете\n\t(4) Найти среднее число шагов в выбранном месяце\n\t(5) Найти среднее число шагов за всю историю наблюдений\n\t(6) Найти среднее число шагов в выбранный день недели\n\t    за всю историю наблюдений\n\t(7) Найти максимальное число шагов в день в выбранном\n\t    месяце и дату, когда оно было достигнуто\n\t(8) Найти максимальное число шагов в день за всю\n\t    историю наблюдений и дату, когда оно было достигнуто\n\t(9) Сохранить историю подсчетов в файл\n\t10) Считать историю подсчетов из файла\n\t11) Режим тестировщика\n\t(0) Выйти из программы" << endl;
    choice = check(0, 11);
    system("cls");
    try
    {
        switch (choice)
        {
        case 1:
            mode1(pedometer);
            break;
        case 2:
            mode2(pedometer);
            break;
        case 3:
            mode3(pedometer);
            break;
        case 4:
            mode4(pedometer);
            break;
        case 5:
            mode5(pedometer);
            break;
        case 6:
            mode6(pedometer);
            break;
        case 7:
            mode7(pedometer);
            break;
        case 8:
            mode8(pedometer);
            break;
        case 9:
            mode9(pedometer);
            break;
        case 10:
            mode10(pedometer);
            break;
        case 11:
            mode11(pedometer);
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
        cout << "\n" << ex.what() << "\n\n";
    }
    system("pause");
    system("cls");
    return true;
}

void mode1(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Узнать дату начала подсчетов\"\n\n Дата начала подсчетов: ";
    pedometer.PrintStartDate();
    cout << "\n\n";
}

void mode2(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Задать подсчеты\"\n\n";
    pedometer.SetOneDay(CreateNewOneDay());
    cout << "\n";
}

void mode3(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Получить информацию о выбранном подсчете\"\n";
    size_t tmp = 1;
    OneDay tmponeday;
    Count tmpcount;
    if (pedometer.GetSize() == 0)
        throw exception(" Не задано ни одного подсчёта");
    if (pedometer.GetSize() == 1)
    {
        cout << "\n Задан единственный день!\n";
        tmponeday = pedometer[0];
        system("pause");
    }
    else
    {
        cout << "\n";
        pedometer.PrintPedometer();
        if (pedometer.GetSize() > 10)
        {
            cout << "\n Было выведено 10 дней из " << pedometer.GetSize() << "\n Вывести оставшиеся дни? \n 1) Да\n 2) Нет\n";
            if (check(1, 2) == 1)
            {
                cout << "\n";
                pedometer.PrintPedometer(1);
            }
        }
        cout << "\n Выберите один из дней: ";
        tmp = check(size_t(1), pedometer.GetSize());
        tmponeday = pedometer[tmp - 1];
    }
    if (tmponeday.GetCountSize() == 1)
    {
        cout << "\n В этот день задан единственный подсчёт!\n";
        tmpcount = tmponeday.GetCountAtInd(0);
        system("pause");
    }
    else
    {
        cout << "\n\n Выберите один из подсчетов:\n";
        tmponeday.PrintAllCounts();
        tmp = check(size_t(1), tmponeday.GetCountSize());
        tmpcount = tmponeday.GetCountAtInd(tmp - 1);
    }
    system("cls");
    cout << "\n Выбранный подсчёт: \n\n ";
    tmponeday.PrintDateOfDay();
    cout << "\n\n ";
    tmpcount.PrintCount();
    cout << "\n ";
    tmpcount.PrintCountSteps();
    cout << "\n";
}

void mode4(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Найти среднее число шагов в выбранном месяце\"" << endl;
    if (pedometer.GetSize() == 0)
        throw exception(" Не задано ни одного подсчёта");
    size_t tmpsize = pedometer.PrintMonths();
    cout << "\n Выберите нужный месяц: ";
    size_t choice = check(size_t(1), tmpsize);
    double result = pedometer.AverageInMonth(choice);
    cout << "\n Среднее число шагов в выбранном месяце: " << result << "\n\n";
}

void mode5(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Найти среднее число шагов за всю историю наблюдений\"" << endl;
    if (pedometer.GetSize() == 0)
        throw exception(" Не задано ни одного подсчёта");
    double tmp = pedometer.AverageInAllHistory();
    cout << "\n Среднее число шагов за всю историю наблюдений: " << tmp << "\n\n";
}

void mode6(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Найти среднее число шагов в\n выбранный день недели за всю историю наблюдений\"" << endl;
    if (pedometer.GetSize() == 0)
        throw exception(" Не задано ни одного подсчёта");
    cout << "\n Выберите день недели:\n (1)Понедельник\n (2)Вторник\n (3)Среда\n (4)Четверг\n (5)Пятница\n (6)Суббота\n (7)Воскресенье\n";
    int choice = check(1, 7);
    double result;
    if (choice == 7)
        choice = 0;
    result = pedometer.AverageInWeekDay(choice);
    const string WeekDayName[7] = { " воскресенье", " понедельник", "о вторник", " среду", " четверг", " пятницу", " субботу" };
    cout << "\n Среднее число шагов в" << WeekDayName[choice] << ": " << result << "\n\n";
}

void mode7(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Найти максимальное число шагов в день\n в выбранном месяце и дату, когда оно было достигнуто\"" << endl;
    if (pedometer.GetSize() == 0)
        throw exception(" Не задано ни одного подсчёта");
    size_t tmpsize = pedometer.PrintMonths();
    cout << "\n Выберите нужный месяц: \n";
    size_t choice = check(size_t(1), tmpsize);
    OneDay result = pedometer.MaxInMonth(choice);
    system("cls");
    cout << "\n Выбранный месяц: ";
    result.PrintMonthOfDay();
    cout << "\n Максимальное число шагов в день: " << result.GetStepsDay() << "\n\n Дата данного дня:\n\n ";
    result.PrintDateOfDay();
    cout << "\n\n";
}

void mode8(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Найти максимальное число шагов в день\n за всю историю наблюдений и дату, когда оно было достигнуто\"\n";
    if (pedometer.GetSize() == 0)
        throw exception(" Не задано ни одного подсчёта");
    cout << "\n";
    OneDay tmponeday = pedometer.MaxInDay();
    cout << " ";
    tmponeday.PrintDateOfDay();
    cout << "\n\n Количество шагов: " << tmponeday.GetStepsDay() << "\n\n";
}

void mode9(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Сохранить историю подсчетов в файл\"\n";
    pedometer.SaveInFile();
    cout << "\n Сохранение прошло успешно!\n\n";
}

void mode10(Pedometer& pedometer)
{
    cout << "\n Вы выбрали действие: \"Считать историю подсчетов из файла\"\n";
    pedometer.ReadFromFile();
    cout << "\n Считывание прошло успешно!\n\n";
}

void mode11(Pedometer& pedometer)
{
    cout << "\n Вы выбрали режим тестировщика\n\n Дальнейшие действия удалят всю сохранённую информацию\n Продолжить?\n (1) Да\n (2) Нет\n";
    if (check(1, 2) == 2)
        return;
    cout << "\n Выберите количество дней, нужных для теста: ";
    int tmp = check(1, INT_MAX);
    pedometer.RandomGenerator(tmp);
    cout << "\n Успешно создано случайных дней: " << tmp << "\n\n";
}
