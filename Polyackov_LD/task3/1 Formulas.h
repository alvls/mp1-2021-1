#pragma once

class Function
{
public:
	virtual double count(double x) = 0;
};

//default
class ReturnX : public Function
{
public:
	virtual double count(double x) override { return x; }
};

// Тригонометрические функции

class Sin : public Function
{
public:
	virtual double count(double x) override { return sin(x); }
};

class Cos : public Function
{
public:
	virtual double count(double x) override	{ return cos(x); }
};

class Tan : public Function
{
public:
	virtual double count(double x) override { return tan(x); }
};

class Cot : public Function
{
public:
	virtual double count(double x) override { return tan(PI / 2 - x); }
};

// Обратные тригонометрические функции

class Arcsin : public Function
{
public:
	virtual double count(double x) override { return asin(x); }
};

class Arccos : public Function
{
public:
	virtual double count(double x) override	{ return acos(x); }
};

class Arctan : public Function
{
public:
	virtual double count(double x) override	{ return atan(x); }
};

class Arccot : public Function
{
public:
	virtual double count(double x) override	{ return (PI / 2 - atan(x)); }
};

// Гиперболические функции

class Sinh : public Function
{
public:
	virtual double count(double x) override	{ return sinh(x); }
};

class Cosh : public Function
{
public:
	virtual double count(double x) override { return cosh(x); }
};

class Tanh : public Function
{
public:
	virtual double count(double x) override { return tanh(x); }
};

class Cotanh : public Function
{
public:
	virtual double count(double x) override { return cosh(x) / sinh(x); }
};

// Обратные гиперболические функции

class Asinh : public Function
{
public:
	virtual double count(double x) override	{ return asinh(x); }
};

class Acosh : public Function
{
public:
	virtual double count(double x) override { return acosh(x); }
};

class Atanh : public Function
{
public:
	virtual double count(double x) override { return atanh(x); }
};

class Acotanh : public Function
{
public:
	virtual double count(double x) override { return 1 / 2 * (log(fabs(x + 1)) - log(fabs(x - 1))); }
};

// Степени

class XPowTwo : public Function
{
public:
	virtual double count(double x) override { return pow(x, 2); }
};

class XPowThree : public Function
{
public:
	virtual double count(double x) override { return pow(x, 3); }
};

// Степенные

class Sqrt : public Function
{
public:
	virtual double count(double x) override { return sqrt(x); }
};

class Cbrt : public Function
{
public:
	virtual double count(double x) override { return cbrt(x); }
};

class TwoPowX : public Function
{
public:
	virtual double count(double x) override { return pow(2, x); }
};

class ExpPowX : public Function
{
public:
	virtual double count(double x) override { return exp(x); }
};

class TenPowX : public Function
{
public:
	virtual double count(double x) override { return pow(10, x); }
};

// Логарифмы

class Log2 : public Function
{
public:
	virtual double count(double x) override { return log2(x); }
};

class Loge : public Function
{
public:
	virtual double count(double x) override { return log(x); }
};

class Log10 : public Function
{
public:
	virtual double count(double x) override { return log10(x); }
};

// Дробная и целая части 

class FractPart : public Function
{
public:
	virtual double count(double x) override { return (x - floor(x)); }
};

class Floor : public Function
{
public:
	virtual double count(double x) override { return floor(x); }
};

// Модуль числа

class Abs : public Function
{
public:
	virtual double count(double x) override	{ return abs(x); }
};
