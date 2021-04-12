
#include "all.h"

bool menu(CashMachine& box)
{
    static void(*modeptr[5])(CashMachine & box) = { mode0, mode1, mode2, mode3, mode4 };
    cout << "\n  _____________\n |\\  _________ \\\n | \\ \\        \\_\\\n |  \\ \\        \\_\\\n |   \\ \\________\\ \\\n |    \\____\\\\\\\\____\\\n |    |  ________  |\n |    | |________| |\n |    |            |\n |    |            |\n |    |  Банкомат  |\n |    |    24/7    |\n |____|____________|\n ";
    try
    {
        if (!box.IsOpenCard())
        {
            modeptr[0](box);
            system("cls");
            return true;
        }
        cout << "\n Выберите, что нужно сделать:\n\t (1) Распечатать состояние счета клиента\n\t (2) Выдать клиенту наличные (списав выданную сумму со счета)\n\t (3) Принять от клиента наличные\n\t (4) Вернуть карту клиенту\n\t";
        int choice = GetDigit('1', '4');
        cout << choice;
        modeptr[choice](box);
        system("cls");
    }
    catch (const exception &ex)
    {
        cout << "\n" << ex.what() << "\n\n";
        if (string(" Ошибка считывания id карты") == ex.what())
            cout << "Да";
    }
    system("pause");
    system("cls");
    return true;
}

void mode0(CashMachine& box)
{
    cout << "\n Ожиданние карты клиента (введите ID карты)\n\n";
    int CardID = GetNumber(4);
    box.SetCard(CardID);
    cout << "\n";
    system("pause");
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
    // Добавить 45 сек отсчёт до блокировки карты
    system("cls");
    cout << "\n Возьмите вашу карту в течение пяти секунд";
    for (int i = 0; i < 5; i++)
    {
        _sleep(1000);
        if (_kbhit())
        {
            box.BackCard();
            return;
        }
    }
    box.BlockCard();
    box.BackCard();
    cout << "\n Ваша карта заблокирована!";
    system("pause");
}
