#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Redactor
{
private:
	char *str;
	int x, y;
	int buffer;
	int length;
public:
	Redactor()//�����������
	{
		str = new char[5];
		x = 0; y = 0;
		length = 4;
		buffer = 5;
		str[length] = '\0';
	}
	void setlength(int l)//��������� ����� ���� �����
	{
		delete[] str;
		buffer = l + 1;
		length = l;
		str = new char[buffer];
		str[length] = '\0';
	}
	int getlength()//������� ����� ���� �����
	{
		return length;
	}
	void poz(int _x, int _y)//������� ������� ���� � �������
	{
		x = _x;
		y = _y;
	}
	int retX()//������� ���������� X
	{
		return x;
	}
	int  retY()//������� ���������� Y
	{
		return y;
	}
	void read()//��������� ��������
	{
		char s;
		int i = 0;
		while (i != buffer)
		{
			s = _getch();
			switch (s) {
			case '\r':
				str[i] = '\0';
				return;
			case '\b':
				i--;
				if (i < 0)
					i++;
				else cout << "\b \b";
				break;
			default:
				if (i != length)
				{
					str[i] = s;
					cout << str[i];
					i++;
				}
			}
		}
	}
	char* line()//������� ������
	{
		return str;
	}
	~Redactor()//����������
	{
		delete [] str;
	}
};

void position(int x, int y)//����������� ������� � �������
{
	COORD position;										
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	
	position.X = x;									// ��������� ���������� X
	position.Y = y;									// ��������� ���������� Y
	SetConsoleCursorPosition(hConsole, position);
}

int menu()
{
	int a;
	cout << "�������� ���������� ��������" << endl;
	cout << "1.������ ����� ���� �����" << endl << "2.������ ����� ���� �����" << endl << "3.������ ������� ���� ����� � ���� �������" << endl << "4.������ ������� ���� ����� � ���� �������" << endl <<
		"5.������ ������ � ��������� ���������" << endl << "6.������ ��������� ������������� ������." << endl <<"0.�����" << endl;
	cin >> a;
	return a;
}

void main()
{
	SetConsoleCP(1251);//������� ���� ��� ����� � �������
	SetConsoleOutputCP(1251);
	cout << "�� ��������� ����� ���� ����� ����� 4" << endl;
	Redactor ak;
	char* str;
	int m, size=4, x=0, y=0;
p:
	m = menu();
	switch (m)
	{
	case 1://������� ����� ���� �����
		cout << "������� ����� ���� �����" << endl;
	s:
		cin >> size;
		if (size < 0)
		{
			cout << "������������ �����, ������� �����" << endl;
			goto s;
		}
		ak.setlength(size);
		cout << "�������� ������� ������" << endl;
		break;
	case 2://������� ����� ���� �����
		size = ak.getlength();
		cout << "����� ���� ����� �����: " << size << endl;
		break;
	case 3://������� ��������� ���� �����
		cout << "������� ���������� X � Y " << endl;
	l:
		cin >> x >> y;
		if ((x < 0) || (y < 0))
		{
			cout << "������������ ����������, ������� �����" << endl;
			goto l;
		}
		ak.poz(x, y);
		cout << "�������� ������� ������" << endl;
		break;
	case 4://������� ��������� ���� �����
		cout << "���������� �� X: " << ak.retX() << endl;
		cout << "���������� �� Y: " << ak.retY() << endl;
		break;
	case 5://���������� ���������� ��������� � ���� ������
		system("cls");
		position(x, y);
		ak.read();
		system("cls");
		break;
	case 6://����� �� ������� ��������� ������������� ������
		str = ak.line();
		cout << str <<endl;
		break;
	case 0://����� �� ���������
		return;
		break;
	}
	goto p;	
}