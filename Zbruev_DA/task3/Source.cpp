#include <clocale>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#define N 7//число пунктов в меню 
class Text_editor
{
	char* str;
	int size = 0;//длина поля ввода
	int num_whitespace = 0;//число пробелов (горизонталь)
	int indent_line = 0;//вертикаль
public:
	Text_editor(int razmer)//конструктор
	{
		size = razmer;
		str = new char[size + 1];//чтобы дописать \0 в конце
		str[size] = '\0';//чтобы в конце строки всегда стоял символ конца строки
	}
	void setvvod(int size_new)//изменить длину поля ввода
	{
		int i;
		delete[] str;
		size = size_new;
		str = new char[size + 1];
		str[size] = '\0';//чтобы в конце строки всегда стоял символ конца строки
	}
	
	void setpozition(int num_line, int num_ws)//установка положения поля ввода
	{
		num_whitespace = num_ws;//число пробелов (горизонталь)
		indent_line = num_line;//вертикаль
	}
	void setstr()//инициализацияя строки
	{

		system("cls");
		std::cout << "Введите строку: ";
		indent_line++;
		set_cursor();
		std::cin >> str;
		indent_line--;
	}

	int getsize()//задать длину поля ввода
	{
		return(size);
	}
	int get_indent_line_pos()//узнать положение поля ввода
	{
		return(indent_line);
	}
	int get_whitespace_pos()//узнать положение поля ввода
	{
		return(num_whitespace);
	}
	void getstr()//узнать строку
	{
		system("cls");
		indent_line++;
		std::cout << "Строка: ";
		set_cursor();
		puts(str);
		std::cout << '\n';
		indent_line--;
	}
	void set_cursor()
	{
		COORD position;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		position.X= num_whitespace;
		position.Y= indent_line;
		SetConsoleCursorPosition(hConsole, position);
	}
	~Text_editor()//деструктор
	{
		delete[] str;
	}
};
void showmenu()
{
	char* menu[N] = { "Задать длину поля ввода ", "Узнать длину поля ввода ", "Задать позицию поля ввода в окне консоли", "Узнать позицию поля ввода в окне консоли", "Обеспечить ввод пользователем строки с длиной не больше длины поля ввода", "Вывести введенную пользователем строку", "Выход" };//массив с названиями операций
	short int menu_number[N] = { 1, 2, 3, 4, 5, 6, 0 };//массив с номерами каждого пункта меню
	int i;
	std::cout << "Операции: " << '\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i] << ". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "Введите номер операции, которую необходимо выполнить: ";
}
void main()
{
	int size, number = 1, num_line, num_ws;
	char* s;
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::cout << "Введите длину поля ввода: ";//для вызова конструктора
	std::cin >> size;
	while (size <= 0)//проверка введенных данных
	{
		std::cout << "Недопустимо - отрицательный размер поля ввода, попытайтесь заново: ";
		std::cin >> size;
	}
	Text_editor t(size);
	s = new char[size + 1];
	while (number != 0)
	{
		showmenu();
		std::cin >> number;
		switch (number)
		{
		case 1://задать размер поля ввода
			std::cout << "Введите размер поля ввода: ";
			std::cin >> size;
			while (size <= 0)//проверка введенных данных
			{
				std::cout << "Недопустимо - отрицательный размер поля ввода, попытайтесь заново: ";
				std::cin >> size;
			}
			t.setvvod(size);
			delete[] s;
			s = new char[size + 1];
			s[size] = '\0';
			break;
		case 2://узнать размер
			std::cout << "Размер поля ввода: " << t.getsize() << " символов" << '\n';
			break;
		case 3://Задать позицию поля ввода в окне консоли
			std::cout << "Введите смещение поля ввода по вертикали: ";
			std::cin >> num_line;
			std::cout << "Введите смещение поля ввода по горизонтали: ";
			std::cin >> num_ws;
			t.setpozition(num_line, num_ws);
			break;
		case 4://Узнать позицию поля ввода в окне консоли
			std::cout << "Смещение поля ввода по вертикали: " << t.get_indent_line_pos() << " строк";
			std::cout << "Смещение поля ввода по горизонтали: " << t.get_whitespace_pos() << " символов";
			break;
		case 5://ввод строки пользователем
			
			t.setstr();
			break;
		case 6://вывод строки на экран
			t.getstr();
		}
	}
	delete[] s;
	system("pause");
}