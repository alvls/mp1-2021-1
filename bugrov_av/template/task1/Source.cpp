#include <iostream>
#include <cmath>
using namespace std;
class Rational
{
private:
	signed long long p;
	unsigned long long q;
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
	long long Algebsum(unsigned long long n, long long m)//общее для сложения и вычитания
	{
		unsigned long long nok = NOK(n);
		p *= long long (nok / q);
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
		p /= long long (nod);
		q /= nod;
	}
	void num_multiply(long long m, unsigned long long n)
	{
		p *= m;
		q *= n;
	}
	long long open_p()
	{
		return p;
	}
	unsigned long long open_q()
	{
		return q;
	}
public:
	void out()
	{
		reduction();
		cout << p;
		cout << "/";
		cout << q << "\n";
	}
	void multiply(Rational r)
	{
		long long m = r.p;
		unsigned long long n = r.q;
		num_multiply(m, n);
	}
	void division(Rational r)
	{
		long long n1 = long long(r.q);
		long long m = r.p;
		unsigned long long m1;
		if (m < 0)
		{
			n1 *= -1;
			m1 = unsigned long long((-1) * m);
		}
		else
			m1 = unsigned long long(m);
		num_multiply(n1, m1);
	}
	void addition(Rational r)
	{
		long long m = r.p;
		unsigned long long n = r.q;
		m = Algebsum(n, m);
	}
	void subtraction(Rational r)
	{
		m = Algebsum(n, m);
	}
	void operation(int choice, long long m, unsigned long long n)
	{
		switch (choice)
		{
		case 1: case 2:
			if (m != 0)
			{
				m = Algebsum(n, m);
				if (choice == 1)
					p += m;
				else
					p -= m;
			}
				break;
		case 3:
			//multiply(m, n);
			break;
		case 4:
			long long n1 = long long(n);
			unsigned long long m1;
			if (m < 0)
			{
				n1 *= -1;
				m1 = unsigned long long((-1) * m);
			}
			else
				m1 = unsigned long long(m);
			//multiply(n1, m1);
			break;
		}
	}
	Rational(long long a, unsigned long long b)
	{
		p = a;
		q = b;
		reduction();
	}
	void operator = (Rational& from)
	{
		this->p = from.p;
		this->q = from.q;
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите числитель и знаменатель дроби (знаменатель положителен)\n";
	long long a;
	unsigned long long b;
	bool repeat = true;
	do
	{
		cin >> a >> b;
		if (b != 0)
		{
			Rational drob(a, b);
			int ans;
			do 
			{
				cout << "Выберите требуемую операцию:" << endl;
				cout << "1 - Сложение" << endl;
				cout << "2 - Вычитание" << endl;
				cout << "3 - Умножение" << endl;
				cout << "4 - Деление" << endl;
				cout << "5 - Повторный вывод рациональной дроби на экран" << endl;
				cout << "6 - Изменение значения дроби" << endl;
				cout << "0 - Выход из программы" << endl;
				cin >> ans;
				if (ans < 0 || ans>6)
					cout << "Вы ошиблись, попробуйте ещё раз" << endl;
				else 
				{
					if (ans == 6)//я бы мог просто в кейсе 6 сделать инициализацию,но мне почему-то не дали 
					{
						cout << "Введите новые числитель и знаменатель" << endl;
						cin >> a >> b;
						Rational newdrob(a, b);
						drob = newdrob;
					}
					else
					{
						switch (ans)
						{
						case 1: case 2: case 3: case 4:
							cout << "Введите числитель и знаменатель второй дроби" << endl;
							cin >> a >> b;
							if (b == 0)
							{
								cout << "На нуль делить нельзя" << endl;
								break;
							}
							drob.operation(ans, a, b);
						case 5:
							cout << "Ответ: ";
							drob.out();
							break;
						case 0:
							repeat = false;
							cout << "До свидания!" << endl;
							break;
						}
					}
				}				
			} while (repeat);
		}
		else
			cout << "На 0 делить нельзя\n";
	} while (repeat);
	system("pause");
}