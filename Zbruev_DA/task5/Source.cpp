#include <fstream>
#include <clocale>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>
#define N 10//����� ������� � ���� 
using  namespace std;
struct Tovar //��������� � ����������� � ������
{
	string str_kod;//�����-��� � ���� ������ (�������� � ����� string �� ������, ��������, ��������� 0001, � int ��� ������ ��� 1 ���������)
	int kod;//�����-���
	float cost;//��������� �� �������
	float sale;//������
	string name;//������������ ������
	int num=0;//����������
};
int privedenie_koda(string char_kod)
{
	int i, kod=0, tmp=0, s=char_kod.size();
	for (i = 0; i < s; i++)
	{
		switch (char_kod[i])
		{
		case '1':
			tmp = 1;
			break;
		case '2':
			tmp = 2;
			break;
		case '3':
			tmp = 3;
			break;
		case '4':
			tmp = 4;
			break;
		case '5':
			tmp = 5;
			break;
		case '6':
			tmp = 6;
			break;
		case '7':
			tmp = 7;
			break;
		case '8':
			tmp = 8;
			break;
		case '9':
			tmp = 9;
			break;
		}
		kod = kod * 10 + tmp;
		tmp = 0;
	}
	return (kod);
}
class Sklad
{
	vector <struct Tovar> Spisok;//������ ��������� ������� ��� ����
	int size;//����� ��������� ������� �� ������ 
public:
	Sklad()
	{
		size = 0;
	}
	void setTovar(Tovar new_elem)
	{
		Spisok.push_back(new_elem);
		size++;
	}
	bool delete_tovar(string kod)//������� ����� �� ������
	{
		vector <Tovar>::iterator it;
		bool flag = false;//false - ���� ����� �� ������
		int i, num_elem;
		it = Spisok.begin();
		for (i = 0; i < size; i++)
		{
			if (Spisok[i].str_kod == kod)
			{
				flag = true;
				break;
			}
			it++;
		}
		if (flag == false)
		{
			return(flag);
		}
		Spisok.erase(it);
		size = Spisok.size();
		return (flag);
	}
	Tovar get_elem(string kod_search_elem)//������ ���������� � ������
	{
		bool flag=false;//false - ���� ����� �� ������
		int i, num_elem;
		Tovar t;
		for (i = 0; i < size; i++)
		{
			if (Spisok[i].str_kod == kod_search_elem)
			{
				flag = true;
				break;
			}
		}
		num_elem = i;
		if (flag == false)
		{
			t.kod = 0;//����� ��� =0, ���� ����� �� ������
			t.name = "0";//����� ��������� ������
			t.sale = 0;//����� ��������� ������
			t.cost = 0;//����� ��������� ������
		}
		else
		{
			t = Spisok[num_elem];
		}
		return(t);
	}
	vector <Tovar> get_all_spisok()//������ ���� ������ �������
	{
		return(Spisok);
	}
	void get_from_file(string name_of_file)//������� ������ �� �����
	{
		ifstream fin(name_of_file);
	    Tovar Temp;
		bool flag = true;
		Spisok.clear();
		while (!fin.eof())
		{
			if (flag == false)//����� �� ������ �������� ����� ��� �������� ��� ���� 
			{
				fin.get();
			}
			flag = false;
			getline(fin, Temp.name);
			fin >> Temp.str_kod;
			Temp.kod = privedenie_koda(Temp.str_kod);
			fin >> Temp.cost;
			fin >> Temp.sale;
			Spisok.push_back(Temp);
		}
		size = Spisok.size();//������ ������ ������
		fin.close();
	}
	int getsize()//������ ������� ����� ������������ ������� �� ������ 
	{
		size = Spisok.size();
		return(size);
	}
	void set_in_file(string name_of_file)//���������� ������ � ����
	{
		ofstream fout;
		fout.open(name_of_file);
		bool flag = false;
		size = Spisok.size();
		for (int i = 0; i < size; i++)
		{
			if (flag == true)//��� �����, ����� � ����� ����� �� ���� ������� �������� �������. ��� ������� �������� ��� ������������ ���������� ����� ����������� �����
			{
				fout << '\n';
			}
			flag = true;
			fout << Spisok[i].name << '\n';
			fout << Spisok[i].str_kod << '\n';
			fout << Spisok[i].cost << '\n';
			fout << Spisok[i].sale;
		}
		size = Spisok.size();
		fout.close();
	}
};
void print(Tovar T)//�������� 1 �����
{
	std::cout << "�������� ������: ";
	std::cout << T.name << '\n';
	std::cout << "���: ";
	std::cout << T.str_kod << '\n';
	std::cout << "���� ������ �� �������: ";
	printf("%.2f", T.cost);//����� ������� 2 ����� ����� �����
	std::cout << " ���" << '\n';
	std::cout << "������: ";
	std::cout << T.sale << " %" << '\n';
	std::cout << "���������� ������: ";
	std::cout << T.num << '\n';
}
void print_for_skan(Tovar T)//�� �������� �������� ���� num (���������� ������)
{
	std::cout << "�������� ������: ";
	std::cout << T.name << '\n';
	std::cout << "���: ";
	std::cout << T.str_kod << '\n';
	std::cout << "���� ������ �� �������: ";
	std::cout << T.cost << " ���" << '\n';
	std::cout << "������: ";
	std::cout << T.sale << " %" << '\n';
}
void print(vector <Tovar> S)//�������� ������ �������
{
	int size = S.size();
	for (int i = 0; i < size; i++)
	{
		print(S[i]);
	}
}
void showmenu()
{
	char* menu[N] = { "������� ������ ������� �� ����� ", "������������� ����� ","�������� ���", "���������� �������� ����� � ������", "������� ����� �� �������", 
		"������� �� ����� ���������� ��� ��� ������ �� ������","�������� ����� �� �����", "��������� ������ ������� � ����", "������� ����� �� ������", "�����" };//������ � ���������� ��������
	short int menu_number[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };//������ � �������� ������� ������ ����
	int i;
	std::cout << "��������: " << '\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i] << ". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "������� ����� ��������, ������� ���������� ���������: ";
}
Tovar proverka(Tovar t)//������ ��� kod �������� � �������� ���������, ��� ����� ������� ��������
{
	t.kod = privedenie_koda(t.str_kod);
	while (t.kod > 9999)
	{
		std::cout << "������������ �������� �����-����, ����������� ������ " << '\n';
		std::cout << "������� �����-��� (4-� ������� ����� �����): ";
		std::cin >> t.str_kod;
		t.kod = privedenie_koda(t.str_kod);
	}
	return (t);
}
class Kassa
{
	vector <Tovar> Check;//������ ��������������� ������� ��� ����
	float total_discount;//��������� ������
	float Sum;//�������� ����� � ������
	int size;//����� ������� � ����
	Sklad sklad;
public:
	void skan_tovara()//������������ ������
	{
		bool flag = false;
		Tovar t;
		string char_kod;
		t.kod = 0;
		size = Check.size();
		while (t.kod == 0)
		{
			std::cin.get();
			if (flag == true)
			{
				std::cout << "����� �� ������ �� ������. ����������� ������" << '\n';
			}
			flag = true;
			std::cout << "������� �����-��� (4-� ������� ����� �����): ";
			std::cin >> t.str_kod;
			t = proverka(t);
			t = gettovar_from_sklad(t.str_kod);
		}
		print_for_skan(t);
		t.num = get_num_elem(t.str_kod);
		t.num++;
		if (t.num == 1)
		{
			Check.push_back(t);
		}
		else
		{
			int num_elem = get_num_elem(t.str_kod);
			Check.at(num_elem) = t;
		}
		size = Check.size();
	}
	bool delete_tovar_from_check(string kod_search_elem)//������� �����
	{
		bool flag = false;//false - ���� ����� �� ������ 
		int i = 0;
		vector<Tovar>::iterator it;
		it = Check.begin();
		size = Check.size();
		while (i < size)//������� ����� ����� �������� 
		{
			if (Check[i].str_kod == kod_search_elem) 
			{
				flag = true;
				break;
			}
			i++;
			it++;
		}
		if (flag == false)
		{
			return(flag);
		}
		else
		{
			flag = true;
			Check.erase(it);
			size--;
			return (flag);
		}
	}
	int get_num_elem(string kod_search_elem)//������ ����� ��������
	{
		int i, num_elem;
		Tovar t;
		for (i = 0; i < size; i++)
		{
			if (Check[i].str_kod == kod_search_elem)
			{
				break;
			}
		}
		num_elem = i;
		return(num_elem);
	}
	float calculate_sum()//���������� ����� � ������
	{
		int i;
		float Sum = 0;
		size = Check.size();
		for (i = 0; i < size; i++)
		{
			Sum += (Check[i].cost * ((100 - Check[i].sale) / 100) * Check[i].num);
		}
		return (Sum);
	}
	void get_check()//������ ���
	{
		int i;
		size = Check.size();
		std::cout << '\n' << "���" <<'\n';
		for (i = 0; i < size; i++)
		{
			print(Check[i]);
			std::cout << '\n';
		}
		std::cout << "�������� ����� � ������: ";
		printf("%.2f", calculate_sum());//����� ������� 2 ����� ����� �����
		std::cout << " ���" << '\n';
	}
    Tovar gettovar_from_sklad(string kod)
	{
		Tovar t;
		t = sklad.get_elem(kod);
		return(t);
	}
	void menu()//���� �����
	{
		int num_operation=1;
		string char_kod;
		string name_file;
		vector <Tovar> Temp;//
		int sz;//��� ������ 6
		Tovar t;//��� ������ 7
		bool flag=false;
		bool f=false;
		while (num_operation!=0)
		{
			showmenu();
			std::cin >> num_operation;
			switch (num_operation)
			{
			case 1://������� ������ ������� �� �����
				std::cin.get();
				std::cout << "������� ��� �����, �������� ��� ���������� (�������� .txt): ";//�������� ��������
				std::getline(std::cin, name_file);
				sklad.get_from_file(name_file);
				break;
			case 2://����������� �����
				skan_tovara();
				break;
			case 3://������ ���
				get_check();
				break;
			case 4://���������� �������� �����
				std::cout << "�������� ����� � ������: " << calculate_sum() << " ���" << '\n';
				break;
			case 5://�������� ������ �� ����
				flag = false;
				do
				{
					if (flag == true)
					{
						std::cout << "����� �� ������. ����������� ������" << '\n';
					}
					std::cout << "������� �����-��� ������, ������� ������ �������: ";
					std::cin >> t.str_kod;//���-�� ����� ��������
					t = proverka(t);
					flag = true;
					f=delete_tovar_from_check(t.str_kod);
				} while (f == false);
				break;
			case 6://������� ������ ������� �� ������ �� �����
				Temp = sklad.get_all_spisok();
				sz = sklad.getsize();
				for (int i = 0; i < sz; i++)
				{
					print_for_skan(Temp[i]);
					std::cout << '\n';
				}
				break;
			case 7://������ ����� �� �����
				std::cin.get();
				std::cout << "������� �������� ������: ";//�������� ��������
				std::getline(std::cin, t.name);
				std::cout << "������� ��� (4-� ������� ����� �����): ";
				std::cin >> t.str_kod;
				t = proverka(t);
				std::cout << "������� ���� ������ �� ������� (� ������), ������� ����� �� ������ ������: ";
				std::cin >> t.cost;
				std::cout << "������� ������ (� %): ";
				std::cin >> t.sale;
				sklad.setTovar(t);
				break;
			case 8://��������� ������ ������� � ����
				std::cin.get();
				std::cout << "������� ��� �����, �������� ��� ���������� (�������� .txt): ";//�������� ��������
				std::getline(std::cin, name_file);
				sklad.set_in_file(name_file);
				break;
			case 9://������� ����� �� ������
				flag = false;
				f = false;//false-����� �� ������
				size = Check.size();
				while (f == false)
				{
					if (flag == true)
					{
						std::cout << "����� �� ������ �� ������. ����������� ������" << '\n';
					}
					flag = true;
					std::cout << "������� �����-��� (4-� ������� ����� �����): ";
					std::cin >> t.str_kod;
					t = proverka(t);
					f=sklad.delete_tovar(t.str_kod);
				}
				break;
			}
		}
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Kassa kassa;
	kassa.menu();
	system("pause");
}