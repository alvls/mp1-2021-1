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
	double lim[2];// ����� � ������ ������� ��������������
	math foo;// ��������� �� �������
	int n;// ����� ���������
	double res;// ��������� ����������
	way method;// ����� ��������������
	void calc();// ���������� ���������
public:
	integral(double l = 0, double r = 0, math f = line) :lim{ l, r }, foo(f) // �����������, ���������� �������� �� �����
	{
		n = 1;
		res = 0;
		method = _mid;
	}
	void SetFoo(math f)// ������ ������� �������
	{
		foo = f;
	}
	void SetLim(double l, double r)// ������ ������� ��������������
	{
		lim[0] = l;
		lim[1] = r;
	}
	const double* GetLim()// ����� �������� ��������������
	{
		return lim;
	}
	void SetsegNum(int number)// ������ ����� �������� ������ ���������������
	{
		n = number;
	}
	double out() // ������� ��������� ���������� �� �����
	{
		calc();
		return res;
	}
	void SetWay(way choice)// ������� ����� ����������
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
		cout << "���-�� ����� �� ���" << endl;
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
			cout << "������������ ������, ������� ����� �����" << endl;
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
				cout << "������������ ������, ������� ����� �����" << endl;
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
				cout << "������������ ������, ������� ����� �����" << endl;
				repeat = true;
				break;
			}
		}
	} while (repeat);
	/*double res = atof(s); - ������-�� ����������� ������� �����
	return res;*/
	//���� � ��� ������ ������ ��� �������, ����� ����, ����� ���������
	double integer = 0.0; // ����� ����� �����
	double fractional = 0.0; // ������� ����� �����
	double tmp; // �������������� ���������� ��� ������� �����
	double res;//�������� �����
	bool posdeg = true;// ������������� �� ������� ������� 10
	bool negative = false; // �������� �� ����� �������������
	int j = 1;// ������ �������
	int t; // ������ �������
	int a;// ����� ��� (��������) ����� ����������� ������������� �����
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
	cout << "�������� ����� �������:" << endl;
	cout << "1. ����������" << endl;
	cout << "2. �����" << endl;
	cout << "3. �������" << endl;
	cout << "4. ��������������� �����" << endl;
	cout << "5. ��������������� �������" << endl;
	cout << "6. ���������� ������" << endl;
	cout << "7. ����������� ��������" << endl;
	cout << "8. ������ y=x" << endl;
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
			cout << "���-�� ����� �� ���, ������� ����� �����" << endl;
			flag = true;
			break;
		}
	} while (flag);
	s.SetFoo(funk);
}
void useway(integral& s)
{
	cout << "�������� ����� ���������� ���������" << endl;
	cout << "1. ����� ����� ���������������" << endl;
	cout << "2. ����� ������� ���������������" << endl;
	cout << "3. ����� ������ ���������������" << endl;
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
			cout << "���-�� ����� �� ���, ������� ����� �����" << endl;
			flag = true;
			break;
		}
	} while (flag);
	s.SetWay(getmeth);
}
void menu()
{
	integral s;
	const double* limits = nullptr;
	integral& sum = s;
	int ans;
	do {
		usefunk(sum);
		cout << "������� ����� � ������ ������� �������������� ����� Enter" << endl;
		double leflim, riglim;
		bool flag = true;
		do
		{
			leflim = getdb();
			riglim = getdb();
			if (leflim < riglim)
				flag = false;
			else
				cout << "�������� ������� ��� ����������� ���������� ����� ����������" << endl;
		} while (flag);
		s.SetLim(leflim, riglim);
		limits = s.GetLim();
		cout << "����� ������ ��������������: " << limits[0] << endl;
		cout << "������ ������ ��������������: " << limits[1] << endl;
		cout << "������� ����� �������� ������ ���������������" << endl;
		int segnum;
		segnum = getint();
		s.SetsegNum(segnum);
		cout << "����� �������� ����� " << segnum << endl;
		useway(sum);
		double res;
		res = s.out();
		cout << "��������� ����������: " << res << endl;
		cout << "���� �� ������� ����������, ������� 0, ����� ������� ���-���� ������" << endl;
		ans = getnum(INT_MAX, INT_MIN);
	} while (!ans);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "��������� �� ���������� ��������� �� ������������ ������� ������� ���������������"<<endl;
	menu();
	cout << "�������� ���!" << endl;
	system("pause");
}
