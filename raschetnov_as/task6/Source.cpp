#include <iostream>
#include <ctime>
#include <Windows.h>
#include "Field.h"
#include "Cell.h"

using namespace std;

void RulesOutput()
{
  cout << "Правила расстановки кораблей: " << endl;
  cout << "Вы вводите координату: сначала букву по вертикали, затем цифру по горизонтали. Получившаяся координата является как бы 'началом' корабля." << endl << "Затем Вы вводдите цифру, которая соответствует желаемому направлению корабля." << endl << endl;
}

bool ResultOutput()
{
  bool result;
  cout << "0. Промах" << endl;
  cout << "1. Попадание" << endl;
  cin >> result;
  return result;
}

void SetShootCoordinates(int* coordinates)
{
  int i = 0;
  char tempchar;
  int tempint;
  char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  char letters1[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  char letters2[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
  cout << "Введите координаты: " << endl;
  cin >> tempchar >> tempint;
  for(i = 0; i < 10; i++)
    if(tempchar == letters1[i] || tempchar == letters2[i])
    {
      coordinates[1] = i + 2;
      break;
    }
  coordinates[0] = tempint + 2;
}

inline void SetColor(int text, int bg)
{
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void SetCoordinates(int* coordinates, int& direction, int& indicator)
{
  int i = 0;
  char tempchar;
  int tempint;
  bool correct = false;
  char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  char letters1[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  char letters2[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
  cout << "Введите координаты: " << endl;
  cin >> tempchar >> tempint;
  for(i = 0; i < 10; i++)
    if(tempchar == letters1[i] || tempchar == letters2[i])
    {
      correct = true;
    }
  while (tempint < 0 || tempint > 9 || !correct)
  {
    cout << "Вы ошиблись, повторите ввод." << endl;
    cout << "Введите координаты: " << endl;
    cin >> tempchar >> tempint;
    for (i = 0; i < 10; i++)
      if (tempchar == letters1[i] || tempchar == letters2[i])
      {
        correct = true;
      }
  }
  for(i = 0; i < 10; i++)
    if(tempchar == letters1[i] || tempchar == letters2[i])
    {
      coordinates[1] = i + 2;
      break;
    }
  coordinates[0] = tempint + 2;
  if (indicator < 6)
  {
    cout << "Введите направление: " << endl;
    cout << "1. Влево" << endl;
    cout << "2. Вправо" << endl;
    cout << "3. Вверх" << endl;
    cout << "4. Вниз" << endl;
    cin >> direction;
    while (direction < 1 || direction > 4)
    {
      cout << "Вы ошиблись, повторите ввод." << endl;
      cout << "Введите направление: " << endl;
      cout << "1. Влево" << endl;
      cout << "2. Вправо" << endl;
      cout << "3. Вверх" << endl;
      cout << "4. Вниз" << endl;
      cin >> direction;
    }
  }
  else
    direction = 0;
}


int main()
{
  srand(time(NULL));
  setlocale(LC_ALL, "Russian");
  int* coordinates;
  int* enemyShootCoordinates;
  int ships[10] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
  bool gameOver = false;
  int i = 0;
  bool iskilled = 0;
  int counterOfMyShips = 10;
  int counterOfEnemyShips = 10;
  bool status = 0;
  int direction = 0;
  coordinates = new int[2];
  enemyShootCoordinates = new int[2];
  Field myfield;
  Field enemyfield;
  Field myenemyfield;
  Field enemymyfield;
  RulesOutput();
  for (i = 0; i < 10; i++)
  {
    myfield.FieldOutput();
    cout << "Сейчас вам необходимо расположить " << ships[i] << "-х палубный корабль." << endl;
    SetCoordinates(coordinates, direction, i);
    system("cls");
    while (!myfield.PlaceShip(ships[i], coordinates, direction))
    {
      cout << "Вы не можете расположить корабль таким образом! Расположите корабль иначе." << endl;
      cout << "Сейчас вам необходимо расположить " << ships[i] << "-х палубный корабль." << endl;
      myfield.FieldOutput();
      SetCoordinates(coordinates, direction, i);
      system("cls");
    }
  }
  enemyfield.PlaceShipAI();
  myfield.FieldOutput();
  myenemyfield.FieldOutput();
  while (!gameOver)
  {
    SetShootCoordinates(coordinates);
    status = enemyfield.Shoot(myenemyfield, coordinates);
    system("cls");
    myfield.FieldOutput();
    myenemyfield.FieldOutput();
    if (status)
      if (iskilled = enemyfield.IsKilled(coordinates))
      {
        SetColor(4, 0);
        cout << "Убит" << endl;
        SetColor(7, 0);
        counterOfEnemyShips--;
      }
      else
      {
        SetColor(4, 0);
        cout << "Ранен" << endl;
        SetColor(7, 0);
      }
    else
    {
      SetColor(2, 0);
      cout << "Мимо" << endl;
      SetColor(7, 0);
    }
    if (!counterOfEnemyShips)
    {
      cout << "Вы выиграли!" << endl;
      gameOver = 1;
      goto finish;
    }
    while (status)
    {
      SetShootCoordinates(coordinates);
      status = enemyfield.Shoot(myenemyfield, coordinates);
      system("cls");
      myfield.FieldOutput();
      myenemyfield.FieldOutput();
      if (status)
        if (iskilled = enemyfield.IsKilled(coordinates))
        {
          SetColor(4, 0);
          cout << "Убит" << endl;
          SetColor(7, 0);
          counterOfEnemyShips--;
        }
        else
        {
          SetColor(4, 0);
          cout << "Ранен" << endl;
          SetColor(7, 0);
        }
      else
      {
        SetColor(2, 0);
        cout << "Мимо" << endl;
        SetColor(7, 0);
      } 
      if (!counterOfEnemyShips)
      {
        cout << "Вы выиграли!" << endl;
        gameOver = 1;
        goto finish;
      }
    }
    myfield.GenerateCoordinatesAI(enemymyfield, enemyShootCoordinates);
    status = ResultOutput();
    if (status)
      if (iskilled = myfield.IsKilled(enemyShootCoordinates))
        counterOfMyShips--;
    myfield.ShootAI(enemyShootCoordinates, status);
    enemymyfield.ShootAI(enemyShootCoordinates, status);
    system("cls");
    myfield.FieldOutput();
    myenemyfield.FieldOutput();
    while (status)
    {
      myfield.GenerateCoordinatesAI(enemymyfield, enemyShootCoordinates);
      status = ResultOutput();
      if (status)
        if (iskilled = myfield.IsKilled(enemyShootCoordinates))
          counterOfMyShips--;
      myfield.ShootAI(enemyShootCoordinates, status);
      enemymyfield.ShootAI(enemyShootCoordinates, status);
      system("cls");
      myfield.FieldOutput();
      myenemyfield.FieldOutput();
    }
    if (!counterOfMyShips)
    {
      cout << "Вы проиграли!" << endl;
      gameOver = 1;
    }
finish:
    {}
  } 
  return 0;
}