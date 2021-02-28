#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "all.h"
void menu()
{
	int away;
	int ans;//ответ пользователя
	char c;
	do {
		printf("======================== MENU =========================\n");
		printf("Выберите режим: \n1 - Однократный расчёт функции\n");
		printf("2 - Серийный эксперимент\n");
		printf("0 - Выход из программы\n");
		printf("======================== MENU =========================\n");
		ans = cleaner(0, 2);
		away = 1;
		switch (ans)
		{
		case 0:
			printf("Вы точно уверены, что хотите выйти?\n");
			printf("Если да, то нажмите 0\n");
			printf("Eсли нет, то нажмите любой другой символ\n");
			scanf("%c", &c);
			ans = c - '0';
			if (ans)
				away--;
			break;
		case 1: case 2:
			mode(ans);
			printf("Если вы желаете продолжать, нажмите 0, если нет, то любую другую клавишу\n\n");
			away = getch();
			away -= '0';
			break;
		}
	} while (!away);
	printf("Для похвалы создателя нажмите любую клавишу . . .\n");
	getch();
}
db db_cleaner(db min)
{
	db ans;//ответ пользователя
	int clean;//чтобы корректно считать число
	do
	{
		clean = scanf("%lf", &ans);
		if ((!clean) || ans < min)
			printf("Ошибка ввода\n");
	} while (getchar() != '\n' || !clean || ans < min);
	return ans;
}
int cleaner(int min, int max)
{
	int ans;//ответ пользователя
	int clean;//чтобы корректно считать число
	do
	{
		clean = scanf("%d", &ans);
		if (!clean || ans<min || ans>max)
			printf("Ошибка ввода\n");
	} while (getchar() != '\n' || !clean || ans<min || ans>max);
	return ans;
}
operation choice()
{
	int ans;//ответ пользователя
	db(*funk)(db) = NULL;//выбор эталонной функциич
	printf("Выберите номер функции, которую желаете вычислить:\n");
	printf("1 - Косинус\n");
	printf("2 - Синус\n");
	printf("3 - Экспонента (e^x) \n");
	printf("4 - Квадратный корень из 1+х\n");
	printf("5 - Арктангенс\n");
	printf("6 - Ареатангенс - гиперболический тангенс\n");
	printf("7 - Гиперболический синус\n");
	printf("8 - Гиперболический косинус\n");
	printf("9 - Натуральный логарифм от 1+x\n");
	printf("0 - Выход в меню\n");
	ans = cleaner(0, 9);
	switch (ans)/////////////////////////////////
	{
	case 0:
		printf("\n");
		menu();
		break;
	case 1:
		funk = cos;
		break;
	case 2:
		funk = sin;
		break;
	case 3:
		funk = exp;
		break;
	case 4:
		funk = sqrt;
		break;
	case 5: 
		funk = atan;
		break;
	case 6:
		funk = atanh;
		break;
	case 7:
		funk = sinh;
		break;
	case 8:
		funk = cosh;
		break;
	case 9:
		funk = log;
		break;
	}
	return funk;
}
void mode(int a)
{
	db acc;// точность вычисления (задаёт пользователь в виде величины, меньшей единицы)
	int count;//количество слагаемых
	db x;//аргумент функции
	operation funk = NULL;//получение эталонной функции для выбора программной
	sum res;//результат вычисления ряда
	int nmax;//максимальное число слагаемых
	db t1, t2;//для получения времени
	int sq;//для проверки корня
	a--;
	if (a)
		printf("======================== ВТОРОЙ РЕЖИМ =========================\n");
	else
		printf("======================== ПЕРВЫЙ РЕЖИМ =========================\n");
	funk = choice();
	printf("Введите точку х, в которой будет вычислена функция, отделяя запятой дробную часть от целой\n");
	printf("Для квадратного корня и натурального логарифма x по модулю не больше единицы\n");
	printf("Для ареатангенса и арктангенса по модулю меньше единицы\n");
	if (funk == sqrt || funk == atanh || funk == atan || funk == log)
	{
		if (funk == sqrt || funk == log)
		do {
			sq = 0;
			x = db_cleaner(-1.0);
			if (x > 1.0)
			{
				sq = 1;
				printf("Ошибка ввода\n");
			}
		} while (sq);
		if (funk == atanh || funk == atan)
			do {
				sq = 0;
				x = db_cleaner(-0.999999);
				if (x >= 1.0)
				{
					sq = 1;
					printf("Ошибка ввода\n");
				}
			} while (sq);
	}
	else
		x = db_cleaner(-10000000.0);
	if (a)
	{
		printf("Введите число экспериментов, не превышающее 25\n");
		nmax = cleaner(1, 25);
		printf("======================== ВТОРОЙ РЕЖИМ =========================\n\n");
		head(x, funk);
		t1 = omp_get_wtime();
		for (count = 1; count <= nmax; count++)
		{
			res = polinom(0.0, count, x, funk);
			printer(count, x, res.s, funk);
		}
		t2 = omp_get_wtime() - t1;
		printf("\nРяды Тейлора были вычислены и написаны за %0.6lf секунды\n\n", t2);
		printf("============================ РЕЗУЛЬТАТ =============================\n\n");
	}
	else
	{
		printf("Введите точность вычисления в виде десятичной дроби от 0,000001\n");
		acc = db_cleaner(0.000001);
		printf("Введите количество слагаемых ряда в виде целого числа от 1 до 1000\n");
		count = cleaner(1, 1000);
		printf("======================== ПЕРВЫЙ РЕЖИМ =========================\n\n");
		t1 = omp_get_wtime();
		res = polinom(acc, count, x, funk);
		t2 = omp_get_wtime() - t1;
		head(x, funk);		
		printer(res.count, x, res.s, funk);		
		printf("\nРяд Тейлора был вычислен за %0.6lf секунды\n\n", t2);
		printf("============================ РЕЗУЛЬТАТ =============================\n\n");
	}
}