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
int main()
{
	class polinom
	{
		double* term;
		int max;
	public:
		polinom()//����������� �� ���������
		{
			term = new double[1];
			term[0] = 1.0;
			max = 0;
		}
		polinom(int n)//����������� �� ��������� ��� �������� ������� ��������
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
		unsigned short int degree()//��������� ������� ��������
		{
			return max;
		}
		double monom(int k)//��������� ������������ ������
		{
			return term[k];
		}
		double point_value(double x)//�������� ��� ������ ���
		{
			double answer;
			
		}
		polinom* derivative()//����������� 
		{
			polinom der(max);
			for (int i = 0; i < max; i++)
				der.term[i] = der.term[i + 1] * double(i + 1);
			der.term[max] = 0.0;
		}
		~polinom()//����������, ��������� �������
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