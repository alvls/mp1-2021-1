
#include "all.h"

bool menu(CashMachine& box)
{
    static void(*modeptr[4])(CashMachine & box) = { mode1, mode2, mode3, mode4 };
    static bool access = false;
    try
    {
        while (!access)
        {
            PrintCashMachine();
            PrintStatus(3);
            if (!box.IsCardOpen())
            {
                OpenCard(box);
                continue;
            }
            if (box.IsCardBlocked())
            {
                BlockedCardInf(box);
                break;
            }
            if (!box.IsCodeEntered())
                access = EnterPINcode(box);
            waiting();
        }
    }
    catch (const exception& ex)
    {
        cout << ex.what();
        PrintStatus(1);
        waiting();
        return true;
    }
    try
    {
        PrintMenu();
        int choice = GetNumber(1);
        if (--choice == 3)
            access = false;
        system("cls");
        modeptr[choice](box);
    }
    catch (const exception& ex)
    {
        cout << "\n " << ex.what();
    }
    waiting();
    return true;
}

void OpenCard(CashMachine& box)
{
    gotoxy(22, 2);
    cout << "Ожидание карты клиента (введите ID карты)";
    gotoxy(22, 4);
    int CardID = GetNumber(4, false);
    gotoxy(22, 6);
    box.SetCard(CardID);
    PrintStatus(2);
    waiting();
}

bool EnterPINcode(CashMachine& box)
{
    enum { WRITESTAR = 1 };
    PrintStatus();
    gotoxy(22, 2);
    cout << "Введите PIN-код";
    gotoxy(9, 4);
    int tmpPIN = GetNumber(4, false, WRITESTAR);
    int CurrentAttempts = 0;
    gotoxy(22, 4);
    if (!box.CheckPINcode(tmpPIN, CurrentAttempts))
    {
        if (!box.IsCardOpen())
            throw exception("Ваша карта заблокирована!");
        cout << "Введён неверный PIN-код";
        gotoxy(22, 6);
        char tmpstr[21] = "Осталось попыток : ";
        tmpstr[19] = '3' - CurrentAttempts;
        throw exception(tmpstr);
        return false;
    }
    else
    {
        cout << "Вы успешно ввели PIN-код";
        PrintStatus(2);
        return true;
    }
    waiting();
}

void BlockedCardInf(CashMachine& box)
{
    system("cls");
    cout << "\n (нельзя использовать заблокированную карту)";
    mode4(box);
}

void mode1(CashMachine& box)
{
    cout << box;
}

void mode2(CashMachine& box)
{
    cout << "\n Введите сумму, которую хотите списать со счёта\n ";
    int value = GetNumber(6);
    box.GiveMoney(value);
}

void mode3(CashMachine& box)
{
    NominalValues tmpvalues;
    int digit;
    while (true)
    {
        system("cls");
        cout << "\n Вставьте купюры в купюроприёмник\n (добавить купюру - нажать на её номер в списке)\n (нажмите ENTER, чтобы прекратить вставлять купюры)\n ";
        cout << tmpvalues;
        digit = GetDigit();
        if (digit >= 1 && digit <= tmpvalues.NumOfElements())
            tmpvalues.AddQuantity(size_t(--digit));
        if (digit == ENTER - '0')
            break;
    }
    box.TakeMoney(tmpvalues);
    cout << "\n Общая сумма: " << tmpvalues.GetSum() << "\n\n Наличные внесены!";
}

void mode4(CashMachine& box)
{
    box.BackCard();
    cout << "\n Возьмите карту";
}
