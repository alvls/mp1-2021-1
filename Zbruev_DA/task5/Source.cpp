//����� ����� ������ ������������� ��������� �������� : 1) ������������� ��������� �����, 
//2) �������� �������� ������ �� ������, 3) �������� ������ � ������ � ���, 4) ������������ ��� �� �������,
//5) ���������� �������� ����� � ������, 6) ������� ��������� ����� �� �������. ����� ��������������� � �������������
//�������� ������, ����������, �������� �� ������
#include <fstream>
#include <clocale>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>
#define N 13//����� ������� � ���� 
using  namespace std;
struct Tovar //��������� � ����������� � ������
{
	int kod;//�����-���
	float cost_unit;//��������� �� �������
	float sale;
	string tovar_name;//������������ ������
};

class Sklad
{
	vector <struct Tovar> Spisok;//������ ��������� ������� ��� ����
	int size;//����� ��������� ������� �� ������ 
public:
	Sklad()
	{
		size = 0;
	}
	void setTovar(struct Tovar new_elem)
	{
		Spisok.push_back(new_elem);
		size++;
	}
	void delete_tovar(string new_elem)
	{
		if (size == 1)//���� ������ ���� ����� �� ������
		{
			Spisok.clear();
			size = 0;
		}
		else//���� �� ������ ��������� �������
		{
			int i, num_elem;;
			for (i = 0; i < size; i++)
			{
				if (Spisok[i].tovar_name == new_elem)
					break;
			}
			num_elem = i;
			swap(Spisok[num_elem], Spisok.back());
			Spisok.pop_back();
			size--;
		}
	}
	int get_size()//������ ������� ����� ������������ ������� �� ������ (��������, �������) 
	{
		size = Spisok.size();
		return (size);
	}
	vector <struct Tovar> get_all_spisok()//������ ���� ������
	{
		return(Spisok);
	}
	~Sklad()//����������
	{
		Spisok.clear();
	}
};

class Kassa
{
	vector <struct Tovar> Check;//������ ��������������� ������� ��� ����
	float total_discount;//��������� ������
	float Sum;//�������� ����� � ������
	int size;//����� ������� � ����
public:

};

void main()
{
	int i;
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);





	system("pause");
}