#include <iostream>
#include "_vector.h"

void main()
{
	using namespace std;
	setlocale(LC_ALL, "Russian");
	Vector a(5, 25, 74, 44, 64, -30);
	cout << "A:" <<endl;
	a.PrintVec();
	cout << "Размер A: " << a.GetSize() << endl;
	cout << "Длина A: " << a.LengthVec() << endl;
	cout << endl;
	char* str = "254 432 22 -3 321";
	Vector b;
	b.SetFromStr(str);
	cout << "B:" << endl;
	b.PrintVec();
	cout << endl;
	cout << "C = A + B:" << endl;
	Vector c = a + b;
	c.PrintVec();
	cout << endl;
	cout << "Скалярное проивзедение A и B: " << a.ScalarProduct(b)<<endl;
	cout << endl;
	cout << "2-ой компонент из A: " << a.GetComponent(1) << endl;
	cout << endl;
	a.SetComponent(1, 7);
	cout << "A после изменения второго компонента на 7:" << endl; 
	a.PrintVec();
	cout << endl;
	cout << "Увеличить размер вектора B на 3 ячейки с сохранением данных:" << endl;
	b.ChangeSize(8);
	b.PrintVec();

	system("pause");
}

