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
//
/*Задание степени - in_deg
Задание коэффициентов - in_coef
Узнать степень полинома - out_deg
Узнать коэффициент при данной степени икс - out_coef
Вычислить значение полинома в заданной точке х - value 
Найти производную полинома - derivative
*/
class polinom
{
	double* coef;
	int deg;
public:
	friend void class_printer(const polinom& p);
	polinom(int n = 0)//конструктоp
	{
		deg = n;
		coef = new double[deg + 1];
		coef[deg] = 1.0;
		for (int i = 0; i < deg; i++)
		{
			coef[i] = 0.0;
		}
	}
	void in_deg(int n)//задание степени полинома
	{
		deg = n;
		coef = new double[deg + 1];
		coef[deg] = 1.0;
		for (int i = 0; i < deg; i++)
		{
			coef[i] = 0.0;
		}
	}
	unsigned short int out_deg()//вывод степени полинома
	{
		return deg;
	}
	void in_coef(int n)//ввод коэффициентов
	{
		if (n != deg)
		{
			delete[]coef;
			coef = new double[n + 1];
		}
		deg = n;
		double a;
		for (int i = n; i >= 0; i--)
		{
			cin >> a;
			coef[i] = a;
		}
		while (coef[deg] == 0.0)
		{
			if (!deg)
				break;
			deg--;
		}
	}
	double out_coef(int k)//вывод коэффициента монома
	{
		return (k > deg) ? 0.0 : coef[k];
	}
	double value(double x)//значение при данном икс
	{
		double monom_val;
		double answer = 0.0;
		int i, t;
		for (i = 0; i < deg + 1; i++)
		{
			monom_val = 1.0;
			for (t = 1; t < i + 1; t++)
			{
				monom_val *= x;
			}
			monom_val *= coef[i];
			answer += monom_val;
		}
		return answer;
	}
	polinom derivative()//производная 
	{
		if (deg == 0)
		{
			polinom der(0);
			der.coef[0] = 0.0;
			return der;
		}
		polinom der(deg-1);
		for (int i = 0; i < deg; i++)
			der.coef[i] = coef[i + 1] * double(i + 1);
		return der;
	}
	~polinom() //деструктор, удаляющий полином
	{
		delete[]coef;
	}
	polinom(const polinom& p)//оператор копирования
	{
		deg = p.deg;
		coef = new double[deg + 1];
		for (int i = 0; i < deg + 1; i++)
		{
			coef[i] = p.coef[i];
		}
	}
	polinom& operator = (const polinom& from) //оператор присваивания
	{
		if (this == &from)
			return *this;
		delete[] coef;
		deg = from.deg;
		coef = new double[deg+1];
		for (int i = 0; i < deg+1; i++)
		{
			coef[i] = from.coef[i];
		}
		return *this;
	}
};
template <typename T>
void printer(const T print)
{
	cout << "Ответ: " << noshowpos << print << endl;
}
void class_printer(const polinom& p)
{
	cout << "Ответ: ";
	if (p.deg > 1)
	{
		if (p.coef[p.deg] == 1.0 && p.deg > 1)
			cout << noshowpos << "x^" << p.deg;
		else
			cout << noshowpos << p.coef[p.deg] << "x^" << p.deg << " ";
		for (int i = p.deg - 1; i > 1; i--)
		{
			if (p.coef[i] != 0.0)
			{
				cout << showpos << p.coef[i];
				cout << noshowpos << "x^" << i << " ";
			}
		}
		if (p.coef[1] != 0.0)
		{
			cout << showpos << p.coef[1];
			cout << "x" << " ";
		}
		if (p.coef[0] != 0.0)
			cout << showpos << p.coef[0] << " ";
	}
	else
	{
		if (p.deg > 0)
		{
			if (p.coef[1] != 0.0)
			{
				cout << p.coef[1];
				cout << "x" << " ";
			}
			if (p.coef[0] != 0.0)
				cout << showpos << p.coef[0] << " ";
		}
		else
			cout << noshowpos << p.coef[0] << " ";
	}
	cout << "\n";
}
int get_deg()
{
	int n;
	do {
		cin >> n;
		if (n < 0 || n>12)
			cout << "Вы ошиблись, введите заново" << endl;
	} while (n < 0 || n>12);
	return n;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	polinom p;
	int a;
	int n;
	polinom der_x;
	unsigned short _deg;
	double _coef;
	double x;
	double y;
	cout << "Все дробные значения вводите, отделяя дробную часть точкой" << endl << endl;
	do {
		cout << "1. Заменить степень полинома" << endl;
		cout << "2. Задать коэффициенты мономов полинома" << endl;
		cout << "3. Вывести степень полинома" << endl;
		cout << "4. Вывести значение коэффициента при указанной степени х" << endl;
		cout << "5. Вычислить значение полинома в заданной точке х" << endl;
		cout << "6. Найти k-ую производную полинома и вывести её" << endl;
		cout << "7. Вывести полином на экран" << endl;
		cout << "0. Выйти из программы" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "Введите степень" << endl;
			p.in_deg(get_deg());
			break;
		case 2:
			cout << "Укажите дополнительно степень полинома" << endl;
			cout << "Затем вводите коэффициенты при степенях, расположенных в порядке убывания" << endl;
			p.in_coef(get_deg());
			break;
		case 3:
			_deg = p.out_deg();
			printer(_deg);
			break;
		case 4:
			cout << "Введите степень икс" << endl;
			_coef = p.out_coef(get_deg());
			printer(_coef);
			break;
		case 5:
			cout << "Введите значение точки х" << endl;
			cin >> x;
			y = p.value(x);
			printer(y);
			break;
		case 6:
			cout << "Введите k" << endl;
			n = get_deg();
			der_x = p;
			for (int i = 0; i < n; i++)
				der_x = der_x.derivative();
			class_printer(der_x);
			break;
		case 7:
			class_printer(p);
			break;
		case 0:
			cout << "До свидания!" << endl;
			break;
		default:
			cout << "Вы ошиблись, повторите ввод снова" << endl;
		}
	} while (a);
	system("pause");
}