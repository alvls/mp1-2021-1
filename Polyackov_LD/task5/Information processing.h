#pragma once

template <typename T> T check(T a, T b)
{
    T choice = -1;
    while ((choice < a) || (choice > b))
    {
        cin >> choice;
        if ((choice < a) || (choice > b))
        {
            cout << "������� �������� �����. ���������� ������ �����." << endl;
            cleaner();
        }
    }
    return choice;
}

void cleaner(); // ������� ����� �����
