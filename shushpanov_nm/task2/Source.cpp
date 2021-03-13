#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

class String
{
private:
	int size;
	char* str;
public:
	String()
	{
		size = 40;
		str = new char[1];
		str[0] = '\0';
	}
	String(char* ss)
	{
		size = strlen(ss);
		str = new char[size + 1];
		strcpy(str, ss);
	}
	~String()
	{
		delete[] str;
	}
	void PrintString()
	{
		cout << "Ваша строка: " << str << endl;
	}
	int LengthString()
	{
		return size;
	}
	char CharByIndexString(int index)
	{
		return str[index];
	}
	void EditCharByIndexString(int index, char symbol)
	{
		str[index] = symbol;
	}
	char* SubstringFromAString(int indexLeft, int indexRight)
	{
		int sizeSub = indexRight - indexLeft + 1;
		int sizeFor;
		char* substr = new char[sizeSub];
		int i = indexLeft - 1, n = 0;
		sizeFor = i + sizeSub;
		for (i; i <= sizeFor; i++)
		{
			if (i == sizeFor)
			{
				substr[n] = '\0';
			}
			else
			{
				substr[n] = str[i];
				n++;
			}
		}
		return substr;
	}
	bool PalindromeString()
	{
		int i = 0;
		for (i; i < size / 2; ++i)
		{
			if (str[i] != str[size - i - 1])
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	int LatinCharString()
	{
		char* countChar = new char[size];
		strcpy(countChar, str);
		char symbolCheck;
		int i, j, k, count = 0, n = 0;
		bool check = true;
		for (k = 0; k < size; k++)
		{
			if (str[k] >= 'A' && str[k] <= 'Z' || str[k] >= 'a' && str[k] <= 'z' || str[k] == ' ')
			{
			}
			else
			{
				check = false;
				break;
			}
		}
		if (check == true)
		{
			for (i = 0; i <= size; i++)
			{
				if (str[i] != ' ')
				{
					symbolCheck = str[i];
					for (j = i + 1; j < size; j++)
					{
						if (countChar[j] == symbolCheck)
						{
							countChar[j] = '\0';
						}
					}
				}
			}
			for (i = 0; i < size; i++)
			{
				if (countChar[i] != '\0' && countChar[i] != ' ')
				{
					count++;
				}
			}
			return count;
		}
		else
		{
			return 0;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	bool end = true, checkIndex;
	int size=256, indexMenu = 0, index, indexRight;
	char *ss=new char[size];
	char symbol;
	cout << "Добро пожаловать!" << endl;
	cout << "Программа работает только с латинским алфавитом..." << endl;
	cout << "Введите строку: ";
	cin.getline(ss, 256);
	String s(ss);
	while (end)
	{
		cout << "\nПрограмма умеет: \n" << "1. Вывести строку;\n" << "2. Узнать длину строки;\n" << "3. Получить символ строки по его индексу;\n"
			<< "4. Изменить символ строки по заданному индексу;\n" << "5. Выделить подстроку из строки;\n"
			<< "6. Проверить, является ли строка палиндромом;\n"
			<< "7. Найти, сколько различных символов латинского алфавита содержится в строке;\n" << "8. Выйти из программы.\n"<< endl;
		cout << "Выберите пункт меню: ";
		cin >> indexMenu;
		cout << endl;
		switch (indexMenu)
		{
			case 1:
			{
				s.PrintString();
				break;
			}
			case 2:
			{
				cout << "Длина строки составляет: " << s.LengthString() << endl;
				break;
			}
			case 3:
			{
				checkIndex = true;
				while (checkIndex)
				{
					cout << "Введите индекс от 1 до " << s.LengthString() << " чтобы узнать символ: ";
					cin >> index;
					index -= 1;
					if (index >= 0 && index < s.LengthString())
					{
						cout << "\nСимвол по заданному индексу: " << s.CharByIndexString(index) << endl;
						checkIndex = false;
					}
					else
					{
						cout << "\nТакого индекса не существует, пожалуйста, попробуйте еще раз!" << endl << endl;
					}
				}
				break;
			}
			case 4:
			{
				cout << "Чтобы изменить символ, необходимо вести индекс от 1 до " << s.LengthString() << ": ";
				cin >> index;
				index -= 1;
				cout << "\nВведите символ, на который хотите заменить: ";
				cin >> symbol;
				s.EditCharByIndexString(index, symbol);
				break;
			}
			case 5:
			{
				checkIndex = true;
				while (checkIndex)
				{
					cout << "Чтобы выделить подстроку из строки, введите левый и правый индекс (вводите через пробел и от 1 до " << s.LengthString() << "): ";
					cin >> index >> indexRight;
					if ((index < 0 && indexRight > s.LengthString()) || (index > indexRight) || (index > s.LengthString() && indexRight < 0))
					{
						cout << "\nВведены неверные значения! Левая граница должна быть меньше правой границы и больше 0!\nПравая граница не может быть меньше левой!" << endl;
						cout << "Пожалуйста, попробуйте еще раз!" << endl << endl;
					}
					else
					{
						cout << "Выделенная подстрока: " << s.SubstringFromAString(index, indexRight) << endl;
						checkIndex = false;
					}
				}
				break;
			}
			case 6:
			{
				if (s.PalindromeString() == false)
				{
					cout << "Не является палиндромом!" << endl;
				}
				else
				{
					cout << "Является палиндромом!" << endl;
				}
				break;
			}
			case 7:
			{
				if (s.LatinCharString() != 0)
				{
					cout << "Строка содержит " << s.LatinCharString() << " различных букв из латинского алфавита!" << endl;
				}
				else
				{
					cout << "Ошибка! Строка должна содержать только латинские символы!" << endl;
				}
				break;
			}
			case 8:
			{
				cout << "До свидания! Спасибо что воспользовались нашей программой!\n" << endl;
				end = false;
				break;
			}
			default:
			{
				cout << "Данный пункт меню не найден, попробуйте еще раз!" << endl << endl;
				break;
			}
		}
	}
	system("pause");
	return 0; 
}