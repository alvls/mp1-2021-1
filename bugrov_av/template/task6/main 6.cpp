//class myships
//{
//	//� ������� ������ ������� 4 �������������� (�� ����� ������) �������, 3 ��������������, 2 �������������� � 1 ����������������
//	vector<int> y;
//	vector<int> x;
//	const int max = 10;
//	const char separator = '|';
//	bool check(int* pointer);
//public:
//	myships()
//	{
//		int tmp = -2;
//		for (int i = 0; i < max; i++)
//		{
//			x.push_back(tmp);
//			y.push_back(tmp);
//		}
//	}
//	void setxy();
//};

/*
* ����������� ������� ������� � ����������� � �� ������� ���� ������� ���.

���������� (�������).
* ������ ��� ������ (������� � ���������).
* � ������� ������ ��� ���� 10x10 ������. � ����� ���� ����� ����������� ���� �������. � ������ ����� �������� �������� ����� �������.
* � ������� ������ ������� 4 �������������� (�� ����� ������) �������, 3 ��������������, 2 �������������� � 1 ���������������� �������.
* ������������� ������� ����� ������������� ������ �� ����������� ��� ���������.
* ������� �� ����� ������������� � �������� �������. ��������� ��� ������ ������ ��������� 8 ���������� �� ������.
* ���� ������� �� ����������� ����� �������.
* ������ ��� ��������� �������.
* ������ ��� ������� �� ��������� ��������:
* �����, ����������� ���, ��������� ��������� ������ (����������).
* �������� ��������� ���������� �� ����� �����. ���� � ��������� ������ ���������� �������, �������� �������� ���������, ����� ������.
* �����, ����������� ���, ������ �� ����� ������ ����� �� ��������� ����������� ������� � ����������� ����.
* ���� �����, ����������� ���, ����� � �������, ��� �������� � ����, ����� ��������� � ���������.
* ���������� ��� �����, ��� ������ ������� ��� ������� ����������.
*/

#include "all.h"
void getxy(int& letter, int& digit)
{
	int input;
	char output;
	bool garbage;
setletter:
	do
	{
		input = _getch();
		if (224 <= input && input <= 232)
		{
			output = input;
			letter = input - 224;
			cout << output;
			garbage = false;
		}
		else
			if (192 <= input && input <= 200)
			{
				output = input;
				letter = input - 192;
				cout << output;
				garbage = false;
			}
			else
				if (234 == input)
				{
					output = input;
					letter = input - 225;
					cout << output;
					garbage = false;
				}
				else
					if (202 == input)
					{
						output = input;
						letter = input - 193;
						cout << output;
						garbage = false;
					}
					else
						garbage = true;
	} while (garbage);
setdigit:
	do
	{
		input = _getch();
	} while ((input < '1' || input>'9') && input != '\b');
	if (input == '\b')
	{
		cout << "\b \b";
		goto setletter;
	}
	else
	{
		output = input;
		cout << output;
		digit = input - '1';
	}
	do
	{
		input = _getch();
	} while (input != '0' && input != '\b' && input != 13 && input != ' ');
	if (input == '0')
	{
		cout << "0";
		digit = 9;
	}
	else
		if (input == '\b')
		{
			cout << "\b \b";
			goto setdigit;
		}
		else
			return;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color E0");
	cout << "�������� ����� ����: 1 - ���� �����, 2 - ��� ������\n";
	int input = _getch();
	while (input != '1' && input != '2')
	{
		input = _getch();
	}
	input -= '0';
	cout << input;
	input--;
	cout << "\n������� ����� �������, ����� ����������\n";
	_getch();
	game g(input);
	system("cls");
	g.play();
}
//===============================================

///����� ���� ��������� ������, �� ��������� ��������� ��� �������, ���� ������� �� ������������

//===============================================
