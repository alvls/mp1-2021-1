#pragma once

class Tabulator
{
private:
    int Points;
    double LeftBound;
    double RightBound;
    Function* func;
    double counter(Function* func, double x) { return (func->count(x)); }
public:
    //Конструктор
    Tabulator(int _Points = 2, double _LeftBound = DBL_MIN, double _RightBound = DBL_MAX) : Points(_Points), LeftBound(_LeftBound), RightBound(_RightBound) { func = new ReturnX; }

    //Геттеры
    int GetPoints() { return Points; }
    double GetLeftBound() { return LeftBound; }
    double GetRightBound() { return RightBound; }
    Function* GetFunc() { return func; }

    //Сеттеры
    void SetPoints(int _Points) { Points = _Points; }
    void SetLeftBound(double _LeftBound) { LeftBound = _LeftBound; }
    void SetRightBound(double _RightBound) { RightBound = _RightBound; }
    void SetFunc(int type);

    //Табулятор
    double** TabFunc(Function* func);

    //Деструктор
    ~Tabulator() {}
};
