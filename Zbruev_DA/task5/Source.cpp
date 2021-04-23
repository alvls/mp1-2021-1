#include <fstream>
#include <clocale>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>
#define N 10//число пунктов в меню 
using  namespace std;
struct Tovar //структура с информацией о товаре
{
	string str_kod;//штрих-код в виде строки (отдельно с типом string на случай, например, штрихкода 0001, в int это просто как 1 запишется)
	int kod;//штрих-код
	float cost;//стоимость за единицу
	float sale;//скидка
	string name;//наименование товара
	int num=0;//количество
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
	vector <struct Tovar> Spisok;//массив различных товаров для чека
	int size;//число различных товаров на складе 
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
	bool delete_tovar(string kod)//удалить товар со склада
	{
		vector <Tovar>::iterator it;
		bool flag = false;//false - если товар не найден
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
	Tovar get_elem(string kod_search_elem)//выдать информацию о товаре
	{
		bool flag=false;//false - если товар не найден
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
			t.kod = 0;//штрих код =0, если товар не найден
			t.name = "0";//иначе программа падает
			t.sale = 0;//иначе программа падает
			t.cost = 0;//иначе программа падает
		}
		else
		{
			t = Spisok[num_elem];
		}
		return(t);
	}
	vector <Tovar> get_all_spisok()//выдать весь список товаров
	{
		return(Spisok);
	}
	void get_from_file(string name_of_file)//считать список из файла
	{
		ifstream fin(name_of_file);
	    Tovar Temp;
		bool flag = true;
		Spisok.clear();
		while (!fin.eof())
		{
			if (flag == false)//чтобы на первой итерации цикла все работало как надо 
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
		size = Spisok.size();//меняем размер списка
		fin.close();
	}
	int getsize()//узнать текущее число наименований товаров на складе 
	{
		size = Spisok.size();
		return(size);
	}
	void set_in_file(string name_of_file)//записываем список в файл
	{
		ofstream fout;
		fout.open(name_of_file);
		bool flag = false;
		size = Spisok.size();
		for (int i = 0; i < size; i++)
		{
			if (flag == true)
			{
				fout << '\n';
			}
			flag = true;
			fout << Spisok[i].name << '\n';
			fout << Spisok[i].kod << '\n';
			fout << Spisok[i].cost << '\n';
			fout << Spisok[i].sale;
		}
		size = Spisok.size();
		fout.close();
	}
};
void print(Tovar T)//печатает 1 товар
{
	std::cout << "Название товара: ";
	std::cout << T.name << '\n';
	std::cout << "Код: ";
	std::cout << T.str_kod << '\n';
	std::cout << "Цена товара за единицу: ";
	printf("%.2f", T.cost);//чтобы вывести 2 знака после точки
	std::cout << " руб" << '\n';
	std::cout << "Скидка: ";
	std::cout << T.sale << " %" << '\n';
	std::cout << "Количество товара: ";
	std::cout << T.num << '\n';
}
void print_for_skan(Tovar T)//не печатает значение поля num (количество товара)
{
	std::cout << "Название товара: ";
	std::cout << T.name << '\n';
	std::cout << "Код: ";
	std::cout << T.str_kod << '\n';
	std::cout << "Цена товара за единицу: ";
	std::cout << T.cost << " руб" << '\n';
	std::cout << "Скидка: ";
	std::cout << T.sale << " %" << '\n';
}
void print(vector <Tovar> S)//печатает вектор фильмов
{
	int size = S.size();
	for (int i = 0; i < size; i++)
	{
		print(S[i]);
	}
}
void showmenu()
{
	char* menu[N] = { "Считать список товаров из файла ", "Отсканировать товар ","Получить чек", "Рассчитать итоговую сумму к оплате", "Удалить товар из покупки", 
		"Вывести на экран информацию про все товары со склада","Добавить товар на склад", "Сохранить список товаров в файл", "Удалить товар со склада", "Выход" };//массив с названиями операций
	short int menu_number[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };//массив с номерами каждого пункта меню
	int i;
	std::cout << "Операции: " << '\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i] << ". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "Введите номер операции, которую необходимо выполнить: ";
}
Tovar proverka(Tovar t)//первый раз kod вводится в основной программе, это чисто функция проверки
{
	t.kod = privedenie_koda(t.str_kod);
	while (t.kod > 9999)
	{
		std::cout << "Некорректное значение штрих-кода, попытайтесь заново " << '\n';
		std::cout << "Введите штрих-код (4-х значное целое число): ";
		std::cin >> t.str_kod;
		t.kod = privedenie_koda(t.str_kod);
	}
	return (t);
}
class Kassa
{
	vector <Tovar> Check;//массив отсканированных товаров для чека
	float total_discount;//суммарная скидка
	float Sum;//итоговая сумма к оплате
	int size;//число товаров в чеке
	Sklad sklad;
public:
	void skan_tovara()//сканирование товара
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
				std::cout << "Товар на складе не найден. Попытайтесь заново" << '\n';
			}
			flag = true;
			std::cout << "Введите штрих-код (4-х значное целое число): ";
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
	bool delete_tovar_from_check(string kod_search_elem)//удалить фильм
	{
		bool flag = false;//false - если товар не найден 
		int i = 0;
		vector<Tovar>::iterator it;
		it = Check.begin();
		size = Check.size();
		while (i < size)//находим номер этого элемента 
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
	int get_num_elem(string kod_search_elem)//выдать номер элемента
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
	float calculate_sum()//рассчитать сумму к оплате
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
	void get_check()//выдать чек
	{
		int i;
		size = Check.size();
		std::cout << '\n' << "Чек" <<'\n';
		for (i = 0; i < size; i++)
		{
			print(Check[i]);
			std::cout << '\n';
		}
		std::cout << "Итоговая сумма к оплате: ";
		printf("%.2f", calculate_sum());//чтобы вывести 2 знака после точки
		std::cout << " руб" << '\n';
	}
    Tovar gettovar_from_sklad(string kod)
	{
		Tovar t;
		t = sklad.get_elem(kod);
		return(t);
	}
	void menu()//меню кассы
	{
		int num_operation=1;
		string char_kod;
		string name_file;
		vector <Tovar> Temp;//
		int sz;//для режима 6
		Tovar t;//для режима 7
		bool flag=false;
		bool f=false;
		while (num_operation!=0)
		{
			showmenu();
			std::cin >> num_operation;
			switch (num_operation)
			{
			case 1://считать список товаров из файла
				std::cin.get();
				std::cout << "Введите имя файла, указывая его расширение (например .txt): ";//проверки добавить
				std::getline(std::cin, name_file);
				sklad.get_from_file(name_file);
				break;
			case 2://сканировать товар
				skan_tovara();
				break;
			case 3://выдать чек
				get_check();
				break;
			case 4://рассчитать итоговую сумму
				std::cout << "Итоговая сумма к оплате: " << calculate_sum() << " руб" << '\n';
				break;
			case 5://удаление товара из чека
				flag = false;
				do
				{
					if (flag == true)
					{
						std::cout << "Товар не найден. Попытайтесь заново" << '\n';
					}
					std::cout << "Введите штрих-код товара, который хотите удалить: ";
					std::cin >> t.str_kod;//где-то здесь проблема
					t = proverka(t);
					flag = true;
					f=delete_tovar_from_check(t.str_kod);
				} while (f == false);
				break;
			case 6://вывести список товаров со склада на экран
				Temp = sklad.get_all_spisok();
				sz = sklad.getsize();
				for (int i = 0; i < sz; i++)
				{
					print_for_skan(Temp[i]);
					std::cout << '\n';
				}
				break;
			case 7://довать товар на склад
				std::cin.get();
				std::cout << "Введите название товара: ";//проверки добавить
				std::getline(std::cin, t.name);
				std::cout << "Введите код (4-х значное целое число): ";
				std::cin >> t.str_kod;
				t = proverka(t);
				std::cout << "Введите цену товара за единицу (в рублях), отделяя рубли от копеек точкой: ";
				std::cin >> t.cost;
				std::cout << "Введите скидку (в %): ";
				std::cin >> t.sale;
				sklad.setTovar(t);
				break;
			case 8://сохранить список товаров в файл
				std::cin.get();
				std::cout << "Введите имя файла, указывая его расширение (например .txt): ";//проверки добавить
				std::getline(std::cin, name_file);
				sklad.set_in_file(name_file);
				break;
			case 9://удалить товар со склада
				flag = false;
				f = false;//false-товар не найден
				size = Check.size();
				while (f == false)
				{
					if (flag == true)
					{
						std::cout << "Товар на складе не найден. Попытайтесь заново" << '\n';
					}
					flag = true;
					std::cout << "Введите штрих-код (4-х значное целое число): ";
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