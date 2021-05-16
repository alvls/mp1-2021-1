#include <conio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
using namespace std;
class Draw
{
private:
    int height;
    int width;
    int h_cl;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    void cls(HANDLE hConsole)
    {
        COORD coordScreen = { 0, 0 };
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;

        if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
            return;
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ',
            dwConSize, coordScreen, &cCharsWritten))
            return;
        if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
            return;
        if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
            dwConSize, coordScreen, &cCharsWritten))
            return;
        SetConsoleCursorPosition(hConsole, coordScreen);
    }
    void SetColor(int text, int bg) {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
    }
    Draw() = default;
public:
    Draw(int _width, int _height, int _h_cl) : width(_width + 2), height(_height + 2), h_cl(_h_cl)
    {  }
    int Get_Width()
    {
        return width;
    }
    int Get_Height()
    {
        return height;
    }
    void Clear_Screen()
    {
        cls(hConsole);
    }
    void DisableShowConsoleCursor()
    {
        CONSOLE_CURSOR_INFO     showCursor;
        GetConsoleCursorInfo(hConsole, &showCursor);
        showCursor.bVisible = false;
        SetConsoleCursorInfo(hConsole, &showCursor);
    }
    void Draw_Console(int** field, int snake_len)
    {
        for (int i = 0; i < height; i++)
            for (int k = 0; k < width; k++)
            {
                if ((i > 0) && (!k))
                    cout << endl;
                if (field[i][k] == -1)
                    cout << "#";
                if (field[i][k] == 0)
                    cout << " ";
                if (field[i][k] > 0) {
                    if (field[i][k] == snake_len) {
                        SetColor(h_cl, 0);
                        cout << "O";
                        SetColor(7, 0);
                    }
                    else {
                        cout << "o";
                    }
                }
                if (field[i][k] == -2)
                    cout << "F";
            }
        cout << endl;
    }
};





class Snake
{
private:
    Draw* Paint;
    int width;
    int height;
    int score;
    int level;
    bool isgame;
    int snake_len;
    int snake_end_len;
    int** field;
    int Duration;
    enum class Directions {
        Left,
        Right,
        Up,
        Down
    };
    Directions C_Dir;
    int Tick(int& head_x, int& head_y)
    {
        int fruit_x = -1, fruit_y = -1;
        while (true) {
            if (_kbhit()) {
                switch (_getch()) {
                case 72:
                    if (C_Dir != Directions::Down) {
                        C_Dir = Directions::Up;
                    }
                    break;
                case  80:
                    if (C_Dir != Directions::Up) {
                        C_Dir = Directions::Down;
                    }
                    break;
                case 75:
                    if (C_Dir != Directions::Right) {
                        C_Dir = Directions::Left;
                    }
                    break;
                case 77:
                    if (C_Dir != Directions::Left) {
                        C_Dir = Directions::Right;
                    }
                    break;
                }
            }
            if (snake_len == snake_end_len) {
                return score;
            }
            if (fruit_x == -1) {
                Set_Fruit(fruit_x, fruit_y, head_y);
            }
            Paint->Clear_Screen();
            if (!Snake_Move(head_x, head_y, fruit_x, fruit_y)) {
                Paint->Clear_Screen();
                return score;
            }
            Paint->Draw_Console(field,snake_len);
            Sleep(Duration);
        }
        cin.ignore();
    }
    bool Snake_Move(int& head_x, int& head_y, int& fruit_x, int& fruit_y)
    {

        switch (C_Dir) {
        case Directions::Left:head_x--; break;
        case Directions::Right: head_x++; break;
        case Directions::Up: head_y--; break;
        case Directions::Down: head_y++; break;
        }
        if (!(field[head_y][head_x] == -1 || field[head_y][head_x] > 1))
        {

            if ((head_x == fruit_x) && (head_y == fruit_y))
            {
                field[head_y][head_x] = snake_len + 1;
                snake_len += 1;
                Delete_Fruit(fruit_x, fruit_y);
                score++;
            }
            else {
                field[head_y][head_x] = snake_len + 1;
                for (int i = 0; i < height; i++) {
                    for (int k = 0; k < height; k++) {
                        if (field[i][k] > 0) {
                            field[i][k]--;
                        }
                    }
                }
            }
            return true;
        }
        else
            return false;
    }
    void Draw_Field()
    {
        for (int i = 0; i < width; i++)
        {
            field[0][i] = -1;
        }
        for (int i = 1; i < height - 1; i++)
        {
            field[i][0] = -1;
            for (int k = 1; k < width - 1; k++) {
                field[i][k] = 0;
            }
            field[i][width - 1] = -1;
        }
        for (int i = 0; i < width; i++)
        {
            field[height - 1][i] = -1;
        }
    }
    void Set_Fruit(int& fruit_x, int& fruit_y, int& head_y)
    {
        srand(time(NULL));
         do{
            fruit_y = rand() % (width - 2) + 1;
         } while (fruit_y == head_y);
        fruit_x = rand() % (height - 2) + 1;
        field[fruit_y][fruit_x] = -2;
    }
    void Delete_Fruit(int& fruit_x, int& fruit_y)
    {
        fruit_x = -1;
        fruit_y = -1;
    }
    void Set_Snake(int& head_x, int& head_y)
    {
        srand(time(NULL));
        head_y = height / 2;
        head_x = width / 2;
        for (int i = 0; i < snake_len; i++)
        {
            field[head_y][head_x + i] = snake_len - i;
        }
    }
    int Level_Select(int lvl) {
        switch (lvl) {
        case 1:
            return 500;
        case 2:
            return 300;
        case 3:
            return 200;
        }
    }

public:
    Snake(Draw* _Paint,int _end_len,int _len, int _lvl) : Paint(_Paint),score(0),isgame(false), snake_len(_len),snake_end_len(_end_len),C_Dir(Directions::Left)
    {
        width = Paint->Get_Width();
        height = Paint->Get_Height();
        Duration = Level_Select(_lvl);
        field = new int* [height];
        for (int i = 0; i < height; i++)
        {
            field[i] = new int[width];
        }
    }
    int Start() {
        int head_x, head_y;
        isgame = true;
        Draw_Field();
        Set_Snake(head_x, head_y);
        Paint->Draw_Console(field,snake_len);
        return Tick(head_x, head_y);
    }
    ~Snake()
    {
        for (int i = 0; i < height; i++) {
            delete[] field[i];
        }
        delete[] field;
    }
};





int main()
{
    Draw a(20,20,14);
    a.DisableShowConsoleCursor();
    Snake s(&a,10,5,500);
    cout << s.Start() << endl;
    system("pause");
}
