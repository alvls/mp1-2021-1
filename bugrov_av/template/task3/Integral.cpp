#include <iostream>
#include <cmath>
#include <limits>
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
double line(double x)
{
	return x;
}
class integral
{
	double lim[2];// левый и правый пределы интегрирования
	math foo;// указатель на функцию
	int n;// число сегментов
	double res;// результат вычислений
	way method;// метод интегрирования
	void calc();// вычисление интеграла
public:
	integral(double l = 0, double r = 0, math f = abs) :lim{ l, r }, foo(f) // конструктор
	{
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
		lim[0] = l;
		lim[1] = r;
	}
	const double* OutLim()// вывод пределов интегрирования
	{
		return lim;
	}
	void GetsegNum(int number)// задать число отрезков метода прямоугольников
	{
		n = number;
	}
	double out() // вывести результат вычисления на экран
	{
		calc();
		return res;
	}
	void GetWay(way choice)// выбрать метод вычисления
	{
		method = choice;
	}
};
void integral::calc()
{
	res *= 0;
	double addend, segment = (lim[1] - lim[0]) / n;
	int  i = 0, _n = n;
	double x_i = lim[0];
	switch (method)
	{
	case _left:
		break;
	case _mid:
		for (; i < _n; i++)
		{
			addend = foo(x_i + (i + 0.5) * segment);
			res += addend;
		}
		res *= segment;
		return;
	case _right:
		x_i += segment;
		break;
	default:
		cout << "Что-то пошло не так" << endl;
		return;
	}
	for (; i < _n; i++)
	{
		addend = foo(x_i + i * segment);
		res += addend;
	}
	res *= segment;
}
inline void repeater(bool& flag)
{
	flag = true;
	cout << "Bведите число из заданного диапазона" << endl;
}
int getnum()
{
	char c[2];
	int n;
	bool flag;
	int i;
	do
	{
		i = 0;
		n = c[0] = c[1] = 'a';
		flag = false;
		do
		{
			c[i % 2] = getchar();
			i++;
		} while (c[0] != '\n' && c[1] != '\n');
		if (i < 3)
			n = c[0] - '0';
		if (n < 0 || n>9)
		{
			cout << "Некорректный ввод" << endl;
			flag = true;
		}
	} while (flag);
	return n;
}
void usefunk(integral& s)
{
	enum fname { _exp = 1, _sin, _cos, _sinh, _cosh, _sqrt, _log, _line };
	cout << "Выберите номер функции:" << endl;
	cout << "1. Экспонента" << endl;
	cout << "2. Синус" << endl;
	cout << "3. Косинус" << endl;
	cout << "4. Гиперболический синус" << endl;
	cout << "5. Гиперболический косинус" << endl;
	cout << "6. Квадратный корень" << endl;
	cout << "7. Натуральный логарифм" << endl;
	cout << "8. Прямая y=x" << endl;
	math funk = line;
	bool flag = false;
	bool& f = flag;
	int ans;
	do
	{
		ans = getnum();
		switch (ans)
		{
		case _exp:
			funk = exp;
			break;
		case _sin:
			funk = sin;
			break;
		case _cos:
			funk = cos;
			break;
		case _sinh:
			funk = sinh;
			break;
		case _cosh:
			funk = cosh;
			break;
		case _sqrt:
			funk = sqrt;
			break;
		case _log:
			funk = log;
			break;
		case _line:
			funk = line;
			break;
		default:
			repeater(f);
			break;
		}
	} while (flag);
	s.GetFoo(funk);
}
void useway(integral& s)
{
	cout << "Выберите метод вычисления интеграла" << endl;
	cout << "1. Метод левых прямоугольников" << endl;
	cout << "2. Метод средних прямоугольников" << endl;
	cout << "3. Метод правых прямоугольников" << endl;
	bool flag = false;
	bool& f = flag;
	way getmeth;
	int ans;
	do 
	{
		ans = getnum();
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
			repeater(f);
			break;
		}
	} while (flag);
	s.GetWay(getmeth);
}
void menu()
{
	integral s;
	const double* limits = nullptr;
	integral& sum = s;
	int ans;
	do {
		usefunk(sum);
		cout << "Задайте пределы интегрирования" << endl;
		double leflim, riglim;
		bool flag = true;
		do
		{
			cin >> leflim >> riglim;
			if (leflim < riglim)
				flag = false;
			else
				cout << "Неверные данные" << endl;
		} while (flag);
		s.GetLim(leflim, riglim);
		limits = s.OutLim();
		cout << "Левый предел интегрирования: " << limits[0] << endl;
		cout << "Правый предел интегрирования: " << limits[1] << endl;
		cout << "Задайте число отрезков метода прямоугольников" << endl;
		int segnum;
		cin >> segnum;
		s.GetsegNum(segnum);
		useway(sum);
		double res;
		res = s.out();
		cout << "Результат вычислений: " << res << endl;
		cout << "Если вы желаете продолжать, введите 0, иначе введите любой другой символ" << endl;
		ans = getnum();
	} while (!ans);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Программа по вычислению интеграла от элементарных функций методом прямоугольников"<<endl;
	menu();
	system("pause");
}
