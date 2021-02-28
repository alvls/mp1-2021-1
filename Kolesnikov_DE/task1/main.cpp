#include <iostream>
using namespace std;
class LenConv
{
private:
    double ArchinCoef = 0.7112f;
    double YardCoef = 0.9144f;
    double SazhenCoef = 1.8288f;
    double FtCoef = 3.28084f;
    double len;
public:
    LenConv(int a)
    {
        len = a;
    }
    double Get_Metr() 
    {
	return len;
    }
    void Print()
    {
	cout << "Lenght in meters = " << len << endl;
	cout << "Lenght in Archin = " << ConvArchin() << endl;
	cout << "Lenght in Yard = " << ConvYard() << endl;
	cout << "Lenght in Sazhen = " << ConvSazhen() << endl;
	cout << "Lenght in Ft = " << ConvFt() << endl;
    }
    LenConv& operator= (const LenConv &conv)
    {
	len = conv.len;
	return *this;
    }
    double ConvArchin()
    {
        return len * ArchinCoef;
    }
    double ConvYard()
    {
        return len * YardCoef;
    }
    double ConvSazhen() 
    {
        return len * SazhenCoef;
    }
    double ConvFt()
    {
        return len * FtCoef;
    }

};
int main()
{   
    int val = 2;
    LenConv a(val);
    cout << a.Get_Metr() << endl;
    cout << a.ConvArchin() << endl;
    LenConv b(3);
    b = a;
    cout << b.Get_Metr() << endl;
    b.Print();
}
