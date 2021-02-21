#include <iostream>
using namespace std;
class LenConv
{
private:
    double ArchinCoef = 0.7112f;
    double YardCoef = 0.9144f;
    double SazhenCoef = 1.8288f;
    double FtCoef = 3.28084f;
    double len[5] = { 0 };
public:
    LenConv(int a) 
    {
        len[0] = a;
    }
    void Print(int mode = 0) 
    {	
        if (!len[mode]) {
            if (mode == 0) {
                cout << "You don`t set init val"<<endl;
            }
            else {
                cout << "You don`t convert to it"<<endl;
            }
        }
        else {
            cout << len[mode]<<endl;
        }
    }
    void Init(int a) 
    {
        len[0] = a;
        for (int i = 1; i < 5; i++) {
            len[i] = 0;
        }
    }
    LenConv& operator= (const LenConv &conv)
    {
	for(int i = 0;i<5;i++){
		len[i] = conv.len[i];
	}
	return *this;
    }
    void Convert(int mode) 
    {
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
    LenConv a(val);
    a.Print();
    a.Convert(1);
    a.Print(1);   
    LenConv b(3);
    b = a;
    b.Print(1);
    b.Print(3);
}
