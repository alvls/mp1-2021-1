#include <iostream>
#include <vector>
#include <iomanip>
#include <clocale>
#include <cstdlib>
#include <ctime>
using namespace std;

class RandomGenerator
{
	int leftBound;
	int rightBound;
	bool isInitialized;
public:
	RandomGenerator(int left = 0, int right = 10) : leftBound(left), rightBound(right), isInitialized(false)
	{}
	void init()
	{
		srand(time(NULL));
		isInitialized = true;
	}
	int getRandom()
	{
		if (!isInitialized)
		{
			init();
		}
		return rand() % (rightBound - leftBound) + leftBound;
	}
	vector <int> getRandomSequence(int size)
	{
		vector <int> setOfNumbers;
		int number;
		bool count = false;
		while (setOfNumbers.size() != size)
		{
			number = getRandom();
			for (int i = 0; i < setOfNumbers.size(); i++)
			{
				if (number == setOfNumbers[i])
				{
					count = true;
					break;
				}
			}
			if (count == false)
			{
				setOfNumbers.push_back(number);
			}
			count = false;
		}
		return setOfNumbers;
	}
	~RandomGenerator()
	{}
};

class GameBullsAndCows
{
	RandomGenerator* Random;
	vector <int> computerNumber;
	vector <int> userNumber;
	int size;
public:
	GameBullsAndCows(RandomGenerator* _Random)
	{
		Random = _Random;
		size = 0;
	}
	void setSize(int _size)
	{
		size = _size;
	}
	void setUserNumber(vector <int> number)
	{
		userNumber = number;
	}
	void makeNumber()
	{
		computerNumber = Random->getRandomSequence(size);
	}
	vector <int> getNumber()
	{
		return computerNumber;
	}
	int numberOfBulls()
	{
		int bulls = 0;
		for (int i = 0; i < size; i++)
		{
			if (userNumber[i] == computerNumber[i])
				bulls++;
		}
		return bulls;
	}
	int numberOfCows()
	{
		int cows = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (userNumber[i] == computerNumber[j])
					cows++;
			}
		}
		return cows - numberOfBulls();
	}
	~GameBullsAndCows()
	{}
};

int main()
{
	setlocale(LC_ALL, "rus");
	RandomGenerator Random;
	GameBullsAndCows Game(&Random);
	int size;
	int number;
	int bulls;
	int countSize = 0;
	vector <int> computerNumber;
	vector <int> userNumber;
	cout << "ИГРА <БЫКИ И КОРОВЫ>" << endl << endl;
	cout << "- Играют два игрока (человек и компьютер)." << endl;
	cout << "- Игрок выбирает длину загадываемого числа – n." << endl;
	cout << "- Компьютер «задумывает» n - значное число с неповторяющимися цифрами." << endl;
	cout << "- Игрок делает попытку отгадать число – вводит n - значное число с неповторяющимися цифрами." << endl;
	cout << "- Компьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе(то есть количество коров)" << endl;
	cout << "и сколько угадано вплоть до позиции в загаданном числе(то есть количество быков)." << endl;
	cout << endl << "Удачи!" << endl << endl;
	cout << "Введите размер числа: ";
	cin >> size;
	Game.setSize(size);
	Game.makeNumber();
	computerNumber = Game.getNumber();
	cout << "Компьютер загадал число: ";
	for (int i = 0; i < computerNumber.size(); i++) 
	{
		cout << computerNumber[i];
	}
	cout << "\nПопробуйте угадать число, загаданное компьютером (Придумайте n-значное число с неповторяющимися цифрами).\nЕсли захотите сдаться, введите 0." << endl;
	while (1)
	{
		cout << "Введите это число (оно не должно начинаться с 0): ";
		while (1)
		{
			cin >> number;
			if (number == 0)
			{
				cout << "Вы сдались." << endl;
				cout << "Число, загаданное компьютером: ";
				for (int i = 0; i < computerNumber.size(); i++)
				{
					cout << computerNumber[i];
				}
				cout << endl;
				return 0;
			}
			while (number > 0)
			{
				userNumber.push_back(number % 10);
				number /= 10;
				countSize++;
			}
			if (userNumber.size() == size)
				break;
			else
			{
				userNumber.clear();
				cout << "Число введено в неверном формате (число не должно быть короче или длинне загадываемого, а также оно не должно начинаться с 0)." << endl;
				cout << "Введите число ещё раз: ";
			}
		}
		reverse(userNumber.begin(), userNumber.end());
		cout << "\nПользователь ввел число: ";
		for (int i = 0; i < userNumber.size(); i++)
		{
			cout << userNumber[i];
		}
		cout << endl;
		Game.setUserNumber(userNumber);
		bulls = Game.numberOfBulls();
		cout << "Число быков: " << bulls << endl;
		cout << "Число коров: " << Game.numberOfCows() << endl << endl;
		userNumber.clear();
		if (bulls == size)
		{
			cout << "Поздравляю! Вы угадали, загаданное число!" << endl << endl;
			break;
		}
	}
	system("pause");
	return 0;
}