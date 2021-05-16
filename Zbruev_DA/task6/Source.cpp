#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
class randomgenerator //загадать число
{
protected:
	int len;//длина числа
	//int n;//число
public:
	randomgenerator()
	{
		len = 0;
		//n=0;
	}
	int make_number(int ln)
	{
		len = ln;
		int n = 0;
		srand(time(NULL));
		int tmp;
		//n = get_number();//иначе ошибка
		for (int i = 0; i < len; i++)
		{
			do
			{
				tmp = rand() % 10;
				n = n * 10 + tmp;
			} while (n == 0);//если на первой итерации рандомное число tmp=0
		}
		std::cout << n << '\n';//потом убрать!
		return (n);
	}
	int get_len()
	{
		return(len);
	}
};
class computer : public randomgenerator
{
	//randomgenerator r;
	//computer *random;
protected:
	int cow;
	int buffalo;
	int n;
public:
	computer()//выдать быки-коровы
	{
		//random = NULL;
		cow = 0;
		buffalo = 0;
		n = 0;
	}
	/*int get_number()
	{
		return(n);
	}*/
	/*void set_number(int num)
	{
		n = num;
	}*/
	void count_cow_and_buf(int n_user)
	{
		cow = 0;
		buffalo = 0;
		int step;
		int l;
		l = get_len();
		int* n_user_mas = new int[l];
		for (int i = l - 1; i >= 0; i--)//старший разряд иммет индекс 0 в массиве
		{
			n_user_mas[i] = n_user % 10;
			n_user = n_user / 10;
		}
		for (int i = l - 1; i >= 0; i--)//сравниваем число P с числом b, которое загадал компьютер
		{
			int n_copy = n;
			step = n_copy % 10;
			n_copy = n_copy / 10;
			for (int j = 0; j < l; j++)
			{
				if (n_user_mas[j] == step)
					cow++;
			}
			if (step == n_user_mas[i])
			{
				buffalo++;
				cow--;
			}
		}
		delete[] n_user_mas;
	}
	int set_number(int ln)
	{
		n = make_number(ln);
	}
	int get_cow()
	{
		return(cow);
	}
	int get_buffalo()
	{
		return(buffalo);
	}
};

class game : private computer {//menu
	//randomgenerator r;
	//computer c;
	int n_gamer;
	int n_user;
	int attempt = 0;
public:
	game()
	{
		n_gamer = 0;
		n_user = 0;
		attempt = 0;
	}
	void menu()
	{
		//int n, len;
		attempt = 0;
		std::cout << "Введите длину числа (для выхода нажмите 0): ";
		std::cin >> len;
		n = make_number(len);
		cow = 0;
		buffalo = 0;
		while (1)
		{
			//int n = set_number(5);
			std::cout << "Введите число n-значной длины: ";
			std::cin >> n_user;
			attempt++;
			count_cow_and_buf(n_user);
			buffalo = get_buffalo();
			cow = get_cow();
			if (buffalo == len)
			{
				std::cout << "Вы выиграли!" << '\n';
				std::cout << "Всего попыток: " << attempt << '\n';
				break;
			}
			//else {
			std::cout << "Число коров: " << cow << '\n';
			std::cout << "Число быков: " << buffalo << '\n';
			//}
		}
	}
	//set_number(tmp);

};
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	int n = 0, tmp;
	game Game;

	/*for (int i = 0; i < 5; i++)
	{
		do
		{
			tmp = rand() % 10;
			std::cout << tmp << "\n";
			n = n * 10 + tmp;
		} while (n == 0);//если на первой итерации рандомное число tmp=0
	}*/
	/*randomgenerator rnd;
	n=rnd.make_number(5);
	std::cout << n << "\n";*/
	Game.menu();
	system("pause");
}