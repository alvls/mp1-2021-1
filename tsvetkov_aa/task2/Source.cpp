#include <clocale>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class Matrix
{
private:
	int** matr;
	int size;
public:
	Matrix(int a)
	{
		int i = 0, j = 0;
		size = a;
		matr = (int**)malloc(sizeof(int*) * size);//создание двумерного массива size*size
		for (i = 0; i < size; i++)
			matr[i] = (int*)malloc(sizeof(int) * size);

		for (i = 0; i < size; i++)
		{
			for ( j = 0; j < size; j++)
				matr[i][j] = 0;//зануление элементов матрицы
		}


	}
	void setsize(int a)//задание размера матрицы
	{
		int i = 0,j=0;
		for (i = 0; i < size; i++)//очищаем старое
		{
			free(matr[i]);
		}
		free(matr);
		size = a;

		matr = (int**)malloc(sizeof(int*) * size );//создаем новую матрицу с новым размером
		for ( i = 0; i < size; i++)
			matr[i] = (int*)malloc(sizeof(int) * size);
		for (i = 0; i < size; i++)
		{
			for ( j = 0; j < size; j++)
				matr[i][j] = 0;
		}
	}
	int getsize()//возврат размера матрицы
	{
		return size;
	}
	void Print()//вывод матрицы на консоль
	{
		int i = 0, j = 0;
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				cout << matr[i][j] << "\t";
			}
			cout << endl;
		}

	}
	void setind(int i, int j, int a)//задание элемента по его индексу
	{
		matr[i][j] = a;
	}
	int getind(int i, int j)// возврта значения элемента по его индексу
	{
		return matr[i][j];
	}
	bool diag()//проверка на диагональное преобладание
	{

		int i=0,j=0, s; 
		int** a;
		a = (int**)malloc(sizeof(int*)* size);//двумерный массив из 2 столбцов и size строк
		// в нулевой столбец заносим значения элементов на диагонали, в первый сумму элементов каждой каждой строки

		for (i = 0; i < size; i++)  
		{
			a[i] = (int*)malloc(sizeof(int)*2);
		}
		bool flag = 1;//изначально true ,если найдется хоть один диагональный элемент меньше суммы элементов в строке flag становится 0
		for (i = 0; i < size; i++)
		{
			s = 0;
			a[i][0] = matr[i][i];
			for ( j = 0; j < size; j++)
			{
				if (j != i)
					s += matr[i][j];
			}
			a[i][1] = s;
		}
		for ( j = 0; j < size; j++)
			if (a[j][1] > a[j][0])
				flag = 0;
		for (i = 0; i < size; i++)//чистим созданный двумерный массив
		{
			free(a[i]);
		}

		free(a);
		return flag;
	}

	Matrix operator+ (const Matrix& c)//оператор сложения матриц одного размера
	{
		Matrix res(size);

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				res.matr[i][j] = matr[i][j] + c.matr[i][j];
			}
		return res;
	}

	Matrix(const Matrix& m)//конструктор копирования
	{
		int i = 0, j = 0;
		size = m.size;
		matr = (int**)malloc(sizeof(int*) * size);//создание матрицы
		for ( i = 0; i < size; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * size);
		}
		for ( i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				matr[i][j] = m.matr[i][j];
	}
	~Matrix()//деструктор
	{
		for (int i = 0; i < size; i++)
		{
			free(matr[i]);
		}
		free(matr);
	}

};


int menu()//Вывод меню на консоль и возврат значения режима работы
{
	int a;
	cout << "Выберите дальнейшее действие" << endl;
	cout << "1.Задать размер матрицы" << endl << "2.Узнать размер матрицы" << endl << "3.Задать элемент матрицы по его индексам" << endl << "4.Узнать элемент матрицы по его индексам" << endl<<
	"5.Проверить, обладает ли матрица диагональным преобладанием" << endl << "6.Вычислить сумму двух матриц одного размера" << endl <<"7.Вывести матрицу на консоль"<<endl<< "0.Выход" << endl;
	cin >> a;
	return a;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	int m, size, i=0, j=0, a;
	bool flag;
	Matrix p(2);
	cout << "По умолчанию размер квадратной матрицы равен 2" << endl;
	size = 2;//пригодится если пользователь в первый раз вызовет case 3,case 4 до setsize
p:
	m = menu();
	switch (m)
	{
	case 1://задание размера
		cout << "Введите размер матрицы" << endl;
		cin >> size;
		p.setsize(size);
		break;
	case 2://возврат размера
		size = p.getsize();
		cout << "Квадратная матрица " << size << " порядка" << endl;
		break;
	case 3://задание элемента по индексу
		cout << "Введите индекс элемента" << endl;
	l:
		cin >> i >> j;
		if ((i > size) || (i < 1) || (j > size) || (j < 1))
		{
			cout << "Несуществующий индекс,введите снова" << endl;
			goto l;
		}
		cout << "Введите присваиваемое значение" << endl;
		cin >> a;
		p.setind(i - 1, j - 1, a);
		cout << "Значение успешно задано" << endl;
		break;
	case 4://возврат элемента по индексу
		cout << "Введите индекс элемента" << endl;
	k:
		cin >> i >> j;
		if ((i > size) || (i < 1) || (j > size) || (j < 1))
		{
			cout << "Несуществующий индекс,введите снова" << endl;
			goto k;
		}
		a = p.getind(i - 1, j - 1);
		cout << "Элемент матрицы " << a << endl;
		break;
	case 5://проверка на диагональное преобладание
		flag = p.diag();
		if (flag == 1)
			cout << "Матрица обладает диагональным преобладанием" << endl;
		else cout << "Матрица не обладает диагональным преобладанием" << endl;
		break;
	case 6://суммирование матриц
	{
		size = p.getsize();
		Matrix c(size);

		for (i = 0; i < size; i++)//инициализация второго слагаемого-матрицы(задаем элементы с помощью setind)
		{
			cout << "Задайте значение элементов " << i + 1 << " строки" << endl;
			for (j = 0; j < size; j++)
			{
				cin >> a;
				c.setind(i, j, a);
			}

		}
		Matrix rep(p + c);
		cout << "Сумма матриц равна:" << endl;
		rep.Print();
		break;
	}
	case 7://для удобства вывод матрицы на экран(хотя в задании этого не требовалось)
		p.Print();
		break;
	case 0://выход из программы
		return;
		break;
	}
	goto p;
}