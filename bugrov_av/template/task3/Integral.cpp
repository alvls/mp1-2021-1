#include <iostream>
#include <cmath>
using namespace std;
//Разработать класс Расчет интегралов.
//Класс должен позволять вычислять приближенное значение интеграла от произвольной функции одной переменной, заданной в виде функции языка C++.
//Интеграл необходимо вычислять в заданных пределах интегрирования, используя методы левых, правых и средних прямоугольников.
//Класс должен содержать необходимые служебные методы(конструкторы, деструктор и пр.).
//Класс должен предоставлять следующие операции : 
//1) задать текущую функцию, +
//2) задать пределы интегрирования, +
//3) узнать пределы интегрирования, + 
//4) задать число отрезков метода прямоугольников, +
//5) выбрать метод вычисления, +
//6) вычислить значение интеграла выбранным методом,
//7) вывести результат вычисления на экран. +

typedef double(*math)(double);
enum way
{
	_left = 1,
	_mid,
	_right
};
class integral
{
	double a, b;// левый и правый пределы интегрирования
	math foo;// указатель на функцию
	int n;// число сегментов
	double res;// результат вычислений
	way method;// метод интегрирования
	double midfinder(double a1, double b1)
	{
		return (b1 + (b1 - a1) / 2);
	}
public:
	void calc();// вычисление интеграла
	integral(double l = 0, double r = 0, math f = cos) :a(l), b(r), foo(f) // конструктор
	{
		b = 0;
		a = 0;
		n = 1;
		res = 0;
		method = _mid;
	}
	void GetFoo(math f)// Задать текущую функцию
	{
		foo = f;
	}
	void GetLim(double l, double r)// задать пределы интегрирования
	{
		a = l;
		b = r;
	}
	const double* OutLim()// вывод пределов интегрирования
	{
		double* lim = new double[2];
		lim[0] = a;
		lim[1] = b;
		return lim;
	}
	void GetsegNum(int number)// задать число отрезков метода прямоугольников
	{
		n = number;
	}
	double out() // вывести результат вычисления на экран
	{
		return res;
	}
	void GetWay(way choice)// выбрать метод вычисления
	{
		method = choice;
	}
};
void integral::calc()
{
	double addend;
	double segment = (b - a) / (double)n;
	double a1 = a;
	double b1 = a + segment;
	int i = 0, _n = n;
	double* x_i = nullptr;
	switch (method)
	{
	case _left:
		*x_i = a1;
		break;
	case _mid:
		for (; i < _n; i++)
		{
			addend = foo(midfinder(a1, b1)) * (b1 - a1);
			res += addend;
			a1 += segment;
			b1 += segment;
		}
		return;
	case _right:
		i++;
		_n++;
		*x_i = b1;
		break;
	default:
		cout << "Что-то пошло не так" << endl;
		break;
	}
	for (; i < _n; i++)
	{
		addend = foo(*x_i) * (b1 - a1);
		res += addend;
		a1 += segment;
		b1 += segment;
	}
}
void printer()
{

}
int main()
{
	setlocale(LC_ALL, "Russian");
	int a;
	integral s;
	const double* limits = nullptr;
	enum fname { _exp = 1, _sin, _cos, _sinh, _cosh, _sqrt, _log };
	do {
	cout << "1. Задать текущую функцию" << endl;
	cout << "2. Задать пределы интегрирования" << endl;
	cout << "3. Узнать пределы интегрирования" << endl;
	cout << "4. Задать число отрезков метода прямоугольников" << endl;
	cout << "5. Выбрать метод вычисления" << endl;
	cout << "6. Вычислить значение интеграла выбранным методом" << endl; 
	cout << "7. Вывести результат вычисления на экран" << endl;
	cout << "0. Выйти из программы" << endl;
	cin >> a;
		switch (a)
		{
			int segnum;
			way getmeth;
			double res;
			int ans;
			double leflim, riglim;
			math funk;
		case 1:
			cout << "1. Экспонента" << endl;
			cout << "2. Синус" << endl;
			cout << "3. Косинус" << endl;
			cout << "4. Гиперболический синус" << endl;
			cout << "5. Гиперболический косинус" << endl;
			cout << "6. Квадратный корень" << endl;
			cout << "7. Натуральный логарифм" << endl;
			cin >> ans;
			switch (ans)
			{
			case _exp:
				funk = exp;
				printf("exp");
				break;
			case _sin:
				printf("sin");
				funk = sin;
				break;
			case _cos:
				printf("cos");
				funk = cos;
				break;
			case _sinh:
				printf("sinh");
				funk = sinh;
				break;
			case _cosh:
				printf("cosh");
				funk = cosh;
				break;
			case _sqrt:
				printf("sqrt");
				funk = sqrt;
				break;
			case _log:
				printf("log");
				funk = log;
				break;
			default:
				printf("default");
				funk = abs;
				break;
			}
			s.GetFoo(funk);
			break;
		case 2:
			cin >> leflim >> riglim;
			s.GetLim(leflim, riglim);
			break;
		case 3:
			limits = s.OutLim();
			cout << "" << limits[0] << endl;
			cout << "" << limits[1] << endl;
			break;
		case 4:
			cin >> segnum;
			s.GetsegNum(segnum);
			break;
		case 5:
			cin >> ans;
			switch (ans)
			{
			case _left:
				getmeth = _left;
				break;
			case _mid:
				getmeth = _mid;
				break;
			case _right:
				getmeth = _right;
				break;
			default:
				break;
			}
			s.GetWay(getmeth);
			break;
		case 6:
			s.calc();
			break;
		case 7:
			res = s.out();
			break;
		default:
			cout << "Всего доброго, до свидания!" << endl;
			break;
		}
	}while (a);
	system("pause");
}
//void integral::left_rectangle()
//{
//	double addend;
//	double segment = (b - a) / (double)n;
//	double a1 = a;
//	double b1 = a + segment;
//	for (int i = 0; i < n; i++)
//	{
//		addend = foo(a1) * (b1 - a1);
//		res += addend;
//		a1 += segment;
//		b1 += segment;
//	}
//}
//void integral::right_rectangle()
//{
//	double addend;
//	double segment = (b - a) / (double)n;
//	double a1 = a;
//	double b1 = a + segment;
//	for (int i = 1; i < n + 1; i++)
//	{
//		addend = foo(b1) * (b1 - a1);
//		res += addend;
//		a1 += segment;
//		b1 += segment;
//	}
//}
//void integral::mid_rectangle()
//{
//	double addend;
//	double segment = (b - a) / (double)n;
//	double a1 = a;
//	double b1 = a + segment;
//	for (int i = 0; i < n; i++)
//	{
//		addend = foo(midfinder(a1, b1)) * (b1 - a1);
//		res += addend;
//		a1 += segment;
//		b1 += segment;
//	}
//}

