#include <iostream>
#include <fstream>
#include <sstream>
#include "Field.h"
#include "Cell.h"

using namespace std;

Field::Field()
{
  char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  int i = 0, j = 0;
  for(j = 2; j < 12; j++)
    field[0][j].SetSymbol(letters[j - 2]);
  for(i = 2; i < 12; i++)
    field[i][0].SetSymbol(numbers[i - 2]);
  for(j = 1; j < 13; j++)
    field[1][j].SetSymbol('*');
  for(j = 1; j < 13; j++)
    field[12][j].SetSymbol('*');
  for(i = 2; i < 12; i++)
    field[i][1].SetSymbol('*');
  for(i = 2; i < 12; i++)
    field[i][12].SetSymbol('*');
  for(i = 2; i < 12; i++)
    for(j = 2; j < 12; j++)
      field[i][j].SetStatus(1);
}

void Field::FieldOutput()
{
  int i = 0, j = 0;
  for(i = 0; i < 13; i++)
  {
    for(j = 0; j < 13; j++)
      cout << field[i][j].GetSymbol() << " ";
    cout << endl;
  }
}

bool Field::PlaceShip(int length, int* coordinates, int direction)
{
  int i = 0, j = 0;
  if(!field[coordinates[0]][coordinates[1]].GetStatus() || field[coordinates[0]][coordinates[1]].GetStatus() == 2)
    return false;
  switch (direction)
  {
    case 0:
    {
      field[coordinates[0]][coordinates[1]].SetSymbol('+');
      field[coordinates[0]][coordinates[1]].SetStatus(2);
      field[coordinates[0] - 1][coordinates[1]].SetStatus(0);
      field[coordinates[0] - 1][coordinates[1] - 1].SetStatus(0);
      field[coordinates[0] - 1][coordinates[1] + 1].SetStatus(0);
      field[coordinates[0] + 1][coordinates[1] + 1].SetStatus(0);
      field[coordinates[0] + 1][coordinates[1] - 1].SetStatus(0);
      field[coordinates[0]][coordinates[1] - 1].SetStatus(0);
      field[coordinates[0] + 1][coordinates[1]].SetStatus(0);
      field[coordinates[0]][coordinates[1] + 1].SetStatus(0);
      break;
    }
    case 1:
    {
      for(j = coordinates[1], i = 0; i < length; i++, j--)
        if(!field[coordinates[0]][j].GetStatus() || field[coordinates[0]][j].GetStatus() == 2)
          return false;
      for(j = coordinates[1], i = 0; i < length; i++, j--)
      {
        field[coordinates[0]][j].SetSymbol('+');
        if (!i)
        {
          field[coordinates[0]][j].SetStatus(2);
          field[coordinates[0]][j + 1].SetStatus(0);
          field[coordinates[0] + 1][j + 1].SetStatus(0);
          field[coordinates[0] - 1][j + 1].SetStatus(0);
          field[coordinates[0] + 1][j].SetStatus(0);
          field[coordinates[0]- 1][j].SetStatus(0);
        }
        else if (i == length - 1)
        {
          field[coordinates[0]][j].SetStatus(2);
          field[coordinates[0] + 1][j - 1].SetStatus(0);
          field[coordinates[0] - 1][j - 1].SetStatus(0);
          field[coordinates[0]][j - 1].SetStatus(0);
          field[coordinates[0] + 1][j].SetStatus(0);
          field[coordinates[0] - 1][j].SetStatus(0); 
        }
        else
        {
          field[coordinates[0]][j].SetStatus(2);
          field[coordinates[0] + 1][j].SetStatus(0);
          field[coordinates[0] - 1][j].SetStatus(0); 
        }  
      }
      break;
    }
    case 2:
    {
      for(j = coordinates[1], i = 0; i < length; i++, j++)
        if(!field[coordinates[0]][j].GetStatus() || field[coordinates[0]][j].GetStatus() == 2)
          return false;
      for(j = coordinates[1], i = 0; i < length; i++, j++)
      {
        field[coordinates[0]][j].SetSymbol('+');
        if (!i)
        {
          field[coordinates[0]][j].SetStatus(2);
          field[coordinates[0]][j - 1].SetStatus(0);
          field[coordinates[0] + 1][j - 1].SetStatus(0);
          field[coordinates[0] - 1][j - 1].SetStatus(0);
          field[coordinates[0] + 1][j].SetStatus(0);
          field[coordinates[0]- 1][j].SetStatus(0);
        }
        else if (i == length - 1)
        {
          field[coordinates[0]][j].SetStatus(2);
          field[coordinates[0] + 1][j + 1].SetStatus(0);
          field[coordinates[0] - 1][j + 1].SetStatus(0);
          field[coordinates[0]][j + 1].SetStatus(0);
          field[coordinates[0] + 1][j].SetStatus(0);
          field[coordinates[0] - 1][j].SetStatus(0); 
        }
        else
        {
          field[coordinates[0]][j].SetStatus(2);
          field[coordinates[0] + 1][j].SetStatus(0);
          field[coordinates[0] - 1][j].SetStatus(0); 
        }  
      }
      break;
    }
    case 3:
    {
      for(i = coordinates[0], j = 0; j < length; i--, j++)
        if(!field[i][coordinates[1]].GetStatus() || field[i][coordinates[1]].GetStatus() == 2)
          return false;
      for(i = coordinates[0], j = 0; j < length; i--, j++)
      {
        field[i][coordinates[1]].SetSymbol('+');
        if (!j)
        {
          field[i][coordinates[1]].SetStatus(2);
          field[i + 1][coordinates[1]].SetStatus(0);
          field[i + 1][coordinates[1] - 1].SetStatus(0);
          field[i + 1][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] + 1].SetStatus(0);
        }
        else if (j == length - 1)
        {
          field[i][coordinates[1]].SetStatus(2);
          field[i - 1][coordinates[1]].SetStatus(0);
          field[i - 1][coordinates[1] - 1].SetStatus(0);
          field[i - 1][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] + 1].SetStatus(0);
        }
        else
        {
          field[i][coordinates[1]].SetStatus(2);
          field[i][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] - 1].SetStatus(0);
        }  
      }
      break;
    }
    case 4:
    {
      for(i = coordinates[0], j = 0; j < length; i++, j++)
        if(!field[i][coordinates[1]].GetStatus() || field[i][coordinates[1]].GetStatus() == 2)
          return false;
      for(i = coordinates[0], j = 0; j < length; i++, j++)
      {
        field[i][coordinates[1]].SetSymbol('+');
        if (!j)
        {
          field[i][coordinates[1]].SetStatus(2);
          field[i - 1][coordinates[1]].SetStatus(0);
          field[i - 1][coordinates[1] - 1].SetStatus(0);
          field[i - 1][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] + 1].SetStatus(0);
        }
        else if (j == length - 1)
        {
          field[i][coordinates[1]].SetStatus(2);
          field[i + 1][coordinates[1]].SetStatus(0);
          field[i + 1][coordinates[1] - 1].SetStatus(0);
          field[i + 1][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] + 1].SetStatus(0);
        }
        else
        {
          field[i][coordinates[1]].SetStatus(2);
          field[i][coordinates[1] + 1].SetStatus(0);
          field[i][coordinates[1] - 1].SetStatus(0);
        }  
      }
      break;
    }
  }
  return true;
}

bool Field::Shoot(Field& Field, int* coordinates)
{
  if(field[coordinates[0]][coordinates[1]].GetStatus() == 2)
  {
    Field.field[coordinates[0]][coordinates[1]].SetSymbol('x');
    field[coordinates[0]][coordinates[1]].SetStatus(4); 
    return true;
  }
  else
  {
    Field.field[coordinates[0]][coordinates[1]].SetSymbol('-');  
    field[coordinates[0]][coordinates[1]].SetStatus(3); 
    return false;
  }
}

void Field::PlaceShipAI()
{
  int tempvar;
  ifstream filein;
  ostringstream ost;
  char tempchar = '0';
  int i = 0, j = 0;
  string path = "Fields/Field";
  tempvar = rand() % 50 + 1;
  ost << tempvar;
  path += ost.str();
  path += ".txt"; 
  filein.open(path);
  for(i = 2; i < 12; i++)
    for(j = 2; j < 12; j++)
    {
      filein >> tempchar;
      if(tempchar == '+')
      {
        field[i][j].SetStatus(2);
        field[i][j].SetSymbol(tempchar);
      }
    }
}

void Field::GenerateCoordinatesAI(Field& Field, int* enemyShootCoordinates)
{
  char letters1[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
  enemyShootCoordinates[0] = rand() % 10 + 2;
  enemyShootCoordinates[1] = rand() % 10 + 2;
  while (Field.field[enemyShootCoordinates[0]][enemyShootCoordinates[1]].GetStatus() == 3)
  {
    enemyShootCoordinates[0] = rand() % 10 + 2;
    enemyShootCoordinates[1] = rand() % 10 + 2;
  }
  cout << letters1[enemyShootCoordinates[1] - 2] << enemyShootCoordinates[0] - 2 << endl;
}

bool Field::IsKilled(int* coordinates)
{
  int temp;
  int counter = 0;
  int direction = 0;
  if (field[coordinates[0] - 1][coordinates[1]].GetStatus() == 2 || field[coordinates[0]][coordinates[1] + 1].GetStatus() == 2 || field[coordinates[0] + 1][coordinates[1]].GetStatus() == 2 || field[coordinates[0]][coordinates[1] - 1].GetStatus() == 2)
    return 0;
  if(field[coordinates[0] - 1][coordinates[1]].GetStatus() == 4)
    direction = 3;
  if (field[coordinates[0]][coordinates[1] + 1].GetStatus() == 4)
    direction = 2;
  if (field[coordinates[0] + 1][coordinates[1]].GetStatus() == 4)
    direction = 4;
  if (field[coordinates[0]][coordinates[1] - 1].GetStatus() == 4)
    direction = 1;
  switch(direction)
  {
    case 1:
    {  
      coordinates[1]--;
      while (field[coordinates[0]][coordinates[1]].GetStatus() != 3 && field[coordinates[0]][coordinates[1]].GetStatus() != 0 && field[coordinates[0]][coordinates[1]].GetStatus() != 1)
      {
        if (field[coordinates[0]][coordinates[1]].GetStatus() == 2)
        {
          counter++;
        }
        coordinates[1]--;
      }
      if (!counter)
        return 1;
      return 0;
    }
    case 2:
    {
      coordinates[1]++;
      while (field[coordinates[0]][coordinates[1]].GetStatus() != 3 && field[coordinates[0]][coordinates[1]].GetStatus() != 0 && field[coordinates[0]][coordinates[1]].GetStatus() != 1)
      {
        if (field[coordinates[0]][coordinates[1]].GetStatus() == 2)
        {
          counter++;
        }
      coordinates[1]++;
      }
      if (!counter)
        return 1;
      else
        return 0;
    }
    case 3:
    {
      coordinates[0]--;
      while (field[coordinates[0]][coordinates[1]].GetStatus() != 3 && field[coordinates[0]][coordinates[1]].GetStatus() != 0 && field[coordinates[0]][coordinates[1]].GetStatus() != 1)
      {
        if(field[coordinates[0]][coordinates[1]].GetStatus() == 2)
        {
          counter++;
        }
        coordinates[0]--;
      }
      if (!counter)
        return 1;
      else
        return 0;
    }
    case 4:
    {
      coordinates[0]++;
      while (field[coordinates[0]][coordinates[1]].GetStatus() != 3 && field[coordinates[0]][coordinates[1]].GetStatus() != 0 && field[coordinates[0]][coordinates[1]].GetStatus() != 1)
      {
        if (field[coordinates[0]][coordinates[1]].GetStatus() == 2)
        {
          counter++;
        }
        coordinates[0]++;
      }
      if (!counter)
        return 1;
      else
        return 0;
    }
    default:
      return 1;
  }
}

void Field::ShootAI(int* enemyShootCoordinates, bool status)
{
  field[enemyShootCoordinates[0]][enemyShootCoordinates[1]].SetStatus(3);
  if (status)
  {
    field[enemyShootCoordinates[0]][enemyShootCoordinates[1]].SetSymbol('x');
  }
  else
  {
    field[enemyShootCoordinates[0]][enemyShootCoordinates[1]].SetSymbol('-');
  }
}