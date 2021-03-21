#pragma once

class Tabulator
{
private:
    int Points;
    double LeftBound;
    double RightBound;
    Function* func;
    struct TabPoint {
        double x;
        double y;
    };
    TabPoint* TabData;
    int MaxLengthX(int quantity);
    double counter(double x) { return (func->count(x)); }
public:
    //Конструктор
    Tabulator(int _Points = 0, double _LeftBound = DBL_MIN, double _RightBound = DBL_MAX);

    //Геттеры
    int GetPoints() { return Points; }
    double GetLeftBound() { return LeftBound; }
    double GetRightBound() { return RightBound; }
    double* GetBounds();
    double* GetTabPointData(int point);
    Function* GetFunc() { return func; }
    // Получить информацию, есть ли данные в TabData
    bool TabDataExist();

    //Сеттеры
    void SetPoints(int _Points) { Points = _Points; }
    void SetLeftBound(double _LeftBound) { LeftBound = _LeftBound; }
    void SetRightBound(double _RightBound) { RightBound = _RightBound; }
    void SetFunc(int type);

    //Табулятор
    void TabFunc();

    //Удаление неактуальной памяти
    void DeleteTabData();
    
    //Вывести данные на экран
    void PrintData();
    void PrintData(int quantity);

    //Сохранить данные в файл
    void SaveData();

    //Деструктор
    ~Tabulator();
};
