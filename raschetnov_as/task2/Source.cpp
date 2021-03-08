#include <iostream>
#include <cmath>

using namespace std;

class Polynomials;
void setPower(Polynomials& object);
int* setCoefficients(Polynomials& object, int* p);
Polynomials operator+(const Polynomials& object1, const Polynomials& object2);
class Polynomials
{
    int power;
    int* p;
public:
    explicit Polynomials(int power = 0) :power(power)
    {
        int i = 0;
        p = new int[power + 1];
        for (i = power; i >= 0; i--)
            p[i] = 0;
    };
    Polynomials(double power) :power(0)
    {
        p = new int[1];
        p[0] = power;
    };
    Polynomials(const Polynomials& object);
    ~Polynomials();
    void polynomialsSetPower(int power);
    void polynomialsSetCoefficients(int* pointer);
    int polynomialsGetPower() const;
    int polynomialsGetCoefficient(int number);
    void polynomialsOutput();
    int polynomialsGetValue(int point);
    Polynomials polynomialsGetDerivative();
    Polynomials& operator=(const Polynomials& object);
    friend Polynomials operator+(const Polynomials& object1, const Polynomials& object2);
    friend Polynomials operator*(const double& object1, const Polynomials& object2);
    friend Polynomials operator*(const Polynomials& object2, const double& object1);
    Polynomials& operator+=(const Polynomials& object);
    Polynomials& operator*=(const Polynomials& object);
};

Polynomials::Polynomials(const Polynomials& object)
{
    int i = 0;
    power = object.power;
    p = new int[power + 1];
    for (i = power; i >= 0; i--)
        p[i] = object.p[i];
}

Polynomials::~Polynomials()
{
    delete[] p;
}

void Polynomials::polynomialsSetCoefficients(int* pointer)
{
    int i = 0;
    if (power == 0)
    {
        setPower(*this);
    }
    for (i = power; i >= 0; i--)
        p[i] = pointer[i];
}

void Polynomials::polynomialsOutput()
{
    int i = 0, j = 0;
    cout << "Coefficients of monomers(by highest power): ";
    for (i = power; i >= 0; i--)
        cout << p[i] << " ";
    cout << endl;
}

void Polynomials::polynomialsSetPower(int power)
{
    int i = 0;
    this->power = power;
    p = new int[power + 1];
    for (i = power; i >= 0; i--)
        p[i] = 0;
}

int Polynomials::polynomialsGetPower() const
{
    return power;
}

int Polynomials::polynomialsGetCoefficient(int number)
{
    return p[number];
}

void setPower(Polynomials& object)
{
    int power = 0;
    cout << "Set power of a polynomial: " << endl;
    cin >> power;
    object.polynomialsSetPower(power);
}

int* setCoefficients(Polynomials& object, int* p)
{
    int object_power = object.polynomialsGetPower();
    int i = 0;
    cout << "Power of a current polynomial: " << object_power << endl;
    p = new int[object_power + 1];
    cout << "Enter coefficients starting with the highest power: " << endl;
    for (i = object_power; i >= 0; i--)
        cin >> p[i];
    return p;
}

int Polynomials::polynomialsGetValue(int point)
{
    int i = 0;
    int value_point = 0;
    for (i = power; i >= 0; i--)
        value_point += p[i] * pow(point, i);
    return value_point;
}

Polynomials Polynomials::polynomialsGetDerivative()
{
    int i = 0;
    Polynomials derivative;
    int copy_power = power;
    derivative.polynomialsSetPower(power - 1);
    for (i = derivative.power; i >= 0; i--)
        derivative.p[i] = p[copy_power--] * (i + 1);
    return derivative;
}

Polynomials& Polynomials::operator=(const Polynomials& object)
{
    int i = 0;
    power = object.power;
    delete[] p;
    p = new int[power + 1];
    for (i = power; i >= 0; i--)
        p[i] = object.p[i];
    return *this;
}

Polynomials operator+(const Polynomials& object1, const Polynomials& object2)
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
    Polynomials helper(hpower);
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

Polynomials operator*(const double& object1, const Polynomials& object2)
{
    int hpower = 0, i = 0;
    int rememberer = 0;
    int flag = 0;
    hpower = object2.power;
    Polynomials helper(hpower);
    for (i = hpower; i >= 0; i--)
        helper.p[i] = object1 * object2.p[i];
    return helper;
}

Polynomials operator*(const Polynomials& object2, const double& object1)
{
    int hpower = 0, i = 0;
    int rememberer = 0;
    int flag = 0;
    hpower = object2.power;
    Polynomials helper(hpower);
    for (i = hpower; i >= 0; i--)
        helper.p[i] = object2.p[i] * object1;
    return helper;
}

Polynomials& Polynomials::operator+=(const Polynomials& object) // object1.operator+=(object2);
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

Polynomials& Polynomials::operator*=(const Polynomials& object)
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
    Polynomials temp1, temp2;
    Polynomials temp3;
    //temp2.polynomialsSetPower(3);
    temp3.polynomialsSetPower(4);
    pointer3 = setCoefficients(temp3, pointer3);
    //pointer2 = setCoefficients(temp2, pointer2);
    //temp2.polynomialsSetCoefficients(pointer2);
    temp3.polynomialsSetCoefficients(pointer3);
    temp3 *= 3;
    temp2 += 5;
    temp3.polynomialsOutput();
    temp1 = temp3.polynomialsGetDerivative();
    //temp3 *= 2;
    temp3.polynomialsOutput();
    //temp2.polynomialsOutput();
    temp1.polynomialsOutput();
    delete[] pointer1;
    delete[] pointer2;
    return 0;
}
