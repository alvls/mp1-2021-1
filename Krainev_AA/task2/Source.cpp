﻿/*Разработать класс Строка.
Класс должен хранить строку символов произвольной длины(от 0 до 40).
Класс должен предоставлять следующие операции:
1) задать строку,
2) узнать длину строки,
3) получить символ строки по его индексу,
4) изменить символ строки по заданному индексу,
5) выделить подстроку из строки,
6) проверить, является ли строка палиндромом,
7) найти, сколько разных символов латинского алфавита содержится в строке.
Класс должен содержать все необходимые конструкторы,
деструктор, оператор присваивания, а также «уметь» выводить себя на консоль.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <locale>
using namespace std;
void printMainMenu();
void welcomMessege();
//enum TCmystringExeption { strINDOUTOFRANGE };
class String
{
private:
	char* str;
	int len;
public:
	//конструктор по умолчанию без аргументов 
	String();
	// конструктор с одним аргументом
	String(char* val);
	//конструктор который принимает длину строки
	String(int lenOther);
	//для печати str
	void printStr();
	//задать строку 
	void scanString(char* getChar);
	//Для получения длины (2)
	int  getLength();

	//для получения символа строки по индексу(3)
	char getSymbolByIndex(int index);

	//изменить символ строки по индексу(4)
	void changeSymbolByIndex(int index, char zamena);

	//выделить строку из-под строки(5)
	//void extractSubstring(int left, int lenSub, String *sub);
	String extractSubstring(int left, int lenSub);
	//счетчик буковок(6)
	void countChar();//

	//проверка на полиндром(7)
	bool checkPolyindrome();
	~String();
};

int main()
{
	setlocale(LC_ALL, "rus");
	const int strLimit = 40;
	int menuExit = true; // для менюшек
	char* stringForOperation = new char[strLimit];
	welcomMessege();
	cout << "Введите строку" << endl;
	cin.getline(stringForOperation, strLimit);
	String objectForOperation(stringForOperation);
	while (1) {
		printMainMenu();
		int variantMenu;
		cout << "Введите номер нужного пункта" << endl;
		cin >> variantMenu;
		while ((variantMenu < 1) || (variantMenu) > 8) {
			cout << "Такого пункта меню нет. Повторите ввод заново!" << endl;
			cin >> variantMenu;
		}
		switch (variantMenu) {
		case 1:
			cout << "Введенная строка:" << endl;
			objectForOperation.printStr();
			break;
		case 2:
			cout << "Количество символов в текущей строке:" << endl;
			cout << objectForOperation.getLength() << endl;
			cout << "Это число включает в себя число пробелов, в том числе которые могли поставить по ошибке в конце предложения" << endl;
			cout << "________________________________________________________________________________________" << endl;
			break;
		case 3:
			//cout << "Введите индекс элемента, который хотите вернуть" << endl;
			int index;
			cout << "Введите индекс интересующего элемента." << endl;
			cin >> index;
			while ((index > objectForOperation.getLength()) || (index < 1)) {
				cout << "Элемента с таким индексом нет. Повторите ввод заново." << endl;
				cin >> index;
			}
			cout << "Возвращенный индекс:" << "' " << objectForOperation.getSymbolByIndex(index) << " '" << endl;
			//cout <<"_______" <<objectForOperation.getSymbolByIndex(index) << endl;
			cout << "________________________________________________________________________________________" << endl;
			break;
		case 4:

			cout << "Введите индекс элемента, который хотите изменить" << endl;
			cin >> index;
			while ((index > objectForOperation.getLength()) || (index < 1)) {
				cout << "Элемента с таким индексом нет. Повторите ввод заново." << endl;
				cin >> index;
			}
			char symbol;
			cout << "Введите символ, на который хотите заменить" << endl;
			cin >> symbol;
			objectForOperation.changeSymbolByIndex(index, symbol);
			cout << "Получившаяся строка:" << endl;
			objectForOperation.printStr();
			cout << "________________________________________________________________________________________" << endl;
			break;
		case 5: {
			cout << "Сейчас вы сможете выделить подстроку из строки" << endl;
			cout << "Для этого нужно будет ввести индекс с которого начать выделять и количество символов, которые нужно выделить" << endl;
			cout << "Введите индекс символа с которого нужно начать" << endl;
			int left;
			cin >> left;
			cout << "Введите длину нужной подстроки" << endl;
			int len;
			cin >> len;
			// hfString* sub = new String(len + 1);
			//objectForOperation.extractSubstring(left, len, sub);
			cout << "Выделенная подстрока: ";
			objectForOperation.extractSubstring(left, len).printStr();
			//рабочая со звездой если objectForOperation.extractSubstring(left, len)->printStr();
			//p.printStr();
			cout << "________________________________________________________________________________________" << endl;
			break;
		}
		case 6:
			cout << "Здесь будет выведено какие и сколько символов в строке находятся. Если вдруг вы изменяли строку" << endl;
			cout << "в режиме 4, то произойдет разбор измененной строки." << endl;
			cout << "Сколько каждых символов в строке:" << endl;
			objectForOperation.countChar();
			cout << "________________________________________________________________________________________" << endl;
			break;
		case 7:
			cout << "Сейчас будет проверочка на полиндром" << endl;
			if (objectForOperation.checkPolyindrome() == true) {
				cout << "Полиндром" << endl;
			}
			else { cout << "Не полиндром" << endl; }
			cout << "________________________________________________________________________________________" << endl;
			break;
		case 8:
			return 0;
		}
	}

}
//констрктор по умолчанию
String::String() {
	//cout << "Сработал конструктор по умолчанию" << endl;
	len = 0;
	str = new char[1];
	str[0] = '\0';//строка по умолчанию
}

String::String(char* val) {
	//cout << "Сработал конструктор принимающий char" << endl;
	scanString(val);
}

String::String(int lenOther) {
	//cout << "Сработал конструктор принимающий int" << endl;
	len = lenOther;
	const int lenOtherConst = lenOther + 1;
	str = new char[lenOtherConst];
}

void String::printStr()
{
	cout << str << endl;
}
void String::scanString(char* getChar)
{
	{
		if (getChar == nullptr) {
			str = new char[1];
			str[0] = '\0';
		}
		else {
			str = new char[strlen(getChar) + 1];
			// Копируем символ getChar []
			// используя strcpy
			strcpy(str, getChar);
			//cout << "Переданная строка : " << str << endl;
		}
	}
	len = strlen(str);
}

int String::getLength() {
	return len;
}

char String::getSymbolByIndex(int index) {
	return str[index - 1];
}

void String::changeSymbolByIndex(int index, char zamena) {
	str[index - 1] = zamena;
}
/*
void String::extractSubstring(int left, int lenSub, String* sub)
{
	for (int i = 1; i <= lenSub; i++) {
		sub->str[i - 1] = str[left - 1];
		left++;
	}
	sub->str[lenSub] = '\0';
}*/

bool String::checkPolyindrome() {
	//int i, j;
	/*//для отладочки
	for (i = 0; i <len;++i)
	{

		cout << "В прямом порядке" << endl;
		cout << str[i] << endl;
	}
	for (i = len-1; i >=0; --i)
	{

		cout << "В обратном порядке" << endl;
		cout << str[i] << endl;
	}
	*/
	for (int i = 0, j = len - 1; i <= j; ++i, --j) {
		if (str[i] != str[j]) {
			//cout << "Не полиндром\n";
			return false;
		}
	}
	//cout << "Полиндром\n";
	return true;
}

String::~String()
{
	delete[] str;
}

void printMainMenu()
{
	cout << "Меню:" << endl;
	cout << "________________________________________________" << endl;
	cout << "1.Узнать введенную строку" << endl;
	cout << "2.Узнать длину строки" << endl;
	cout << "3.Получить символ строки по индексу" << endl;
	cout << "4.Изменить символ строки по его индексу" << endl;
	cout << "5.Выделить подстроку из строки" << endl;
	cout << "6.Подсчитать символы" << endl;
	cout << "7.Проверка является ли полиндромом" << endl;
	cout << "8.Выход" << endl << endl;
}
void welcomMessege() {
	cout << "Добро пожаловать!" << endl;
	cout << "Вам будет предложено ввести строку и выбрать что с ней сделать." << endl;
	cout << "Программа считает пробел как символ. Не забывайте об этом!!!" << endl;
}
String String::extractSubstring(int left, int lenSub) {
	static String sub(lenSub);

	for (int i = 1; i <= lenSub; i++) {
		sub.str[i - 1] = str[left - 1];
		left++;
	}
	sub.str[lenSub] = '\0';
	//cout <<"Получаем : " <<sub->str << endl;
	return sub;
}
void String::countChar() {
	char* disassemble;
	disassemble = new char[len];
	int flag = 0;
	int i, j, k = 0;
	int countOfWord = 1; //для подсчета количества символиков
	int l = len;
	for (i = 0; i < l; i++) {
		for (j = 0; j <= k; j++) {
			if (str[i] == disassemble[j]) {
				countOfWord = 1;
				flag = 1;
			}
		}
		if (flag == 1) {
			flag = 0;
			continue;
		}
		for (j = i + 1; j < l; j++) {
			if (str[i] == str[j])
				countOfWord++;
		}
		disassemble[k++] = str[i];
		cout << "'" << str[i] << "'" << " таких: " << countOfWord << endl;
		countOfWord = 1;
	}
	delete[] disassemble;
}