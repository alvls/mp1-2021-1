#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define line 4 // число символов в штрих-коде (4)
#define end 47 // наибольшее число  символов в строке (47)
#define strok 17 // число разных cтрок (17)
const unsigned etalon[strok] = { 9999, 1, 70, 6996, 1234, 2020, 6065, 5432, 2018, 3112, 2019, 1000, 1990, 7770, 1959, 1030, 1945};
const char stroka[strok][end] = { "Завершение ввода товаров", "Билет лотереи \"Pobed.net\"", "Фигурка Джеймса Бонда","Клубника (упаковка)", "Генератор паролей карманный", "Маски медицинские (упаковка)", "Пенсионная скидка", "Дневник школьный" , "Футбольный мяч \"Жак Фрескo\"", "Мандарины (упаковка)", "Гречка (упаковка)", "Бумага туалетная (упаковка)", "Водка \"Прощай, товарищ!\"", "Топор \"Раскольников\"", "Кукуруза (упаковка)", "БП с изображением говядины", "Знамя Победы настенное"}; // число строк х число символов
char strih[line]; //очередной поступаемый штрих-код
unsigned short pens = 0;//чтобы someone смог почувствовать себя старым
int kol_vo[strok]; //количество единиц товара
float prise[strok] = { 0.0, 100.0, 77.0, 179.0, 144.0, 112.0, 0, 120.0, 480.0, 69.0, 58.0, 36.0, 259.0, 866.0, 96.0, 6.0, 300.0};// временные цены на товары данных штрих-кодов
const float standprise[strok] = { 0.0, 100.0, 77.0, 179.0, 144.0, 112.0, 0, 120.0, 480.0, 69.0, 58.0, 36.0, 259.0, 866.0, 96.0, 6.0, 300.0}; // неизменяемые цены на товары
int skidka[strok]; // размер скидки в целых числах процентов
float sum = 0.0; // итоговая сумма
unsigned short j = 0;
int flag = 1;
void stringp(int i) // вывод строки
{
	while (stroka[i][j] != '\0')
	{
		printf("%c", stroka[i][j]);
		j++;
	}
	printf("\n");
	j = 0;
}
unsigned translator() //споиск штрих-кода
{
	int i = 0, t;// параметр массива
	unsigned kod;//преобразованный штрих-код
	unsigned plus;//вспомогательная переменная для преобразования штрих-кода
	int flag; // чтобы не ругался на нулевой код, которого нет в списке, но который значит полное завершение работы
	do {
		flag = 0;
		kod = 0;
		do scanf("%c%c%c%c", &strih[0], &strih[1], &strih[2], &strih[3]);
		while (getchar() != '\n');
		if (strih[0] == strih[0] == strih[0] == strih[0] == '0')
			strih[0] = 1;
		for (i = 0; i < line; i++)
		{
			plus = 1;
			if (strih[i] - '0' < 10 && strih[i] - '0' >= 0)
			{
				for (t = line - 1; t > i; t--)
					plus *= 10;
				plus = plus * (strih[i] - '0');
				kod += plus;
			}
			else
			{
				kod = 0;
				flag = 1;
				break;
			}
		}
		for (i = 0; i < strok && !flag; i++)
			if (kod == etalon[i])
			{
				stringp(i);
				break;
			}
		if (i = strok && kod != etalon[i])
		{
			flag = 1;
		}
		if (flag)
		{
			printf("Такого штрих-кода нет в базе данных, повторите ввод\n");
			strih[0] = 'j';
		}
	} while (strih[0] - '0' >= 10 || strih[0] - '0' < 0 || strih[1] - '0' >= 10 || strih[1] - '0' < 0 || strih[2] - '0' >= 10 || strih[2]- '0' < 0 || strih[3] - '0' >= 10 || strih[3] - '0' < 0);
	return kod;
}
void codes()// вывод доступных штрих-кодов 
{
	int i = 0;
	setlocale(LC_ALL, "Russian");
	printf("Код %u - ", etalon[i]);
	stringp(i);
	i++;
	printf("Код 000%u - ", etalon[i]);
	stringp(i);
	i++;
	printf("Код 00%u - ", etalon[i]);
	stringp(i);
	i++;
	for (i; i < strok; i++)
	{
		printf("Код %u - ", etalon[i]);
		stringp(i);
	}
	printf("\n");
	printf("Любой код, содержащий не цифры, означает ввод штрих-кода заново\n");
	printf("Вводите только сочетания по 4 символа, в конце ввода каждого сочетания нажимайте Enter\n\n");
	printf("Если вы ознакомились с информацией и готовы вводить штрих-коды, нажмите на любую клавишу");
	getch();
	system("CLS");
}
float sale(int t) // создание скидки
{
	int a[25];
	int i;
	for (i = 0; i < 25; i++)
	{		 
		a[i] = rand() % 11;
		if (a[i] != 0)
			a[i] *= 5;
		else
		{
			a[24] = 0;
			break;
		}
	}
	i = 24;
	prise[t] *= (1.0 - (a[i] / 100.0));
	skidka[t] = a[i];
}
void summator(int kod) // получение количества товаров
{
	int i;
	for (i = 1; i < strok; i++)
		if (kod == etalon[i])
		{
			kol_vo[i]++;
			break;
		}
}
void check() // формирование чека
{
	int i;
	printf("\nЧек за покупки в магазине \"Сфинкс\"\n\n");
	for (i = 0; i < strok; i++)
	{
		if (kol_vo[i])
		{
			stringp(i);
			if ((standprise[i] - prise[i]) != 0)
			{
				printf("Цена: %3.0f руб ", standprise[i]);
				printf("Кол-во: %d шт\n", kol_vo[i]);
				printf("Цена со скидкой: %3.2f руб\n", prise[i]);
			}
			else 
			{
				printf("Цена: %3.0f руб ", standprise[i]);
				printf("Кол-во: %d шт\n", kol_vo[i]);
			}
			printf("Стоимость: %0.2f руб\n\n", prise[i] * kol_vo[i]);
			sum = sum + prise[i] * kol_vo[i];
		}
	}
}
void main() // здесь и производится сборка фрагментов
{
	int r = 0;
	int i, t;
	unsigned kod;
	setlocale(LC_ALL, "Russian");
	do 
	{
		codes();
		srand(time(NULL));
		for (i = 0; i < strok; i++)
			if (i != 6)
				sale(i);
		do
		{
			kod = translator();
			summator(kod);
		} while (kod != 9999 && kod!=0);
		system("color F0");
		check();
		if (pens)
		{
			printf("Пенсионная скидка - %0.2f руб (5%%)\n\n", 0.05 * sum);
			sum *= 0.95;
		}
		printf("Сейчас рандомная скидка на товары:\n");
		for (i = 1; i < strok; i++)
		{
			if (skidka[i] != 0)
			{
				r++;
				while (stroka[i][j] != '\0')
				{
					printf("%c", stroka[i][j]);
					j++;
				}
				j = 0;
				printf(" (%d%%)\n", skidka[i]);
			}
		}
		if (r == 0)
			printf("Шуткa, её сейчас нет :)\n");
		printf("\nИтоговая сумма: ");
		printf("%0.2f руб\n", sum);
		printf("Спасибо за покупки в нашем магазине!\n");
		system("pause");
		for (i = 0; i < strok; i++)
		{
			prise[i] = standprise[i];
			kol_vo[i] = 0;
			sum = 0.0;
			pens = 0;
		}
		system("color 0F");
	} while (kod!=0);
	printf("Вы были последним покупателем в нашем магазине!\n");
	system("pause");
}
