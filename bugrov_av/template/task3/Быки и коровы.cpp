#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include "memory.h"

enum TColor {
	BLACK = 0, 
	BLUE = 1 , 
	GREEN = 2, 
	CYAN = 3, 
	RED = 4, 
	MAGENTA = 5, 
	BROWN = 6, 
	LIGHTGRAY = 7,
	DARKGRAY = 8, 
	LIGHTBLUE = 9, 
	LIGHTGREEN = 10, 
	LIGHTCYAN = 11, 
	LIGHTRED = 12,
	LIGHTMAGENTA = 13, 
	YELLOW = 14, 
	WHITE = 15
};

//-----------------------------------------------------------------------------
int wherex(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(Console, &buf);
	return buf.dwCursorPosition.X;
}

//-----------------------------------------------------------------------------
int wherey(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(Console, &buf);
	return buf.dwCursorPosition.Y;
}

//-----------------------------------------------------------------------------
COORD WhereXY(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { -1, -1 };
	if (!Console)
		return pos;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(Console, &buf);
	return buf.dwCursorPosition;
}

//-----------------------------------------------------------------------------
void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int col = Attr;
	int width = buf.dwSize.X;
	int height = buf.dwSize.Y;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;
	SetConsoleCursorPosition(Console, zpos);

	FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
	FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}

//-----------------------------------------------------------------------------
void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}

//-----------------------------------------------------------------------------
void textcolor(int color)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int bk_col = Attr / 16;
	int col = color % 16;
	col = col + bk_col * 16;

	SetConsoleTextAttribute(Console, col);

	char ch;
	pos = WhereXY();
	ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
	printf("%c", ch);
	gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textbackground(int color)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int text_col = Attr % 16;
	int col = color % 16;
	col = color * 16 + text_col;

	SetConsoleTextAttribute(Console, col);

	char ch;
	pos = WhereXY();
	ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
	printf("%c", ch);
	gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textattr(int color)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	SetConsoleTextAttribute(Console, color);

	DWORD Count;
	char ch;
	COORD pos = WhereXY();
	ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
	printf("%c", ch);
	gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void setwindow(int width, int height)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = width - 1;
	rect.Top = 0;
	rect.Bottom = height - 1;
	COORD size;
	size.X = width;
	size.Y = height;
	SetConsoleWindowInfo(Console, 1, &rect);
	//  printf("%d %d %d %d", rect.Left, rect.Top, rect.Right, rect.Bottom);
	SetConsoleScreenBufferSize(Console, size);
	//  printf("%d %d", size.X, size.Y);
}

//-----------------------------------------------------------------------------
void SetWindow(SMALL_RECT rect, COORD size)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	SetConsoleScreenBufferSize(Console, size);
	SetConsoleWindowInfo(Console, 1, &rect);
}

//-----------------------------------------------------------------------------
void GetWindow(SMALL_RECT* rect, COORD* size)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	*rect = buf.srWindow;
	size->X = buf.dwSize.X;
	size->Y = buf.dwSize.Y;
}

//-----------------------------------------------------------------------------
void HideCursor(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_CURSOR_INFO buf;
	GetConsoleCursorInfo(Console, &buf);
	buf.bVisible = 0;
	SetConsoleCursorInfo(Console, &buf);
}

//-----------------------------------------------------------------------------
void ShowCursor(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_CURSOR_INFO buf;
	GetConsoleCursorInfo(Console, &buf);
	buf.bVisible = 1;
	SetConsoleCursorInfo(Console, &buf);
}

/*Разработать программу, реализующую игру «Быки и коровы».
Требования(правила)
Играют два игрока(человек и компьютер).
Игрок выбирает длину загадываемого числа – n(от 2 до 5). proverit'
Компьютер «задумывает» n - значное число с неповторяющимися цифрами.
Игрок делает попытку отгадать число – вводит n - значное число с неповторяющимися цифрами.
Компьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе(то есть количество коров) и сколько угадано вплоть до позиции в загаданном числе(то есть количество быков).
Игрок делает попытки, пока не отгадает всю последовательность или не сдастся.
Пример
Пусть n = 4.
Пусть задумано число «3219».
Игрок ввел число «2310».
Результат: две «коровы»(две цифры : «2» и «3» — угаданы на неверных позициях) и один «бык»(одна цифра «1» угадана вплоть до позиции). switch switch*/
#define num 5
void main()
{
	int n, i = 0, igrok, t, c; // n знаков в числе; i - счётчик; igrok - число игрока; t - дополнительный счётчик; 
	unsigned short zagad[num] = { 0 }, x, p[num] = { 0 }, bik = 0, kor = 0; // zagad - загаданное компьютером число; x - случайное число; p пользовательское число; bik - число быков; kor  - число коров;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("color B8");
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	printf("Давайте сыграем в игру \"Быки и коровы\"\n");
	printf("Введите количество цифр в числе (не менее 2 и не более 5)\n");
nachalo: 
	scanf("%d", &n);
	if (n < 2 || n > 5)
	{
		printf("Вы ввели неправильное число, введите снова\n");
		goto nachalo;
	}
	for (t = 0; t < num; t++)
	{
		zagad[t] = 42;
		p[t] = 13;
	}
	zagad[i] = rand() % 9 + 1;	
	for (i = 1; i < n; i++) // Генерация числа
	{
	met1:
		x = rand() % 10; // создание очередной цифры
		zagad[i] = x;
		for (t = 0; t < i; t++)
		{
			if (zagad[i] == zagad[t]) // проверка на равенство 
				goto met1;
		}
	}
	printf("Если вы захотите сдасться, введите нуль, иначе продолжим\n");
	do
	{
		printf("Введите число\n");
		scanf("%d", &igrok);
		if (igrok == 0)
			break;
		for (i = 0; i < n; i++)
		{
			x = 1;
			for (t = 0; t < n- 1 - i; t++)
			{
				x *= 10;
			}
			p[i] = igrok / x;
			igrok = igrok - p[i] * x;
		}
		igrok = 42;
		for (i = 0; i < n; i++) // проверка сходства с числом пользователя
		{
			if (zagad[i] == p[i]) // для полного сходства (место и цифра)
				bik++;
			else
			{
				for (t = 0; t < n; t++)
				{
					if (zagad[i] == p[t]) // сходство только цифры
					{
						kor++;
						break;
					}

				}
			}
		}
		if (bik < n)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | LIGHTMAGENTA));
			switch (bik)
			{
			case 0: case 5:
				switch (kor)
				{
				case 0: case 5:
					printf("%d быков и %d коров\n", bik, kor);
					break;
				case 1:
					printf("%d быков и %d корова\n", bik, kor);
					break;
				case 2: case 3: case 4:
					printf("%d быков и %d коровы\n", bik, kor);
					break;
				}
				break;
			case 1:
				switch (kor)
				{
				case 0: case 5:
					printf("%d бык и %d коров\n", bik, kor);
					break;
				case 1:
					printf("%d бык и %d корова\n", bik, kor);
					break;
				case 2: case 3: case 4:
					printf("%d бык и %d коровы\n", bik, kor);
					break;
				}
				break;
			case 2: case 3: case 4:
				switch (kor)
				{
				case 0: case 5:
					printf("%d быка и %d коров\n", bik, kor);
					break;
				case 1:
					printf("%d быкa и %d корова\n", bik, kor);
					break;
				case 2: case 3: case 4:
					printf("%d быкa и %d коровы\n", bik, kor);
					break;
				}
				break;
			}
			/*
			for (i = 0; i < n; i++)
			{
				printf("%d", zagad[i]);
				
			}
			*/
			/*
			printf("\n");
			for (i = 0; i < n; i++)
			{
				printf("%d", p[i]);
			}
			printf("\n");
			*/
			bik = 0;
			kor = 0;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGRAY << 4) | GREEN));
			printf("И это правильный ответ! ");
			printf("Вы победили, поздравляю!\n");
			printf("Вы проявили много терпения и показали навыки игры в эту очень увлекательную игру\n");
			break;
		}
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | DARKGRAY));
	} while (igrok != 0);
	if (bik < n)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGRAY << 4) | GREEN));
		printf("Это было число ");
		for (i = 0; i < n; i++)
		{
			printf("%d", zagad[i]);
		}
		printf("\n");
	}
	SetConsoleTextAttribute(hConsole, (WORD)((LIGHTCYAN << 4) | DARKGRAY));
	system("pause");
}