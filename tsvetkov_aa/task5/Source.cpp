#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <cstring>
#include <time.h>	
using namespace std;
#define ALL 7

class storage//класс склад товаров
{
protected:
	char names[ALL][20] = { "AMD RADEON RX580", "NVIDIA GTX1050", "NVIDIA GTX1050TI", "AMD RADEON RX460", "NVIDIA GTX1660", "NVIDIA GT710", "NVIDIA RTX3090" };
	char codes[ALL][5] = { "1243","5136","5128","3014","8391","5814","2631" };
	float prices[ALL] = { 19990 ,7650 ,13020 ,6340 ,19720 ,3220 ,190000 };//стоимость товара
	float discount[ALL] = { 0.1,0.05,0.2,0.1,0.25,0.05,0.5 };//массив скидок на каждый товар
public:
	void printlist()//вывод на консоль списка товаров на складе
	{
		int j = 0;
		for (j = 0; j < 17; j++)
			cout << "-";
		cout << "Товары в наличии";
		for (j = 0; j < 17; j++)
			cout<<"-";
		cout << endl;
	 cout << setiosflags(ios::left) << setw(17) << "Штрих-код" << setw(24) << "Название" << "Стоимость" << endl;
	 for(j=0;j<ALL;j++)
		 cout << setiosflags(ios::left) << setw(17) << codes[j] << setw(24) << names[j] << prices[j] << endl;
	}
	void printunit(int i)//вывод на консоль товара с информаицей
	{
		cout << "Видеокарта " << setw(24) << names[i] << "Цена(руб)=" << prices[i] << endl << "Скидка на товар составляет: " << setw(2) << discount[i] * 100 << setw(5) << "%";
	}
};

void timesec()//функция для вывода времени в чек
{
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &result);
	cout << str;
}

class cashbox:public storage//класс касса(потомок класса склад, в целом наследование тут не нужно, но хотелось попробовать)
{
private:
	int kol[ALL] = {0};//массив для подсчитывания кол-ва товаров в корзине
	char code [5];//буфер кода для сканировнаия товара
public:
	void read()//текстовый редактор для считывания кода(не позволяет считывать более 4 символов)
	{
		char s;
		int i = 0;
		while (i != 5)
		{
			s = _getch();
			switch (s) 
			{
			case '\r':
				code[i] = '\0';
				return;
			case '\b':
				i--;
				if (i < 0)
					i++;
				else cout << "\b \b";
				break;
			default:
				if (i != 4)
				{
					code[i] = s;
					cout << code[i];
					i++;
				}
			}
		}
	}
	void check()//проверка формата кода(4 символа от 0 до 9)
	{
		bool flag = false;
		int i = 0;
		for (i = 0; i < 4; i++)
				if ((code[i] >= '0') && (code[i] <= '9'))//проверка на правильность символов штрих-кода
					flag = true;
				else
				{
					throw 1.5;
				}
	}
	void addunit()//добавление товара в корзину
	{
		int i = 0;
	v:	bool flag = false;
		cout << "Введите код товара или введите 1 для отмены" << endl;
		read();
		cout << endl;
		if ((code[0] == '1') && (code[1] == '\0'))//проверка на ввод 1
			return;
		try
		{
			check();
		}
		catch(double)
		{
			cout << "Неверный формат кода" << endl;
			goto v;
		}
		for (i = 0; i < ALL; i++)//поиск товара на складе
		{
			if (strcmp(code, codes[i]) == 0)
			{
				kol[i]++;
				printunit(i);
				cout << endl << "Товар добавлен в корзину" << endl;
				flag = true;
			}
		}
		if (flag == false)
		{
			cout << "Кода " << code << " нет в базе данных" << endl;
			goto v;
		}
	}
	void printshoppinglist()//вывод на консоль корзины(для удаление товара)
	{
		bool flag = false;
		int i = 0;
		for (i = 0; i < ALL; i++)
			if (kol[i] > 0)
			{
				if (flag == false)
					cout << "Товары в корзине:" << endl;
				flag = true;
				printunit(i);
				cout  <<"Код:"<<setw(8)<<codes[i]<< "Количество: " << kol[i] << endl;
			}
		if (flag == false)
			throw 1;//уходит в main
	}
	void deleteunit()//удаление товара из корзины
	{
		int i = 0, poz = 0, n = 0;
		printshoppinglist();
		bool flag = false;
	y:	cout << "Введите код товара, который требуется удалить или введите 1 для отмены" << endl;
		read();
		cout << endl;
		if ((code[0] == '1') && (code[1] == '\0'))
			return;
		try
		{
			check();
		}
		catch(double)
		{
			cout << "Неверный формат кода" << endl;
			goto y;
		}
		for (i = 0; i < ALL; i++)
		{
			if ((strcmp(code, codes[i]) == 0) && (kol[i]!=0))//поиск товара в корзине
			{
				poz = i;
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			cout << "Товар с кодом " << code << " не найден в коризне" << endl;
			goto y;
		}
		cout << "Введите количество товара, которое необходимо удалить(не более "<< kol[poz] << ")" << endl;
		cin >> n;
		while ((kol[poz] > 0) && (n > 0))
		{
			kol[poz]--;
			n--;
		}
		cout << "Товар удален" << endl;
	}
	void printreceipt()//создание и вывод чека в консоль
	{
		int i = 0, j = 0;
		double fp = 0, fd = 0, pr = 0;//fp-общая стоимость покупки,fd- полная скидка покупки, pr-стоимость позиции в чеке
		bool flag = false;
		for (i = 0; i < ALL; i++)
			if (kol[i] != 0)
				flag = true;
		if (flag == false)
			throw 1;//уходит в main
		system("cls");
		for (j = 0; j < 22; j++)//оформление
			cout << "-";
		cout<<"ЧЕК";
		for (j = 0; j < 23; j++)
			cout<<"-";
		cout << endl;
		for (i=0; i<ALL; i++)
			if (kol[i]!=0)
			{
				pr = kol[i] * prices[i] * (1 - discount[i]);
				fp += pr;
				fd+=prices[i] * kol[i] - pr;
				cout << setw(20) << names[i] << "X" << setw(7) << kol[i] <<"Цена(руб/шт)="<<prices[i]<< endl << "Скидка=" << setw(2) << discount[i] * 100 << setw(11) << "%"<< "Общая стоимоcть(руб)=" << pr << endl;
			}
		for (j = 0; j < 48; j++)//оформление
			cout<<"-";
		cout << endl;
		cout << "Сумма покупки(руб)=" << fp << endl;
		cout << "Общая скидка(руб)=" << fd << endl;
		timesec();
		for (j = 0; j < 48; j++)//оформление
			cout << "-";
		cout<<"\n";
	}
};

int menu()//вывод меню в консоль
{
	int m;
	cout << "Выберите дальнейшее действие" << endl;
	cout << "1.Отсканировать новый товар\n" << "2.Удалить товар из корзины\n" << "3.Сформировать чек за покупку\n"<<"0.Выход"<<endl;
	cin >> m;
	return m;
}

void main()
{
u:	SetConsoleCP(1251);//русский язык при вводе в консоль
	SetConsoleOutputCP(1251);
	cashbox k;
	int m, n=0;
l:	m = menu();
	switch (m)
	{
	case 1://добавление товара в корзину
		if(n%5==0)// каждые 5 товаров список товаров со склада выводится в консоль
		k.printlist();
			k.addunit();
		cout << endl;
		n++;
		break;
	case 2://удаление товара из корзины
		try
		{
			k.deleteunit();
		}
		catch (int)
		{
			cout << "Товаров в корзине не найдено"<<endl;
			goto l;
		}
		break;
	case 3://печать чека
		try
		{
			k.printreceipt();
		}
		catch (int)
		{
			cout << "Товаров в корзине не найдено" << endl;
			goto l;
		}
		cout << "Для создания нового чека нажмите 1, для выхода из программы нажмите любую клавишу" << endl;
		cin >> m;
		if (m == 1)
		{
			system("cls");
			goto u;
		}
		else
			return;
		break;
	case 0:
		return;
	}
	goto l;	
}
