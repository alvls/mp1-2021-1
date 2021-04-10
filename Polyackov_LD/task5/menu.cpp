
#include "all.h"

bool menu(CashMachine& box)
{
    static void(*modeptr[5])(CashMachine & box) = { mode0, mode1, mode2, mode3, mode4 };
    cout << "\n  _____________\n |\\  _________ \\\n | \\ \\        \\_\\\n |  \\ \\        \\_\\\n |   \\ \\________\\ \\\n |    \\____\\\\\\\\____\\\n |    |  ________  |\n |    | |________| |\n |    |            |\n |    |            |\n |    |  ��������  |\n |    |    24/7    |\n |____|____________|\n ";
    try
    {
        if (!box.IsOpenCard())
        {
            modeptr[0](box);
            system("cls");
            return true;
        }
        cout << "\n ��������, ��� ����� �������:\n\t (1) ����������� ��������� ����� �������\n\t (2) ������ ������� �������� (������ �������� ����� �� �����)\n\t (3) ������� �� ������� ��������\n\t (4) ������� ����� �������\n\t";
        int choice = GetDigit('1', '4');
        cout << choice;
        modeptr[choice](box);
        system("cls");
    }
    catch (const exception &ex)
    {
        cout << "\n" << ex.what() << "\n\n";
        if (string(" ������ ���������� id �����") == ex.what())
            //�������� ����� �� ���������
            ;
    }
    system("pause");
    system("cls");
    return true;
}

void mode0(CashMachine& box)
{
    cout << "\n ��������� ����� ������� (������� ID �����)\n\n";
    int CardID = GetNumber(4);
    box.SetCard(CardID);
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
    // ���-�� �������� �����
}
