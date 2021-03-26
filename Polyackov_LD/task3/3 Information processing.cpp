
#include "all.h"

int checking(int a, int b)
{
    int choice = INT_MIN;
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

void cleaner()
{
    while (getchar() != '\n');
    cin.clear();
}

void gotoxy(int x, int y)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(Console, pos);
}
