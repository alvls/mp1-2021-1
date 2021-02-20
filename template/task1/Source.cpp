#include <iostream>
#include <cmath>
using namespace std;
class Rational
{
private:
	signed long long p;
	unsigned long long q;
public:
	void out()
	{
		reduction();
		cout << p;
		cout << "/";
		cout << q << "\n";
	}
	void operation(int choice, long long m, unsigned long long n)
	{
		switch (choice)
		{
		case 1: case 2:
			m = Algsum(n, m);
			if (choice == 1)
				p += m;
			else
				p -= m;
		case 3:
			multiply(m, n);
		case 4:
			long long n1 = n;
			unsigned long long m1;
			if (m < 0)
			{
				n1 *= -1;
				m1 = (-1) * m;
			}
			else
				m1 = m;
			multiply(n1, m1);
		}
	}
	void multiply(long long m, unsigned long long n)
	{
		p *= m;
		q *= n;
	}
	unsigned long long NOK(unsigned long long n)
	{
		if (n % q == 0)
			return q;
		else
			if (q % n == 0)
				return n;
			else
			{
				unsigned long long nok = 1, q_tmp = q, n_tmp = n;
				if (q_tmp > n_tmp)
					nok = NOD(n_tmp, q_tmp);
				else
					nok = NOD(q_tmp, n_tmp);
				nok = (q / nok) * n;// a так формула для НОК была бы такая: НОК(а,b) = (a/НОД(a,b)) * (b/НОД(a,b)) * НОД(a,b), но я сократил
				return nok;
			}
	}
	unsigned long long NOD(unsigned long long min, unsigned long long max)
	{
		if (max % min == 0)
		{
			return min;
		}
		else
		{
			unsigned long long min_tmp = min, max_tmp = max, tmp;
			while (max_tmp % min_tmp)
			{
				tmp = max_tmp;
				max_tmp = min_tmp;
				min_tmp = tmp % min_tmp;
			}
			return min_tmp;
		}
	}
	long long Algsum(unsigned long long n, long long m)//общее для сложения и вычитания
	{
		unsigned long long nok = NOK(n);
		p *= nok / q;
		m *= nok / n;
		q = nok;
		return m;
	}
	void reduction()//Сокращение дроби на НОД числителя и знаменателя
	{
		unsigned long long p_tmp, nod;//p_tmp - чтобы не потерять значения при переходе в беззнаковые
		if (p < 0)
			p_tmp = (-1) * p;
		else
			p_tmp = p;
		if (p_tmp < q)
			nod = NOD(p_tmp, q);
		else
			nod = NOD(q, p_tmp);
		p /= nod;
		q /= nod;
	}
	Rational(long long a, unsigned long long b)
	{
		p = a;
		q = b;
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите через пробел числитель и знаменатель дроби (знаменатель положителен)\n";
	long long a;
	unsigned long long b;
	cin >> a >> b;
	bool repeat = true;
	do
	{
		if (b != 0)
		{
			Rational drob(a, b);
			do 
			{
				cout << "Выберите ту операцию, которая вам требуется:" << endl;
				cout << "1 - Сложение" << endl;
				cout << "2 - Вычитание" << endl;
				cout << "3 - Умножение" << endl;
				cout << "4 - Деление" << endl;
				cout << "5 - Вывод на экран результата" << endl;
				cout << "0 - Выход из программы" << endl;
				int ans;
				cin >> ans;
				switch (ans)
				{
				case 1: case 2: case 3: case 4:
					cout << "Введите числитель и знаменатель второй дроби" << endl;
					cin >> a >> b;
					drob.operation(ans, a, b);
				case 5:
					drob.out();
				case 0:
					repeat = false;
				}
			} while (repeat);
		}
		else
			cout << "На 0 делить нельзя\n";
	} while (repeat);
	system("pause");
}