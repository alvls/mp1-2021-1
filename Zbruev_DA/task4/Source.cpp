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
struct Film
{
	string film_name;//�������� ���� ������ ������ �������������������� ����� 
	string director;//��������
	string screenwriter;//����� ��������
	string musician;//��� �����������
	int year, month, day;//���� ������
	int fees;//�����
};
class Filmoteka
{
	int size;//����� ������� � ����������
	std::vector<Film> F;
public:
	Filmoteka(int razmer)
	{
		size = razmer;
	}
	void set_in_file(string name_of_file)//���������� ���������� � ����
	{
		ofstream fout;
		fout.open(name_of_file);
		size = F.size();
		for (int i = 0; i < size; i++)
		{
			fout << F[i].film_name << '\n';
			fout << F[i].director << '\n';
			fout << F[i].screenwriter << '\n';
			fout << F[i].musician << '\n';
			fout << F[i].day << '\n';
			fout << F[i].month << '\n';
			fout << F[i].year << '\n';
			fout << F[i].fees << '\n';
		}
		size = F.size();
		fout.close();
	}
	void get_from_file(string name_of_file)
	{
		ifstream fin(name_of_file);
		struct Film Temp;
		bool flag=true;
		F.clear();
		while (!fin.eof())
		{
			if (flag == false)//����� �� ������ �������� ����� ��� �������� ��� ���� 
			{
				fin.get();
			}
			flag = false;
			getline(fin, Temp.film_name);
			getline(fin, Temp.director);
			getline(fin, Temp.screenwriter);
			getline(fin, Temp.musician);
			fin >> Temp.day;
			fin >> Temp.month;
			fin >> Temp.year;
			fin >> Temp.fees;
			F.push_back(Temp);
		}
		size = F.size();//������ ������ ����������
		fin.close();
	}
	bool delete_film(string name, int year)//������� �����
	{
		bool flag=false;//false - ���� ������ �� ������� 
		int i = 0;
		vector<Film>::iterator it;
		it = F.begin();
		while (i < size)//������� ����� ����� �������� 
		{
			if ((F[i].film_name == name) && (F[i].year == year))
			{
				it++;
				flag = true;
				break;
			}
			i++;
		}
		if (flag == false)
		{
			return(flag);
		}
		F.erase(it);
		size = F.size();
		return (flag);
	}
	void setfilm(Film Temp)//�������� �����
	{
		int i;
		if (F.empty() == true)// ���� ������ ��� ����
		{
			size++;
			F.push_back(Temp);
		}
		else {
			std::vector<Film> TMP;
			i = 0;
			while ((F[i].film_name > Temp.film_name) && (i < size))//������� ����� ����� ��������    (s[i] >temp)
			{
				i++;
			}
			int tmp_num;//==i
			while ((F[i].film_name == Temp.film_name) && (i < size))//���������� ������� ��� ������ ����� �� ����
			{
				if (F[i].year > Temp.year)
				{
					break;
				}
				i++;
			}
			tmp_num = i;//����� �����, � ������� ���������� ��������� ����� ������� Temp 
			size++;
			for (i = 0; i < tmp_num; i++)//��������� � tmp ��� ����� ������� F �� ������ tmp_num
			{
				TMP.push_back(F[i]);// = F[i];
			}
			TMP.push_back(Temp);
			for (i = tmp_num + 1; i < size; i++)//��������� � tmp ��� ����� ������� F ����� ������ tmp_num
			{
				TMP.push_back(F[i - 1]);
			}
			F.clear();//����� ������ ������ F � ������������ � ���� ��� �������� tmp
			for (i = 0; i < size; i++)
			{
				F.push_back(TMP[i]);
			}
			TMP.clear();//������� ������ ���������� ������� �� ������ ��������
		}
	}
	vector <Film> get_films_of_director(string director)//������ ��� ������ ��������� ���������
	{
		int i;
		std::vector<Film> TMP;
		bool flag = false;//false-�� ����� �����, true-�����
		Film Temp;
		for (i = 0; i < size; i++)//���� ��� ���������� �������� � ���������� �� � TMP
		{
			if (F[i].director == director)
			{
				flag = true;
				TMP.push_back(F[i]);
			}
		}
		if (flag == false)
		{
			Temp.year = 0;//���� ����� �� ������, �� ��� ������ � ������ ����� 0
			Temp.film_name = "0";//����� ��������� �������
			Temp.director = "0";//����� ��������� �������
			Temp.screenwriter = "0";//����� ��������� �������
			Temp.musician = "0";//����� ��������� �������
			TMP.push_back(Temp);
		}
		return(TMP);
		TMP.clear();
	}
	vector <Film> get_films_in_year(int year)
	{
		int i;
		std::vector<Film> TMP;
		Film Temp;
		bool flag = false;//false-�� ����� �����, true-�����
		for (i = 0; i < size; i++)//���� ��� ���������� �������� � ���������� �� � TMP
		{
			if (F[i].year == year)
			{
				flag = true;
				TMP.push_back(F[i]);
			}
		}
		if (flag == false)
		{
			Temp.year = 0;//���� ����� �� ������, �� ��� ������ � ������ ����� 0
			Temp.film_name = "0";//����� ��������� �������
			Temp.director = "0";//����� ��������� �������
			Temp.screenwriter = "0";//����� ��������� �������
			Temp.musician = "0";//����� ��������� �������
			TMP.push_back(Temp);
		}
		return(TMP);
		TMP.clear();
	}
	Film find_film_by_name_and_year(string name, int year)//����� ����� �� �������� � ����
	{
		int i;
		bool flag = false;//false-�� ����� �����, true-�����
	    Film film;
		for (i = 0; i < size; i++)//���� ���������� ������� � ���������� ��� � film
		{
			if ((F[i].year == year)&&(F[i].film_name==name))
			{
				film= F[i];
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			film.year = 0;//���� ����� �� ������, �� ��� ������ � ������ ����� 0
			film.film_name = "0";//����� ��������� �������
			film.director = "0";//����� ��������� �������
			film.screenwriter = "0";//����� ��������� �������
			film.musician = "0";//����� ��������� �������
		}
		return(film);
	}
	vector <Film> get_films_with_max_fees(int num_films_with_max_fees)
	{
		int i, size_copy = size, j, max_fees, elem_num;//elem_num-����� �������� ��������
		std::vector<Film> COPY;//COPY-����� ������� F  
		std::vector<Film> MAX_FEES;//������ ������� �������
		COPY = F;
		for (i = 0; i < num_films_with_max_fees; i++)//   while (MAX_FEES.size() < num_films_with_max_fees)
		{
			max_fees = 0;
			size_copy = COPY.size();
			for (j = 0; j < size_copy; j++)//���� ������� � ������������� ������� 
			{
				if (COPY[j].fees > max_fees)//>
				{
					max_fees = COPY[j].fees;
				}
			}//����� �������� ��������
			for (j = 0; j < size_copy; j++)//������� ����� ����� �������� 
			{
				if (COPY[j].fees == max_fees)
				{
					break;
				}
				j++;
			}
			elem_num = j;
			MAX_FEES.push_back(COPY[elem_num]);//���������� ��������� ������� � ������ ������� �������
			swap(COPY[elem_num], COPY.back());//������� �� COPY ������� � ������� elem_num, ����� �� ��� ����� ��������� ������� COPY (������� ������� � COPY ��� �������)
			COPY.pop_back();
		}
		COPY.clear();
		return(MAX_FEES);
		MAX_FEES.clear();

	}
	vector <Film> get_films_with_max_fees_in_year(int num_films_with_max_fees, int year)
	{
		int i, size_copy, j, max_fees, elem_num, size_copy_fix;
		std::vector<Film> COPY;//COPY-����� ������� F  
		std::vector<Film> MAX_FEES;//������ ������� �������
		Film Temp;
		bool flag = false;//false-�� ����� �����, true-�����
		for (i = 0; i < size; i++)//�������� ������ COPY 
		{
			if (F[i].year == year)
			{
				flag = true;
				COPY.push_back(F[i]);
			}
		}
		if (flag == false)
		{
			Temp.year = 0;//���� ����� �� ������, �� ��� ������ � ������ ����� 0
			Temp.film_name = "0";//����� ��������� �������
			Temp.director = "0";//����� ��������� �������
			Temp.screenwriter = "0";//����� ��������� �������
			Temp.musician = "0";//����� ��������� �������
			MAX_FEES.push_back(Temp);
			return (MAX_FEES);
			MAX_FEES.clear();
		}
		else
		{

			size_copy = COPY.size();
			size_copy_fix = size_copy;
			for (i = 0; i < num_films_with_max_fees; i++)
			{
				if (i >= size_copy)
					break;
				max_fees = 0;
				size_copy = COPY.size();
				for (j = 0; j < size_copy; j++)//���� ������� � ������������� �������
				{
					if (COPY[j].fees > max_fees)//>
					{
						max_fees = COPY[j].fees;
					}
				}//����� �������� ��������
				for (j = 0; j < size_copy; j++)//������� ����� ����� �������� 
				{
					if (COPY[j].fees == max_fees)
					{
						break;
					}
					j++;
				}
				elem_num = j;
				MAX_FEES.push_back(COPY[elem_num]);//���������� ��������� ������� � ������ ������� ������� 
				swap(COPY[elem_num], COPY.back());//������� �� COPY ������� � ������� elem_num, ����� �� ��� ����� ��������� ������� COPY (������� ������� � COPY ��� �������)
				COPY.pop_back();
			}
			COPY.clear();
			return(MAX_FEES);
			MAX_FEES.clear();
		}
	}
	vector <Film> get_all_films()//������ ��� ������
	{
		return(F);
	}
	int get_size()//������ ������� ����� �������
	{
		size = F.size();
		return (size);
	}
};
void print(Film F)//�������� 1 �����
{
	std::cout << "�������� ������: ";
	std::cout << F.film_name << '\n';
	std::cout << "��� ���������: ";
	std::cout << F.director << '\n';
	std::cout << "��� ����������: ";
	std::cout << F.screenwriter << '\n';
	std::cout << "��� �����������: ";
	std::cout << F.musician << '\n';
	std::cout << "���� ������ � ������: ";
	std::cout << F.day<<"."<<F.month<<"."<<F.year << '\n';
	std::cout << "�����: "<< F.fees << " ���" << '\n' << '\n'; ;
}
void print(vector <Film> F)//�������� ������ �������
{
	int size = F.size();
	for (int i = 0; i < size; i++)
	{
		print(F[i]);
	}
}
void showmenu()
{
	char* menu[N] = { "�������� ����� ", "�������� ������ ���������� ������", "����� ����� �� �������� � ����", "������ ��� ������ ��������� ���������", "������ ��� ������, �������� � ������ � ��������� ����", 
		"������ �������� ����� ������� � ����������� �������", "������ �������� ����� ������� � ����������� ������� � ��������� ����", 
		"������ ������� ����� �������", "������� �����", "��������� ���������� � ����", "������� ���������� �� �����", "������� �� ����� ��� ������ ", "�����"};//������ � ���������� ��������
	short int menu_number[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0 };//������ � �������� ������� ������ ����
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
	int i, num = 1, size = 0, num_films_with_max_fees, num_operation = 1, film_num;//num - ����� �������� � ������� ����� ���������;  num_operation - ����� �������� (����� ��� 2 ������); film_num - ����� ������ � ����������, ����� ��� 2 ������
	class Filmoteka Filmoteka1(size);
	bool flag = false;//����� ��� 3 ������
	bool f=false;//����� ��� 9 ������
	Film Temp, film;//film-����� ��� 3 ������
	string name_of_file;
	vector <Film> F;//������, � ������� ������������ ������ ��� ������ ������� ������ 
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	i = 0;
	while (num != 0)
	{
		showmenu();
		std::cin >> num;
		if (num == 0)
			break;
		switch (num)
		{
		case 1://�������� �����
			std::cin.get();
			std::cout << "������� �������� ������: "; 
			std::getline(std::cin, Temp.film_name);
			std::cout << "������� ��� ���������: "; 
			std::getline(std::cin, Temp.director);
			std::cout << "������� ��� ����������: ";
			std::getline(std::cin, Temp.screenwriter);
			std::cout << "������� ��� �����������: ";
			std::getline(std::cin, Temp.musician);
			std::cout << "������� ���� ������ � ������: ";
			std::cin >> Temp.day;
			std::cout << "������� ����� ������ � ������: ";
			std::cin >> Temp.month;
			std::cout << "������� ��� ������ � ������: ";
			std::cin >> Temp.year;
			std::cout << "������� �������� ����� ������: ";
			std::cin >> Temp.fees;
			Filmoteka1.setfilm(Temp);
			break;
		case 2://�������� ������ ������
			flag = false;
			do {
				std::cin.get();
				if (flag == true)
				{
					std::cout << "����� �� ������. ����������� ������" << '\n';
				}
				std::cout << "������� �������� ������, ������� ���������� ��������: ";
				std::getline(std::cin, Temp.film_name);
				std::cout << "������� ��� ������ � ������: ";
				std::cin >> Temp.year;//��� ����� ����� ����� � ��������� ��� Temp
				flag = true;
				Temp = Filmoteka1.find_film_by_name_and_year(Temp.film_name, Temp.year);
			} while (Temp.year == 0);
			Filmoteka1.delete_film(Temp.film_name, Temp.year);
			while (num_operation!=0)
			{
				std::cout << "������� 0, ���� ������ ��������� �����" << '\n';
				std::cout << "������� 1, ���� ������ �������� �������� ������" << '\n';
				std::cout << "������� 2, ���� ������ �������� ��� ���������" << '\n';
				std::cout << "������� 3, ���� ������ �������� ��� ����������" << '\n';
				std::cout << "������� 4, ���� ������ �������� ��� �����������" << '\n';
				std::cout << "������� 5, ���� ������ �������� ���� ������ � ������" << '\n';
				std::cout << "������� 6, ���� ������ �������� ���� ����� � ������" << '\n';
				std::cin >> num_operation;
				switch (num_operation)
				{
				case 1:
					std::cin.get();
					std::cout << "������� ���������� �������� ������: ";
					std::getline(std::cin, Temp.film_name);
					break;
				case 2:
					std::cin.get();
					std::cout << "������� ���������� ��� ���������: ";
					std::getline(std::cin, Temp.director);
					break;
				case 3:
					std::cin.get();
					std::cout << "������� ���������� ��� ����������: ";
					std::getline(std::cin, Temp.screenwriter);
					break;
				case 4:
					std::cin.get();
					std::cout << "������� ���������� ��� �����������: ";
					std::getline(std::cin, Temp.musician);
					break;
				case 5:
					std::cout << "������� ���������� ����� ���: ";
					std::cin >> Temp.day;
					std::cout << "������� ���������� ����� ������: ";
					std::cin >> Temp.month;
					std::cout << "������� ���������� ���: ";
					std::cin >> Temp.year;
					break;
				case 6:
					std::cout << "������� ���������� ����� �������� ������ (� ������): ";
					std::cin >> Temp.fees;
				}
			}
			Filmoteka1.setfilm(Temp);
			break;
		case 3://����� ����� �� �������� � ����
			flag = false;
			do {
				std::cin.get();
				if (flag == true)
				{
					std::cout << "����� �� ������. ����������� ������" << '\n';
				}
				std::cout << "������� �������� ������, ������� ������ �����: ";
				std::getline(std::cin, Temp.film_name);
				std::cout << "������� ��� ������, ������� ������ �����: ";
				std::cin >> Temp.year;
				flag = true;
				film = Filmoteka1.find_film_by_name_and_year(Temp.film_name, Temp.year);
			} while (film.year == 0);
			print(film);
			break;
		case 4://������ ��� ������ ��������� ��������� 
			F.clear();
			flag = false;
			std::cin.get();
			do {
				if (flag == true)
				{
					std::cout << "�� ���� ����� �� ������. ����������� ������" << '\n';
				}
				std::cout << "������� ��� ���������: ";
				std::getline(std::cin, Temp.director);
				flag = true;
				F = Filmoteka1.get_films_of_director(Temp.director);
			} while (F[0].year == 0);
			print(F);
			break;
		case 5://������ ��� ������, �������� � ������ � ��������� ����
			F.clear();
			flag = false;
			do {
				if (flag == true)
				{
					std::cout << "�� ���� ����� �� ������. ����������� ������" << '\n';
				}
				std::cout << "������� ��� ������ ������ � ������: ";
				std::cin >> Temp.year;
				flag = true;
				F = Filmoteka1.get_films_in_year(Temp.year);
			} while (F[0].year == 0);
			print(F);
			break;
		case 6: //������ �������� ����� ������� � max �������
			F.clear();
			std::cout << "������� ����� ������� � ������������� �������: ";
			std::cin >> num_films_with_max_fees;
			F = Filmoteka1.get_films_with_max_fees(num_films_with_max_fees);
			print(F);
			break;
		case 7://������ �������� ����� ������� � max ������� � ��������� ����
			F.clear();
			int year;
			flag = false;
			do {
				if (flag == true)
				{
					std::cout << "�� ���� ����� �� ������. ����������� ������" << '\n';
				}
				std::cout << "������� ����� ������� � ������������� �������: ";
				std::cin >> num_films_with_max_fees;
				std::cout << "������� ���, �� ������� ������ �������� ������: ";
				std::cin >> year;
				flag = true;
				F = Filmoteka1.get_films_with_max_fees_in_year(num_films_with_max_fees, year);
			} while (F[0].year == 0);
			print(F);
			break;
		case 8: //������ ������
			size = Filmoteka1.get_size();
			std::cout << "������� ����� �������: " << size<<'\n';
			break;
		case 9://������� �����
			do {
				std::cin.get();
				if (flag == true)
				{
					std::cout << "����� �� ������. ����������� ������" << '\n';
				}
				std::cout << "������� �������� ������, ������� ������ �������: ";
				std::getline(std::cin, Temp.film_name);
				std::cout << "������� ��� ������, ������� ������ �������: ";
				std::cin >> Temp.year;//���������� ���� ��������� Temp, ����� �� �������� ������ ��� ������ � ��������� ������ � ����� ���� int - ���
				flag = true;
				f=Filmoteka1.delete_film(Temp.film_name, Temp.year);
			} while (f == false);
			break;
		case 10://��������� ���������� � ����
			std::cin.get();
			std::cout << "������� ��� �����, �������� ��� ���������� (�������� .txt): "; 
			std::getline(std::cin, name_of_file);
			Filmoteka1.set_in_file(name_of_file);
			break;
		case 11://��������� ���������� � ����
			std::cin.get();
			std::cout << "������� ��� �����, �������� ��� ���������� (�������� .txt): "; 
			std::getline(std::cin, name_of_file);
			Filmoteka1.get_from_file(name_of_file);
			break;
		case 12://������� �� ����� ��� ������
			F.clear();
			F = Filmoteka1.get_all_films();
			print(F);
			break;
		}
	}
	F.clear();
	system("pause");
}