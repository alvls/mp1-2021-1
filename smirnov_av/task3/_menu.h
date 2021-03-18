#include <iostream>
#include <stdarg.h> 
#include <string>
#include <Windows.h>
using namespace std;

class Menu
{
private:
	int countActs;
	int lastChoice;
	string* nameAct;
	char* keys;
public:
	Menu()
	{
		countActs = 0;
		lastChoice = 0;
		nameAct = nullptr;
		keys = nullptr;
	}

	Menu(int _countActs)
	{
		countActs = _countActs;
		lastChoice = 0;
		nameAct = new string[countActs];
		keys = new char[countActs];
	}

	~Menu()
	{
		delete[]nameAct;
		delete[]keys;
	}

	//установить количество команд в меню
	void SetCountActs(int _countActs)
	{
		countActs = _countActs;
	}

	//узнать количество команд в меню
	int GetCountActs()
	{
		return countActs;
	}

	//установить позицию в меню, ключ и название пункта
	void SetAct(int number,char key, string name)
	{
		nameAct[number] = name;
		keys[number] = key;
	}

	//печать меню
	void PrintMenu(int x, int y)
	{
		COORD position;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < countActs; i++)
		{
			position.X = x;
			position.Y = y++;
			SetConsoleCursorPosition(hConsole, position);
			cout << keys[i] << " ";
			cout << nameAct[i] << endl;	
		}
	}

	//выбор пользователя с возвращением номера ключа
	int Choice(char choice)
	{
		for (int i = 0; i < countActs; i++)
		{
			if (keys[i] == choice)
			{
				lastChoice = i;
				return i;
			}
		}
		lastChoice = -1;
		return -1;
	}

	//получение номера последнего выбора(начиная с 0)
	int GetLastChoice()
	{
		return lastChoice;
	}

	//печать последнего выбора
	void PrintChoicedAct()
	{
		cout << nameAct[lastChoice] << endl;
	}


};