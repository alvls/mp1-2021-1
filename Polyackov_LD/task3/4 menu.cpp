
#include "all.h"

bool menu()
{
    static Tabulator tab;
    int vibor = -1;
    cout << "\n ������ �� ���������� � ����. ��������, ��� ����� �������:\n\t(1) ������ ������� �������\n\t(2) ������ ������� ����� ����� �������������\n\t(3) ������ ������� ����� ����� �������������\n\t(4) ������ ������� �������������\n\t(5) ������ ������� �������������\n\t(6) ��������� ������������� �������\n\t(7) ������ ���������� �������������\n\t(8) ��������� ���������� ������������� � ����\n\t(0) ����� �� ���������" << endl;
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
            throw exception("������ ������ �������� � ����");
        }
    }
    catch (const exception &ex)
    {
        cout << endl << ex.what() << endl << endl;
    }
    system("pause");
    system("cls");
    return true;
}

void rezhim1(Tabulator& tab)
{
    cout << "\n �� ������� �������� \"������ ������� �������\"\n\n �������� ��������� �������:" << endl << endl;
    string NameOfFunc[NUMOFFUNC] = { "�����", "�������", "�������", "��������", "����������", "����������", "��������������� �����", "��������������� �������", "��������������� �������", "���������", "�����������", "�����������", "x � ��������", "x � ����", "���������� ������ �� x", "���������� ������ �� x", "2 � ������� x", "e � ������� x ", "10 � ������� x", "�������� ��������", "����������� ��������", "���������� ��������", "������� ����� �����", "����� ����� �����", "������" };
    for (int i = 0; i < NUMOFFUNC; i++)
    {
        cout << " " << i + 1 << ") " << NameOfFunc[i] << endl;
        if (i > 10)
            gotoxy(29, i - 6);
    }
    gotoxy(0, 19);
    cout << " �������� ������ �������: ";
    int tmpnum = proverka(1, NUMOFFUNC);
    tab.SetFunc(tmpnum);
    cout << "\n �� ������� ������ ������� �������!\n" << endl;
}

void rezhim2(Tabulator& tab)
{
    int tmpnum = -1;
    cout << "\n �� ������� �������� \"������ ������� ����� ����� �������������\"\n\n ������� ������ ���������� ����� ������������� (>=2): ";
    tmpnum = proverka(2, INT_MAX);
    tab.SetPoints(tmpnum);
    cout << "\n �� ������� ������ ����� ����� �������������!\n\n";
}

void rezhim3(Tabulator& tab)
{
    cout << "\n �� ������� �������� \"������ ������� ����� ����� �������������\"" << endl; 
    if (tab.GetPoints() < 2)
        throw exception(" ������ ��������� ����������!\n �������� ����� ����� �������������!");
    cout << "\n �������� ����� ����� : " << tab.GetPoints() << endl << endl;
}

void rezhim4(Tabulator& tab)
{
    double tmp;
    cout << "\n �� ������� �������� \"������ ������� �������������\"\n\n ���� \".\" ������������ � �������� ����������� ��� ������� �������� \n\n ������� �������� ����� ������� �������: ";
    cin >> tmp;
    tab.SetLeftBound(tmp);
    tab.SetRightBound(tmp - 1);
    while (tab.GetLeftBound() >= tab.GetRightBound())
    {
        cout << "\n ������� �������� ������ ������� �������: ";
        cleaner();
        cin >> tmp;
        tab.SetRightBound(tmp);
        if (tab.GetLeftBound() > tab.GetRightBound())
            cout << "\n �������� ������ ������� �� ����� ���� ������ �������� ����� �������! " << endl;
        if (tab.GetLeftBound() == tab.GetRightBound())
            cout << "\n �������� ������ ������� �� ����� ���� ����� �������� ����� �������! " << endl;
    }
    cout << "\n �� ������� ������ ������� �������������" << endl << endl;
}

void rezhim5(Tabulator& tab)
{
    cout << "\n �� ������� �������� \"������ ������� �������������\"" << endl;
    if ((tab.GetLeftBound() == DBL_MIN) || (tab.GetRightBound() == DBL_MAX))
        throw exception(" ������ ��������� ����������!\n �������� ������� �������������!");
    double* tmp = tab.GetBounds();
    cout << "\n �������� ������� ������������� : �� " << tmp[0] << " �� " << tmp[1] << endl << endl;
    delete[] tmp;
}

void rezhim6(Tabulator& tab)
{
    cout << "\n �� ������� �������� \"��������� ������������� �������\"" << endl;
    if (tab.GetFunc() == nullptr)
        throw exception(" ������ ������������� �������!\n �������� ������� �������!");
    if (tab.GetPoints() < 2)
        throw exception(" ������ ������������� �������!\n �������� ����� ����� �������������!");
    if ((tab.GetLeftBound() == DBL_MIN) || (tab.GetRightBound() == DBL_MAX))
        throw exception(" ������ ������������� �������!\n �������� ������� �������������!");
    if (tab.TabDataExist())
        throw exception(" ��������� ������������� ������� �� ���������,\n ��� ��� ��������� ������������� �� ����������!");
    tab.TabFunc();
    cout << "\n ������������� ������� ������ �������!" << endl << endl;
}

void rezhim7(Tabulator& tab)
{
    cout << "\n �� ������� �������� \"������ ���������� �������������\"" << endl;
    if (!tab.TabDataExist())
        throw exception(" ������ ��������� ����������!\n ��������� �������������� ��������������� �������!");
    if (tab.GetPoints() > MAXPOINTSFORPRINT)
    {
        tab.PrintData(MAXPOINTSFORPRINT);
        cout << "\n ���������� ����� ������������� ������ " << MAXPOINTSFORPRINT << "\n ������� �� ����� ������ ������?\n (����� ������ ������� ������ �������)\n 1) ��\n 2) ���" << endl;
        int No = proverka(1, 2) - 1;
        if (!No)
        {
            cout << "\n �� ������� �������� \"������ ���������� �������������\"" << endl << endl;
            system("cls");
            tab.PrintData();
        }
    }
    else 
        tab.PrintData();
}

void rezhim8(Tabulator& tab)
{
    cout << "\n �� ������� �������� \"C�������� ���������� ������������� � ����\"" << endl;
    if (!tab.TabDataExist())
        throw exception(" ������ ��������� ����������!\n ��������� �������������� ��������������� �������!");
    tab.SaveData();
    cout << "\n ������ ������� ������� ��������� � ����� � ����������!" << endl << endl;
}
