
#include "all.h"

bool menu(CashMachine& box)
{
    //�������� GetStatus � ����� � ����������� �� ���� ������������ ������������ ����
    if (!box.GetStatus())
        mode0(box);
    else
    {

    }
    cout << "\n ��������, ��� ����� �������:\n\t (1) ����������� ��������� ����� �������\n\t (2) ������ ������� �������� (������ �������� ����� �� �����)\n\t (3) ������� �� ������� ��������\n\t (4) ������� ����� �������\n\t";
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
            throw exception("������ ������ �������� � ����");
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
    cout << "\n ��������� ����� ������� (������� ID �����)\n\n";
    box.SetCard(check(1, 9999));
    //�������� PIN-code
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
