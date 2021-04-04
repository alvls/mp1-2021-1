
#include "all.h"

bool menu(Pedometer& pedometer)
{
    int choice = -1;
    cout << "\n ������ �� ���������� � ����. ��������, ��� ����� �������:\n\t(1) ������ ���� ������ ���������\n\t(2) ������ ��������\n\t(3) �������� ���������� � ��������� ��������\n\t(4) ����� ������� ����� ����� � ��������� ������\n\t(5) ����� ������� ����� ����� �� ��� ������� ����������\n\t(6) ����� ������� ����� ����� � ��������� ���� ������\n\t    �� ��� ������� ����������\n\t(7) ����� ������������ ����� ����� � ���� � ���������\n\t    ������ � ����, ����� ��� ���� ����������\n\t(8) ����� ������������ ����� ����� � ���� �� ���\n\t    ������� ���������� � ����, ����� ��� ���� ����������\n\t(9) ��������� ������� ��������� � ����\n\t10) ������� ������� ��������� �� �����\n\t11) ����� ������������\n\t(0) ����� �� ���������" << endl;
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

void mode1(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"������ ���� ������ ���������\"\n\n ���� ������ ���������: ";
    pedometer.PrintStartDate();
    cout << "\n\n";
}

void mode2(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"������ ��������\"\n\n";
    pedometer.SetOneDay(CreateNewOneDay());
    cout << "\n";
}

void mode3(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"�������� ���������� � ��������� ��������\"\n";
    size_t tmp = 1;
    OneDay tmponeday;
    Count tmpcount;
    if (pedometer.GetSize() == 0)
        throw exception(" �� ������ �� ������ ��������");
    if (pedometer.GetSize() == 1)
    {
        cout << "\n ����� ������������ ����!\n";
        tmponeday = pedometer[0];
        system("pause");
    }
    else
    {
        cout << "\n";
        pedometer.PrintPedometer();
        if (pedometer.GetSize() > 10)
        {
            cout << "\n ���� �������� 10 ���� �� " << pedometer.GetSize() << "\n ������� ���������� ���? \n 1) ��\n 2) ���\n";
            if (check(1, 2) == 1)
            {
                cout << "\n";
                pedometer.PrintPedometer(1);
            }
        }
        cout << "\n �������� ���� �� ����: ";
        tmp = check(size_t(1), pedometer.GetSize());
        tmponeday = pedometer[tmp - 1];
    }
    if (tmponeday.GetCountSize() == 1)
    {
        cout << "\n � ���� ���� ����� ������������ �������!\n";
        tmpcount = tmponeday.GetCountAtInd(0);
        system("pause");
    }
    else
    {
        cout << "\n\n �������� ���� �� ���������:\n";
        tmponeday.PrintAllCounts();
        tmp = check(size_t(1), tmponeday.GetCountSize());
        tmpcount = tmponeday.GetCountAtInd(tmp - 1);
    }
    system("cls");
    cout << "\n ��������� �������: \n\n ";
    tmponeday.PrintDateOfDay();
    cout << "\n\n ";
    tmpcount.PrintCount();
    cout << "\n ";
    tmpcount.PrintCountSteps();
    cout << "\n";
}

void mode4(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"����� ������� ����� ����� � ��������� ������\"" << endl;
    if (pedometer.GetSize() == 0)
        throw exception(" �� ������ �� ������ ��������");
    size_t tmpsize = pedometer.PrintMonths();
    cout << "\n �������� ������ �����: ";
    size_t choice = check(size_t(1), tmpsize);
    double result = pedometer.AverageInMonth(choice);
    cout << "\n ������� ����� ����� � ��������� ������: " << result << "\n\n";
}

void mode5(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"����� ������� ����� ����� �� ��� ������� ����������\"" << endl;
    if (pedometer.GetSize() == 0)
        throw exception(" �� ������ �� ������ ��������");
    double tmp = pedometer.AverageInAllHistory();
    cout << "\n ������� ����� ����� �� ��� ������� ����������: " << tmp << "\n\n";
}

void mode6(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"����� ������� ����� ����� �\n ��������� ���� ������ �� ��� ������� ����������\"" << endl;
    if (pedometer.GetSize() == 0)
        throw exception(" �� ������ �� ������ ��������");
    cout << "\n �������� ���� ������:\n (1)�����������\n (2)�������\n (3)�����\n (4)�������\n (5)�������\n (6)�������\n (7)�����������\n";
    int choice = check(1, 7);
    double result;
    if (choice == 7)
        choice = 0;
    result = pedometer.AverageInWeekDay(choice);
    const string WeekDayName[7] = { " �����������", " �����������", "� �������", " �����", " �������", " �������", " �������" };
    cout << "\n ������� ����� ����� �" << WeekDayName[choice] << ": " << result << "\n\n";
}

void mode7(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"����� ������������ ����� ����� � ����\n � ��������� ������ � ����, ����� ��� ���� ����������\"" << endl;
    if (pedometer.GetSize() == 0)
        throw exception(" �� ������ �� ������ ��������");
    size_t tmpsize = pedometer.PrintMonths();
    cout << "\n �������� ������ �����: \n";
    size_t choice = check(size_t(1), tmpsize);
    OneDay result = pedometer.MaxInMonth(choice);
    system("cls");
    cout << "\n ��������� �����: ";
    result.PrintMonthOfDay();
    cout << "\n ������������ ����� ����� � ����: " << result.GetStepsDay() << "\n\n ���� ������� ���:\n\n ";
    result.PrintDateOfDay();
    cout << "\n\n";
}

void mode8(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"����� ������������ ����� ����� � ����\n �� ��� ������� ���������� � ����, ����� ��� ���� ����������\"\n";
    if (pedometer.GetSize() == 0)
        throw exception(" �� ������ �� ������ ��������");
    cout << "\n";
    OneDay tmponeday = pedometer.MaxInDay();
    cout << " ";
    tmponeday.PrintDateOfDay();
    cout << "\n\n ���������� �����: " << tmponeday.GetStepsDay() << "\n\n";
}

void mode9(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"��������� ������� ��������� � ����\"\n";
    pedometer.SaveInFile();
    cout << "\n ���������� ������ �������!\n\n";
}

void mode10(Pedometer& pedometer)
{
    cout << "\n �� ������� ��������: \"������� ������� ��������� �� �����\"\n";
    pedometer.ReadFromFile();
    cout << "\n ���������� ������ �������!\n\n";
}

void mode11(Pedometer& pedometer)
{
    cout << "\n �� ������� ����� ������������\n\n ���������� �������� ������ ��� ���������� ����������\n ����������?\n (1) ��\n (2) ���\n";
    if (check(1, 2) == 2)
        return;
    cout << "\n �������� ���������� ����, ������ ��� �����: ";
    int tmp = check(1, INT_MAX);
    pedometer.RandomGenerator(tmp);
    cout << "\n ������� ������� ��������� ����: " << tmp << "\n\n";
}
