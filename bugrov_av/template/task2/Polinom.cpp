#include <iostream>
using namespace std;
//Разработать класс Полином.
//Класс должен хранить полином(многочлен) от одной переменной(х).Степень полинома n находится в диапазоне от 0 до 12.
//Класс должен предоставлять следующие операции : 
//1) задать степень полинома, 
//2) задать коэффициенты мономов полинома, 
//3) узнать степень полинома, 
//4) узнать значение коэффициента по его номеру, 
//5) вычислить значение полинома в заданной точке х, 
//6) найти производную полинома.
//Класс должен содержать все необходимые конструкторы, деструктор, оператор присваивания, а также «уметь» выводить себя на консоль.
int main()
{
	class polinom
	{
		double* term;
		int max;
	public:
		polinom()//конструктор по умолчанию
		{
			term = new double[1];
			term[0] = 1.0;
			max = 0;
		}
		polinom(int n)//конструктор по умолчанию при указании степени полинома
		{
			max = n;
			term = new double[max+1];
			term[max] = 1.0;
			for (int i = 0; i < max; i++)
			{
				term[i] = 0.0;
			}
		}
		polinom()
		{

		}
		unsigned short int degree()//получение степени полинома
		{
			return max;
		}
		double monom(int k)//получение коэффициента монома
		{
			return term[k];
		}
		double point_value(double x)//значение при данном икс
		{
			double answer;
			
		}
		polinom* derivative()//производная 
		{
			polinom der(max);
			for (int i = 0; i < max; i++)
				der.term[i] = der.term[i + 1] * double(i + 1);
			der.term[max] = 0.0;
		}
		~polinom()//деструктор, удаляющий полином
		{
			delete []term;
		}
		void out()
		{
			cout << term[max] << "x^" << max;
			for (int i = max-1; i >= 0; i--)
			{
				if (term[i] != 0.0)
					cout << showpos << term[i] << "x^" << i;
			}
		}
	};
}