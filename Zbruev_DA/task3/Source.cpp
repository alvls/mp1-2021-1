#include <clocale>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#define N 7//����� ������� � ���� 
class Text_editor
{
	char* str;
	int size = 0;//����� ���� �����
	int num_whitespace = 0;//����� �������� (�����������)
	int indent_line = 0;//���������
public:
	Text_editor(int razmer)//�����������
	{
		size = razmer;
		str = new char[size + 1];//����� �������� \0 � �����
		str[size] = '\0';//����� � ����� ������ ������ ����� ������ ����� ������
	}
	void setvvod(int size_new)//�������� ����� ���� �����
	{
		int i;
		delete[] str;
		size = size_new;
		str = new char[size + 1];
		str[size] = '\0';//����� � ����� ������ ������ ����� ������ ����� ������
	}
	
	void setpozition(int num_line, int num_ws)//��������� ��������� ���� �����
	{
		num_whitespace = num_ws;//����� �������� (�����������)
		indent_line = num_line;//���������
	}
	void setstr()//�������������� ������
	{

		system("cls");
		std::cout << "������� ������: ";
		indent_line++;
		set_cursor();
		std::cin >> str;
		indent_line--;
	}

	int getsize()//������ ����� ���� �����
	{
		return(size);
	}
	int get_indent_line_pos()//������ ��������� ���� �����
	{
		return(indent_line);
	}
	int get_whitespace_pos()//������ ��������� ���� �����
	{
		return(num_whitespace);
	}
	void getstr()//������ ������
	{
		system("cls");
		indent_line++;
		std::cout << "������: ";
		set_cursor();
		puts(str);
		std::cout << '\n';
		indent_line--;
	}
	void set_cursor()
	{
		COORD position;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		position.X= num_whitespace;
		position.Y= indent_line;
		SetConsoleCursorPosition(hConsole, position);
	}
	~Text_editor()//����������
	{
		delete[] str;
	}
};
void showmenu()
{
	char* menu[N] = { "������ ����� ���� ����� ", "������ ����� ���� ����� ", "������ ������� ���� ����� � ���� �������", "������ ������� ���� ����� � ���� �������", "���������� ���� ������������� ������ � ������ �� ������ ����� ���� �����", "������� ��������� ������������� ������", "�����" };//������ � ���������� ��������
	short int menu_number[N] = { 1, 2, 3, 4, 5, 6, 0 };//������ � �������� ������� ������ ����
	int i;
	std::cout << "��������: " << '\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i] << ". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "������� ����� ��������, ������� ���������� ���������: ";
}
void main()
{
	int size, number = 1, num_line, num_ws;
	char* s;
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::cout << "������� ����� ���� �����: ";//��� ������ ������������
	std::cin >> size;
	while (size <= 0)//�������� ��������� ������
	{
		std::cout << "����������� - ������������� ������ ���� �����, ����������� ������: ";
		std::cin >> size;
	}
	Text_editor t(size);
	s = new char[size + 1];
	while (number != 0)
	{
		showmenu();
		std::cin >> number;
		switch (number)
		{
		case 1://������ ������ ���� �����
			std::cout << "������� ������ ���� �����: ";
			std::cin >> size;
			while (size <= 0)//�������� ��������� ������
			{
				std::cout << "����������� - ������������� ������ ���� �����, ����������� ������: ";
				std::cin >> size;
			}
			t.setvvod(size);
			delete[] s;
			s = new char[size + 1];
			s[size] = '\0';
			break;
		case 2://������ ������
			std::cout << "������ ���� �����: " << t.getsize() << " ��������" << '\n';
			break;
		case 3://������ ������� ���� ����� � ���� �������
			std::cout << "������� �������� ���� ����� �� ���������: ";
			std::cin >> num_line;
			std::cout << "������� �������� ���� ����� �� �����������: ";
			std::cin >> num_ws;
			t.setpozition(num_line, num_ws);
			break;
		case 4://������ ������� ���� ����� � ���� �������
			std::cout << "�������� ���� ����� �� ���������: " << t.get_indent_line_pos() << " �����";
			std::cout << "�������� ���� ����� �� �����������: " << t.get_whitespace_pos() << " ��������";
			break;
		case 5://���� ������ �������������
			
			t.setstr();
			break;
		case 6://����� ������ �� �����
			t.getstr();
		}
	}
	delete[] s;
	system("pause");
}