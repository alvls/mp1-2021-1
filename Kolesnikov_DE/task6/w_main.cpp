#include <conio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
using namespace std;
class Snake
{
    private:
        int width;
        int height;
        int score;
        int level;
        bool isgame;
        int snake_len;
        int **field;
        enum class Directions{
            Left,
            Right,
            Up,
            Down
        };
        Directions C_Dir;
        void Draw_Console()
        {
            for(int i = 0;i< height;i++)
                for(int k = 0;k < width;k++)
                {
                    if((i>0) && (!k))
                        cout << endl;
                    if(field[i][k] == -1)
                        cout << "#";
                    if(field[i][k] == 0)
                        cout << " ";
                    if(field[i][k] > 1){
                        if (field[i][k] == snake_len) {
                            cout << "O";
                        }
                        else {
                            cout << "o";
                        }
                    }
                    if(field[i][k] == -2)
                        cout << "F";
                }
            cout << endl;
        }
        void Input(int& head_x, int& head_y)
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
                if (fruit_x == -1) {
                    Set_Fruit(fruit_x, fruit_y,head_x);
                }
                system("cls");
                if (!Snake_Move(head_x, head_y, fruit_x, fruit_y)) {
                    system("cls");
                    cout << "Game Over" << endl;
                    cout << "Your score: " << score << endl;
                    break;
                }
                Draw_Console();
                Sleep(500);
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
                    Delete_Fruit(fruit_x,fruit_y);
                    Set_Fruit(fruit_x, fruit_y,head_x);
                    score++;
                }
                else {
                    field[head_y][head_x] = snake_len + 1 ;
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
            for(int i = 0; i < width;i++)
            {
                field[0][i] = -1;
            }
            for(int i = 1; i < height - 1;i++)
            {
                field[i][0] = -1;
                for(int k = 1; k < width - 1;k++){
                    field[i][k] = 0;
                }
                field[i][width-1] = -1;
            }
            for(int i = 0; i < width;i++)
            {
                field[height - 1][i] = -1;
            }
        }
        void Set_Fruit(int& fruit_x, int& fruit_y,int & head_x)
        {
            srand(time(NULL));
            while (fruit_x != head_x) {
                fruit_x = rand() % (width - 2) + 1;
            }
            fruit_y = rand() % (height-2) +1 ;
            field[fruit_y][fruit_x] = -2;
        }
        void Delete_Fruit(int& fruit_x,int& fruit_y)
        {
            field[fruit_y][fruit_x] = 0;
        }
        void Draw_Snake(int& head_x,int& head_y)
        {
            srand(time(NULL));
            head_x = rand() % (width - 5) + 1;
            head_y = rand() % (height - 2) + 1;
            for (int i = 0; i < snake_len; i++)
            {
                field[head_y][head_x+i] = snake_len + 1 - i;
            }
        }

    public:
        Snake(int _width,int _height,int _len,int _level = 1) : score(0),level(_level),isgame(false),snake_len(_len),C_Dir(Directions::Left)
        {
            height = _height + 2;
            width = _width + 2;
            field = new int* [height];
            for(int i = 0; i < height;i++)
            {
                field[i] = new int [width];
            }
        }
        void Draw(){
            int head_x, head_y;
            isgame = true;
            Draw_Field();
            Draw_Snake(head_x,head_y);
            Draw_Console();
            Input(head_x, head_y);
        }
        ~Snake()
        {
            for(int i = 0;i < height;i++){
                delete[] field[i];
            }
            delete [] field;
        }
};
int main()
{
    Snake s(20,20,5);
    s.Draw();
}
