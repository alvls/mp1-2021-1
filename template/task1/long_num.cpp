#include <iostream>
#include "uint64.cpp"
#include <math.h>

using namespace std;

class LongNumber
{
private:
	char sign;
	uint64 num;
public:
	LongNumber()
	{
		num = 0;
		sign = 1;
	}

	LongNumber(const long long& _num)
	{
		if (_num < 0)
		{
			sign = -1;
			num = abs(_num);
		}
		else
		{
			sign = 1;
			num = _num;
		}
	}

	LongNumber(char _sign, uint64 _num)
	{
		sign = _sign;
		num = _num;
	}

	LongNumber operator=(LongNumber& _num)
	{
		sign = _num.sign;
		num = _num.num;
		return *this;
	}

	LongNumber operator+(LongNumber& _num)
	{
		uint64 result;
		char resultSign;

		if (sign == _num.sign)
		{
			result = num + _num.num;
			resultSign = sign;
		}
		else
		{
			if (num > _num.num)
			{
				result = num - _num.num;
				resultSign = sign;
			}
			if (num < _num.num)
			{

				result = _num.num - num;
				resultSign = _num.sign;
			}
			if (num == _num.num)
			{
				result = 0;
				resultSign = 1;
			}

		}
		return LongNumber(resultSign, result);

	}

	LongNumber operator-(LongNumber& _num)
	{
		LongNumber result(_num.sign * (-1), _num.num);
		return (*this) + result;
	}

	LongNumber operator*(LongNumber& _num)
	{
		char resultSign = sign * _num.sign;
		uint64 result = num * _num.num;
		return LongNumber(resultSign, result);
	}

	LongNumber operator/(LongNumber& _num)
	{
		char resultSign = sign * _num.sign;
		uint64 result = num / _num.num;
		return LongNumber(resultSign, result);
	}

	LongNumber operator%(LongNumber& _num)
	{
		char resultSign = sign * _num.sign;
		uint64 result = num % _num.num;
		return LongNumber(resultSign, result);
	}

	void Print()
	{
		if (sign == -1)
		{
			cout << '-';
			num.PrintNum();
		}
		else
			num.PrintNum();
	}

};