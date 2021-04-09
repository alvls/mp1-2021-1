//Класс Касса должен предоставлять следующие операции : 1) «сканировать» очередной товар, 
//2) получить описание товара со склада, 3) добавить данные о товаре в чек, 4) сформировать чек за покупку,
//5) рассчитать итоговую сумму к оплате, 6) удалить выбранный товар из покупки. Касса взаимодействует с пользователем
//описание товара, прлучается, хранится на складе
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
struct Tovar //структура с информацией о товаре
{
	int kod;//штрих-код
	float cost_unit;//стоимость за единицу
	float sale;
	string tovar_name;//наименование товара
};

class Sklad
{
	vector <struct Tovar> Spisok;//массив различных товаров для чека
	int size;//число различных товаров на складе 
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
		if (size == 1)//если только один товар на складе
		{
			Spisok.clear();
			size = 0;
		}
		else//если на складе несколько товаров
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
	int get_size()//узнать текущее число наименований товаров на складе (возможно, удалить) 
	{
		size = Spisok.size();
		return (size);
	}
	vector <struct Tovar> get_all_spisok()//выдать весь список
	{
		return(Spisok);
	}
	~Sklad()//деструктор
	{
		Spisok.clear();
	}
};

class Kassa
{
	vector <struct Tovar> Check;//массив отсканированных товаров для чека
	float total_discount;//суммарная скидка
	float Sum;//итоговая сумма к оплате
	int size;//число товаров в чеке
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