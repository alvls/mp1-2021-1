#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <clocale>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <cstdio>
#include <errno.h>
#include <direct.h>
#include "Menu.h";
#include "InformationUpdate.h"
#include "Client-Manager.h"

using namespace std;

class Manager;
int choice;

int main()
{
  setlocale(LC_ALL, "ru");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  int choice = 0;
  int carCounter;
  int train = INT_MAX;
  int price = 0;
  string car;
  int carnumber;
  int seat;
  string directions[2] = {"MSK", "NN"};
  string FullName[3];
  string trains[5] = {"\\Lastochka0929", "\\Lastochka1331", "\\Firmennii1514", "\\Lastochka1755", "\\Skorii1824"};
  string path = "Days1\\Day";
  string pathcopy = "Days1\\Day";
  int direction;
  string date;
  string trainfolder;
  int counter = 0;
  Manager manager;
  deleteExtraFolders(counter);
  currentInfoUpdate(counter);
  addNewFolders(counter);
  while(choice != 4)
  {
    choice = 0;
    while(choice != 1 && choice != 2)
    {
      choice = 0;
      train = INT_MAX;
      while(train == INT_MAX)
      {
        pathcopy = path; 
        direction = directionChoice();
        date = dateChoice();
        pathcopy += date;
        train = showAvailableTrains(date);
      }
      pathcopy += trains[train - 1];
      pathcopy += directions[direction - 1];
      while(choice != 1 && choice != 3)
      {
        car = carChoice(carnumber, train, direction, date);
        carCounter = manager.informationOutput(pathcopy, car);
        seat = seatChoice(carCounter);
        price = formPrice(train, carnumber);
        cout << "���������� ������ ����� ? ��������� ������ ��������: " << price << " ������."<< endl << "1.��" << endl << "2.���, ���������� ����� ���� (�� ������ �������������� �� ����� ������)." << endl << "3.��������� � ������ ����������� � ����." << endl;
        cout << "4.���������� ������� ������� ������, ����� �� ���������." << endl;
        cin >> choice;
        system("cls");
        if (choice == 4)
          return 0;
      }
    }
    getFullName(FullName);
    manager.createClient(FullName[0], FullName[1], FullName[2], carnumber, seat);
    manager.bookSeat(pathcopy, car, seat);
    manager.formTicket(date, FullName[0], FullName[1], FullName[2], direction, train);
    manager.loadClientsList(pathcopy += "\\Clients.txt");
    manager.clientBaseUpdate(pathcopy);
    cout << "����� ���������. ������������ � ��� �����������, �� ������ � ���������� Tickets. ������� 4, ����� ����� �� ��������� ��� 1, ����� ������ ��� �������." << endl;
    cin >> choice;
  }
  return 0;
};