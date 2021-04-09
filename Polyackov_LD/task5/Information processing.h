#pragma once

template <typename T> T check(T a, T b)
{
    T choice = -1;
    while ((choice < a) || (choice > b))
    {
        cin >> choice;
        if ((choice < a) || (choice > b))
        {
            cout << "Введено неверное число. Попробуйте ввести снова." << endl;
            cleaner();
        }
    }
    return choice;
}

void cleaner(); // Очищает поток ввода
