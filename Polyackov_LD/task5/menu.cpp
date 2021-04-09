
#include "all.h"

bool menu(CashMachine& box)
{
    //Добавить GetStatus и вывод в зависимости от него предлагаемых пользователю штук
    if (!box.GetStatus())
        mode0(box);
    else
    {

    }
    cout << "\n Выберите, что нужно сделать:\n\t (1) Распечатать состояние счета клиента\n\t (2) Выдать клиенту наличные (списав выданную сумму со счета)\n\t (3) Принять от клиента наличные\n\t (4) Вернуть карту клиенту\n\t";
    int choice = check(0, 11);
    system("cls");
    try
    {
        switch (choice)
        {
        case 1:
            mode1(box);
            break;
        case 2:
            mode2(box);
            break;
        case 3:
            mode3(box);
            break;
        case 4:
            mode4(box);
            break;
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

void mode0(CashMachine& box)
{
    cout << "\n Ожиданние карты клиента (введите ID карты)\n\n";
    box.SetCard(check(1, 9999));
    //Добавить PIN-code
}

void mode1(CashMachine& box)
{

}

void mode2(CashMachine& box)
{

}

void mode3(CashMachine& box)
{

}

void mode4(CashMachine& box)
{
    // Как-то вытащить карту
}
