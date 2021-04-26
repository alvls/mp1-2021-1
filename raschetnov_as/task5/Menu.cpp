#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "Menu.h";

using namespace std;

int directionChoice()
{
  int direction;
  cout << "Выберите маршрут поезда: " << endl;
  cout << "1.Москва - Нижний Новгорд." << endl;
  cout << "2.Нижний Новгород - Москва." << endl;
  cin >> direction;
  while (direction != 1 && direction != 2)
  {
    system("cls");
    cout << "Вы допустили ошибку, повторите ввод." << endl;
    cout << "Выберите маршрут поезда: " << endl;
    cout << "1.Москва - Нижний Новгорд." << endl;
    cout << "2.Нижний Новгород - Москва." << endl;
    cin >> direction;
  }
  system("cls");
  return direction;
} 

string dateChoice()
{
  string path = "Days1\\Day";
  string pathcopy = "Days1\\Day";
  string indicatorString = "\\Lastochka0929NN\\Car1.txt";
  ifstream filein;
  bool flag = 0;
  string date;
  cout << "Введите дату предполагаемой поездки в формате ддммгг: " << endl;
  cin >> date;
  pathcopy += date;
  pathcopy += indicatorString;
  filein.open(pathcopy);
  flag = filein.is_open();
  while (!flag)
  {
    pathcopy = path;
    system("cls");
    cout << "Вы допустили ошибку, повторите ввод." << endl;
    cout << "Введите дату предполагаемой поездки в формате ддммгг: " << endl;
    cin >> date;
    pathcopy += date;
    pathcopy += indicatorString;
    filein.open(pathcopy);
    flag = filein.is_open();
  }
  system("cls");
  return date;
}

int showAvailableTrains(std::string date)
{
  int i = 0;
  string day = "Day";
  day += date;
  int train = 0;
  int indicator = 0;
  void (*trains[5])() = {showLastochka0929, showLastochka1331, showFirmennii1514, showLastochka1755, showSkorii1824};
  int time[5] = {929, 1331, 1514, 1755, 1824};
  cout << "Доступные поезда: " << endl;
  if (getDate1() == day)
    for (i = 0; i < 5; i++)
    {
      if (getTime() < time[i] - 100)
      {
        indicator = 1;
        cout << i + 1 << ".";
        trains[i]();
      }
    }
  else
  {
    for(int i = 0; i < 5; i++)
    {
      indicator = 1;
      cout << i + 1 << ".";
      trains[i]();
    }
  }     
  if(!indicator)
  {
    cout << "Нет доступных поездов!" << endl;
    cout << "Вы будете перенаправлены на выбор направления." << endl << endl;
    return INT_MAX;
  }
  cout << "Выберите нужный поезд: " << endl;
  cin >> train;
  while (train < 1 || train > 5)
  {
    cout << "Вы допустили ошибку, повторите ввод." << endl;
    cout << "Выберите нужный поезд: " << endl;
    cin >> train;
  }
  system("cls");
  return train;
} 

int getTime()
{
  time_t rawtime;
  struct tm* timeinfo;
  int var;
  char buffer[80];
  time (&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer,sizeof(buffer),"%H%M",timeinfo);
  string str(buffer);
  var = stoi(str);
  return var;
}

void showLastochka0929()
{
  cout << "Ласточка, 09:29." << endl;
}

void showLastochka1331()
{
  cout << "Ласточка, 13:31." << endl;
}

void showLastochka1755()
{
  cout << "Ласточка, 17:55." << endl;
} 

void showFirmennii1514()
{
  cout << "Фирменный, 15:14." << endl;
}

void showSkorii1824()
{
  cout << "Скорый, 18:24." << endl;
}

string getDate1()
{
  time_t rawtime;
  string str = "Day";
  struct tm* timeinfo;
  char buffer[80];
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, sizeof(buffer), "%d%m%y", timeinfo);
  str += buffer;
  return str;
}

void carInformation(int train, int direction, string date)
{
  int i = 0;
  int j = 0;
  int k = 0;
  int counterOfFreeSeats = 0;
  int tempvar;
  string pathcopy = "Days1\\Day";
  string directions[2] = {"MSK", "NN"};
  string pathtofolder;
  string trains[5] = {"\\Lastochka0929", "\\Lastochka1331", "\\Firmennii1514", "\\Lastochka1755", "\\Skorii1824"};
  string cars[12] = {"\\Car1.txt", "\\Car2.txt", "\\Car3.txt" , "\\Car4.txt" , "\\Car5.txt" , "\\Car6.txt" , "\\Car7.txt" , "\\Car8.txt" , "\\Car9.txt" , "\\Car10.txt", "\\Car11.txt", "\\Car12.txt"};
  ifstream filein;
  pathcopy += date;
  pathcopy += trains[train - 1];
  pathcopy += directions[direction - 1];
  pathtofolder = pathcopy; 
  switch (train)
  {
    case 3:
    {
      for (i = 0; i < 4; i++)
      {
        counterOfFreeSeats = 0;
        cout << i + 1 << ".Тип вагона:  Плацкартный " << "\t";
        filein.open(pathcopy += cars[i]);
        for(k = 0; k < 54; k++)
        {
          for(j = 0; j < 3; j++)
            filein >> tempvar;
          if(!tempvar)
            counterOfFreeSeats++;
        }
        cout << "Количество свободных мест: " << counterOfFreeSeats << endl;
        filein.close();
        pathcopy = pathtofolder;
      }
      for (i; i < 10; i++)
      {
        counterOfFreeSeats = 0;
        cout << i + 1 << ".Тип вагона:  Купейный   " << "\t";
        filein.open(pathcopy += cars[i]);
        for (k = 0; k < 36; k++)
        {
          for(j = 0; j < 3; j++)
            filein >> tempvar;
          if(!tempvar)
            counterOfFreeSeats++;
        }
        cout << "Количество свободных мест: " << counterOfFreeSeats << endl;
        filein.close();
        pathcopy = pathtofolder;
      } 
      for (i; i < 12; i++)
      {
        counterOfFreeSeats = 0;
        cout << i + 1 << ".Тип вагона:  СВ      " << "\t";
        filein.open(pathcopy += cars[i]);
        for (k = 0; k < 18; k++)
        {
          for(j = 0; j < 3; j++)
            filein >> tempvar;
          if(!tempvar)
            counterOfFreeSeats++;
        }
        cout << "Количество свободных мест: " << counterOfFreeSeats << endl;
        filein.close();
        pathcopy = pathtofolder;
      } 
      break;
    }
    case 5:
    {
      for (i = 0; i < 4; i++)
      {
        counterOfFreeSeats = 0;
        cout << i + 1 << ".Тип вагона: Плацкартный " << "\t";
        filein.open(pathcopy += cars[i]);
        for (k = 0; k < 54; k++)
        {
          for(j = 0; j < 3; j++)
            filein >> tempvar;
          if(!tempvar)
            counterOfFreeSeats++;
        }
        cout << "Количество свободных мест: " << counterOfFreeSeats << endl;
        filein.close();
        pathcopy = pathtofolder;
      }
      for (i; i < 12; i++)
      {
        counterOfFreeSeats = 0;
        cout << i + 1 << ".Тип вагона: Купейный   " << "\t";
        filein.open(pathcopy += cars[i]);
        for (k = 0; k < 36; k++)
        {
          for(j = 0; j < 3; j++)
            filein >> tempvar;
          if(!tempvar)
            counterOfFreeSeats++;
        }
        cout << "Количество свободных мест: " << counterOfFreeSeats << endl;
        filein.close();
        pathcopy = pathtofolder;
      } 
      break;
    } 
    default:
    {
      for (i = 0; i < 10; i++)
      {
        counterOfFreeSeats = 0;
        cout << i + 1 << ".Тип вагона: Обычный" << "\t\t\t";
        filein.open(pathcopy += cars[i]);
        for (k = 0; k < 100; k++)
        {
          for(j = 0; j < 3; j++)
            filein >> tempvar;
          if(!tempvar)
            counterOfFreeSeats++;
        }
        cout << "Количество свободных мест: " << counterOfFreeSeats << endl;
        filein.close();
        pathcopy = pathtofolder;
      }
      break;
    }
  }
}

string carChoice(int& carnumber, int train, int direction, string date)
{
  string cars[12] = {"\\Car1.txt", "\\Car2.txt", "\\Car3.txt" , "\\Car4.txt" , "\\Car5.txt" , "\\Car6.txt" , "\\Car7.txt" , "\\Car8.txt" , "\\Car9.txt" , "\\Car10.txt", "\\Car11.txt", "\\Car12.txt"};
  switch (train)
  {
    case 3:
    {
      carInformation(train, direction, date);
      cout << "Введите номер вагона (от 1 до 12): " << endl;
      cin >> carnumber;
      while(carnumber < 1 || carnumber > 12)
      {
        system("cls");
        cout << "Вы допустили ошибку, повторите ввод:" << endl;
        cout << "Введите номер вагона (от 1 до 12): " << endl;
        cin >> carnumber;
      }
    break;
    }
    case 5:
    {
      carInformation(train, direction, date);
      cout << "Введите номер вагона (от 1 до 12): " << endl;
      cin >> carnumber;
      while(carnumber < 1 || carnumber > 12)
      {
        system("cls");
        cout << "Вы допустили ошибку, повторите ввод:" << endl;
        cout << "Введите номер вагона (от 1 до 12): " << endl;
        cin >> carnumber;
      }
    break;
    }
    default:
    {
      carInformation(train, direction, date);
      cout << "Введите номер вагона (от 1 до 10): " << endl;
      cin >> carnumber;
      while(carnumber < 1 || carnumber > 10)
      {
        system("cls");
        cout << "Вы допустили ошибку, повторите ввод:" << endl;
        cout << "Введите номер вагона (от 1 до 10): " << endl;
        cin >> carnumber;
      }
    }
  }
  system("cls");
  return cars[carnumber - 1];
}

int seatChoice(int carCounter)
{
  int seat = 0;
  cout << "Выберите место: " << endl;
  cin >> seat;
  while (seat < 0 || seat > carCounter)
  {
    cout << "Вы допустили ошибку, повторите ввод." << endl;
    cout << "Выберите место: " << endl;
    cin >> seat;
  }
  system("cls");
  return seat;
}

void getFullName(std::string* FullName)
{
  int i = 0;
  cout << "Введите ФИО." << endl;
  cout << "Имя: " << endl;
  cin >> FullName[0];
  cout << "Фамилия: " << endl;
  cin >> FullName[1];
  cout << "Отчество: " << endl;
  cin >> FullName[2];
}

int formPrice(int train, int car)
{
  int prices[4] = {500, 1000, 2000, 5000};
  int price;
  if(train == 1 || train == 2 || train == 4)
    price = prices[0];
  if (train == 3)
  {
    if(car < 5)
      price = prices[1];
    if(car < 11 && car > 4)
      price = prices[2];
    if(car > 10)
      price = prices[3];
  }
  if (train == 5)
  {
    if(car < 9)
      price = prices[1];
    if(car > 8)
      price = prices[2];
  }
  return price;
}