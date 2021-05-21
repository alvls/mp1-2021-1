#include "MyGame.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>

const char FOOD = '*';
const char TIMEBONUSFOOD = '$';

void MyGame::DrawDisplay()
{
	int k = 0;
	int width_tmp = width + 4;
	while (k != 2)
	{
		for (int i = 0; i < width_tmp; i++)
		{
			if (i == 0 || i == 1 || i == width_tmp - 2 || i == width_tmp - 1)
			{
				cout << '#';
				continue;
			}
			cout << '-';
		}
		cout << endl;
		k++;
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width_tmp; j++)
		{
			if (j == 0 || j == 1 || j == width_tmp - 2 || j == width_tmp - 1)
			{
				cout << '|';
				continue;
			}
			cout << ' ';
		}
		cout << endl;
	}
	k = 0;
	while (k != 2)
	{
		for (int i = 0; i < width_tmp; i++)
		{
			if (i == 0 || i == 1 || i == width_tmp - 2 || i == width_tmp - 1)
			{
				cout << '#';
				continue;
			}
			cout << '-';
		}
		cout << endl;
		k++;
	}
}

void MyGame::Game()
{
	char ch = 75;
	rating = 0;
	int numfruit = 0;
	snake.RestartSnake(MyCoordXY(width / 2, height / 2));
	Condition status = Ok;
	MyCoordXY delta(-1, 0);
	MyCoordXY food = CreateFood();
	DrawDisplay();
	snake.DrawSnake(console);
	console.SetColor(2, 0);
	console.GoAndDrawSymbol(food.x, food.y, FOOD);
	console.SetColor(15, 0);
	ShowStatistics(numfruit);
	do
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
			}
		}
		switch (ch)
		{
		case 27: //exit
			status = Exit;
			break;
		case 75: //left
			delta = MyCoordXY(-1, 0);
			break;
		case 77: //right
			delta = MyCoordXY(1, 0);
			break;
		case 72: //up
			delta = MyCoordXY(0, -1);
			break;
		case 80: //down
			delta = MyCoordXY(0, 1);
			break;
		case 97: //left
			delta = MyCoordXY(-1, 0); // 'a' 97
			break;
		case 100: //right
			delta = MyCoordXY(1, 0); // 'd' 100
			break;
		case 119: //up
			delta = MyCoordXY(0, -1); // 'w' 119
			break;
		case 115: //down
			delta = MyCoordXY(0, 1); //'s' 115
			break;
		case 104: //pause - h
			_getch();
			break;
		default:
			break;
		}
		MyCoordXY head = snake.Head();
		head += delta;
		if (head.x == 1 || head.x == width + 2 || head.y == 1 || head.y == height + 2 || snake.IntoSnake(head))
		{
			status = Died;
		}
		if (numfruit == numfood)
		{
			status = Win;
			ShowStatistics(numfruit);
		}	
		if (status == Ok)
		{
			snake.MoveSnake(delta,console);
			if (snake.Head() == food)
			{
				numfruit++;
				if (numfruit % 5 == 0)
				{
					snake.GrowSnake(3);
					food = CreateFood();
					console.SetColor(2, 0);
					console.GoAndDrawSymbol(food.x, food.y, FOOD);
					rating += 30;
				}
				else if (numfruit % 10 == 4 || numfruit % 10 == 9)
				{
					snake.GrowSnake(1);
					food = CreateFood();
					console.SetColor(5, 0);
					console.GoAndDrawSymbol(food.x, food.y, TIMEBONUSFOOD);
					rating += 10;
				}
				else
				{
					snake.GrowSnake(1);
					food = CreateFood();
					console.SetColor(2, 0);
					console.GoAndDrawSymbol(food.x, food.y, FOOD);
					rating += 10;
				}
				console.SetColor(15, 0);
				ShowStatistics(numfruit);
			}
			Sleep(latency);
		}
		else if (status == Died)
		{
			LoserGame();
		}
		else if (status == Win)
		{
			WinnerGame();
		}
	} while (status == Ok);
	console.SetColor(15, 0 );
}

MyCoordXY MyGame::CreateFood()
{
	MyCoordXY food;
	do
	{
		food.x = rand() % width + 2;
		food.y = rand() % height + 2;
	} while (snake.IntoSnake(food));
	return food;
}

MyGame::MyGame(MyDisplay& _displ, int _width, int _height, int _latency) :width(_width), height(_height), latency(_latency), console(_displ)
{
	srand(time(NULL));
	rating = 0;
	numfood = 105;
}

void MyGame::LogoGame()
{
	console.ChangePosCursor(30, 5);
	cout <<"M Y  S N A K E  \n\n\n"
		<< "\t___________________________________________________________\n"
		<< "\t|                                                         |\n"
		<< "\t|                               $                         |\n"
		<< "\t|    oooooooooooooo                                       |\n"
		<< "\t|                 o                                       |\n"
		<< "\t|  *              o          $                            |\n"
		<< "\t|                 o                                       |\n"
		<< "\t|                 o                                       |\n"
		<< "\t|                 o                                       |\n"
		<< "\t|             Ooooo                                       |\n"
		<< "\t|                                                         |\n"
		<< "\t|                                                         |\n"
		<< "\t|                         $                               |\n"
		<< "\t|        *                                                |\n"
		<< "\t|                                                   *     |\n"
		<< "\t|_________________________________________________________|\n";
	Sleep(3000);
	console.ClsConsole();
}

void MyGame::WinnerGame()
{
	console.SetColor(6, 0);
	console.ChangePosCursor(20, height / 2);
	cout << "M Y      C O N G R A T U L A T I O N S!";
	console.ChangePosCursor(10, (height / 2 ) + 3);
	cout << "Y O U   A R E   A   W I N N E R   O F   T H I S   G A M E!!!" << endl;
	console.ChangePosCursor(0, height + 5);
	console.SetColor(15, 0);
	console.PauseConsole();
}

void MyGame::LoserGame()
{
	console.SetColor(2, 0);
	console.ChangePosCursor((width / 2) - 5, height / 2);
	cout << "O H , N O . . . ";
	console.ChangePosCursor((width / 2) - 10, (height / 2) + 2);
	cout << "G A M E   O V E R!!!" << endl;
	console.ChangePosCursor((width / 4) - 5 , (height / 2) + 6);
	console.SetColor(6, 0);
	cout << "T R Y   A G A I N   A N D   Y O U   W I L L   A   W I N N E R!";
	console.ChangePosCursor(0, height + 5);
	console.PauseConsole();
}

void MyGame::TakeNickName(string& str)
{
	nickname = str;
}

void MyGame::MainMenu()
{
	const int NUM_MENU_ITEMS = 3;
	int activeMenuItem = 1;
	int ch = 0;
	bool exit = false;
	while (!exit)
	{
		ShowMainMenu();
		console.ChangePosCursor(0, activeMenuItem);
		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}
		switch (ch)
		{
		case 27:
			exit = true;
			break;
		case 72:
			activeMenuItem--;
			break;
		case 80:
			activeMenuItem++;
			break;
		case 13:
			if (activeMenuItem == 1)
			{
				console.ClsConsole();
				console.HideCursor();
				Game();
				console.ShowCursor();
			}
			else if (activeMenuItem == 2)
			{
				SettingMenu();
			}
			else if (activeMenuItem == 3)
			{
				exit = true;
			}
		}
		if (activeMenuItem < 1)
		{
			activeMenuItem = 1;
		}
		if (activeMenuItem > NUM_MENU_ITEMS)
		{
			activeMenuItem = NUM_MENU_ITEMS;
		}
	}
}

void MyGame::ShowMainMenu()
{
	console.ClsConsole();
	cout << "\t\tМ Е Н Ю" << endl;
	cout << " 1. Начать новую игру" << endl;
	cout << " 2. Настройки игры" << endl;
	cout << " 3. Выход из игры" << endl;
}

void MyGame::SettingMenu()
{
	const int NUM_MENU_ITEMS = 4;
	int activeMenuItem = 1;
	int ch = 0;
	bool exit = false;
	while (!exit)
	{
		console.ClsConsole();
		cout << "\t\tН А С Т Р О Й К И" << endl;
		cout << " 1. Задать размер поля" << endl;
		cout << " 2. Задать скорость змейки" << endl;
		cout << " 3. Задать сложность игры" << endl;
		cout << " 4. Выход в главное меню" << endl;
		console.ChangePosCursor(0, activeMenuItem);
		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}
		switch (ch)
		{
		case 27:
			exit = true;
			break;
		case 72:
			activeMenuItem--;
			break;
		case 80:
			activeMenuItem++;
			break;
		case 13:
			if (activeMenuItem == 1)
			{
				MapDimensionsMenu();
			}
			else if (activeMenuItem == 2)
			{
				SnakeSpeedMenu();
			}
			else if (activeMenuItem == 3)
			{
				DifficultyMenu();
			}
			else if (activeMenuItem == 4)
			{
				exit = true;
			}
		}
		if (activeMenuItem < 1)
		{
			activeMenuItem = 1;
		}
		if (activeMenuItem > NUM_MENU_ITEMS)
		{
			activeMenuItem = NUM_MENU_ITEMS;
		}
	}
}

void MyGame::MapDimensionsMenu()
{
	const int NUM_MENU_ITEMS = 4;
	int activeMenuItem = 1;
	int ch = 0;
	bool exit = false;
	while (!exit)
	{
		console.ClsConsole();
		cout << "\t\tП А Р А М Е Т Р Ы   П О Л Я" << endl;
		cout << " 1. Маленькое поле" << endl;
		cout << " 2. Среднее поле" << endl;
		cout << " 3. Большое поле (только для полноэкранного режима)" << endl;
		cout << " 4. Выход в настройки" << endl;
		console.ChangePosCursor(0, activeMenuItem);
		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}
		switch (ch)
		{
		case 27:
			exit = true;
			break;
		case 72:
			activeMenuItem--;
			break;
		case 80:
			activeMenuItem++;
			break;
		case 13:
			if (activeMenuItem == 1)
			{
				SetMapDimensions(80, 24);
			}
			else if (activeMenuItem == 2)
			{
				SetMapDimensions(100, 30);
			}
			else if (activeMenuItem == 3)
			{
				SetMapDimensions(120, 36);
			}
			else if (activeMenuItem == 4)
			{
				exit = true;
			}
		}
		if (activeMenuItem < 1)
		{
			activeMenuItem = 1;
		}
		if (activeMenuItem > NUM_MENU_ITEMS)
		{
			activeMenuItem = NUM_MENU_ITEMS;
		}
	}
}

void MyGame::SnakeSpeedMenu()
{
	const int NUM_MENU_ITEMS = 4;
	int activeMenuItem = 1;
	int ch = 0;
	bool exit = false;
	while (!exit)
	{
		console.ClsConsole();
		cout << "\t\tП А Р А М Е Т Р Ы   С К О Р О С Т И" << endl;
		cout << " 1. Медленно" << endl;
		cout << " 2. Умеренно" << endl;
		cout << " 3. Быстро" << endl;
		cout << " 4. Выход в настройки" << endl;
		console.ChangePosCursor(0, activeMenuItem);
		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}
		switch (ch)
		{
		case 27:
			exit = true;
			break;
		case 72:
			activeMenuItem--;
			break;
		case 80:
			activeMenuItem++;
			break;
		case 13:
			if (activeMenuItem == 1)
			{
				SetSpeedSnake(100);
			}
			else if (activeMenuItem == 2)
			{
				SetSpeedSnake(75);
			}
			else if (activeMenuItem == 3)
			{
				SetSpeedSnake(50);
			}
			else if (activeMenuItem == 4)
			{
				exit = true;
			}
		}
		if (activeMenuItem < 1)
		{
			activeMenuItem = 1;
		}
		if (activeMenuItem > NUM_MENU_ITEMS)
		{
			activeMenuItem = NUM_MENU_ITEMS;
		}
	}
}

void MyGame::DifficultyMenu()
{
	const int NUM_MENU_ITEMS = 4;
	int activeMenuItem = 1;
	int ch = 0;
	bool exit = false;
	while (!exit)
	{
		console.ClsConsole();
		cout << "\t\tП А Р А М Е Т Р Ы   С Л О Ж Н О С Т И" << endl;
		cout << " 1. Легко" << endl;
		cout << " 2. Средне" << endl;
		cout << " 3. Сложно" << endl;
		cout << " 4. Выход в настройки" << endl;
		console.ChangePosCursor(0, activeMenuItem);
		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}
		switch (ch)
		{
		case 27:
			exit = true;
			break;
		case 72:
			activeMenuItem--;
			break;
		case 80:
			activeMenuItem++;
			break;
		case 13:
			if (activeMenuItem == 1)
			{
				SetScoreForVictory(100);
			}
			else if (activeMenuItem == 2)
			{
				SetScoreForVictory(150);
			}
			else if (activeMenuItem == 3)
			{
				SetScoreForVictory(200);
			}
			else if (activeMenuItem == 4)
			{
				exit = true;
			}
		}
		if (activeMenuItem < 1)
		{
			activeMenuItem = 1;
		}
		if (activeMenuItem > NUM_MENU_ITEMS)
		{
			activeMenuItem = NUM_MENU_ITEMS;
		}
	}
}

void MyGame::ShowStatistics(int numfruit)
{
	console.ChangePosCursor(2, height + 4);
	cout << "Ваше имя: " << nickname << " || Ваш рейтинг: " << rating << " || Количество съеденных фруктов: " << numfruit << " || Нужно для победы: " << numfood << " || Размер змейки: " << snake.Size() << endl;
}
