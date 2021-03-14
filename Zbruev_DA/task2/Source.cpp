#include <clocale>
#include <iostream>
#include <cmath>
#include <cstdlib>
#define N 8//����� ������� � ���� 
class Matrix
{
	int** matr;
	int size=0;//����� �����
public:
	Matrix(int razmer)//�����������
	{
		int i, j;
		size = razmer;
		matr = (int**)malloc(sizeof(int*) * size);
		for (int i = 0; i < size; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * size);
		}
		for (i = 0; i < size; i++)
		  for (j = 0; j < size; j++)
			matr[i][j] = 0;
	}
	void new_matrix(int size_new)//������ ������ �������
	{

		int i, j;
		for (i = 0; i < size; i++) {//����������� ������ ������, ����� �������� ����� (��� ���� ������ �� ���������)
			free(matr[i]);
		}
		free(matr);
		size = size_new;
		matr = (int**)malloc(sizeof(int*) * size);
		for (i = 0; i < size; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * size);
		}
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				matr[i][j] = 0;
	}
	Matrix(const Matrix &m)//����������� �����������
	{
		size = m.size;
		matr = (int**)malloc(sizeof(int*) * size);
		for (int i = 0; i < size; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * size);
		}
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				matr[i][j] = m.matr[i][j];
	}
	void setmatr(int num1, int num2, int elem)//������������� ������� �� ������
	{
		matr[num1][num2] = elem;
	}
	int getmatr(int num1, int num2)//���������� ������� �� ������
	{
		return(matr[num1][num2]);
	}
	~Matrix()//����������
	{
		for (int i = 0; i < size; ++i) {
			free(matr[i]);
		}
		free(matr);
	}
	int setsize(void)//������ ������
	{
		return(size);
	}
	bool diagonal()//�������� �� ������������ ������������
	{
		int i, j, flag;
		bool f=true;//��� ��� ���� ������� ������� �� 1 ��������, �� ���� �� ���� �� ����������, � ������� �� 1 �������� �������� ������������ ������������� 
		for (i = 0; i < size; i++)
		{
			flag = 0;
			for (j = 0; j < size; j++)//�������� � j
			{
				if (matr[i][i] >= matr[i][j])
					flag++;
				else
					break;
			}
			if (flag == size)//������������� ������ ���� size -1, �� ��������� � ����� 1 ��� ������� ������������ ��� � �����, �� ������ size
				f = true;
			else
			{
				f = false;
				break;
			}
		}
		return (f);
	}
    Matrix operator+(const Matrix& m)// ���������� ��������� "+" 
	{
		Matrix res(size);
		int i, j, elem;
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				res.matr[i][j] = this->matr[i][j] + m.matr[i][j];
			}
		return res;
	}
};

void showmenu()
{
	char* menu[N] = { "�������� ������ ���������� ������� (����� ����� ��� ��������) ", "������ ������ �������", "������ ������� ������� �� ��� ��������", "���������������� ������� ��������� (�� ������ ����� �� ��������)", "������ ������� ������� �� ��� ��������", "���������, �������� �� ������� ������������ �������������", "��������� ����� ���� ������ ������ �������", "�����" };//������ � ���������� ��������
	short int menu_number[N] = { 1, 2, 3, 4, 5, 6, 7, 0 };//������ � �������� ������� ������ ����
	int i;
	std::cout << "��������: " << '\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i] << ". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "������� ����� ��������, ������� ���������� ���������: ";
}

void full_init(Matrix& m, int size)//������� ������ ������������� ������� (��� ��������)
{
	int elem, i, j;//������������� ���������� �� �������
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			std::cout << "������� ������� � ��������� " << (i + 1) << "," << (j + 1) << "(������ ������ - ����� ������, ������ - ����� �������)" << ":";
			std::cin >> elem;
			m.setmatr(i, j, elem);
		}
	}
}
void main()
{
	int size, num1, num2, elem, number=1, i, j;
	setlocale(LC_ALL, "Russian");
	std::cout << "������� ������ ���������� ������� (����� ����� ��� ��������): ";//����� ������������ �� ����� ������ ������ �������, �� � ����� �� ��������������
	std::cin >> size;
	while (size <= 0)//�������� ��������� ������
	{
		std::cout << "����������� - ������������� ������ �������, ����������� ������: ";
		std::cin >> size;
	}
	Matrix m1(size), m2(size);
	while (number != 0)
	{
		showmenu();
		std::cin >> number;
		switch (number)
		{
		case 1:
			std::cout << "������� ������ ���������� ������� (����� ����� ��� ��������): ";
			std::cin >> size;
			while (size <= 0)//�������� ��������� ������
			{
				std::cout << "����������� - ������������� ������ �������, ����������� ������: ";
				std::cin >> size;
			}
			m1.new_matrix(size);
			m2.new_matrix(size);//������ ������ ������ �������, ����� �� ����� ���� �������������� � ������
			break;
		case 2://������ ������
			std::cout << "������ �������: "<<m1.setsize() << 'x' << m1.setsize() << '\n';
			break;
		case 3://������ ������� �� ��������
			std::cout << "������� ����� ��������(������), ��������� ���������� � 1: ";
			std::cin >> num1;
			while ((num1 <= 0) || (num1>size))//�������� ��������� ������
			{
				std::cout << "������������ ����� ������, ����������� ������: ";
				std::cin >> num1;
			}
			std::cout << "������� ����� ��������(�������), ��������� ���������� � 1: ";
			std::cin >> num2;
			while ((num2 <= 0) || (num2 > size))//�������� ��������� ������
			{
				std::cout << "������������ ����� ������, ����������� ������: ";
				std::cin >> num2;
			}
			std::cout << "������� �������: ";
			std::cin >> elem;
			m1.setmatr(num1-1, num2-1, elem);//(num1-1), ��������� ��������� ��������� ������� ���������� � 0, � � ���������� ������ ��������� ���������� � 1
			break;
		case 4://������ ������������� ������� �� �������(��� ��������)
			full_init(m1, size);
			break;
		case 5://������ ������� �� ��������
			std::cout << "������� ����� ��������, ������� ������ ������(������), ��������� ���������� � 1: ";
			std::cin >> num1;
			while ((num1 <= 0) || (num1 > size))//�������� ��������� ������
			{
				std::cout << "������������ ����� ������, ����������� ������: ";
				std::cin >> num1;
			}
			std::cout << "������� ����� ��������, ������� ������ ������(�������), ��������� ���������� � 1: ";
			std::cin >> num2;
			while ((num2 <= 0) || (num2 > size))//�������� ��������� ������
			{
				std::cout << "������������ ����� ������, ����������� ������: ";
				std::cin >> num2;
			}
			std::cout << "������� �������: "<<m1.getmatr((num1-1), (num2-1)) << '\n';
			break;
		case 6://�������� �� ������������ ������������
			if (m1.diagonal()==true)
				std::cout << "������� �������� ������������ �������������"<<'\n';
			else
				std::cout << "������� �� �������� ������������ �������������" << '\n';
			break;
		case 7://�������� ���� ������
			//��������������, ��� ������� m1 ������������ ��������������� (� ��������� ������ ��� �� �������� ���� 0), ������ ���������� ���������������� ������� m2
			std::cout << "��� ���������� �������� �������� ���� ������ ������������������ ������ ������� "<<'\n';
			full_init(m2, size);
			Matrix m=m1+m2;//������ ������ �������� ������� m2
			std::cout <<"������������ �����: "<< '\n';
			for (i = 0; i < size; i++)//����� ������������ ����� �� �����
			{
				for (j = 0; j < size; j++)
				{
					std::cout << m.getmatr(i, j) << "  ";
				}
				std::cout << '\n';
			}
			break;
		}

	}
	system("pause");
}