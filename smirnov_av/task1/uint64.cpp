#include <iostream>

typedef unsigned int uint;
using namespace std;
const uint MAX = 4294967295;

class uint64
{
private:
	uint highPart;
	uint lowPart;

public:
	
	uint64()
	{
		highPart = 0;
		lowPart = 0;
	}
	//делим число на 2 части
	uint64(const unsigned long long& num)
	{
		//первые 32 бита
		highPart = num >> 32;
		//вторые 32 бита
		lowPart = num & 0xffffffff;
	}

	uint64(uint64& num)
	{
		highPart = num.highPart;
		lowPart = num.lowPart;
	}

	uint64(const uint& _highPart, const uint& _lowPart)
	{
		highPart = _highPart;
		lowPart = _lowPart;
	}

	//печать числа
	void PrintNum()
	{
		uint a = lowPart;
		uint b = highPart;
		unsigned long long result = ((unsigned long long)b) << 32 | ((unsigned long long)a);
		cout << result;
		
	}

	//+
	uint64 operator+(uint64& num)
	{
		uint64 result;

		if (lowPart + num.lowPart > MAX)
		{
			result.highPart = highPart + num.highPart + 1;
			result.lowPart = lowPart + num.lowPart;
		}
		else
		{
			result.highPart = highPart + num.highPart;
			result.lowPart = lowPart + num.lowPart;
		}
		return result;
	}

	//=
	uint64 operator=(const uint64& num)
	{
		highPart = num.highPart;
		lowPart = num.lowPart;
		return *this;

	}

	bool operator==(const uint64& num)
	{
		return(highPart == num.highPart && lowPart == num.lowPart);
	}
	
	//-
	uint64 operator-(uint64& num)
	{
		uint64 result;
		if (lowPart < num.lowPart)
		{
			result.highPart = highPart - num.highPart - 1;
			result.lowPart = lowPart - num.lowPart;
		}
		else
		{
			result.highPart = highPart - num.highPart;
			result.lowPart = lowPart - num.lowPart;
		}
		return result;
	}

	//<
	bool operator<(uint64& num)
	{
		if ((highPart < num.highPart) || (lowPart < num.lowPart))
			return 1;
		return 0;

	}

	//>
	bool operator>(uint64& num)
	{
		if ((highPart > num.highPart)|| (lowPart > num.lowPart))
			return 1;
		return 0;
	}

	//*
	uint64 operator*(uint64& num)
	{
		//первые 16 битов lowPArt 1-го числа
		uint ff = lowPart >> 16;
		//вторые 16 битов lowPart 1-го числа
		uint fs = lowPart & 0xffff;
		//первые 16 битов lowPart 2-го числа
		uint sf = num.lowPart >> 16;
		//вторые 16 битов lowPart 2-го числа
		uint ss = num.lowPart & 0xffff;

		uint64 result;
		result.highPart = highPart * num.lowPart + num.highPart * lowPart + ff * sf;
		result.lowPart = ((uint)ff * ss << 16) + fs * ss + ((uint)fs * sf << 16);
		return result;
	}

	//деление(очень долгое и неэффективное, но больше ничего не придумал)
	uint64 operator/(uint64& num)
	{
		if (num == 0)
		{
			cout << "ƒеление на 0";
			return 0;
		}
		if (num == (*this))
		{
			return 1;

		}
		if (num > (*this))
		{
			return 0;
		}
		uint64 copy(highPart, lowPart);
		unsigned long long count = 0;
		while (copy > num)
		{
			copy = copy - num;
			count++;
		}
		if (copy == num)
		{
			count++;
		}
		return uint64(count);
	}

	// % такое же неэффективное
	uint64 operator%(uint64& num)
	{
		if (num == 0)
		{
			cout << "ƒеление на 0";
			return 0;
		}
		if (num == (*this))
		{
			return 0;
		}
		if (num > (*this))
		{
			return (*this);
		}
		uint64 copy(highPart, lowPart);
		while (copy > num)
		{
			copy = copy - num;
			if (copy == num)
			{
				copy = 0;
				return uint64(copy);
			}
		}
		return uint64(copy);
	}

};