
#include "all.h"

bool menu(CashMachine& box)
{
    static void(*modeptr[4])(CashMachine & box) = { mode1, mode2, mode3, mode4 };
    PrintCashMachine();
    PrintStatus(3);
    try
    {
        if (!box.IsOpenCard())
        {
            OpenCard(box);
            return true;
        }
        if (box.IsBlockedCard())
        {
            BlockedCardInf(box);
            return true;
        }
        if (!box.IsCodeEntered())
        {
            EnterPINcode(box);
            return true;
        }
        PrintMenu();
        int choice = GetDigit('1', '4');
        cout << choice;
        system("cls");
        PrintCashMachine();
        PrintStatus(2);
        modeptr[--choice](box);
    }
    catch (const exception &ex)
    {
        cout << ex.what();
        PrintStatus(1);
        waiting();
    }
    return true;
}

void OpenCard(CashMachine& box)
{
    gotoxy(22, 2);
    cout << "�������� ����� ������� (������� ID �����)";
    gotoxy(22, 4);
    int CardID = GetNumber(4);
    gotoxy(22, 6);
    box.SetCard(CardID);
    PrintStatus(2);
    waiting();
}

void EnterPINcode(CashMachine& box)
{
    PrintStatus();
    gotoxy(22, 2);
    cout << "������� PIN-���";
    gotoxy(9, 4);
    int tmpPIN = GetNumber(4, 1);
    int CurrentAttempts = 0;
    gotoxy(22, 4);
    if (!box.CheckPINcode(tmpPIN, CurrentAttempts))
    {
        if (!box.IsOpenCard())
            throw exception("���� ����� �������������!");
        cout << "����� �������� PIN-���";
        gotoxy(22, 6);
        char tmpstr[21] = "�������� ������� : ";
        tmpstr[19] = '3' - CurrentAttempts;
        throw exception(tmpstr);
    }
    else
    {
        cout << "�� ������� ����� PIN-���\n";
        PrintStatus(2);
    }
    waiting();
}

void BlockedCardInf(CashMachine& box)
{
    PrintStatus(1);
    gotoxy(22, 4);
    cout << "(������ ������������ ��������������� �����)";
    mode4(box);
}

void mode1(CashMachine& box)
{
    gotoxy(22, 2);
    cout << "���� ��������� �����:" ;
    gotoxy(22, 4);
    box.cheque(cout);
    waiting();
}

void mode2(CashMachine& box)
{

    waiting();
}

void mode3(CashMachine& box)
{

    waiting();
}

void mode4(CashMachine& box)
{
    box.BackCard();
    gotoxy(22, 2);
    cout << "�������� �����";
    waiting();
}
