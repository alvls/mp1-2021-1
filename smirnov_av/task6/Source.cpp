#pragma once
#include "Game.h"
#define DELAY 2300
#define COUNT_MENU_CHOICES 3

void EndWindow(bool isWin)
{
	system("cls");
	if (isWin)
		cout << "����������, �� ��������!";
	else
		cout << "�� ��������� :(";
}

enum Keys
{
	ENTER = 13,
	ECS = 27
};

void ShowMenu()
{
	gotoxy(0, 0);
	cout << "����� ����" << endl;
	cout << "���������" << endl;
	cout << "�����" << endl;
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
			cout << "1)������ ���������� ����� ��� ������: " << needScore << endl;
			cout << "2)������ ����: " << width << endl;
			cout << "3)������ ����: " << height << endl;
			cout << "4)�������� ����: " << speed << endl;
			cout << "ESC - ����� �� ���� ��������" << endl;
			cout << "��� �� ������ �� ��������?" << endl;
		}
		showMenu = true;
		choice = _getch();
		switch (choice)
		{
		case 49:
			system("cls");
			cout << "������ �������� ������� ���������� ����� ��� ������: " << needScore << endl;
			cout << "����� �������� ������� ���������� ����� ��� ������: ";
			cin >> needScore;
			break;
		case 50:
			system("cls");
			cout << "������ �������� ������ ����: " << width << endl;
			cout << "����� �������� ������ ����: ";
			cin >> width;
			break;
		case 51:
			system("cls");
			cout << "������ �������� ������ ����: " << height << endl;
			cout << "����� �������� ������ ����: ";
			cin >> height;
			break;
		case 52:
			system("cls");
			cout << "������ �������� �������� ����: " << speed << endl;
			cout << "����� �������� �������� ����(��� ������ ��������, ��� ������� ��������� ������): ";
			cin >> speed;
			break;
		case ECS:
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
		cout << "��� �����? 1 - ��, 2 - ���" << endl;
		choice = _getch();
		if (choice == 50)
		{
			cout << "�� �������:" << game.GetScore() << " �����" << endl;
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