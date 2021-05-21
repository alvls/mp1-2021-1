#ifndef CELL
#define CELL

class Cell
{
  int status;
  char symbol;
public:
  Cell();
  void SetStatus(int _status);
  void SetSymbol(char _symbol);
  char GetSymbol();
  int GetStatus();
};
#endif CELL
