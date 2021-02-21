#include <iostream>
#include <cmath>
using namespace std;

class rFraction
{
  int numerator;
  int denominator;
  void fractionGCF();
public:
  rFraction();
  rFraction(int numerator, int denominator);
  void fractionInit();
  void fractionStatus();
  void fractionOutput();
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
  numerator = 0;
  denominator = 1;
}

rFraction rFraction::operator+(const rFraction& temp) // overload for +
{
  rFraction helper;
  helper.numerator = this->numerator * temp.denominator + temp.numerator * this->denominator;
  helper.denominator = this->denominator * temp.denominator;
  return helper;
}

rFraction rFraction::operator-(const rFraction& temp) // overload for -
{
    rFraction helper;
    helper.numerator = this->numerator * temp.denominator - temp.numerator * this->denominator;
    helper.denominator = this->denominator * temp.denominator;
    return helper;
}

rFraction rFraction::operator*(const rFraction& temp) // overload for *
{
  rFraction helper;
  helper.numerator = this->numerator * temp.numerator;
  helper.denominator = this->denominator * temp.denominator;
  return helper;
}

rFraction rFraction::operator/(const rFraction& temp) // overload for /
{
  rFraction helper;
  helper.numerator = this->numerator * temp.denominator;
  helper.denominator = this->denominator * temp.numerator;
  return helper;
}

rFraction rFraction::operator=(const rFraction& temp) // overload for =
{
    this->numerator = temp.numerator;
    this->denominator = temp.denominator;
    return *this;
}

void rFraction::fractionGCF() // fraction reduction using gcf
{
  int temp1 = 1, temp2 = 1;
  int numtemp, dentemp;
  numtemp = numerator;
  dentemp = denominator;
  if (numtemp == dentemp)
  {
    numerator = 1;
    denominator = 1;
  }
  while(temp1)
  {
    temp2 = temp1;
    temp1 = numtemp % dentemp;
    numtemp = dentemp;
    dentemp = temp1;
  }
  numerator /= abs(temp2);
  denominator /= abs(temp2);
}

void rFraction::fractionOutput() // fraction output after math operations
{
  this->fractionGCF();
  if (numerator == 0)
    cout << numerator << endl;
  else
    if (numerator == denominator)
      cout << 1 << endl;
    else
      if(denominator == 1)
        cout << numerator << endl;
      else
        cout << numerator << "/" << denominator << endl;
}

void rFraction::fractionInit() // fraction initialization
{
  int numerator, denominator;
  cout << "Enter numerator of the fraction:" << endl;
  cin >> numerator;
  this->numerator = numerator;
  cout << "Enter denominator of the fraction:" << endl;
  cin >> denominator;
  while (denominator == 0)
  {
    cout << "Denominator can't be zero, enter another value:" << endl;
    cin >> denominator;
  }
  
  this->denominator = denominator;
  this->fractionGCF();
}

void rFraction::fractionStatus() // current fraction status
{
  cout << "Numerator:" << numerator << "\t" << "Denominator:" << denominator << endl;
}

int main()
{
  rFraction addition, subtraction, multiplication, division;
  rFraction rfraction1, rfraction2;
  rfraction1.fractionInit();
  rfraction2.fractionInit();
  addition = rfraction1 + rfraction2;
  subtraction = rfraction1 - rfraction2;
  multiplication = rfraction1 * rfraction2;
  division = rfraction1 / rfraction2;
  addition.fractionOutput();
  subtraction.fractionOutput();
  multiplication.fractionOutput();
  division.fractionOutput();
  return 0;
}