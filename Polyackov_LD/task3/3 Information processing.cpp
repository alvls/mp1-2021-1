
#include "all.h"

int proverka(int a, int b)
{
    int vibor = INT_MIN;
    while ((vibor < a) || (vibor > b))
    {
        cin >> vibor;
        if ((vibor < a) || (vibor > b))
        {
            cout << "Введено неверное число. Попробуйте ввести снова." << endl;
            cleaner();
        }
    }
    return vibor;
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
