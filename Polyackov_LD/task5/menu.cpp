
#include "all.h"

bool menu(CashMachine& box)
{
    static void(*modeptr[4])(CashMachine & box) = { mode1, mode2, mode3, mode4 };
    cout << "\n  _____________\n |\\  _________ \\\n | \\ \\        \\_\\\n |  \\ \\        \\_\\\n |   \\ \\________\\ \\\n |    \\____\\\\\\\\____\\\n |    |  ________  |\n |    | |________| |\n |    |            |\n |    |            |\n |    |  ��������  |\n |    |    24/7    |\n |____|____________|\n ";
    try
    {
        if (!box.IsOpenCard())
        {
            OpenCard(box);
            system("pause");
            system("cls");
            return true;
        }
        if (box.IsBlockedCard())
        {
            cout << "\n ���������� ���������� � ��������������� �����";
            box.BackCard();
            system("pause");
            system("cls");
            return true;
        }
        if (!box.IsCodeEntered())
        {
            EnterPINcode(box);
            system("pause");
            system("cls");
            return true;
        }
        cout << "\n ��������, ��� ����� �������:\n\t (1) ����������� ��������� ����� �������\n\t (2) ������ ������� �������� (������ �������� ����� �� �����)\n\t (3) ������� �� ������� ��������\n\t (4) ������� ����� �������\n\t";
        int choice = GetDigit('1', '4');
        cout << choice;
        modeptr[--choice](box);
        system("cls");
    }
    catch (const exception &ex)
    {
        cout << "\n" << ex.what() << "\n\n";
        if (string(" ������ ���������� id �����") == ex.what())
            cout << "��";
    }
    system("pause");
    system("cls");
    return true;
}

void OpenCard(CashMachine& box)
{
    cout << "\n �������� ����� ������� (������� ID �����)\n\n";
    int CardID = GetNumber(4);
    box.SetCard(CardID);
    cout << "\n";
}

void EnterPINcode(CashMachine& box)
{
    cout << "\n ������� PIN-���\n\n";
    int tmpPIN = GetNumber(4, 1);
    int CurrentAttempts = 0;
    if (!box.CheckPINcode(tmpPIN, CurrentAttempts))
    {
        if (!box.IsOpenCard())
        {
            cout << "\n ���� ����� �������������!";
            return;
        }
        cout << "\n ����� �������� PIN-���\n �������� �������: " << 3 - CurrentAttempts;
    }
    else
        cout << "\n �� ������� ����� PIN-���\n";
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
    // �������� 45 ��� ������ �� ���������� �����
    system("cls");
    cout << "\n �������� ���� ����� � ������� ���� ������";
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
    cout << "\n ���� ����� �������������!";
}
