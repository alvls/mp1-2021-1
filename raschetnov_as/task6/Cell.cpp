#include "Cell.h"

using namespace std;

Cell::Cell()
{
  status = 0;
  symbol = ' ';
}

void Cell::SetStatus(int _status)
{
  status = _status;
}

void Cell::SetSymbol(char _symbol)
{
  symbol = _symbol;
}

char Cell::GetSymbol()
{
  return symbol;
}

int Cell::GetStatus()
{
  return status;
}