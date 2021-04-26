#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Client-Manager.h"

using namespace std;
string Client::getName()
{
  return name;
}

string Client::getLastName()
{
  return lastname;
}

string Client::getPatronymic()
{
  return patronymic;
}

int Client::getCarNumber()
{
  return carnumber;
}

int Client::getSeatNumber()
{
  return seatnumber;
}

int Manager::informationOutput(string path, string carnumber)
{
  int i = 0;
  ifstream filein;
  int number;
  int counter = 0;
  int car;
  bool location;
  bool availability;
  string pathcopy = path;
  filein.open(pathcopy += carnumber);
  while(!filein.eof())
  {
    counter++;
    filein >> number;
    filein >> location;
    filein >> availability;
    if (!availability)
    {
      cout << "Номер: " << number << "\t";
      if(location)
        cout << "Верхнее" << endl;
      else
        cout << "Нижнее" << endl;
    }
  }
  return counter;
}

void Manager::createClient(string _name, string _lastname, string _patronymic, int _carnumber, int _seatnumber)
{
  Client client(_name, _lastname, _patronymic, _carnumber, _seatnumber);
  clients.push_back(client);
}

void Manager::loadClientsList(string path)
{
  string indicator;
  int counter = -1;
  int carnumber;
  int seatnumber;
  string information[3];
  ifstream filein;
  filein.open(path);
  while (!filein.eof())
  {
    for(int i = 0; i < 3; i++)
      filein >> information[i];
    filein >> carnumber;
    filein >> seatnumber;
    Client client(information[0], information[1], information[2], carnumber, seatnumber);
    clients.push_back(client);
    counter++;
  }
  if(!counter)
    clients.pop_back();
  filein.close();
}

void Manager::showClients()
{
  for (int i = 0; i < clients.size(); i++)
  { 
    cout << "Имя: " << clients[i].getName() << endl;
    cout << "Фамилия: " << clients[i].getLastName() << endl;
    cout << "Отчество: "<< clients[i].getPatronymic() << endl;
    cout << "Номер вагона: " << clients[i].getCarNumber() << endl;
    cout << "Номер места: " << clients[i].getSeatNumber() << endl;
  }
}

int Manager::getSize()
{
  return clients.size();
}

void Manager::clientBaseUpdate(string path)
{
  ofstream fileout(path);
  for (int i = 0; i < clients.size() - 1; i++)
  {
    fileout << clients[i].getName() << " ";
    fileout << clients[i].getLastName() << " ";
    fileout << clients[i].getPatronymic() << " ";
    fileout << clients[i].getCarNumber() << " ";
    fileout << clients[i].getSeatNumber();
    fileout << endl;
  }
  fileout << clients[clients.size() - 1].getName() << " ";
  fileout << clients[clients.size() - 1].getLastName() << " ";
  fileout << clients[clients.size() - 1].getPatronymic() << " ";
  fileout << clients[clients.size() - 1].getCarNumber() << " ";
  fileout << clients[clients.size() - 1].getSeatNumber();
  fileout.close();
}

void Manager::showFreeSeats(string path)
{
  int information[3];
  ifstream filein;
  filein.open(path);
  while (!filein.eof())
  {
    for(int i = 0; i < 3; i++)
      filein >> information[i];
    if (information[2])
    {
      cout << "Номер места: " << information[0] << "\t\t";
      if (information[1])
        cout << "Расположение: Верхнее" << endl;
      else 
        cout << "Расположение: Нижнее" << endl;
    }
  }
}

void Manager::bookSeat(string path, string car, int _seatnumber)
{
  int information[3];
  string pathcopy = path;
  ofstream fileout;
  int temp;
  string oldname(pathcopy += "\\TempCar.txt");
  string newname(path += car);
  ifstream filein;
  fileout.open(pathcopy);
  if(fileout.is_open())
  filein.open(path);
  if (filein.is_open())
    for (int i = 0; i < _seatnumber - 1; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        filein >> information[j];
      }
      for (int j = 0; j < 3; j++)
      {
        fileout << information[j] << " ";
      }
      fileout << endl;
    }
  for (int i = 0; i < 2; i++)
    filein >> information[i];
  for (int i = 0; i < 2; i++)
    fileout << information[i] << " ";
  filein >> temp;
  fileout << 1;
  while(!filein.eof())
  {
    fileout << endl;
    for (int j = 0; j < 3; j++)
    {
      filein >> information[j];
    }
    for (int j = 0; j < 2; j++)
    {
      fileout << information[j] << " ";
    }
    fileout << information[2];
  }
  filein.close();
  fileout.close();
  remove(path.c_str());
  rename(oldname.c_str(), newname.c_str());
}

void Manager::formTicket(string _date, string _name, string _lastname, string _patronymic, int direction, int train)
{
  string path = "Tickets\\";
  string trainNumbersNN[5] = {"727", "619", "224", "197", "201"};
  string trainNumbersMSK[5] = { "453", "129", "205", "111", "732" };
  string directions[2] = {"Москва", "Нижний Новгород"};
  string departureStation = directions[direction - 1];
  string arrivalStation;
  string trainNumber;
  if (direction == 1)
    arrivalStation = directions[1];
  else
    arrivalStation = directions[0];
  if(direction == 1)
    trainNumber = trainNumbersMSK[train - 1];
  else
    trainNumber = trainNumbersNN[train - 1];
  Ticket ticket(_date, trainNumber, _name, _lastname, _patronymic, departureStation, arrivalStation);
  ofstream fileout;
  path += _lastname;
  path += ".txt";
  fileout.open(path);
  fileout << "Дата: "<< _date << endl;
  fileout << "Номер поезда: " << trainNumber << endl;
  fileout << "Имя: "<< _name << endl;
  fileout << "Фамилия: "<< _lastname << endl;
  fileout << "Отчество: "<< _patronymic << endl;
  fileout << "Станция отправления: "<< departureStation << endl;
  fileout << "Станция прибытия: "<< arrivalStation;
  fileout.close();
}