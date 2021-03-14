#include <iostream>
#include <cmath>

using namespace std;

class Polynomial;
void fsetPower(Polynomial& object);
int* FillInArray(int amount, int* p);
Polynomial operator+(const Polynomial& object1, const Polynomial& object2);
class Polynomial
{
    int power;
    int* p;
public:
    explicit Polynomial(int power = 0) :power(power)
    {
        int i = 0;
        p = new int[power + 1];
        for (i = power; i >= 0; i--)
            p[i] = 0;
    };
    Polynomial(double scalar) :power(0)
    {
        p = new int[1];
        p[0] = scalar;
    };
    Polynomial(const Polynomial& object);
    ~Polynomial();
    void setPower(int power);
    void setCoefficients(int* pointer);
    int getPower() const;
    int getCoefficient(int number);
    void Output();
    int getValue(int point);
    Polynomial getDerivative();
    Polynomial& operator=(const Polynomial& object);
    friend Polynomial operator+(const Polynomial& object1, const Polynomial& object2);
    friend Polynomial operator*(const double& object1, const Polynomial& object2);
    friend Polynomial operator*(const Polynomial& object2, const double& object1);
    Polynomial& operator+=(const Polynomial& object);
    Polynomial& operator*=(const Polynomial& object);
};

Polynomial::Polynomial(const Polynomial& object)
{
    int i = 0;
    power = object.power;   
    p = new int[power + 1];
    for (i = power; i >= 0; i--)
        p[i] = object.p[i];
}

Polynomial::~Polynomial()
{
    delete[] p;
}

void Polynomial::setCoefficients(int* pointer)
{
    int i = 0;
    if (power == 0)
    {
        fsetPower(*this);
    }
    for (i = power; i >= 0; i--)
        p[i] = pointer[i];
}

void Polynomial::Output()
{
    int i = 0, j = 0;
    cout << "Coefficients of monomers(by highest power): ";
    for (i = power; i >= 0; i--)
        cout << p[i] << " ";
    cout << endl;
}

void Polynomial::setPower(int power)
{
    int i = 0;
    this->power = power;
    delete[] p;
    p = new int[power + 1];
    for (i = power; i >= 0; i--)
        p[i] = 0;
}

int Polynomial::getPower() const
{
    return power;
}

int Polynomial::getCoefficient(int number)
{
    return p[number];
}

void fsetPower(Polynomial& object)
{
    int power = 0;
    cout << "Set power of a polynomial: " << endl;
    cin >> power;
    object.setPower(power);
}

int* fillInArray(int amount, int* p)
{
    int object_power = amount;
    int i = 0;
    cout << "Power of a current polynomial: " << object_power << endl;
    p = new int[object_power + 1];
    cout << "Enter coefficients starting with the highest power: " << endl;
    for (i = object_power; i >= 0; i--)
        cin >> p[i];
    return p;
}

int Polynomial::getValue(int point)
{
    int i = 0;
    int value_point = 0;
    for (i = power; i >= 0; i--)
        value_point += p[i] * pow(point, i);
    return value_point;
}

Polynomial Polynomial::getDerivative()
{
    int i = 0;
    Polynomial derivative;
    int copy_power = power;
    derivative.setPower(power - 1);
    for (i = derivative.power; i >= 0; i--)
        derivative.p[i] = p[copy_power--] * (i + 1);
    return derivative;
}

Polynomial& Polynomial::operator=(const Polynomial& object)
{
    int i = 0;
    if(this == &object)
      return *this;
    power = object.power;
    delete[] p;
    p = new int[power + 1];
    for (i = power; i >= 0; i--)
        p[i] = object.p[i];
    return *this;
}

Polynomial operator+(const Polynomial& object1, const Polynomial& object2)
{
    int hpower = 0, i = 0;
    int rememberer = 0;
    int flag = 0;
    if (object1.power >= object2.power)
    {
        hpower = object1.power;
        rememberer = object2.power;
        flag = 1;
    }
    else
    {
        hpower = object2.power;
        rememberer = object1.power;
    }
    Polynomial helper(hpower);
    for (i = 0; i <= rememberer; i++)
        helper.p[i] = object1.p[i] + object2.p[i];
    if (flag)
        for (i; i <= hpower; i++)
            helper.p[i] = object1.p[i];
    else
        for (i; i <= hpower; i++)
            helper.p[i] = object2.p[i];
    return helper;
}

Polynomial operator*(const double& object1, const Polynomial& object2)
{
    int hpower = 0, i = 0;
    int rememberer = 0;
    int flag = 0;
    hpower = object2.power;
    Polynomial helper(hpower);
    for (i = hpower; i >= 0; i--)
        helper.p[i] = object1 * object2.p[i];
    return helper;
}

Polynomial operator*(const Polynomial& object2, const double& object1)
{
    int hpower = 0, i = 0;
    int rememberer = 0;
    int flag = 0;
    hpower = object2.power;
    Polynomial helper(hpower);
    for (i = hpower; i >= 0; i--)
        helper.p[i] = object2.p[i] * object1;
    return helper;
}

Polynomial& Polynomial::operator+=(const Polynomial& object)
{
    int i = 0;
    int highest_power = 0;
    int lowest_power = 0;
    int size = power;
    int flag = 0;
    int* temparray;
    temparray = new int[size + 1];
    for (i = 0; i <= size; i++)
        temparray[i] = p[i];
    if (power >= object.power)
    {
        highest_power = power;
        lowest_power = object.power;
        flag = 1;
    }
    else
    {
        highest_power = object.power;
        lowest_power = power;
        power = highest_power;
        delete[] p;
        p = new int[power + 1];
        for (i = 0; i <= size; i++)
            p[i] = temparray[i];
        for (i; i <= highest_power; i++)
            p[i] = 0;
    }
    for (i = 0; i <= lowest_power; i++)
        p[i] += object.p[i];
    for (i = lowest_power + 1; i <= highest_power; i++)
        if (!flag)
            p[i] = object.p[i];
    delete[] temparray;
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& object)
{
    int i = 0;
    int highest_power = 0;
    int lowest_power = 0;
    int size = power;
    int flag = 0;
    int* temparray;
    temparray = new int[size + 1];
    for (i = 0; i <= size; i++)
        temparray[i] = p[i];
    if (power >= object.power)
    {
        highest_power = power;
        lowest_power = object.power;
        flag = 1;
    }
    else
    {
        highest_power = object.power;
        lowest_power = power;
        power = highest_power;
        delete[] p;
        p = new int[power + 1];
        for (i = 0; i <= size; i++)
            p[i] = temparray[i];
        for (i; i <= highest_power; i++)
            p[i] = 0;
    }
    if (object.power == 0)
        for (i = 0; i <= highest_power; i++)
            p[i] *= object.p[0];
    else
    {
        for (i = 0; i <= lowest_power; i++)
            p[i] *= object.p[i];
        for (i = lowest_power + 1; i <= highest_power; i++)
            if (!flag)
                p[i] = object.p[i];
    }
    delete[] temparray;
    return *this;
}

int main()
{
    int* pointer1 = nullptr;
    int* pointer2 = nullptr;
    int* pointer3 = nullptr;
    int value = 0;
    Polynomial temp1(5), temp2;
    Polynomial temp3;
    //temp2.setPower(3);
    temp3.setPower(4);
    pointer3 = fillInArray(4, pointer3);
    //temp2.polynomialsSetCoefficients(pointer2);
    temp3.setCoefficients(pointer3);
    temp3 *= 3;
    temp2 += 5;
    temp3.Output();
    temp3 *= 2;
    temp1 = temp3.getDerivative();
    temp3.Output();
    //temp2.polynomialsOutput();
    temp1.Output();
    delete[] pointer1;
    delete[] pointer2;
    return 0;
}
