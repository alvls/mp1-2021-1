#include <iostream>
using namespace std;
//����������� ����� �������.
//����� ������ ������� �������(���������) �� ����� ����������(�).������� �������� n ��������� � ��������� �� 0 �� 12.
//����� ������ ������������� ��������� �������� : 
//1) ������ ������� ��������, 
//2) ������ ������������ ������� ��������, 
//3) ������ ������� ��������, 
//4) ������ �������� ������������ �� ��� ������, 
//5) ��������� �������� �������� � �������� ����� �, 
//6) ����� ����������� ��������.
//����� ������ ��������� ��� ����������� ������������, ����������, �������� ������������, � ����� ������� �������� ���� �� �������.
//
/*������� ������� - in_deg
������� ������������� - in_coef
������ ������� �������� - out_deg
������ ����������� ��� ������ ������� ��� - out_coef
��������� �������� �������� � �������� ����� � - value 
����� ����������� �������� - derivative
*/
class polinom
{
	double* coef;
	int deg;
public:
	friend void class_printer(const polinom& p);
	polinom(int n = 0)//����������p
	{
		deg = n;
		coef = new double[deg + 1];
		coef[deg] = 1.0;
		for (int i = 0; i < deg; i++)
		{
			coef[i] = 0.0;
		}
	}
	void in_deg(int n)//������� ������� ��������
	{
		deg = n;
		coef = new double[deg + 1];
		coef[deg] = 1.0;
		for (int i = 0; i < deg; i++)
		{
			coef[i] = 0.0;
		}
	}
	int out_deg()//����� ������� ��������
	{
		return deg;
	}
	void in_coef(double* p, int n)//���� �������������
	{
		if (n != deg)
		{
			delete[]coef;
			coef = new double[n + 1];
		}
		deg = n;
		for (int i = 0; i < n + 1; i++)
		{
			coef[i] = p[i];
		}
	}
	double out_coef(int k)//����� ������������ ������
	{
		return (k > deg) ? 0.0 : coef[k];
	}
	double value(double x)//�������� ��� ������ ���
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
	polinom derivative()//����������� 
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
	~polinom() //����������, ��������� �������
	{
		delete[]coef;
	}
	polinom(const polinom& p)//�������� �����������
	{
		deg = p.deg;
		coef = new double[deg + 1];
		for (int i = 0; i < deg + 1; i++)
		{
			coef[i] = p.coef[i];
		}
	}
	polinom& operator = (const polinom& from) //�������� ������������
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
	cout << "�����: " << noshowpos << print << endl;
}
void class_printer(const polinom& p)
{
	cout << "�����: ";
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
			cout << "�� ��������, ������� ������" << endl;
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
	double* coefs;
	int deg_coef;
	cout << "��� ������� �������� �������, ������� ������� ����� ������" << endl << endl;
	do {
		cout << "1. �������� ������� ��������" << endl;
		cout << "2. ������ ������������ ������� ��������" << endl;
		cout << "3. ������� ������� ��������" << endl;
		cout << "4. ������� �������� ������������ ��� ��������� ������� �" << endl;
		cout << "5. ��������� �������� �������� � �������� ����� �" << endl;
		cout << "6. ����� k-�� ����������� �������� � ������� �" << endl;
		cout << "7. ������� ������� �� �����" << endl;
		cout << "0. ����� �� ���������" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "������� �������" << endl;
			p.in_deg(get_deg());
			break;
		case 2:
			cout << "������� ������������� ������� ��������" << endl;
			cout << "����� ������� ������������ ��� ��������, ������������� � ������� ��������" << endl;
			deg_coef = get_deg();
			coefs = new double[deg_coef+1];
			for (int i = deg_coef; i >= 0; i--)
			{
				cin >> coefs[i];
			}
			p.in_coef(coefs, deg_coef);
			break;
		case 3:
			_deg = p.out_deg();
			printer(_deg);
			break;
		case 4:
			cout << "������� ������� ���" << endl;
			_coef = p.out_coef(get_deg());
			printer(_coef);
			break;
		case 5:
			cout << "������� �������� ����� �" << endl;
			cin >> x;
			y = p.value(x);
			printer(y);
			break;
		case 6:
			cout << "������� k" << endl;
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
			cout << "�� ��������!" << endl;
			break;
		default:
			cout << "�� ��������, ��������� ���� �����" << endl;
		}
	} while (a);
	system("pause");
}