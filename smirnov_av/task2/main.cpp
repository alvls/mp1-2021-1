#include <iostream>
#include "_vector.cpp"

void main()
{
	using namespace std;
	setlocale(LC_ALL, "Russian");
	Vector a(3);
	a.SetComponent(0, 10);
	a.SetComponent(1, 10);
	a.SetComponent(2, 10);
	a.PrintVec();
	//Vector b = a;
	Vector b = a;
	b.SetComponent(1, 20);
	b.PrintVec();
	

	system("pause");
	

}

