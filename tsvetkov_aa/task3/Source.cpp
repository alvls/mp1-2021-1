#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Redactor
{
private:
	char *str;
	int x, y;
	int buffer;
	int length;
public:
	Redactor()//конструктор
	{
		str = new char[5];
		x = 0; y = 0;
		length = 4;
		buffer = 5;
		str[length] = '\0';
	}
	void setlength(int l)//установка длины поля ввода
	{
		delete[] str;
		buffer = l + 1;
		length = l;
		str = new char[buffer];
		str[length] = '\0';
	}
	int getlength()//возврат длины поля ввода
	{
		return length;
	}
	void poz(int _x, int _y)//задание позиции поля в консоли
	{
		x = _x;
		y = _y;
	}
	int retX()//возврат координаты X
	{
		return x;
	}
	int  retY()//возврат координаты Y
	{
		return y;
	}
	void read()//текстовый редактор
	{
		char s;
		int i = 0;
		while (i != buffer)
		{
			s = _getch();
			switch (s) {
			case '\r':
				str[i] = '\0';
				return;
			case '\b':
				i--;
				if (i < 0)
					i++;
				else cout << "\b \b";
				break;
			default:
				if (i != length)
				{
					str[i] = s;
					cout << str[i];
					i++;
				}
			}
		}
	}
	char* line()//возврат строки
	{
		return str;
	}
	~Redactor()//деструктор
	{
		delete [] str;
	}
};

void position(int x, int y)//перемещение курсора в консоли
{
	COORD position;										
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	
	position.X = x;									// Установка координаты X
	position.Y = y;									// Установка координаты Y
	SetConsoleCursorPosition(hConsole, position);
}

int menu()
{
	int a;
	cout << "Выберите дальнейшее действие" << endl;
	cout << "1.Задать длину поля ввода" << endl << "2.Узнать длину поля ввода" << endl << "3.Задать позицию поля ввода в окне консоли" << endl << "4.Узнать позицию поля ввода в окне консоли" << endl <<
		"5.Ввести строку в текстовом редакторе" << endl << "6.Выдать введенную пользователем строку." << endl <<"0.Выход" << endl;
	cin >> a;
	return a;
}

void main()
{
	SetConsoleCP(1251);//русский язык при вводе в консоль
	SetConsoleOutputCP(1251);
	cout << "По умолчанию длина поля ввода равна 4" << endl;
	Redactor ak;
	char* str;
	int m, size=4, x=0, y=0;
p:
	m = menu();
	switch (m)
	{
	case 1://задание длины поля ввода
		cout << "Введите длину поля ввода" << endl;
	s:
		cin >> size;
		if (size < 0)
		{
			cout << "Неккоректная длина, введите снова" << endl;
			goto s;
		}
		ak.setlength(size);
		cout << "Значение успешно задано" << endl;
		break;
	case 2://возврат длины поля ввода
		size = ak.getlength();
		cout << "Длина поля ввода равна: " << size << endl;
		break;
	case 3://задание координат поля ввода
		cout << "Введите координаты X и Y " << endl;
	l:
		cin >> x >> y;
		if ((x < 0) || (y < 0))
		{
			cout << "Неккоректные координаты, введите снова" << endl;
			goto l;
		}
		ak.poz(x, y);
		cout << "Значение успешно задано" << endl;
		break;
	case 4://возврат координат поля ввода
		cout << "Координата по X: " << ak.retX() << endl;
		cout << "Координата по Y: " << ak.retY() << endl;
		break;
	case 5://размещение текстового редактора и ввод строки
		system("cls");
		position(x, y);
		ak.read();
		system("cls");
		break;
	case 6://вывод на консоль введенной пользователем строки
		str = ak.line();
		cout << str <<endl;
		break;
	case 0://выход из программы
		return;
		break;
	}
	goto p;	
}