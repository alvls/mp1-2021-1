#include <clocale>
#include <iostream>
#include <cmath>//можно ли создать динамический массив в привате;    размер массива в €чейках или числе строк;(8x8)    3 пункт - инициализаци€;    6 пункт - вторую матрицу вводим отдельно или нужен 2 класса типа Matrix?
class Matrix//класс 1, переменных 3
{
	int* matr;
public:
	/*int* new_matrix(int razmer)//возвращает указатель 
	{
		int* matr = new int[razmer];
		return (matr);
	}*/
	void getmatr(int num, int elem)//инициализаци€ матрицы по номеру
	{
		matr[num] = elem;
	}
	int setmatr(int num)//возвращает элемент по номеру
	{
		return(matr[num]);
	}
	Matrix(int razmer)
	{
		int i;
		int *matr = new int[razmer];
		for (i = 0; i < razmer; i++)
			matr[i] = 0;
	}
};

void main()
{
	int razmer, num, elem;
	setlocale(LC_ALL, "Russian");
	std::cout << "¬ведите размер: ";
	std::cin >> razmer;
	//std::cout << razmer;
	Matrix m1(razmer);
	std::cout << "¬ведите номер элемента: ";
	std::cin >> num;
	std::cout << "¬ведите элемент: ";
	std::cin >> elem;
	//std::cout << elem;
	m1.getmatr(num, elem);
	std::cout << "¬ведите номер элемента, который хотите узнать: ";
	std::cin >> num;
	elem = m1.setmatr(num);
	std::cout << elem << '\n';
	system("pause");
}