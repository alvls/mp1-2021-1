//����������� ����� ����������.
//����� ������ ������� ���������� � �������.������ ����� ����������� ���������� ������� : ��������, ��������, ���������, ����������, ���� ������ � ������(����, �����, ���), �����(� ������).������ �������� ������������ �� �������� � �����.������ �������� �� ������� �����. �� ������ ����� ��������������, �� ���� ���� 2 ������ � ���������� ���������, �� ������ - ���, ��� ����� ������
//����� ������ ��������� ����������� ��������� ������.
//����� ������ ������������� ��������� �������� : 1) �������� �����, 2) �������� ������ ���������� ������, 3) ����� ����� �� �������� � ����, 4) ������ ��� ������ ��������� ���������, 5) ������ ��� ������, �������� � ������ � ��������� ����, 6) ������ �������� ����� ������� � ����������� �������, 7) ������ �������� ����� ������� � ����������� ������� � ��������� ����, 8) ������ ������� ����� �������, 9) ������� �����, 10) ��������� ���������� � ����, 11) ������� ���������� �� �����.
#include <clocale>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <string>
#include <conio.h>

#define N 11//����� ������� � ���� 
#define size 100//����� �������� ������
#define size_f_name 100//������������ ����� ���� ����������
#define name 100
using  namespace std;
class Film
{
    //string film_name;//std::
	char* film_name[name];
	char* director[name];
	char* screenwriter[name];//
	char* musician[name];//��� �����������
	int year, month, day;//���� ������
	int fees;//�����
public:
	void set_film()
	{


	}
};



void main()
{
	int i;
	//const int size=300;
	char s[size];
	//string s;//� ����� string �� �������� getline
	char tmp;
	//s = new char[30];
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::cout << "������� ������: ";
	i = 0;
	cin.getline(s, size, '\n');//���������� ������, \n - ������ ����� ������
	/*while (s[i] != '\0')
	{
		//if (s[i] == ' ')
			//s[i] = '_';
		putchar(s[i]);
		i++;
	}*///���� ���� �� �����
	//std::cout << '\n';
	std::cout <<s<<'\n';//����: 267 ���������� ������� ����

	system("pause");//strcmp (str1, str2)-��������� 2 ������
}