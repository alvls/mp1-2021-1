#include <clocale>
#include <iostream>
#include <cmath>//можно ли создать динамический массив в привате;    размер массива в €чейках или числе строк;(8x8)    3 пункт - инициализаци€;    6 пункт - вторую матрицу вводим отдельно или нужен 2 класса типа Matrix?
#include <cstdlib>
class Matrix//класс 1, переменных 3
{
	int** matr;
	int size=0;//число строк
	//int size2 = 0;//число столбцов
public:
	Matrix(int razmer /*int razmer2*/)
	{
		int i, j;
		size = razmer;
		//size2 = razmer2;
		//int* matr = new int[size];
		matr = (int**)malloc(sizeof(int) * size*size);
		for (int i = 0; i < /*size1*/size; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * size);
		}
		for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			matr[i][j] = 0;
	}
	/*int* new_matrix(int razmer)//возвращает указатель 
	{
		int* matr = new int[razmer];
		return (matr);
	}*/
	void getmatr(int num1, int num2, int elem)//инициализаци€ матрицы по номеру
	{
		matr[num1][num2] = elem;
	}
	int setmatr(int num1, int num2)//возвращает элемент по номеру
	{
		return(matr[num1][num2]);
	}
	~Matrix()
	{
		free (matr);
	}
	int setsize(void)//узнать размер
	{
		return(size);
	}
};

void main()
{
	int razmer, /*razmer2*/ num1, num2, elem;
	setlocale(LC_ALL, "Russian");
	std::cout << "¬ведите число строк: ";
	std::cin >> razmer;
	/*std::cout << "¬ведите число столбцов: ";
	std::cin >> razmer2;*/
	Matrix m1(razmer/*razmer2*/);
	std::cout << "¬ведите номер элемента(строка): ";
	std::cin >> num1;
	std::cout << "¬ведите номер элемента(столбец): ";
	std::cin >> num2;
	std::cout << "¬ведите элемент: ";
	std::cin >> elem;
	//std::cout << elem;
	m1.getmatr(num1, num2, elem);
	std::cout << "¬ведите номер элемента, который хотите узнать(строка): ";
	std::cin >> num1;
	std::cout << "¬ведите номер элемента, который хотите узнать(столбец): ";
	std::cin >> num2;
	elem = m1.setmatr(num1, num2);
	std::cout << elem << '\n';
	razmer = m1.setsize();
	std::cout << razmer <<'x'<< razmer <<'\n';
	system("pause");
}