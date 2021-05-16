#pragma once
#include "Game.h"
#define DELAY 2300
#define COUNT_MENU_CHOICES 3

void EndWindow(bool isWin)
{
	system("cls");
	if (isWin)
		cout << "Поздравляю, Вы победили!";
	else
		cout << "Вы проиграли :(";
}

void ShowMenu()
{
	gotoxy(0, 0);
	cout << "Новая игра" << endl;
	cout << "Настройки" << endl;
	cout << "Выход" << endl;
}

void ShowSettings(int& needScore,int& speed, int& width, int& height)
{
	bool exit = false;

	int choice = 0;
	int temp = 0;
	bool showMenu = true;
	while (!exit)
	{
		if (showMenu)
		{
			cout << "1)Нужное количество очков для победы: " << needScore << endl;
			cout << "2)Ширина поля: " << width << endl;
			cout << "3)Высота поля: " << height << endl;
			cout << "4)Скорость игры: " << speed << endl;
			cout << "ESC - Выход из меню настроек" << endl;
			cout << "Что Вы хотели бы изменить?" << endl;
		}
		showMenu = true;
		choice = _getch();
		switch (choice)
		{
		case 49:
			system("cls");
			cout << "Старое значение нужного количества очков для победы: " << needScore << endl;
			cout << "Новое значение нужного количества очков для победы: ";
			cin >> needScore;
			break;
		case 50:
			system("cls");
			cout << "Старое значение ширины поля: " << width << endl;
			cout << "Новое значение ширины поля: ";
			cin >> width;
			break;
		case 51:
			system("cls");
			cout << "Старое значение высоты поля: " << height << endl;
			cout << "Новое значение высоты поля: ";
			cin >> height;
			break;
		case 52:
			system("cls");
			cout << "Старое значение скорости игры: " << speed << endl;
			cout << "Новое значение скорости игры(Чем меньше значение, тем быстрее двигается змейка): ";
			cin >> speed;
			break;
		case 27:
			system("cls");
			exit = true;
			break;
		default:
			choice = _getch();
			showMenu = false;
		}
	}
}

void StartGame(int needScore = 15,int speed = 120,int width = 28 , int height = 20)
{
	bool isWin = false;
	bool exit = false;
	int choice;
	while (!exit)
	{
		Game game(needScore,speed, width + 2, height + 2);
		game.StartGame();
		isWin = game.GetResult();
		EndWindow(isWin);
		cout << endl;
		cout << "Еще разок? 1 - Да, 2 - Нет" << endl;
		choice = _getch();
		if (choice == 50)
		{
			cout << "Вы набрали:" << game.GetScore() << " очков" << endl;
			Sleep(DELAY);
			system("cls");
			break;
		}
		game.NewTry();
		system("cls");
	}
}

void main()
{
	setlocale(LC_ALL, "ru");
	system("color F0");
	bool exit = false;
	int choice;
	int needMode = 0;
	int needScore = 15;
	int width = 28;
	int height = 20;
	int speed = 120;

	while(!exit)
	{

		ShowMenu();
		gotoxy(0, needMode);
		choice = _getch();
		if (choice == 224)
			choice = _getch();

		switch (choice)
		{
		case UP:
			needMode--;
			break;
		case DOWN:
			needMode++;
			break;
		case ENTER:
			if (needMode == 0)
			{
				StartGame(needScore,speed,width,height);		
			}	
			else if (needMode == 1)
			{
				system("cls");
				ShowSettings(needScore,speed, width, height);				
			}
			else if (needMode == 2)
				return;
		}
		if (needMode > COUNT_MENU_CHOICES - 1)
			needMode = COUNT_MENU_CHOICES - 1;
		if (needMode < 0)
			needMode = 0;
		
	}
	system("pause");
}