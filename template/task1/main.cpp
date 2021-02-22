#include <iostream>
#include "long_num.cpp"

using namespace std;

void Div()
{
	long long num1;
	long long num2;
	system("cls");
	cout << "Продемонстрирую на маленьких, а большие выберите сами" << endl;
	LongNumber a(-543543543543);
	cout << "a = ";
	a.Print();
	cout << endl;
	LongNumber b(-50435043);
	cout << "b = ";
	b.Print();
	cout << endl;
	cout << "a / b = ";
	LongNumber c = a / b;
	c.Print();
	cout << endl;
	cout << "a % b = ";
	c = a % b;
	c.Print();
	cout << endl;
	
	LongNumber d(100000);
	cout << "d = ";
	d.Print();
	cout << endl;
	LongNumber e(500);
	cout << "e = ";
	e.Print();
	cout << endl;
	cout << "d / e = ";
	c = d / e;
	c.Print();
	cout << endl;
	cout << "d % e = ";
	c = d % e;
	c.Print();
	cout << endl;

	cout << "Теперь можете ввести свои числа" << endl;
	cout << "num1: ";
	cin >> num1;
	cout << endl;
	cout << "num2: ";
	cin >> num2;
	cout << endl;
	LongNumber _num1(num1);
	LongNumber _num2(num2);
	cout << "num1 / num2 = ";
	c = _num1 / _num2;
	c.Print();
	cout << endl;
	cout << "a % b = ";
	c = _num1 % _num2;
	c.Print();
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	char choice;
	LongNumber a(10000000000000000);
	cout << "a = ";
	a.Print();
	cout << endl;
	cout << "b = ";
	LongNumber b(43432406054);
	b.Print();
	cout << endl;
	cout << "a + b = ";
	LongNumber c = a + b;
	c.Print();
	cout << endl;
	cout << "b - a = ";
	c = b - a;
	c.Print();
	cout << endl;
	cout << "a - b = ";
	c = a - b;
	c.Print();
	cout << endl;
	LongNumber d(-7);
	LongNumber res = b * d;
	cout << "b * (-7) = ";
	res.Print();
	cout << endl;
	cout << "Деление работает очень медленно при больших числах, поэтому вызывается принудительно" << endl;
	cout << "Все равно хотите попробовать? 1- Да! 2-Нет!" << endl;
	cin >> choice;
	if (choice == '1')
	{
		Div();
	}
	else
	{
		cout << "Ну и славно:)";
	}
	system("pause");

}