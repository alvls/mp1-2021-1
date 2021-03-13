#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

class String
{
private:
	int size;
	char* str;
public:
	String()
	{
		size = 40;
		str = new char[1];
		str[0] = '\0';
	}
	String(char* ss)
	{
		size = strlen(ss);
		str = new char[size + 1];
		strcpy(str, ss);
	}
	~String()
	{
		delete[] str;
	}
	void PrintString()
	{
		cout << "���� ������: " << str << endl;
	}
	int LengthString()
	{
		return size;
	}
	char CharByIndexString(int index)
	{
		return str[index];
	}
	void EditCharByIndexString(int index, char symbol)
	{
		str[index] = symbol;
	}
	char* SubstringFromAString(int indexLeft, int indexRight)
	{
		int sizeSub = indexRight - indexLeft + 1;
		int sizeFor;
		char* substr = new char[sizeSub];
		int i = indexLeft - 1, n = 0;
		sizeFor = i + sizeSub;
		for (i; i <= sizeFor; i++)
		{
			if (i == sizeFor)
			{
				substr[n] = '\0';
			}
			else
			{
				substr[n] = str[i];
				n++;
			}
		}
		return substr;
	}
	bool PalindromeString()
	{
		int i = 0;
		for (i; i < size / 2; ++i)
		{
			if (str[i] != str[size - i - 1])
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	int LatinCharString()
	{
		char* countChar = new char[size];
		strcpy(countChar, str);
		char symbolCheck;
		int i, j, k, count = 0, n = 0;
		bool check = true;
		for (k = 0; k < size; k++)
		{
			if (str[k] >= 'A' && str[k] <= 'Z' || str[k] >= 'a' && str[k] <= 'z' || str[k] == ' ')
			{
			}
			else
			{
				check = false;
				break;
			}
		}
		if (check == true)
		{
			for (i = 0; i <= size; i++)
			{
				if (str[i] != ' ')
				{
					symbolCheck = str[i];
					for (j = i + 1; j < size; j++)
					{
						if (countChar[j] == symbolCheck)
						{
							countChar[j] = '\0';
						}
					}
				}
			}
			for (i = 0; i < size; i++)
			{
				if (countChar[i] != '\0' && countChar[i] != ' ')
				{
					count++;
				}
			}
			return count;
		}
		else
		{
			return 0;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	bool end = true, checkIndex;
	int size=256, indexMenu = 0, index, indexRight;
	char *ss=new char[size];
	char symbol;
	cout << "����� ����������!" << endl;
	cout << "��������� �������� ������ � ��������� ���������..." << endl;
	cout << "������� ������: ";
	cin.getline(ss, 256);
	String s(ss);
	while (end)
	{
		cout << "\n��������� �����: \n" << "1. ������� ������;\n" << "2. ������ ����� ������;\n" << "3. �������� ������ ������ �� ��� �������;\n"
			<< "4. �������� ������ ������ �� ��������� �������;\n" << "5. �������� ��������� �� ������;\n"
			<< "6. ���������, �������� �� ������ �����������;\n"
			<< "7. �����, ������� ��������� �������� ���������� �������� ���������� � ������;\n" << "8. ����� �� ���������.\n"<< endl;
		cout << "�������� ����� ����: ";
		cin >> indexMenu;
		cout << endl;
		switch (indexMenu)
		{
			case 1:
			{
				s.PrintString();
				break;
			}
			case 2:
			{
				cout << "����� ������ ����������: " << s.LengthString() << endl;
				break;
			}
			case 3:
			{
				checkIndex = true;
				while (checkIndex)
				{
					cout << "������� ������ �� 1 �� " << s.LengthString() << " ����� ������ ������: ";
					cin >> index;
					index -= 1;
					if (index >= 0 && index < s.LengthString())
					{
						cout << "\n������ �� ��������� �������: " << s.CharByIndexString(index) << endl;
						checkIndex = false;
					}
					else
					{
						cout << "\n������ ������� �� ����������, ����������, ���������� ��� ���!" << endl << endl;
					}
				}
				break;
			}
			case 4:
			{
				cout << "����� �������� ������, ���������� ����� ������ �� 1 �� " << s.LengthString() << ": ";
				cin >> index;
				index -= 1;
				cout << "\n������� ������, �� ������� ������ ��������: ";
				cin >> symbol;
				s.EditCharByIndexString(index, symbol);
				break;
			}
			case 5:
			{
				checkIndex = true;
				while (checkIndex)
				{
					cout << "����� �������� ��������� �� ������, ������� ����� � ������ ������ (������� ����� ������ � �� 1 �� " << s.LengthString() << "): ";
					cin >> index >> indexRight;
					if ((index < 0 && indexRight > s.LengthString()) || (index > indexRight) || (index > s.LengthString() && indexRight < 0))
					{
						cout << "\n������� �������� ��������! ����� ������� ������ ���� ������ ������ ������� � ������ 0!\n������ ������� �� ����� ���� ������ �����!" << endl;
						cout << "����������, ���������� ��� ���!" << endl << endl;
					}
					else
					{
						cout << "���������� ���������: " << s.SubstringFromAString(index, indexRight) << endl;
						checkIndex = false;
					}
				}
				break;
			}
			case 6:
			{
				if (s.PalindromeString() == false)
				{
					cout << "�� �������� �����������!" << endl;
				}
				else
				{
					cout << "�������� �����������!" << endl;
				}
				break;
			}
			case 7:
			{
				if (s.LatinCharString() != 0)
				{
					cout << "������ �������� " << s.LatinCharString() << " ��������� ���� �� ���������� ��������!" << endl;
				}
				else
				{
					cout << "������! ������ ������ ��������� ������ ��������� �������!" << endl;
				}
				break;
			}
			case 8:
			{
				cout << "�� ��������! ������� ��� ��������������� ����� ����������!\n" << endl;
				end = false;
				break;
			}
			default:
			{
				cout << "������ ����� ���� �� ������, ���������� ��� ���!" << endl << endl;
				break;
			}
		}
	}
	system("pause");
	return 0; 
}