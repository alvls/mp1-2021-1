#include <iostream>
#include <math.h>
using namespace std;

class Vector
{
private:
	short size;
	int* vec;
public:
	Vector(short size)
	{
		this->size = size;
		vec = new int[size];
	}
	Vector()
	{
		size = 0;
		vec = nullptr;
	}
	//конструктор копирования
	Vector(const Vector& vec2)
	{
		this->size = vec2.size;
		vec = new int[this->size];
		for (short i = 0; i < size; i++)
		{
			this->vec[i] = vec2.vec[i];
		}
	}
	//конструктор на size элементов с инициализацией
	/*Vector(short size, int value1, ...)
	{
		this->size = size;
		va_list 
		for (int i = 0;i < size;i++)
		{
			this->vec[i] = 
		}

	}*/
	short GetSize()
	{
		return size;
	}
	//изменять размер для измения длины
	void ChangeSize(short size)
	{
		this->size = size;
		for (int i = 0; i < size; i++)
		{
			this->vec[i] = vec[i];
		}
	}
	void SetComponent(short index, int component)
	{
		vec[index] = component;
	}
	int GetComponent(short index)
	{
		return vec[index];
	}
	double LengthVec()
	{
		long sumSqrt = 0;
		for (short i = 0; i < size; i++)
		{
			sumSqrt += vec[i] * vec[i];
		}
		return sqrt(sumSqrt);
	}
	long ScalarProduct(Vector vec2)
	{
		long result = 0;
		if (this->size == vec2.size)
		{
			for (short i = 0; i < size; i++)
			{
				result += this->vec[i] * vec2.vec[i];
			}
			return result;
		}
		return 0;
	}
	//*this - содержит ссылку на объект класса, в котором вызывается
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
	}
	void PrintVec()
	{
		for (int i = 0; i < size; i++)
		{
			cout << vec[i] << endl;
		}
	}
	Vector operator=(const Vector& vec2)
	{
		Vector temp(vec2);
		return temp;
	}

};