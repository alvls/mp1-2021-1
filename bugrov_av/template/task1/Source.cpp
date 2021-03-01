#include <iostream>
#include <cmath>
using namespace std;
class Rational
{
private:
	signed long long p;
	unsigned long long q;
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
	long long Algebsum(unsigned long long n, long long m)//����� ��� �������� � ���������
	{
		p *= long long (n);
		m *= q;
		q *= n;
		return m;
	}
	void reduction()//���������� ����� �� ��� ��������� � �����������
	{
		if (p == 0)
		{
			q = 1;
			return;
		}
		unsigned long long p_tmp, nod;//p_tmp - ����� �� �������� �������� ��� �������� � �����������
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
		if (n == 0)
		{
			cout << "�� 0 ������ ������" << endl;
			return;
		}
		p *= m;
		q *= n;
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
		p += m;
	}
	void subtraction(Rational r)
	{
		long long m = r.p;
		unsigned long long n = r.q;
		m = Algebsum(n, m);
		p -= m;
	}
	Rational()
	{
		p = 1;
		q = 1;
	}
	Rational(long long a, unsigned long long b)
	{
		p = a;
		q = b;
		reduction();
	}
	void operator = (const Rational& from)
	{
		this->p = from.p;
		this->q = from.q;
	}
};
Rational second_value()
{
	long long a;
	unsigned long long b;
	Rational second;
	do 
	{
		cout << "������� ��������� � ����������� ������ �����" << endl;
		cin >> a >> b;
		Rational second1(a, b);
		second = second1;
	} while (b == 0);
	return second;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "������� ��������� � ����������� ����� (����������� �����������)\n";
	long long a;
	unsigned long long b;
	bool repeat = true;
	do
	{
		cin >> a >> b;
		if (b != 0)
		{
			bool flag = false;
			Rational drob(a, b);
			int ans;
			do
			{
				cout << "�������� ��������� ��������:" << endl;
				cout << "1 - ��������" << endl;
				cout << "2 - ���������" << endl;
				cout << "3 - ���������" << endl;
				cout << "4 - �������" << endl;
				cout << "5 - ����� ����������� ����� �� �����" << endl;
				cout << "6 - ��������� �������� �����" << endl;
				cout << "0 - ����� �� ���������" << endl;
				cin >> ans;
				if (ans < 0 || ans>6)
					cout << "�� ��������, ���������� ��� ���" << endl;
				else
				{
					Rational second;
					switch (ans)
					{
					case 1:
						second = second_value();
						drob.addition(second);
						goto answer;// ��� goto ������ � ���� �����, ������ ��� ���� while ������ �� �������
						break;
					case 2:
						second = second_value();
						drob.subtraction(second);
						goto answer;
						break;
					case 3:
						second = second_value();
						drob.multiply(second);
						goto answer;
						break;
					case 4:
						second = second_value();
						drob.division(second);
					answer:	case 5:
						cout << "���������: ";
						drob.out();
						break;
					case 6:
						drob = second_value();
						goto answer;
						break;
					case 0:
						repeat = false;
						cout << "�� ��������!" << endl;
						break;
					}

				}
			} while (repeat);
		}
		else
			cout << "�� 0 ������ ������\n";
	} while (repeat);
	system("pause");
}