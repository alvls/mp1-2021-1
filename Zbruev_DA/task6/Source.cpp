#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>
using  namespace std;
class computer
{
protected:
	int len;//длина числа
	int cow;
	int buffalo;
	int n;
public:
	computer()
	{
		cow = 0;
		buffalo = 0;
		n = 0;
		len = 0;
	}
	void make_number(int ln)
	{
		len = ln;
		vector <int> no_repeat;
		no_repeat.push_back(0);
		srand(time(NULL));
		int tmp;
		bool flag = true;
		for (int i = 0; i < len; i++)
		{
			do
			{
				flag = true;
				tmp = rand() % 10;

				for (int j = 0; j < no_repeat.size(); j++)//цикл проверки на неповторяемость цифр числа
				{
					if (no_repeat[j] == tmp)
						flag = false;
				}
			} while (flag == false);//если на первой итерации рандомное число tmp=0
			n = n * 10 + tmp;
			no_repeat.push_back(tmp);
		}
	}
	void count_cow_and_buf(int n_user)
	{
		cow = 0;
		buffalo = 0;
		int step;
		int* n_user_mas = new int[len];
		for (int i = len - 1; i >= 0; i--)//старший разряд иммет индекс 0 в массиве
		{
			n_user_mas[i] = n_user % 10;
			n_user = n_user / 10;
		}
		int n_copy = n;
		for (int i = len - 1; i >= 0; i--)//сравниваем число P с числом b, которое загадал компьютер
		{
			step = n_copy % 10;
			n_copy = n_copy / 10;
			for (int j = 0; j < len; j++)
			{
				if (n_user_mas[j] == step)
				{
					cow++;
					break;
				}
			}
			if (step == n_user_mas[i])
			{
				buffalo++;
				cow--;
			}
		}
		delete[] n_user_mas;
	}
	void set_number(int N)
	{
		n = N;
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
		attempt = 0;
		std::cout << "Введите длину числа (для выхода нажмите 0): ";
		std::cin >> len;
		make_number(len);
		cow = 0;
		buffalo = 0;
		while (1)
		{
			std::cout << "Введите число n-значной длины: ";
			std::cin >> n_user;
			attempt++;
			set_number(n);
			count_cow_and_buf(n_user);
			buffalo = get_buffalo();
			cow = get_cow();
			if (buffalo == len)
			{
				std::cout << "Вы выиграли!" << '\n';
				std::cout << "Всего попыток: " << attempt << '\n';
				break;
			}
			std::cout << "Число коров: " << cow << '\n';
			std::cout << "Число быков: " << buffalo << '\n';
		}
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	int n = 0, tmp;
	game Game;
	Game.menu();
	system("pause");
}