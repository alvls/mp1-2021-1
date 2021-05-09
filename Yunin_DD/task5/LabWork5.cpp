//����������� ������ �������� � �������������� �����.
//����� �������� ������ ����������� ������ ��������� �� ������ � ������ �������� �������� �������(� ������).
//����� ������ ������������ ������ � �������� � 100, 200, 500, 1000, 2000, 5000 ������.
//���������� ��� ����������� �� ���� �������� ����� ���������� 40 ��������(���������� �� �� �����������).
//������ ������� ����������� �������� � ��������� �������.������� ������ ������� � 2000 �����.
//�������, ��� ��������� �������� ��������� ���������� 80 % ��� ������ �������.
//�������, ��� ������ ����� ���������������� �� ������ ����������� �����(��� ��������� � ����� ����� �� �0001� �� �9999�).
//���� �������� �������� � ������ �������������� �����.������ �������� �������� ���� ����� ���� �� ������.
//�������, ��� ���������� � ������� ������� �� ������ �����, ��� ���������, ����� �� �����, (��� ��������� � ��� ������), 
//PIN - ����(������������������ �� 4 - � ����, ������ �� 0 �� 9).
//����� �������� ������ ������������� ��������� �������� : 1) ������� ����� �������, 2) ����� ������� �� ������ �����, 
//3) ��������� PIN - ���, 4) ����������� ��������� ����� �������, 5) ������ ������� ��������(������ �������� ����� �� �����), 
//6) ������� �� ������� ��������(�������� ���������� ����� �� ����), 
//7) ������������� ����� �������, ���� �� �� ������� ��� ���� ������ ������ �������� PIN - ���, 8) ������� ����� �������.
//��� �������� ������ �������������� ������������ ���������� �� ��������� ���� �����������.
//����� �������������� ����� ������ �������������� ��� ��������� ������ ������ �������� � ����� ���� ���������� � ���������� - ����������� ��������.

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <conio.h>

//� ��� ���� � ������ � ������ ������������� ����� ������������ ������ � ����� � ������� ������ ������� ����� � ������ ����� ������� ��������� ������� ��������
//��� ������� ��������� �����, ���������� ��������, ������� ����� ������������� ��� ����� ����� ���������� � �������������� �������,
//� ������ ��������, ��� ����� � ������� �������� �� �������������� �����, � �� ��������. ����� ���� ���� ������ � ������ �� � ����������� �� �����?
//�� ����� ��������� ������, ����� �� ����� �������������� ����� - �� ��, �� ����� �����, ���� ��� ����� �������� ��� �������������� ������.

//�������������� ����� - ��� � ���� ��� ������, ������� ��� � ����� ����� ��������� ������. � ����� ����� - ���������� � �������������

//� ��������� ����� ��������� �� ��, �� ��� ���� ����������, ����� ����� ������ ������������� ������ ��� ������������ ����� �������������� ��������� => ����� ��������������
//����� ����� ������������ ������. � ����� ���������������� ��� � ������� ������ ���������� �� �����. ��������� ��� - ���������� ���� ������ ��������� (��������� � ������ �������� �� �������� ����� � ������ ����� ������), ������� ��������
//� ������ ��������, ����������� ���������� � �������� ����������� ������� (� �� ��� ���������, ���� �� �����) � ����� �� ����� ����� ����� ������ � ���������.

using namespace std;

const int NumKinds = 6;//���������� ���������, �������� �� ���������� ������ ����� �����.
const int LimitOfNotes = 40;//���������� ���������, �������� ������� �������� �������� ��� ������ �����.
const int NumNotesInitially = 1600;//���������� ���������, �������� ������� ������� � ����� ����� ������� ����������� ����������.
const int LimitOfStore = 2000;//���������� ���������, �������� ������� ������� � ������ �������� ������.

int ArrOfParNotes[NumKinds] = { 100,200,500,1000,2000,5000 };//���������� ������ �������� �����, ���� � ������ ������ ����� ���� ���.

struct FIO
{
	string surname;
	string name;
	string patronymic;
};

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(Console, pos);
}

struct UserData
{
	FIO person;//�������, ��� � �������� ��������.
	string cardnum;//���� ������, ���������� �� ����� ����� (������� �� 4 ����).
	long summoney;//����� ����� �� �����.
	string pincode;//���-��� �����.
};

//������� ��� ����� �������� ������ �� �����.
ostream& operator<<(ostream& out, const UserData& data)
{
	out << "��� �������: " << data.person.surname << " " << data.person.name << " " << data.person.patronymic << endl << "����� ����� �������: " << data.cardnum << endl << "����� ����� �������: " << data.summoney << endl << "���-��� �������: " << data.pincode << endl;
	return out;
}

//������� ��� �������� ������ ���.
ostream& operator<<(ostream& out, const FIO& fio)
{
	out << fio.surname << " " << fio.name << " " << fio.patronymic;
	return out;
}

class ProcessingCenter
{
private:
	UserData* persons;//������ ������ �����.
	bool* arrofaccess;//������, �������� ���������� � ������� � ������������� �����.
	int numpeople;//���������� �����, ������ ������� �� ����� ���������.
	int nownumpeole;//���������� �����, ������ ������� ��� ��� ��������.

	//����� �������� �������, ��������� ���������� � �����.
	void CreateArraysOfPersons()
	{
		persons = new UserData[numpeople];
		arrofaccess = new bool[nownumpeole];
	}

	//����� ������� ���������� �������� � ������.
	int CountWhiteSymbols(string str)
	{
		int num = 0;
		size_t len;
		len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (str[i] == ' ')
			{
				num++;
			}
		}
		return num;
	}

	//����� ����� ���������� �����, ��� ������ ��� ���� � �������������� ������.
	int GetNowNumPeopleFromStr(string& str)
	{
		int res = 0;
		size_t len;
		string temp = "������ ������";
		len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (str[i] == ' ')
			{
				res = stoi(temp);
				break;
			}
			temp[i] = str[i];
		}
		return res;
	}

	//����� ����� ������ ��������, ������� ��� ���� � ������������ ������.
	UserData GetDataOfPerson(string& str)
	{
		UserData res;
		long num;
		size_t len, counterwords = 0, numchar;
		string temp;
		len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (str[i] == ' ')
			{
				if (counterwords == 0)
				{
					res.person.surname = temp;
				}
				else if (counterwords == 1)
				{
					res.person.name = temp;
				}
				else if (counterwords == 2)
				{
					res.person.patronymic = temp;
				}
				else if (counterwords == 3)
				{
					res.cardnum = temp;
				}
				else if (counterwords == 4)
				{
					num = stoi(temp);
					res.summoney = num;
				}
				else if (counterwords == 5)
				{
					res.pincode = temp;
				}
				temp.clear();
				counterwords++;
				i++;
			}
			temp.push_back(str[i]);
		}
		return res;
	}
	//����� ��������� ������ ������� � ������.
	void FillArrOfAccess()
	{
		for (size_t i = 0; i < nownumpeole; i++)
		{
			arrofaccess[i] = true;
		}
	}

public:
	//����������� �� ���������.
	ProcessingCenter(): numpeople(100),nownumpeole(0)
	{
		CreateArraysOfPersons();
	}
	//����� ��������� ���-���� �������.
	string GetPinCode(int i)
	{
		string temp;
		temp = persons[i].pincode;
		return temp;
	}
	//����� ������������� �������� false � ��������� ������� ������� bool.
	void SetElemOfArrAccess(int i)
	{
		arrofaccess[i] = false;
	}
	//����� ��������� ������� � �����.
	bool GetElemOfArrAccess(int i)
	{
		return arrofaccess[i];
	}
	//����� ��������� ��� �������.
	FIO GetFIO(int i)
	{
		FIO temp;
		temp = persons[i].person;
		return temp;
	}
	//����� ��������� ������ ����� �������.
	string GetNumOfCard(int i)
	{
		string temp;
		temp = persons[i].cardnum;
		return temp;
	}
	//����� ��������� ���������� �������� ������� �� ����� �������.
	int GetSumOfMoney(int i)
	{
		int temp;
		temp = persons[i].summoney;
		return temp;
	}
	//������� ��������� ������ �������.
	void FillArrOfDataFromFail()
	{
		int counter, countwhitesym, i = 0;
		ifstream fail("DataForProgram.txt");
		UserData data;
		while (fail)
		{
			string strInput;
			getline(fail, strInput);
			countwhitesym = CountWhiteSymbols(strInput);
			if (countwhitesym == 1)
			{
				nownumpeole = GetNowNumPeopleFromStr(strInput);
				FillArrOfAccess();
			}
			else if (countwhitesym == 6)
			{
				data = GetDataOfPerson(strInput);
				persons[i] = data;
				i++;
			}
		}
	}
	//����� ������������ ����� ������� �� ��� ������
	int SearchOfClient(const string& str)
	{
		int flag = -1;
		for (size_t i = 0; i < nownumpeole; i++)
		{
			if (persons[i].cardnum == str)
			{
				flag = i;
			}
		}
		return flag;
	}
	//����� �������� ���������� � �������� �� �����.(�� ������ ������ � privat�, ���� ��� ��������� ������).
	void PrintArray()
	{
		for (int i = 0; i < nownumpeole; i++)
		{
			cout << "\t\t\t ������ � " << i + 1 << endl << persons[i] << endl;
		}
	}
	//����� �������� ����������� �����
	void SubtractSum(int sum, int i)
	{
		persons[i].summoney -= sum;
	}
	//����� ��������� �������� �� ����.
	void AddOnAccount(int sum, int i)
	{
		persons[i].summoney += sum;
	}
	//����������
	~ProcessingCenter()
	{
		delete[] persons;
	}
};

class CashMachine
{
private:
	ProcessingCenter* server;//����� �������� ����� ������� ����� ���������� � �������.
	int numnotes;//������� ����� �������� � �������� �����.
	int arrnumnotes[NumKinds];//������, � ������� �������� ���������� �����, ������� �������� � ��������� (�� ������� ������ �� ��������� ����� ����� ��������)
	int arrparnotes[NumKinds];//������, � ������� �������� �������� ������ �� �����.
	int sumtaken;//���������� ��� ���������� ����� ����� �� ���� �������.
	int index;//��� ����� ������, ��� ��� ������ ������� ��������� ��� ������������, ����� ����� ��� �� ���������� � �������.
	short counterpincodes;//��� �������� ���������� ������� ����� ���-����.
	string numofcard;//������,�������� ����� ����� �������.

	//������������� ������� ���������� ����� ������� �����������.
	void InitArrNumNotes()
	{
		for (size_t i = 0; i < NumKinds; i++)
		{
			arrnumnotes[i] = NumNotesInitially;
		}
	}
	//������������� ������� �������� ������ ������.
	void InitArrParNotes()
	{
		for (size_t i = 0; i < NumKinds; i++)
		{
			arrparnotes[i] = ArrOfParNotes[i];
		}
	}
	//����� ���������� ������� ����� �����.
	void RememberNumOfCard(string& str)
	{
		numofcard = str;
	}
	//����� ������������ �������� �� ���������� ������ �������� �����.
	bool CheckArrOfNotes(int num)
	{
		bool control = true;
		if (num > LimitOfStore)
		{
			control = false;
		}
		return control;
	}
	//����� ������������ �������� �� ���������� ����� � ����� ����������.
	bool CheckNumNotes(int num)
	{
		bool control = true;
		if (num > LimitOfNotes)
		{
			control = false;
		}
		return control;
	}
	//����� ��������� ����� �� ������.
	void SmashSum(int* arrnumtemp,int sum)
	{
		for (int i = 5; i > -1; i--)
		{
			while ((sum >= arrparnotes[i]) && (arrnumnotes[i] > 0))//����� ������� �������, ����������� � ������ ���������� ���������� �����, ������� �������
			{
				sum -= arrparnotes[i];
				arrnumtemp[i]++;
				arrnumnotes[i]--;
			}
		}
	}
	//����� ��������� ����� �� ������ (� �������� ����-������).
	void SmashSumTemp(int* arrnumtemp, int sum)
	{
		int arr[NumKinds] = { 0,0,0,0,0,0 };
		for (size_t i = 0; i < NumKinds; i++)
		{
			arr[i] = arrnumnotes[i];
		}
		for (int i = 5; i > -1; i--)
		{
			while ((sum > arrparnotes[i]) && (arr[i] > 0))//����� ������� �������, ����������� � ������ ���������� ���������� �����, ������� �������
			{
				sum -= arrparnotes[i];
				arrnumtemp[i]++;
				arr[i]--;
			}
		}
	}
public:
	//����������� �� ���������.
	CashMachine()
	{
		numnotes = 0;
		index = -1;
		counterpincodes = 0;
		sumtaken = 0;
		InitArrNumNotes();
		InitArrParNotes();
		numofcard = "d000";
	}
	//����� �������� �� ����������.
	bool CheckOfBlock()
	{
		bool temp;
		temp = server->GetElemOfArrAccess(index);
		return temp;
	}
	//����� ��������� �������������� ����� � ��������.
	void LinkPrAndCM(ProcessingCenter* temp)
	{
		server = temp;
	}
	//����� ��������� ����� �������.
	void TakeCardOfClient(string& strofnum)
	{
		//��������� ����� ����� � ��� ���, �� � �������� � ����������, ������������ ������ ����� ������ � �����.
		RememberNumOfCard(strofnum);
	}
	//����� ���� ������� �� ������ ��� �����.
	void FindClientWithNumOfCard()
	{
		index = server->SearchOfClient(numofcard);
	}
	//����� ������������ �������� ������� ������� � ����� �����.
	bool CheckPresenceOfClient()
	{
		bool check = false;
		if (index > -1)
		{
			check = true;
		}
		return check;
	}
	//����� ��������� ���-��� �������.
	bool CheckPinCode(string& pincode)
	{	
		bool check = true;
		string temp;
		temp = server->GetPinCode(index);
		if (temp != pincode)
		{
			check = false;
			counterpincodes++;
			if (counterpincodes == 3)
			{
				BlockCardOfClient();
			}
		}
		return check;
	}
	//����� �������� ��������� ����� �������.
	void PrintAccountStatus()
	{
		FIO tempfio;
		int numofsum, i = 0,y = 10;
		string tempnumofcard;
		tempfio = server->GetFIO(index);
		numofsum = server->GetSumOfMoney(index);
		tempnumofcard = server->GetNumOfCard(index);
		gotoxy(10, y);
		y += 3;
		cout << "��������� ����� �������" << endl;
		while (i < 3)
		{
			gotoxy(5, y);
			if (i == 0)
			{
				cout << "��� �������: " << tempfio;
			}
			if (i == 1)
			{
				cout << "����� ����� �������: " << "**** **** **** " << tempnumofcard;
			}
			if (i == 2)
			{
				cout << "���������� �������� �������: " << numofsum << " -P-";
			}
			y++;
			i++;
		}
	}
	//����� ��������� ����� �������.
	void BlockCardOfClient()
	{
		server->SetElemOfArrAccess(index);
		counterpincodes = 0;
	}
	//����� ������� �� �����, ��� ����� �������� ������.
	void ShowIncorrectPinCode()
	{
		cout << "�� ����� �������� ������" << endl;
	}
	//����� ���������� ����� �������.
	void GiveCardOfClient()
	{
		//� ������ ������ ����� ������� ����������� � ������� ������ �����.
		int y = 10;
		FIO temp;
		gotoxy(10, y);
		cout << "_______________________________________________________";
		for (size_t i = 0; i < 10; i++)
		{
			y++;
			gotoxy(10, y);
			cout << "|                                                     |";
		}
		gotoxy(10, y);
		cout << "-------------------------------------------------------";
		gotoxy(20, 13);
		cout << "1823 2000 0505 " << numofcard;
		gotoxy(15, 16);
		temp = server->GetFIO(index);
		cout << temp;
		gotoxy(0, y + 1);
	}
	//����� ��������� ������ �������.
	int TakeMoney(int note)
	{
		int control = 2;
		for (size_t i = 0; i < NumKinds; i++)
		{
			if (note == arrparnotes[i])
			{
				if (!CheckArrOfNotes(arrnumnotes[i]))
				{
					control = 0;//�������� �� ������������� �������� �����.
					return control;
					//��������� ���� ��������.
				}
				arrnumnotes[i]++;
			}
		}
		if (!CheckNumNotes(numnotes))
		{
			control = 1;//�������� �� ������������ ����� �����.
			return control;
		}
		numnotes++;
		sumtaken += note;
		return control;
	}
	//����� ������������ ���������� ����� �� ����.
	void SendInfoAboutMoney()
	{
		server->AddOnAccount(sumtaken, index);
		sumtaken = 0;
		numnotes = 0;
	}
	//����� ����� ������.
	int GiveMoneyToClient(int sum)
	{
		int arrnumtemp[NumKinds] = { 0,0,0,0,0,0 };
		int tempsum = 0, exitf = 3, tempval;
		tempval = server->GetSumOfMoney(index);
		if (sum > tempval)
		{
			exitf = 0;
			return exitf;
		}
		if (sum % 100 != 0)
		{
			exitf = 1;
			return exitf;
		}
		SmashSumTemp(arrnumtemp, sum);
		for (size_t i = 0; i < NumKinds; i++)
		{
			tempsum += arrnumtemp[i];
		}
		if (tempsum > LimitOfNotes)
		{
			exitf = 2;
			return exitf;
		}
		return exitf;
	}
	//����� �������� ����� �������� �����.
	void PrintNumOfNotes(int sum)
	{
		int arr[NumKinds] = { 0,0,0,0,0,0 };
		SmashSum(arr, sum);
		cout << "5000 P : " << arr[5] << " ����" << endl;
		cout << "2000 P : " << arr[4] << " ����" << endl;
		cout << "1000 P : " << arr[3] << " ����" << endl;
		cout << "500 P : " << arr[2] << " ����" << endl;
		cout << "200 P : " << arr[1] << " ����" << endl;
		cout << "100 P : " << arr[0] << " ����" << endl;
		server->SubtractSum(sum, index);
	}
	//����������.
	~CashMachine()
	{}
};

void ShowMenu();
void showLogo();
void GetCard(CashMachine& bankcase);
bool CheckCode(CashMachine& bankcase);
void ReturnCard(CashMachine& bankcase);
void PrintBackgroundInformation();
void TakeMoney(CashMachine& bankcase);
void GiveMoney(CashMachine& bankcase);

int main()
{
	setlocale(LC_ALL, "Rus");
	ProcessingCenter center;
	center.FillArrOfDataFromFail();
	CashMachine bankcase;
	bankcase.LinkPrAndCM(&center);
	srand(time(0));
	system("color F0");
	system("cls");
	showLogo();
	const int NUM_MENU_ITEMS = 7;
	int activeMenuItem = 0;
	int ch = 0;
	bool exit = false, control1 = false, control2 = false;
	while (!exit)
	{
		ShowMenu();
		gotoxy(0, activeMenuItem);
		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}
		switch (ch)
		{
		case 27:
			exit = true;
			break;
		case 72:
			activeMenuItem--;
			break;
		case 80:
			activeMenuItem++;
			break;
		case 13:
			if (activeMenuItem == 0)
			{
				system("cls");
				GetCard(bankcase);
				system("cls");
				if (!bankcase.CheckPresenceOfClient())
				{
					cout << "�� ���� �� ��������� �������� ������ �����, ������� � ��� ��� �������. ����� ��������" << endl;
					system("pause");
					system("cls");
					break;
				}
				else if (bankcase.CheckOfBlock())
				{
					control1 = true;
					cout << "������� ������." << endl;
					system("pause");
					system("cls");
				}
				else
				{
					cout << "���� ����� �������������!" << endl;
					system("pause");
					system("cls");
				}
			}
			else if (activeMenuItem == 1)
			{
				system("cls");
				if (control1)
				{
					if (!CheckCode(bankcase))
					{
						bankcase.ShowIncorrectPinCode();
						if (!bankcase.CheckOfBlock())
						{
							control1 = false;
						}
						system("pause");
						break;
					}
					else
					{
						cout << "����� ����������!" << endl;
						system("pause");
						control2 = true;
					}
				}
				else
				{
					cout << "������ ������ ��� �� ��������, ����� ��������!" << endl;
					system("pause");
					system("cls");
				}
			}
			else if (activeMenuItem == 2)
			{
				if (control2)
				{		
					system("cls");
					bankcase.PrintAccountStatus();
					cout << "\n\n\n";
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "������ ������ ��� �� ��������, ����� ��������!" << endl;
					system("pause");
					system("cls");
				}
			}
			else if (activeMenuItem == 3)
			{
				if (control2)
				{
					system("cls");
					PrintBackgroundInformation();
					TakeMoney(bankcase);
					system("pause");
				}
				else
				{
					system("cls");
					cout << "������ ������ ��� �� ��������, ����� ��������!" << endl;
					system("pause");
					
				}
			}
			else if (activeMenuItem == 4)
			{
				if (control2)
				{
					system("cls");
					PrintBackgroundInformation();
					GiveMoney(bankcase);
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "������ ������ ��� �� ��������, ����� ��������!" << endl;
					system("pause");
				}
			}
			else if (activeMenuItem == 5)
			{
				if (control2)
				{
					system("cls");
					ReturnCard(bankcase);
					system("pause");
				}
				else
				{
					system("cls");
					cout << "������ ������ ��� �� ��������, ����� ��������!" << endl;
					system("pause");
				}
			}
			else if (activeMenuItem == 6)
			{
				exit = true;
			}
			break;
		}
		if (activeMenuItem < 0) activeMenuItem = 0;
		if (activeMenuItem > NUM_MENU_ITEMS - 1) activeMenuItem = NUM_MENU_ITEMS - 1;
		
	}
	system("cls");
	system("pause");
	return 0;
}

void ShowMenu()
{
	system("cls");
	cout << " 1. ������� ����� �������." << endl;
	cout << " 2. ��������� ���-���" << endl;
	cout <<	" 3. ������� ���������� � ��������� �����" << endl;
	cout << " 4. ������� ������" << endl;
	cout << " 5. ������ ������" << endl;
	cout << " 6. ������ ����� �������" << endl;
	cout << " 7. ��������� ������" << endl;
}

void ReturnCard(CashMachine& bankcase)
{
	bankcase.GiveCardOfClient();
}

void GiveMoney(CashMachine& bankcase)
{
	int sum = -1, counter;
	cout << "������� �����, ������� ������ ����� " << endl;
	while (sum <= 0)
	{
		cin >> sum;
	}
	counter = bankcase.GiveMoneyToClient(sum);
	if (counter == 0)
	{
		cout << "������������ ������� �� ����� " << endl;
	}
	if (counter == 1)
	{
		cout << "����� ����� ���������� ������ " << endl;
	}
	if (counter == 2)
	{
		cout << "����� ����� ���������� ������ " << endl;
	}
	if (counter == 3)
	{
		bankcase.PrintNumOfNotes(sum);
	}
}


void TakeMoney(CashMachine& bankcase)
{
	int control2, i = 0, note, counter = -1;
	bool control = false, control1 = false;
	while (!control1)
	{
		while (!control)
		{
			cout << "������� ������� ������, ������� ������ �������� �� ���� " << endl;
			cin >> note;
			i = 0;
			while (i != NumKinds)
			{
				if (note == ArrOfParNotes[i])
				{
					control = true;
					break;
				}
				i++;
			}
			if (!control)
			{
				cout << "����� ������ �������� �� ��������� " << endl;
			}
			else
			{
				control2 = bankcase.TakeMoney(note);
				if (control2 == 0)
				{
					cout << "�������� �� ����� ���� ���������, ��������� ������������� ������ ����� ���� ������ " << endl;
				}
				else if (control2 == 1)
				{
					cout << "�������� �� ����� ���� ���������, �������� ����� �������� ����� " << endl;
				}
				else
				{
					cout << "�������� ������ �������!" << endl;
				}
			}
		}
		cout << "���� ������ ���������� ���������� ����� ������� 1, ���� ������ ��������� ���� ������� 0" << endl;
		while (counter < 0 || counter > 1)
		{
			cin >> counter;
			if (counter < 0 || counter > 1)
			{
				cout << "����� ������� �� �������� � ��������� " << endl;
			}
		}
		if (counter == 0)
		{
			control1 = true;
		}
		else
		{
			control = false;
			counter = -1;
		}
	}
	bankcase.SendInfoAboutMoney();
}

bool CheckCode(CashMachine& bankcase)
{
	string temp;
	char symbol;
	cout << "������� ������:" << endl;
	for (size_t i = 0; i < 4; i++)
	{
		symbol = '/';
		while (symbol < 48 || symbol > 57)
		{
			cin >> symbol;
			if (symbol < 48 || symbol > 57)
			{
				cout << "������, ����� ������� ������ �����" << endl;
			}
		}
		temp += symbol;
	}
	return bankcase.CheckPinCode(temp);
}

void PrintBackgroundInformation()
{
	cout << "�������� ��������� ��������� ������: 100 P, 200 P, 500 P, 1000 P, 2000 P, 5000 P, � ������ ����� �������� � �������, ������� ����� ���� �������� � ���� �����." << endl;
}

void GetCard(CashMachine& bankcase)
{
	string temp;
	char symbol;
	cout << "������� ����� ����� " << endl;
	for (size_t i = 0; i < 4; i++)
	{
		symbol = '/';
		while (symbol < 48 || symbol > 57)
		{
			cin >> symbol;
			if (symbol < 48 || symbol > 57)
			{
				cout << "������, ����� ������� ������ �����" << endl;
			}
		}
		temp += symbol;
	}
	bankcase.TakeCardOfClient(temp);
	bankcase.FindClientWithNumOfCard();
}

void showLogo()
{
	gotoxy(50, 15);
	cout << "��������� ���������" << endl;
	Sleep(1500);
}
