#include <iostream>
#include <cmath>
using namespace std;

class rFraction;
void initFunction(int& numerator, int& denominator);
class rFraction
{
    int numerator;
    int denominator;
public:
    rFraction();
    rFraction(int numerator, int denominator);
    void fractionInit(int numerator, int denominator);
    void fractionStatus();
    void fractionOutput();
    void fractionGCF();
    rFraction operator+(const rFraction& temp);
    rFraction operator-(const rFraction& temp);
    rFraction operator*(const rFraction& temp);
    rFraction operator/(const rFraction& temp);
    rFraction operator=(const rFraction& temp);
};

rFraction::rFraction(int numerator, int denominator)
{
    this->numerator = numerator;
    this->denominator = denominator;
}

rFraction::rFraction()
{
    this->numerator = 0;
    this->denominator = 1;
}

rFraction rFraction::operator+(const rFraction& temp)
{
    rFraction helper;
    helper.numerator = this->numerator * temp.denominator + temp.numerator * this->denominator;
    helper.denominator = this->denominator * temp.denominator;
    return helper;
}

rFraction rFraction::operator-(const rFraction& temp)
{
    rFraction helper;
    helper.numerator = this->numerator * temp.denominator - temp.numerator * this->denominator;
    helper.denominator = this->denominator * temp.denominator;
    return helper;
}

rFraction rFraction::operator*(const rFraction& temp)
{
    rFraction helper;
    helper.numerator = this->numerator * temp.numerator;
    helper.denominator = this->denominator * temp.denominator;
    return helper;
}

rFraction rFraction::operator/(const rFraction& temp)
{
    rFraction helper;
    helper.numerator = this->numerator * temp.denominator;
    helper.denominator = this->denominator * temp.numerator;
    return helper;
}

rFraction rFraction::operator=(const rFraction& temp)
{
    this->numerator = temp.numerator;
    this->denominator = temp.denominator;
    return *this;
}

void rFraction::fractionGCF()
{
    int temp1 = 1, temp2 = 1;
    int numtemp, dentemp;
    numtemp = this->numerator;
    dentemp = this->denominator;
    if (numtemp == dentemp)
    {
        this->numerator = 1;
        this->denominator = 1;
    }
    while (temp1)
    {
        temp2 = temp1;
        temp1 = numtemp % dentemp;
        numtemp = dentemp;
        dentemp = temp1;
    }
    this->numerator /= abs(temp2);
    this->denominator /= abs(temp2);
}

void rFraction::fractionOutput()
{
    if (this->numerator == 0)
        cout << numerator << endl;
    else
        if (this->numerator == this->denominator)
            cout << 1 << endl;
        else
            if (this->denominator == 1)
                cout << this->numerator << endl;
            else
                cout << this->numerator << "/" << this->denominator << endl; 
}

void rFraction::fractionInit(int numerator, int denominator)
{
    this->numerator = numerator;
    this->denominator = denominator;
    this->fractionGCF();
}

void initFunction(int& numerator, int& denominator)
{
  cout << "Enter numerator of the fraction:" << endl;
  cin >> numerator;
  cout << "Enter denominator of the fraction:" << endl;
  cin >> denominator;
  while (denominator == 0)
  {
      cout << "Denominator can't be zero, enter another value:" << endl;
      cin >> denominator;
  }
}

void rFraction::fractionStatus()
{
    cout << "Numerator:" << this->numerator << "\t" << "Denominator:" << this->denominator << endl;
}

int main()
{
    int numerator = 0, denominator = 0;
    rFraction addition, subtraction, multiplication, division;
    rFraction rfraction1, rfraction2;
    // call initFunction everytime u want to initialize object, than call object.fractionInit.
    initFunction(numerator, denominator);
    rfraction1.fractionInit(numerator, denominator);
    initFunction(numerator, denominator);
    rfraction2.fractionInit(numerator, denominator);
    addition = rfraction1 + rfraction2;
    // call object.fractionGCF everytime u want to reduce fraction.
    addition.fractionGCF();
    subtraction = rfraction1 - rfraction2;
    subtraction.fractionGCF();
    multiplication = rfraction1 * rfraction2;
    multiplication.fractionGCF();
    division = rfraction1 / rfraction2;
    division.fractionGCF();
    addition.fractionGCF();
    addition.fractionOutput();
    subtraction.fractionOutput();
    multiplication.fractionOutput();
    division.fractionOutput(); 
    return 0;
}