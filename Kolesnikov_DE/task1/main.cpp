#include <iostream>
using namespace std;
class LenConv
{
private:
    double ArchinCoef = 0.7112f;
    double YardCoef = 0.9144f;
    double SazhenCoef = 1.8288f;
    double FtCoef = 3.28084f;
    int a = 0;
    double len[5] = { 0 };
public:
    void Print(int mode = 0) {
        if (!len[mode]) {
            if (mode == 0) {
                std::cout << "You don`t set init val\n";
            }
            else {
                std::cout << "You don`t convert to it\n";
            }
        }
        else {
            cout << len[mode]<< "\n";
        }
    }
    LenConv(int a) {
        len[0] = a;
    }
    void Init(int a) {
        len[0] = a;
        for (int i = 1; i < 5; i++) {
            len[i] = 0;
        }
    }
    void Convert(int mode) {
        switch (mode) {
        case (1):
            len[mode] = len[0] * ArchinCoef;
        case (2):
            len[mode] = len[0] * YardCoef;
        case (3):
            len[mode] = len[0] * SazhenCoef;
        case (4):
            len[mode] = len[0] * FtCoef;
        }
    }
};
int main()
{   
    int val = 2;
    std::cin >> val;
    LenConv a(val);
    a.Print();
    a.Convert(1);
    a.Print(1);   
}
