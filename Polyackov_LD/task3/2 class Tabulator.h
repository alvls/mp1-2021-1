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
    //�����������
    Tabulator(int _Points = 0, double _LeftBound = DBL_MIN, double _RightBound = DBL_MAX);

    //�������
    int GetPoints() { return Points; }
    double GetLeftBound() { return LeftBound; }
    double GetRightBound() { return RightBound; }
    double* GetBounds();
    double* GetTabPointData(int point);
    Function* GetFunc() { return func; }
    // �������� ����������, ���� �� ������ � TabData
    bool TabDataExist();

    //�������
    void SetPoints(int _Points) { Points = _Points; }
    void SetLeftBound(double _LeftBound) { LeftBound = _LeftBound; }
    void SetRightBound(double _RightBound) { RightBound = _RightBound; }
    void SetFunc(int type);

    //���������
    void TabFunc();

    //�������� ������������ ������
    void DeleteTabData();
    
    //������� ������ �� �����
    void PrintData();
    void PrintData(int quantity);

    //��������� ������ � ����
    void SaveData();

    //����������
    ~Tabulator();
};
