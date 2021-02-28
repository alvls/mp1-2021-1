#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
void foo()
{

}
void main()
{
	foo();
	return;
	int n, a, ugad, lev, i = 0, num;//n - число выбора режима; a - предполагаемое игроком число; ugad - предполагаемое программой; lev - изменение числа; i - счётчик; num - случайное число;
	char c;// символ, считываемый при угадывании у игрока
	setlocale(LC_ALL, "Russian");
	printf("Давайте сыграем в игру \"Угадай число\"\n");
	printf("Числа могут быть загаданы от 1 до 1000\n");
met1: srand(time(NULL));
	num = rand() % 1000 + 1;
	a = -1;
	printf("Выберите режим:\n 1 - Bы угадываете число,загаданное программой\n 2 - Программа отгадывает число, которое загадал игрок\n");
	scanf("%d", &n);
	system("CLS");
	if (n != 2 && n != 1)
	{
		printf("Вам стоит попробовать себя в роли тестировщика. А пока придётся заново выбирать режим игры\n");
		goto met1;
	}
	switch (n)
	{
	case 1:
		printf("Введите предполагаемое числo\n");
		while (a != num)
		{
			scanf("%d", &a);
			i++;
			if (a < num)
			{
				printf("Загаданное число больше\n");
			}
			else
				if (a > num)
				{
					printf("Загаданное число меньше\n");
				}
		}
		printf("Вы угадали с %d-ой попытки, поздравляю!\n", i);
		i = 0;
		break;
	case 2:
		printf("Загадайте число\n");
		printf("Если загаданное вами число меньше, то пишите <, если больше, то наберите >, если же совпало, то =\n");
	met3:	lev = 500;
		ugad = lev;
	met2:
		i++;
		lev = (lev + 1) / 2;
		if (i == 8)
			lev = 1;
		printf("Это число %d?\n", ugad);
		scanf("%c", &c);
		scanf("%c", &c);
		switch (c)
		{
		case '<':
			ugad -= lev;
			goto met2;
		case '>':
			ugad += lev;
			goto met2;
		case'=':
			printf("Компьютер угадал с %d-ой попытки, программа работает в штатном режиме!\n", i);
			i = 0;
			break;
		default:
			printf("Вы хотели меня перехитрить, но я перехитрил вашу хитрость\n");
			printf("Снова загадывайте число или воспользуйтесь прежним\n");
			i = 0;
			goto met3;
		}
	}
	printf("Если вы хотите ещё раз сыграть, то введите нуль\n");
	c = getch();
	system("CLS");
	if (c == '0')
		goto met1;
	printf("Спасибо за игру! Приходите на занятия первой группы первой подгруппы ФИИТ ещё!\n");
	system("pause");
}