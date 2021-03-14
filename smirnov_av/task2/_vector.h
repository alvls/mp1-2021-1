#include <iostream>
#include <math.h>
#include <stdarg.h> 
using namespace std;

class Vector
{
private:
	short size;
	int* vec;
public:
	Vector(short _size)
	{
		size = _size;
		vec = new int[size];
		for (short i = 0; i < size; i++)
		{
			vec[i] = 0;
		}
	}

	Vector()
	{
		size = 0;
		vec = nullptr;
	}
	
	//конструктор копировани¤
	Vector(const Vector& vec2)
	{
		size = vec2.size;
		vec = new int[size];
		for (short i = 0; i < size; i++)
		{
			vec[i] = vec2.vec[i];
		}
	}

	//конструктор на size элементов с инициализацией
	Vector(short _size,int ...)
	{
		size = _size;
		vec = new int[size];
		va_list firstParm;
		va_start(firstParm, _size);
		for (int i = 0; i < _size; i++)
		{
			vec[i] = va_arg(firstParm, int);
		}
		va_end(firstParm);
	}

	//деструктор
	~Vector()
	{
		delete []vec;
	}
	
	//количество компонентов в векторе
	short GetSize()
	{
		return size;
	}

	//изменить размер
	void ChangeSize(short _size)
	{
		if (size != _size)
		{
			Vector tempVec(*this);
			delete[]vec;
			vec = new int[_size];
			if (size > _size)
			{
				size = _size;
				for (int i = 0; i < _size; i++)
				{
					vec[i] = tempVec.vec[i];
				}
			}
			if (size < _size)
			{
				size = _size;
				for (short i = 0; i < tempVec.size; i++)
				{
					vec[i] = tempVec.vec[i];
				}
				for (short i = tempVec.size; i < _size; i++)
				{
					vec[i] = 0;
				}
			}
		}
		
	}

	//изменить компоненту вектора
	void SetComponent(short index, int component)
	{
		vec[index] = component;
	}

	//получить значение компоненты вектора
	int GetComponent(short index)
	{
		return vec[index];
	}

	//длина вектора
	double LengthVec()
	{
		long sumSqrt = 0;
		for (short i = 0; i < size; i++)
		{
			sumSqrt += vec[i] * vec[i];
		}
		return sqrt(sumSqrt);
	}

	//скал¤рное произведение
	long ScalarProduct(const Vector& vec2)
	{
		long result = 0;
		if (size == vec2.size)
		{
			for (short i = 0; i < size; i++)
			{
				result += vec[i] * vec2.vec[i];
			}
			return result;
		}
		return 0;
	}

	//функци¤ суммы
	Vector SumVector(Vector vec2)
	{
		Vector result(*this);
		if (result.size == vec2.size)
		{
			for (int i = 0; i < size; i++)
			{
				result.vec[i] += vec2.vec[i];
			}
			return result;
		}
		return Vector(result.size);
	}

	//печать
	void PrintVec()
	{
		for (int i = 0; i < size; i++)
		{
			cout << vec[i] << endl;
		}
	}

	//=
	Vector& operator=(const Vector& vec2)
	{
		if (this == &vec2)
			return *this;
		size = vec2.size;
		delete[]vec;
		vec = new int[size];
		for  (short i = 0; i < size;i++)
		{
			vec[i] = vec2.vec[i];
		}
		return *this;
	}

	//+
	Vector operator+(const Vector& vec2)
	{
		return SumVector(vec2);
	}

	//количество чисел в строке
	int CountInStr(char* str)
	{
		int i = 0;
		int inNumber = 0;
		int count = 0;
		while (str[i] != '\0')
		{
			if (str[i] != ' ')
				inNumber = 1;
			if (str[i] == ' ' && inNumber == 1)
			{
				count++;
				inNumber = 0;
			}
			if (str[i + 1] == '\0' && inNumber == 1)
				count++;
			i++;
		}
		return count;
	}

	//забыл про существование atoi 0_о
	int StrToInt(char* str)
	{
		int temp = 0;
		int i = 0;
		int sign = 0; 
		if (str[i] == '-')
		{
			sign = 1;
			i++;
		}
		while (str[i] >= 0x30 && str[i] <= 0x39)
		{
			temp += (str[i] & 0x0F);
			temp *= 10;
			i++;
		}
		temp /= 10;
		if (sign == 1)
			temp = -temp;
		return temp;
	}

	//инициализаци¤ вектора с помощью строки чисел через пробелы
	void SetFromStr(char* str)
	{
		size = CountInStr(str);
		vec = new int[size];
		int i = 0;
		int j = 0;
		int k = 0;
		int inNumber = 0;
		char* temp = new char[12]; 
		while (str[i] != '\0')
		{	
			if (str[i] != ' ')
				inNumber = 1;
			while (inNumber)
			{
				if (str[i] == ' '||str[i] == '\0')
				{
					inNumber = 0;
					//vec[k] = StrToInt(temp);
					vec[k] = atoi(temp);
					for (int j = 0;j < 12;j++)
					{
						temp[j] = 'H';
					}
					k++;
					break;
				}
				temp[j] = str[i];
				i++;
				j++;
			}
			j = 0;
			i++;
		}
		delete[]temp;
		temp = nullptr;
	}

};