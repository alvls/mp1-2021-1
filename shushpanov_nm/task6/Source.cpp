#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <conio.h>
#include <windows.h>

using namespace std;

class SequenceGenerator
{
private:
	int count = 0, number = 0, numberCheck = 0, randomInterval = 0, data = 0, power = 0, powRandom = 0, powVerification = 0, dateVerification = 0;
	bool done = true, isInit = false;
public:
	SequenceGenerator() {};
	~SequenceGenerator() {};
	void Init()
	{
		isInit = true;
		srand(time(NULL));
	}
	int GeneratorNumber(int n)
	{
		if (isInit == false)
			Init();
		done = true;
		while (done)
		{
			randomInterval = NewRandomInterval(n);
			number = rand() % randomInterval;
			if (VeriferNumber(n))
			{
				done = false;
				return number;
			}
		}
	}
	bool VeriferNumber(int n)
	{
		count = 0;
		data = number;
		for (int i = n; i > 0; i--)
		{
			power = i - 1;
			powRandom = pow(10, power);
			data = number / powRandom % 10;
			if ((data == 0) && (power == n - 1))
			{
				count++;
				break;
			}
			for (int j = i - 1; j > 0; j--)
			{
				powVerification = pow(10, (j - 1));
				dateVerification = number / powVerification % 10;
				if (data == dateVerification)
				{
					count++;
					break;
				}
			}
		}
		if (count == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int NewRandomInterval(int n)
	{
		return pow(10, n);
	}
};

class GameInteractor
{
private:
	int n, cow, bull, count;
	string randomNumber, playerNumber;
	bool done, endGame, debugging;
	char key;
	SequenceGenerator generator;
public:
	GameInteractor(int _n = 0, string _randomNumber = "\0", string _playerNumber = "\0", int _cow = 0, int _bull = 0, int _count = 0, bool _done = true, bool _endGame = true, bool _debugging = false) : n(_n), randomNumber(_randomNumber), playerNumber(_playerNumber), cow(_cow), bull(_bull), count(_count), done(_done), endGame(_endGame), debugging(_debugging) {};
	~GameInteractor() {};
	bool CheckNumber(int number)
	{
		if (number >= 2 && number <= 5)
		{
			n = number;
			return true;
		}
		else
		{
			return false;
		}
	}
	void GuessTheNumber()
	{
		if (n != 0)
		{
			cout << "\n��������� ���������� �����.." << endl;
			stringstream ss;
			ss << generator.GeneratorNumber(n);
			randomNumber = ss.str();
			ShowRandomNumber();
			cout << "��������� ������� �����..\n" << endl;
		}
		else
		{
			cout << "\n������� ���������� ���� � �����..\n" << endl;
		}
	}
	void ShowRandomNumber()
	{
		if (debugging == true)
			cout << randomNumber << endl;
	}
	void SetNumberOfDigits()
	{
		cow = 0;
		done = true;
		while (done)
		{
			cout << "\n������� ����� �� 2 �� 5: ";
			cin >> n;
			if (!CheckNumber(n))
			{
				cout << "\n���������� ��� ���, ����� ������ ���� �� ��������� �� 2 �� 5..\n" << endl;
			}
			else
			{
				cout << endl;
				done = false;
			}
		}
	}
	void RefreshData()
	{
		endGame = true;
		cow = 0;
		bull = 0;
		count = 0;
	}
	int CountCow()
	{
		cow = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if ((randomNumber[i] == playerNumber[j]) && (i != j))
					cow++;
			}
		}
		return cow;
	}
	int CountBull()
	{
		bull = 0;
		for (int i = 0; i < n; i++)
		{
			if (randomNumber[i] == playerNumber[i])
				bull++;
		}
		return bull;
	}
	bool WinGame()
	{
		if (CountBull() == n)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool CheckSize()
	{
		if (randomNumber.size() == n)
			return true;
		else
			return false;
	}
	bool CheckUserNumber()
	{
		done = true;
		while (done)
		{
			cout << "������� ����� �����, ����� ����� �� �����������: ";
			cin >> playerNumber;
			if (playerNumber.size() != n)
			{
				cout << "\n���� ����� ������ ���� ������� " << n << "\n����������, ���������� ��� ���!\n" << endl;
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	void StartGame()
	{
		if (CheckSize())
		{
			if (CheckRandomNumber())
			{
				RefreshData();
				cout << "\n������� ����:\n ���������� �����, ��������� ����� ��� �������� '���' - ������� ����� � ������� �����;\n '������' - ������� �����, �� �������� �������.\n" << endl;;
				while (endGame)
				{
					cout << "���� ������ ����� �� ����, �� ������� 'ESC', �����, ������� ����� ������ �������." << endl;
					key = _getch();
					if (key != 27)
					{
						if (CheckUserNumber())
						{
							count++;
							if (WinGame())
							{
								endGame = false;
								cout << "\n�����������! �� ��������!\n���������� ����� �������: " << count << "\n" << endl;
							}
							else
							{
								cout << "\n�����: " << CountCow() << " �����: " << CountBull() << "\n" << endl;
							}
						}
					}
					else
					{
						endGame = false;
						if (count != 0)
						{
							cout << "\n�� �������!\n����� ����� �������: " << count << "\n" << endl;
						}
						else
						{
							cout << "\n�� �������!\n" << endl;
						}
					}
				}
			}
			else
			{
				cout << "\n������� ���������� ���� ����� ��� ����� ��������� �������� ����� ����� ������� ����!\n" << endl;
			}
		}
		else
		{
			cout << "\n���������� ���� ����������� ����� �� ������������ ���������� ��������� ���� ����!\n" << endl;
		}
	}
	bool CheckRandomNumber()
	{
		if (randomNumber != " " && randomNumber != "\0")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Debug()
	{
		if (debugging == false)
		{
			debugging = true;
			cout << "\n����� ������� �������..\n" << endl;
		}
		else
		{
			debugging = false;
			cout << "\n����� ������� ��������..\n" << endl;
		}
	}
};

class MenuGame
{
private:
	int indexMenu = -1;
	bool done = true;
	GameInteractor game;
public:
	MenuGame() {};
	~MenuGame() {};
	void StartMenu()
	{
		cout << "����� ����������! \n" << endl;
		ShowMenu();
	}
	void ShowMenu()
	{
		cout << "������ ����:\n 1. ������ ���������� ���� � �����; \n 2. �������� �����; \n 3. ������ ����; \n 4. ����� ������� (�������� ���������� �����); \n 0. �����." << endl;
		ItemSelection();
	}
	void ItemSelection()
	{
		done = true;
		while (done)
		{
			cout << "\n�������� ����� ����: ";
			cin >> indexMenu;
			if (CheckItemSelection(indexMenu))
			{
				switch (indexMenu)
				{
				case 1:
				{
					game.SetNumberOfDigits();
					ShowMenu();
					break;
				}
				case 2:
				{
					game.GuessTheNumber();
					ShowMenu();
					break;
				}
				case 3:
				{
					game.StartGame();
					ShowMenu();
					break;
				}
				case 4:
				{
					game.Debug();
					ShowMenu();
					break;
				}
				case 0:
				{
					cout << "\n���������!\n������� ��� ��������������� ����� ����������!\n" << endl;
					break;
				}
				}
				done = false;
			}
			else
			{
				cout << "\n������ ������ ���� �� ����������, ����������, ���������� ��� ���!" << endl;
			}
		}
	}
	bool CheckItemSelection(int indexMenu)
	{
		if (indexMenu >= 0 && indexMenu <= 4)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");
	MenuGame game;
	game.StartMenu();
	system("pause");
	return 0;
}