/*
    ����������� ����� ��������� ����������.
    ����� ������ ������� ����������� � �������� ������� � ������������� ������ �� ��� �������������� � ������ ������� ��������� (���������, �������, ������, �).
    ����� ������ ������������� ��������: 1) ���������� ������� ����������� � �������� �������, 2) ������ ������� ����������� � �������� �������, 3) ������ ������� ����������� � ��������� ������� ��������� (�� ������ ��������������).
    ����� ������ ��������� ��� ����������� ������������, � ����� ������� �������� ���� �� �������.
*/

#include <iostream>
#include <limits>
using namespace std;

class Temperature
{
private:
	double tcelc; //����������� � ��������
public:
	//��� ��������� ������������
	Temperature() 
	{
		tcelc = DBL_MIN;
	}
	//������� � �������
	double Get_tcelc()
	{
		return tcelc;
	}
	void Set_tcelc(double value_tcelc)
	{
		tcelc = value_tcelc;
	}
	//�������� �� ����������
	bool exist()
	{
		if (tcelc == DBL_MIN)
			return false;
		else
			return true;
	}
	//���������
	double Fahrenheit()
	{
		return tcelc * 9 / 5 + 32;
	}
	double Kelvin()
	{
		return tcelc + 273.15;
	}
	double Rankine()
	{
		return (tcelc + 273.15) * 9 / 5;
	}
	double Delisle()
	{
		return (100 - tcelc) * 3 / 2;
	}
	double Newton()
	{
		return tcelc * 33 / 100;
	}
	double Reaumur()
	{
		return tcelc * 4 / 5;
	}
	double Romer()
	{
		return tcelc * 21 / 40 + 7.5;
	}
};	

int proverka(int a, int b)
{
	int vibor = -1;
	while ((vibor < a) || (vibor > b))
	{
		cin >> vibor;
		if ((vibor < a) || (vibor > b))
		{		
			cout << "������� �������� �����. ������ ������� �� ������������� ����������." << endl;
			cin.clear();
		}
	}
	return vibor;
}

void main()
{
	Temperature t;
	int vibor[2] = { -1, -1 };
	bool exit = false;
	setlocale(LC_ALL, "Ru");
	cout << "\n ����������� ���! � - ��������� ����������!";
	while (exit == false)
	{
		cout << "\n ������ �� ���������� � ����. ��������, ��� ����� ������� :\n\t(1) ���������� ������� ����������� � �������� �������\n\t(2) ������ ������� ����������� � �������� �������\n\t(3) ������ ������� ����������� � ������ ��� ������� ���������\n\t(0) ����� �� ���������" << endl;
		vibor[0] = proverka(0, 3);
		system("cls");
		switch (vibor[0])
		{
		case 1: //���������� ������� ����������� � �������� �������
			double temp;
			cout << "\n ������� �������� ������� ����������� � �������� �������.\n ��� ������� �������� ����������� \".\" � �������� �����������." << endl;
			cin >> temp;
			t.Set_tcelc(temp);
			temp = DBL_MIN;
			break;
		case 2: //������ ������� ����������� � �������� �������
			if (t.exist())
				cout << "\n ������� ����������� � �������� �������: " << t.Get_tcelc() << " C" << endl;
			else
				cout << "\n ������� ����������� � �������� ������� �� ���� ������" << endl;
			break;
		case 3: //������ ������� ����������� � ������ ������� ���������
			if (t.exist() == false)
				cout << "\n ������� ����������� � �������� ������� �� ���� ������" << endl;
			else
			{
				cout << "\n � ����� ������� ��������� ������� ��������� ������� �����������?\n\t(1) ���������\n\t(2) �������\n\t(3) ������\n\t(4) ������\n\t(5) ������\n\t(6) ������\n\t(7) и���" << endl;
				vibor[1] = proverka(1, 7);
				system("cls");
				switch (vibor[1])
				{
				case 1:
					cout << "\n ������� ����������� � �������� ����������: " << t.Fahrenheit() << " F" << endl;
					break;
				case 2:
					cout << "\n ������� ����������� � �������� ��������: " << t.Kelvin() << " K" << endl;
					break;
				case 3:
					cout << "\n ������� ����������� � �������� �������: " << t.Rankine() << " R" << endl;
					break;
				case 4:
					cout << "\n ������� ����������� � �������� ������: " << t.Delisle() << " De" << endl;
					break;
				case 5:
					cout << "\n ������� ����������� � �������� �������: " << t.Newton() << " N" << endl;
					break;
				case 6:
					cout << "\n ������� ����������� � �������� �������: " << t.Reaumur() << " Re" << endl;
					break;
				case 7:
					cout << "\n ������� ����������� � �������� и����: " << t.Romer() << " Ro" << endl;
					break;
				default:
					cout << "\n �������������� ������." << endl;
					exit = true;
					break;
				}
			}
			break;
		case 0:
			exit = true;
			break;
		default:
			cout << "\n �������������� ������." << endl;
			exit = true;
			break;
		}
		system("pause");
		system("cls");
		vibor[0] = -1;
		vibor[1] = -1;
	}
}
