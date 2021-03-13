#include "all.h"

bool menu()
{
    static Calendar list;
    int vibor = -1;
    cout << "\n ������ �� ���������� � ����. ��������, ��� ����� ������� :\n\t(1) ���������� ������� \n\t(2) ������ ���� ���������� ������� \n\t(3) ��������� ������� ����� �������� ����� � ����� ������� \n\t(4) ������������ ����� �������, ������� ��������� ������������\n\t������� �� �������� �������� � ������� ��� � ������� �������\n\t(0) ����� �� ���������" << endl;
    vibor = proverka(0, 4);
    if ((list.GetCounter() == 0) && ((vibor == 2) || (vibor == 3) || (vibor == 4)))
    {
        cout << "\n ��� ������ ������ (" << vibor << ") ��������� ���� �� ���� �������.\n � ���������, � ��� ��� ������������� �������.\n" << endl;
        system("pause");
        system("cls");
        return true;
    }
    system("cls");
    switch (vibor)
    {
    case 1:
        // 1) ���������� �������
        rezhim1(list);
        break;
    case 2:
        // 2) ������ ���� ���������� �������
        rezhim2(list);
        break;
    case 3:
        // 3) ��������� ������� ����� �������� ����� � ����� ������� (� ����), 
        rezhim3(list);
        break;
    case 4:
        // 4) ������������ ����� �������, ������� ��������� ������������ ������� �� �������� ��������(� ����) � ������� � � ������� �������.
        rezhim4(list);
        break;
    case 0:
        return false;
        break;
    default:
        cout << "�������������� ������." << endl;
        return false;
        break;
    }
    CheckingForExistence(list);
    MemoryAssistant(list);
    system("pause");
    system("cls");
    return true;
}

void CheckingForExistence(Calendar& list)
{
    switch (list.ExistLastDate())
    {
    case 1:
        cout << "\n � ���������, ���� ���������� ������� �������� ���������������� ��������.\n ��������� ������� ������ �������.\n" << endl;
        list.DeleteLastDate();
        break;
    case 2:
        cout << "\n � ���������, ���� ���������� ������� ������� � ����� �� ������������ ���.\n ��������� ������� ������ �������.\n" << endl;
        list.DeleteLastDate();
        break;
    default:
        break;
    }
}

void MemoryAssistant(Calendar& list)
{
    if (list.GetCounter() == list.GetSize())
        list.AddMemory();
}

void rezhim1(Calendar& list)
{
    int count = list.GetCounter();
    cout << "\n �� ������� �������� \n\t\"���������� �������\"." << endl;
    list[count] = CreateNewDate();
    list.SetCounterPlusOne();
    system("cls");
    cout << "\n �� ������������ ������� \"" << list[count].GetEvent() << "\"\n ����� �������: " << count + 1 << endl << endl;
}

void rezhim2(Calendar& list)
{
    int tmpnum = -1;
    cout << "\n �� ������� �������� \n\t\"������ ���� ���������� �������\"." << endl;;
    tmpnum = SelectedEvent(list);
    cout << "\n ���� ���������� �������: ";
    list[tmpnum].PrintDate();
    cout << endl;
}

void rezhim3(Calendar& list)
{
    int tmpnum = -1;
    Date tmpDate;
    int tmpdays;
    cout << "\n �� ������� �������� \n\t\"��������� ������� ����� �������� ����� � ����� ������� (� ����)\".\n\n ������� ����.\n\n ������� ��� (>=1): ";
    cout << "";
    tmpDate.SetYear(proverka(1, INT_MAX));
    cout << "\n ������� ����� (�� 1 �� 12): ";
    tmpDate.SetMonth(proverka(1, 12));
    tmpdays = MonthDays(tmpDate.GetMonth(), tmpDate.GetYear());
    cout << "\n ������� ���� (�� 1 �� " << tmpdays << "): ";
    tmpDate.SetDay(proverka(1, tmpdays));
    cout << "\n ������ �������� ������ ������� " << endl;
    tmpnum = SelectedEvent(list);
    cout << "\n �������� ����: ";
    tmpDate.PrintDate();
    cout << "\n ������� ����� ����� ������� � ����� �����: " << list[tmpnum].DateDifference(tmpDate) << " �." << endl << endl;
}

void rezhim4(Calendar& list)
{
    int tmpnum = -1;
    int vibor = -1;
    int tmpdays = -1;
    int count = list.GetCounter();
    cout << "\n �� ������� �������� \n\t\"������������ ����� �������, ������� ��������� ������������\n\t������� �� �������� �������� � ������� ��� � ������� �������\"." << endl;
    tmpnum = SelectedEvent(list);
    cout << "\n �� ������� ���� �� ������ ����������� �������? (>=1)" << endl;
    tmpdays = proverka(1, INT_MAX);
    cout << "\n � ����� ������� �� ������ ����������� ��������� �������?\n\t1) � ������� �������\n\t2) � ������� �������" << endl;
    vibor = proverka(1, 2);
    if (vibor == 1)
        list[count] = list[tmpnum] + tmpdays;
    if (vibor == 2)
        list[count] = list[tmpnum] - tmpdays;
    list.SetCounterPlusOne();
    system("cls");
    cout << "\n �� ������������ ������� \"" << list[count].GetEvent() << "\"\n ����� �������: " << count + 1 << endl << endl;
}
