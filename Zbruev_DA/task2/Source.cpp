#include <clocale>
#include <iostream>
#include <cmath>
#include <cstdlib>
#define N 8//число пунктов в меню 
class Matrix
{
	int** matr;
	int size=0;//число строк
public:
	Matrix(int razmer)//конструктор
	{
		int i, j;
		size = razmer;
		matr = (int**)malloc(sizeof(int) * size*size);
		for (int i = 0; i < /*size1*/size; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * size);
		}
		for (i = 0; i < size; i++)
		  for (j = 0; j < size; j++)
			matr[i][j] = 0;
	}
	void new_matrix(int size_new)//меняет размер матрицы
	{

		int i, j;
		for (i = 0; i < size; i++) {//освобождаем старую память, чтобы выделить новую (при этом объект не удаляется)
			free(matr[i]);
		}
		free(matr);
		size = size_new;
		matr = (int**)malloc(sizeof(int) * size * size);
		for (i = 0; i < size; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * size);
		}
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				matr[i][j] = 0;
	}
	Matrix(const Matrix &m)//конструктор копирования
	{
		size = m.size;
		matr = (int**)malloc(sizeof(int) * size * size);
		for (int i = 0; i < size; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * size);
		}
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				matr[i][j] = m.matr[i][j];
	}
	void getmatr(int num1, int num2, int elem)//инициализация матрицы по номеру
	{
		matr[num1][num2] = elem;
	}
	int setmatr(int num1, int num2)//возвращает элемент по номеру
	{
		return(matr[num1][num2]);
	}
	~Matrix()//деструктор
	{
		for (int i = 0; i < size; ++i) {
			free(matr[i]);
		}
		free(matr);
	}
	int setsize(void)//узнать размер
	{
		return(size);
	}
	bool diagonal()//проверка на диагональное преобладание
	{
		int i, j, flag;
		bool f=true;//так как если матрица состоит из 1 элемента, то цикл ни разу не выполнится, а матрица из 1 элемента обладает диагональным преобладанием 
		for (i = 0; i < size; i++)
		{
			flag = 0;
			for (j = 0; j < size; j++)//проблема с j
			{
				if (matr[i][i] >= matr[i][j])
					flag++;
				else
					break;
			}
			if (flag == size)//математически должен быть size -1, но поскольку в цикле 1 раз элемент сравнивается сам с собой, то просто size
				f = true;
			else
			{
				f = false;
				break;
			}
		}
		return (f);
	}
    Matrix operator+(const Matrix& m)// перегрузка оператора "+" 
	{
		Matrix res(size);
		int i, j, elem;
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				res.matr[i][j] = this->matr[i][j] + m.matr[i][j];
			}
		return res;
	}
};

void showmenu()
{
	char* menu[N] = { "Изменить размер квадратной матрицы (число строк или столбцов) ", "Узнать размер матрицы", "Задать элемент матрицы по его индексам", "Инициализировать матрицу полностью (по прядку вводя ее элементы)", "Узнать элемент матрицы по его индексам", "Проверить, обладает ли матрица диагональным преобладанием", "Вычислить сумму двух матриц одного размера", "Выход" };//массив с названиями операций
	short int menu_number[N] = { 1, 2, 3, 4, 5, 6, 7, 0 };//массив с номерами каждого пункта меню
	int i;
	std::cout << "Операции: " << '\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i] << ". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "Введите номер операции, которую необходимо выполнить: ";
}

void full_init(Matrix& m, int size)//функция полной инициализации матрицы (для удобства)
{
	int elem, i, j;//инициализация происходит по порядку
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			std::cout << "Введите элемент с индексами " << (i + 1) << "," << (j + 1) << "(первый индекс - номер строки, второй - номер столбца)" << ":";
			std::cin >> elem;
			m.getmatr(i, j, elem);
		}
	}
}
void main()
{
	int size, num1, num2, elem, number=1, i, j;
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите размер квадратной матрицы (число строк или столбцов): ";//чтобы пользователь не забыл задать размер матрицы, да и иначе не скомпилируется
	std::cin >> size;
	while (size <= 0)//проверка введенных данных
	{
		std::cout << "Недопустимо - отрицательный размер матрицы, попытайтесь заново: ";
		std::cin >> size;
	}
	Matrix m1(size), m2(size);
	while (number != 0)
	{
		showmenu();
		std::cin >> number;
		switch (number)
		{
		case 1:
			std::cout << "Введите размер квадратной матрицы (число строк или столбцов): ";
			std::cin >> size;
			while (size <= 0)//проверка введенных данных
			{
				std::cout << "Недопустимо - отрицательный размер матрицы, попытайтесь заново: ";
				std::cin >> size;
			}
			m1.new_matrix(size);
			m2.new_matrix(size);//меняем размер второй матрицы, чтобы ее можно было просуммировать с первой
			break;
		case 2://узнать размер
			std::cout << "Размер матрицы: "<<m1.setsize() << 'x' << m1.setsize() << '\n';
			break;
		case 3://задать элемент по индексам
			std::cout << "Введите номер элемента(строка), нумерация начинается с 1: ";
			std::cin >> num1;
			while ((num1 <= 0) || (num1>size))//проверка введенных данных
			{
				std::cout << "Недопустимый номер строки, попытайтесь заново: ";
				std::cin >> num1;
			}
			std::cout << "Введите номер элемента(столбец), нумерация начинается с 1: ";
			std::cin >> num2;
			while ((num2 <= 0) || (num2 > size))//проверка введенных данных
			{
				std::cout << "Недопустимый номер стобца, попытайтесь заново: ";
				std::cin >> num2;
			}
			std::cout << "Введите элемент: ";
			std::cin >> elem;
			m1.getmatr(num1-1, num2-1, elem);//(num1-1), поскольку нумерация элементов массива начинается с 0, а в математике номера элементов начинаются с 1
			break;
		case 4://полная инициализация матрицы по порядку(для удобства)
			full_init(m1, size);
			break;
		case 5://узнать элемент по индексам
			std::cout << "Введите номер элемента, который хотите узнать(строка), нумерация начинается с 1: ";
			std::cin >> num1;
			while ((num1 <= 0) || (num1 > size))//проверка введенных данных
			{
				std::cout << "Недопустимый номер строки, попытайтесь заново: ";
				std::cin >> num1;
			}
			std::cout << "Введите номер элемента, который хотите узнать(столбец), нумерация начинается с 1: ";
			std::cin >> num2;
			while ((num2 <= 0) || (num2 > size))//проверка введенных данных
			{
				std::cout << "Недопустимый номер стобца, попытайтесь заново: ";
				std::cin >> num2;
			}
			std::cout << "Искомый элемент: "<<m1.setmatr((num1-1), (num2-1)) << '\n';
			break;
		case 6://проверка на диагональное преобладание
			if (m1.diagonal()==true)
				std::cout << "Матрица обладает диагональным преобладанием"<<'\n';
			else
				std::cout << "Матрица не обладает диагональным преобладанием" << '\n';
			break;
		case 7://сложение двух матриц
			//предполагается, что матрицу m1 пользователь инициализировал (в противном случае все ее элементы раны 0), теперь необходимо инициализировать матрицу m2
			std::cout << "Для выполнения операции сложения двух матриц проинициализируйте вторую матрицу "<<'\n';
			full_init(m2, size);
			Matrix m=m1+m2;//сейчас просто печатает матрицу m2
			std::cout <<"Получившаяся сумма: "<< '\n';
			for (i = 0; i < size; i++)//вывод получившейся суммы на экран
			{
				for (j = 0; j < size; j++)
				{
					std::cout << m.setmatr(i, j) << "  ";
				}
				std::cout << '\n';
			}
			break;
		}

	}
	system("pause");
}