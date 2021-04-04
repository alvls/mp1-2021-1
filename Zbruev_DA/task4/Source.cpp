#include <fstream>
#include <clocale>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>
#define N 13//число пунктов в меню 
using  namespace std;
struct Film
{
	string film_name;//проблема была скорее всегов неинициализированных полях 
	string director;//режиссер
	string screenwriter;//автор сценария
	string musician;//имя композитора
	int year, month, day;//дата выхода
	int fees;//сборы
};
class Filmoteka
{
	int size;//число фильмов в фильмотеке
	std::vector<struct Film> F;
public:
	Filmoteka(int razmer)
	{
		size = razmer;
	}
	void set_in_file(string name_of_file)//записываем фильмотеку в файл
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
			if (flag == false)//чтобы на первой итерации цикла все работало как надо 
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
		size = F.size();//меняем размер фильмотеки
		fin.close();
	}
	void delete_film(string name, int year)//удалить фильм
	{
		int i = 0, delete_num;
		std::vector<struct Film> TMP;
		while (i < size)//находим номер этого элемента 
		{
			if ((F[i].film_name == name) && (F[i].year == year))
			{
				break;
			}
			i++;
		}
		delete_num = i;
		size--;//уменьшаем на 1 размер
		for (i = 0; i < delete_num; i++)//переносим в tmp все члены массива F ДО номера tmp_num
		{
			TMP.push_back(F[i]);// = F[i];
		}
		for (i = delete_num + 1; i < size; i++)//переносим в tmp все члены массива F ПОСЛЕ номера tmp_num
		{
			TMP.push_back(F[i - 1]);
		}
		F.clear();//затем чистим массив F и перекатываем в него все элементы tmp
		for (i = 0; i < size; i++)
		{
			F.push_back(TMP[i]);
		}
		TMP.clear();//очищаем память временного массива
	}
	void setfilm(struct Film Temp)//добавить фильм
	{
		int i;
		if (F.empty() == true)// если вектор еще пуст
		{
			size++;
			F.push_back(Temp);
		}
		else {
			std::vector<struct Film> TMP;
			i = 0;
			while ((F[i].film_name > Temp.film_name) && (i < size))//находим номер этого элемента    (s[i] >temp)
			{
				i++;
			}
			int tmp_num;//==i
			while ((F[i].film_name == Temp.film_name) && (i < size))//вычисление позиции для равных строк по году
			{
				if (F[i].year > Temp.year)
				{
					break;
				}
				i++;
			}
			tmp_num = i;//нашли место, в которое необходимо поставить новый элемент Temp 
			size++;
			for (i = 0; i < tmp_num; i++)//переносим в tmp все члены массива F ДО номера tmp_num
			{
				TMP.push_back(F[i]);// = F[i];
			}
			TMP.push_back(Temp);
			for (i = tmp_num + 1; i < size; i++)//переносим в tmp все члены массива F ПОСЛЕ номера tmp_num
			{
				TMP.push_back(F[i - 1]);
			}
			F.clear();//затем чистим массив F и перекатываем в него все элементы tmp
			for (i = 0; i < size; i++)
			{
				F.push_back(TMP[i]);
			}
			TMP.clear();//очищаем память временного массива на каждой итерации
		}
	}
	vector <struct Film> get_films_of_director(string director)//выдать все фильмы заданного режиссера
	{
		int i;
		std::vector<struct Film> TMP;
		for (i = 0; i < size; i++)//ищем все подходящие элементы и записываем их в TMP
		{
			if (F[i].director == director)
			{
				TMP.push_back(F[i]);
			}
		}
		return(TMP);
		TMP.clear();
	}
	vector <struct Film> get_films_in_year(int year)
	{
		int i;
		std::vector<struct Film> TMP;
		for (i = 0; i < size; i++)//ищем все подходящие элементы и записываем их в TMP
		{
			if (F[i].year == year)
			{
				TMP.push_back(F[i]);
			}
		}
		return(TMP);
		TMP.clear();
	}
	struct Film find_film_by_name_and_year(string name, int year)//найти фильм по названию и году
	{
		int i;
		struct Film film;
		for (i = 0; i < size; i++)//ищем подходящий элемент и записываем его в film
		{
			if ((F[i].year == year)&&(F[i].film_name==name))
			{
				film= F[i];
				break;
			}
		}
		return(film);
	}
	vector <struct Film> get_films_with_max_fees(int num_films_with_max_fees)
	{
		int i, size_copy = size, j, max_fees, elem_num;//elem_num-номер искомого элемента
		std::vector<struct Film> COPY;//COPY-копия массива F  
		std::vector<struct Film> MAX_FEES;//массив искомых фильмов
		COPY = F;
		for (i = 0; i < num_films_with_max_fees; i++)//   while (MAX_FEES.size() < num_films_with_max_fees)
		{
			max_fees = 0;
			size_copy = COPY.size();
			for (j = 0; j < size_copy; j++)//ищем элемент с максимальными сборами 
			{
				if (COPY[j].fees > max_fees)//>
				{
					max_fees = COPY[j].fees;
				}
			}//нашли значение элемента
			for (j = 0; j < size_copy; j++)//находим номер этого элемента 
			{
				if (COPY[j].fees == max_fees)
				{
					break;
				}
				j++;
			}
			elem_num = j;
			MAX_FEES.push_back(COPY[elem_num]);//записываем найденный элемент в массив искомых фильмов
			swap(COPY[elem_num], COPY.back());//удаляем из COPY элемент с номером elem_num, ставя на его место последний элемент COPY (порядок фильмов в COPY нам неважен)
			COPY.pop_back();
		}
		COPY.clear();
		return(MAX_FEES);
		MAX_FEES.clear();

	}
	vector <struct Film> get_films_with_max_fees_in_year(int num_films_with_max_fees, int year)
	{
		int i, size_copy, j, max_fees, elem_num;
		std::vector<struct Film> COPY;//COPY-копия массива F  
		std::vector<struct Film> MAX_FEES;//массив искомых фильмов
		for (i = 0; i < size; i++)//заполняе массив COPY 
		{
			if (F[i].year == year)
				COPY.push_back(F[i]);
		}
		size_copy = COPY.size();
		for (i = 0; i < num_films_with_max_fees; i++)//
		{
			max_fees = 0;
			size_copy = COPY.size();
			for (j = 0; j < size_copy; j++)//ищем элемент с максимальными сборами
			{
				if (COPY[j].fees > max_fees)//>
				{
					max_fees = COPY[j].fees;
				}
			}//нашли значение элемента
			for (j = 0; j < size_copy; j++)//находим номер этого элемента 
			{
				if (COPY[j].fees == max_fees)
				{
					break;
				}
				j++;
			}
			elem_num = j;
			MAX_FEES.push_back(COPY[elem_num]);//записываем найденный элемент в массив искомых фильмов 
			swap(COPY[elem_num], COPY.back());//удаляем из COPY элемент с номером elem_num, ставя на его место последний элемент COPY (порядок фильмов в COPY нам неважен)
			COPY.pop_back();
		}
		COPY.clear();
		return(MAX_FEES);
		MAX_FEES.clear();

	}
	int search_num_of_film(struct Film Temp)//найти номер элемента в массиве (нужно для реализации 2 пункта в main)
	{
		int film_num, i=0;
		while ((F[i].film_name == Temp.film_name) && (i < size))
		{
			if (F[i].year > Temp.year)
			{
				break;
			}
			i++;
		}
		film_num = i;
		return(film_num);
	}
	void change_data_film(struct Film Temp, int film_num)
	{
		F.push_back(Temp);//добавляем в конец исправленный фильм
		swap(F[film_num], F.back());//меняем его местами с предыдущей версией
		F.pop_back();//затираем предыдущую версию
	}
	vector <struct Film> get_all_films()//выдать все фильмы
	{
		return(F);
	}
	int get_size()//узнать текущее число фильмов
	{
		size = F.size();
		return (size);
	}
	~Filmoteka()//деструктор
	{
		F.clear();
	}
};
void print(struct Film F)//печатает 1 фильм
{
	std::cout << "Название фильма: ";
	std::cout << F.film_name << '\n';
	std::cout << "Имя режиссера: ";
	std::cout << F.director << '\n';
	std::cout << "Имя сценариста: ";
	std::cout << F.screenwriter << '\n';
	std::cout << "Имя композитора: ";
	std::cout << F.musician << '\n';
	std::cout << "Дата выхода в прокат: ";
	std::cout << F.day<<"."<<F.month<<"."<<F.year << '\n';
	std::cout << "сборы: "<< " руб";
	std::cout << F.fees << '\n' << '\n'; 
}
void print(vector <struct Film> F)//печатает вектор фильмов
{
	int size = F.size();
	for (int i = 0; i < size; i++)
	{
		print(F[i]);
	}
}
void showmenu()
{
	char* menu[N] = { "Добавить фильм ", "Изменить данные выбранного фильма", "Найти фильм по названию и году", "Выдать все фильмы заданного режиссера", "Выдать все фильмы, вышедшие в прокат в выбранном году", 
		"Выдать заданное число фильмов с наибольшими сборами", "Выдать заданное число фильмов с наибольшими сборами в выбранном году", 
		"Узнать текущее число фильмов", "Удалить фильм", "Сохранить фильмотеку в файл", "Считать фильмотеку из файла", "Вывести на экран все фильмы ", "Выход"};//массив с названиями операций
	short int menu_number[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0 };//массив с номерами каждого пункта меню
	int i;
	std::cout << "Операции: " << '\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i] << ". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "Введите номер операции, которую необходимо выполнить: ";
}
void main()
{
	int i, num = 1, size = 0, num_films_with_max_fees, num_operation = 1, film_num;//num - номер операции в главном цикле программы;  num_operation - номер операции (нужен для 2 режима); film_num - номер фильма в фильмотеке, нужен для 2 режима
	class Filmoteka Filmoteka1(size);
	struct Film Temp, film;//film-нужен для 3 режима
	string name_of_file;
	vector <struct Film> F;//массив, в который записываются фильмы при помощи методов класса 
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
		case 1://добавить фильм
			std::cin.get();
			std::cout << "Введите название фильма: "; 
			std::getline(std::cin, Temp.film_name);
			std::cout << "Введите имя режиссера: "; 
			std::getline(std::cin, Temp.director);
			std::cout << "Введите имя сценариста: ";
			std::getline(std::cin, Temp.screenwriter);
			std::cout << "Введите имя композитора: ";
			std::getline(std::cin, Temp.musician);
			std::cout << "Введите день выхода в прокат: ";
			std::cin >> Temp.day;
			std::cout << "Введите месяц выхода в прокат: ";
			std::cin >> Temp.month;
			std::cout << "Введите год выхода в прокат: ";
			std::cin >> Temp.year;
			std::cout << "Введите кассовые сборы фильма: ";
			std::cin >> Temp.fees;
			Filmoteka1.setfilm(Temp);
			break;
		case 2://изменить данные фильма
			std::cin.get();
			std::cout << "Введите название фильма, который необходимо изменить: ";
			std::getline(std::cin, Temp.film_name);
			std::cout << "Введите год выхода в прокат: ";
			std::cin >> Temp.year;//тут нужно найти фильм и присвоить его Temp
			Temp = Filmoteka1.find_film_by_name_and_year(Temp.film_name, Temp.year);
			film_num = Filmoteka1.search_num_of_film(Temp);
			while (num_operation!=0)
			{
				std::cout << "Введите 0, если хотите закончить выбор";
				std::cout << "Введите 1, если хотите изменить название фильма" << '\n';
				std::cout << "Введите 2, если хотите изменить имя режиссера" << '\n';
				std::cout << "Введите 3, если хотите изменить имя сценариста" << '\n';
				std::cout << "Введите 4, если хотите изменить имя композитора" << '\n';
				std::cout << "Введите 5, если хотите изменить дату выхода в прокат" << '\n';
				std::cout << "Введите 6, если хотите изменить если сборы в рублях" << '\n';
				std::cin >> num_operation;
				switch (num_operation)
				{
				case 1:
					std::cin.get();
					std::cout << "Введите измененное название фильма: ";
					std::getline(std::cin, Temp.film_name);
					break;
				case 2:
					std::cin.get();
					std::cout << "Введите измененное имя режиссера: ";
					std::getline(std::cin, Temp.director);
					break;
				case 3:
					std::cin.get();
					std::cout << "Введите измененное имя сценариста: ";
					std::getline(std::cin, Temp.screenwriter);
					break;
				case 4:
					std::cin.get();
					std::cout << "Введите измененное имя композитора: ";
					std::getline(std::cin, Temp.musician);
					break;
				case 5:
					std::cout << "Введите измененный номер дня: ";
					std::cin >> Temp.day;
					std::cout << "Введите измененный номер месяца: ";
					std::cin >> Temp.month;
					std::cout << "Введите измененный год: ";
					std::cin >> Temp.year;
					break;
				case 6:
					std::cout << "Введите измененную сумму кассовых сборов (в рублях): ";
					std::cin >> Temp.fees;
				}
			}
			Filmoteka1.change_data_film(Temp, film_num);
			break;
		case 3://найти фильм по названию и году
			std::cin.get();
			std::cout << "Введите название фильма, который необходимо найти: "; 
			std::getline(std::cin, Temp.film_name);
			std::cout << "Введите год выхода в прокат: ";
			std::cin >> Temp.year;
			film=Filmoteka1.find_film_by_name_and_year(Temp.film_name, Temp.year);
			print(film);
			break;
		case 4://выдать все фильмы заданного режиссера 
			F.clear();
			std::cin.get();
			std::cout << "Введите имя режиссера: "; //Сталинград  Подольские курсанты Единичка Апостол
			std::getline(std::cin, Temp.director);
			F = Filmoteka1.get_films_of_director(Temp.director);
			print(F);
			break;
		case 5://выдать все фильмы, вышедшие в прокат в выбранном году
			F.clear();
			std::cout << "Введите год выхода фильма в прокат: ";
			std::cin >> Temp.year;
			F = Filmoteka1.get_films_in_year(Temp.year);
			print(F);
			break;
		case 6: //выдать заданное число фильмов с max сборами
			F.clear();
			std::cout << "Введите число фильмов с максимальными сборами: ";
			std::cin >> num_films_with_max_fees;
			F = Filmoteka1.get_films_with_max_fees(num_films_with_max_fees);
			print(F);
			break;
		case 7://выдать заданное число фильмов с max сборами в выбранном году
			F.clear();
			int year;
			std::cout << "Введите число фильмов с максимальными сборами: ";
			std::cin >> num_films_with_max_fees;
			std::cout << "Введите год, за который хотите получить данные: ";
			std::cin >> year;
			F=Filmoteka1.get_films_with_max_fees_in_year(num_films_with_max_fees, year);
			print(F);
			break;
		case 8: //узнать размер
			size = Filmoteka1.get_size();
			std::cout << "Текущее число фильмов: " << size<<'\n';
			break;
		case 9://удалить фильм
			std::cin.get();
			std::cout << "Введите название фильма: "; 
			std::getline(std::cin, Temp.film_name);
			std::cout << "Введите год выхода фильма в прокат: ";
			std::cin >> Temp.year;//используем поля структуры Temp, чтобы не выделять память под строку с названием фильма и число типа int - год
			Filmoteka1.delete_film(Temp.film_name, Temp.year);
			break;
		case 10://сохранить фильмотеку в файл
			std::cin.get();
			std::cout << "Введите имя файла, указывая его расширение (например .txt): "; 
			std::getline(std::cin, name_of_file);
			Filmoteka1.set_in_file(name_of_file);
			break;
		case 11://сохранить фильмотеку в файл
			std::cin.get();
			std::cout << "Введите имя файла, указывая его расширение (например .txt): "; 
			std::getline(std::cin, name_of_file);
			Filmoteka1.get_from_file(name_of_file);
			break;
		case 12://вывести на экран все фильмы
			F.clear();
			F = Filmoteka1.get_all_films();
			print(F);
			break;
		}
	}
	F.clear();
	system("pause");
}