#include <iostream>
#include <cmath>
#include <limits>
using namespace std;
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
	integral(double l = 0, double r = 0, math f = line) :lim{ l, r }, foo(f) // конструктор, деструктор оказался не нужен
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
int getnum(int rlim, int llim = 1)
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
		if (n < llim || n>rlim)
		{
			cout << "Некорректный ввод" << endl;
			flag = true;
		}
	} while (flag);
	return n;
}
int getint()
{
	int line = 256;
	char* s = new char[256];
	int i;
	bool repeat;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do
	{		
		repeat = false;
		line = 256;
		s[0] = 0;
		s[0] = getchar();
		for (i = 1; s[i-1] != '\n'; i++)
			s[i] = getchar();
		line = i - 1;
		for (i = 0; i < line; i++)
		{
			if (s[i] < '0' || s[i]>('0' + 9))
			{
				cout << "Неверный ввод, повторите ещё раз" << endl;
				repeat = true;
				break;
			}
		}
	} while (repeat);
	i = atoi(s);
	return i;
}
double getdb()
{
	int line = 256;
	char* s = new char[256];
	int i;
	bool repeat;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do
	{
		repeat = false;
		line = 256;
		s[0] = 0;
		s[0] = getchar();
		for (i = 1; s[i - 1] != '\n'; i++)
			s[i] = getchar();
		line = i - 1;
		bool NoPoint = true;
		if (s[0] == '-')
			i = 1;
		else
			i = 0;
		for (i; i < line; i++)
		{
			if ((s[i] < '0' || s[i]>('0' + 9)) && s[i] != '.' || s[i] == '.' && (!NoPoint))
			{
				cout << "Неверный ввод, повторите ещё раз" << endl;
				repeat = true;
				break;
			}
		}
	} while (repeat);
	/*double res = atof(s); - почему-то отбрасывает дробную часть
	return res;*/
	//зато я сам руками сделал эту функцию, может быть, более медленную
	double integer = 0.0; // целая часть числа
	double fractional = 0.0; // дробная часть числа
	double tmp; // дополнительная переменная для дробной части
	double res;//итоговое число
	bool posdeg = true;// положительная ли текущая степень 10
	bool negative = false; // является ли число отрицательным
	int j = 1;// второй счётчик
	int t; // третий счётчик
	int a;// целое для (возможно) более безопасного пребразования типов
	if (s[0] == '-')
	{
		i = 1;
		negative = true;
	}
	else
		i = 0;
	for (i; i < line; i++)
	{ 
		if (posdeg)
			if (s[i] == '.')
				posdeg = false;
			else
			{
				integer *= 10;
				a = s[i] - '0';
				integer += a;
			}
		else
		{
			a = s[i] - '0';
			tmp = a;
			for (t = 0; t < j; t++)
				tmp /= 10;
			fractional += tmp;
			j++;
		}
	}
	res = integer + fractional;
	if (negative)
		res *= -1;
	return res;
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
		flag = false;
		ans = getnum(8);
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
			cout << "Что-то пошло не так, введите снова" << endl;
			flag = true;
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
	bool flag;
	way getmeth;
	int ans;
	do 
	{
		flag = false;
		ans = getnum(3);
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
			cout << "Что-то пошло не так, введите снова" << endl;
			flag = true;
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
		cout << "Задайте левый и правый пределы интегрирования через Enter" << endl;
		double leflim, riglim;
		bool flag = true;
		do
		{
			leflim = getdb();
			riglim = getdb();
			if (leflim < riglim)
				flag = false;
			else
				cout << "Неверный порядок или отсутствует промежуток между значениями" << endl;
		} while (flag);
		s.GetLim(leflim, riglim);
		limits = s.OutLim();
		cout << "Левый предел интегрирования: " << limits[0] << endl;
		cout << "Правый предел интегрирования: " << limits[1] << endl;
		cout << "Задайте число отрезков метода прямоугольников" << endl;
		int segnum;
		segnum = getint();
		s.GetsegNum(segnum);
		cout << "Число отрезков равно " << segnum << endl;
		useway(sum);
		double res;
		res = s.out();
		cout << "Результат вычислений: " << res << endl;
		cout << "Если вы желаете продолжать, введите 0, иначе введите что-либо другое" << endl;
		ans = getnum(INT_MAX, INT_MIN);
	} while (!ans);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Программа по вычислению интеграла от элементарных функций методом прямоугольников"<<endl;
	menu();
	cout << "Хорошего дня!" << endl;
	system("pause");
}
