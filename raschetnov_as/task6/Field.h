#ifndef FIELD
#define FIELD

#include "Cell.h"

class Field
{
  Cell field[13][13];
public:
  Field();
  void FieldOutput();
  bool PlaceShip(int length, int* coordinates, int direction);
  bool Shoot(Field& Field, int* coordinates);
  void PlaceShipAI();
  void GenerateCoordinatesAI(Field& Field, int* enemyShootCoordinates);
  bool IsKilled(int* coordinates);
  void ShootAI(int* enemyShootCoordinates, bool status);
};
#endif FIELD
