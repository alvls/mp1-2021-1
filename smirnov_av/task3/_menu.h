#include <iostream>
#include <stdarg.h> 
#include <string>
#include <Windows.h>
using namespace std;

class Menu
{
private:
	int countChoices;
	int lastChoice;
	string* str;
	char* keys;
public:
	Menu()
	{
		countChoices = 0;
		lastChoice = 0;
		str = nullptr;
		keys = nullptr;
	}

	Menu(int countChoices)
	{
		this->countChoices = countChoices;
		lastChoice = 0;
		str = new string[countChoices];
		keys = new char[countChoices];
	}

	Menu(int countChoices, string ...)
	{
		this->countChoices = countChoices;
		lastChoice = 0;
		str = new string[countChoices];
		va_list lastParm;
		va_start(lastParm,countChoices);
		for (int i = 0; i < countChoices; i++)
		{
			str[i] =  va_arg(lastParm, string);
		}
		va_end(lastParm);
	}

	~Menu()
	{
		delete[]str;
		str = nullptr;
		delete[]keys;
		keys = nullptr;
		countChoices = 0;
		lastChoice = 0;
	}

	//установить количество выборов в меню
	void SetCountChoices(int countChoices)
	{
		this->countChoices = countChoices;
	}

	//получить количество выборов в меню
	int GetCountChoices()
	{
		return countChoices;
	}

	//установить положение в меню, ключ и название пункта
	void SetChoice(int number,char key, string name)
	{
		str[number] = name;
		keys[number] = key;
	}

	//печать меню
	void PrintMenu(int x, int y)
	{
		COORD position;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < countChoices; i++)
		{
			position.X = x;
			position.Y = y++;
			SetConsoleCursorPosition(hConsole, position);
			cout << keys[i] << " ";
			cout << str[i] << endl;
			
		}
	}

	//выбор пользователя с возвращением номера ключа
	int Choice(char choice)
	{
		for (int i = 0; i < countChoices; i++)
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
		if (lastChoice == -1)
			cout << "Ошибка выбора" << endl;
		cout << str[lastChoice] << endl;
	}






};