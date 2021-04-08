#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#define number 12//����� �������� � ������ ��������
#define date 8//����� �������� � ���� ��������
using namespace std;
enum choice
{
	W = 214,
	w = 246,
	A = 212,
	a = 244,
	S = 219,
	s = 251,
	D = 194,
	d = 226,
	_n = 13,
	esc = 27
};
enum TColor
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGRAY = 7,
	DARKGRAY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};
const string month[12] = { "������", "�������", "�����", "������", "���", "����", "����", "�������", "��������", "�������", "������", "�������" };
//����������� ����� ��������.
//����� ������ ������� ���������� � ��������� ���������.
//������ ������� �������� ��������� ������ : 
//�������; 
//���;
//��������;
//�������;
//���� ��������(����, �����, ���);
//�������, ��������� �� ������� � ���������.
//�������� �������� ������������ �� �������, �����, ��������.
//�������, ���, ��������(���) �������� ������������� ������.
//������ �������� �� ������� �����.
//����� ������ ��������� ����������� ��������� ������.
//����� ������ ������������� ��������� �������� : 
/// 
/// �����:
/// ������� �� ���
/// ������� �� ��������
/// ��� �������� �� ��� �����
/// 
//1) ������� ����� �������,+
//2) �������� ��������� �������, +
//3) ����� ������� �� ���,+
//4) ����� ������� �� ��������, +
//5) ������ ��� �������� �� �������� �����, +
//6) ������ ������� ����� ���������, +
//7) ������ ������� � ������ ���������,+
//8) ������� ������� �� ������ ���������,+
//9) ������ ��� ��������� ��������, +
//10) ������� �������, +
//11) ��������� �������� � ����, +
//12) ������� �������� �� �����.+
//�������� �� ������ ��������� ���� � �� �� ���+

class contact
{
	string surname;
	string name;
	string patronymic;
	char phone[number];
	char birth[date];
	bool favorite;
public:
	contact(string sur = "���", string nam = "����������", string pat = "�������", char* _phone = nullptr, char* _birth = nullptr);
	friend class List;
	bool operator==(const contact& other);
	bool operator!=(const contact& other);
	bool operator >(const contact& other);
	contact& operator =(const contact& other);
	friend ostream& operator<<(ostream& place, const contact& c);
	friend istream& operator>>(istream& place, contact& c);
	void usualprintc(int i = -1);
	void specialprintc(int i = -1);
};
contact::contact(string sur, string nam, string pat, char* _phone, char* _birth) : name(nam), surname(sur), patronymic(pat)
{
	if (_phone == nullptr)
	{
		phone[0] = '+';
		for (int i = 1; i < number; i++)
			phone[i] = '0';
	}
	else
		for (int i = 0; i < number; i++)
			phone[i] = _phone[i];
	if (_birth == nullptr)
	{
		birth[0] = '0';
		birth[1] = '1';
		for (int i = 2; i < date; i++)
			birth[i] = '0';
	}
	else
		for (int i = 0; i < date; i++)
			birth[i] = _birth[i];
	favorite = false;
}
bool contact::operator!=(const contact& other)
{
	if (name != other.name || surname != other.surname || patronymic != other.patronymic)
		return true;
	else
		return false;
}
bool contact:: operator==(const contact& other)
{
	if (name == other.name && surname == other.surname && patronymic == other.patronymic)
		return true;
	else
		return false;
}
bool contact::operator>(const contact& other)
{
	if (surname < other.surname)
		return true;
	else
		if (surname > other.surname)
			return false;
		else
			if (name < other.name)
				return true;
			else
				if (name > other.name)
					return false;
				else
					if (patronymic < other.patronymic)
						return true;
					else
						return false;
}// ��� ����������
contact& contact::operator=(const contact& other)
{
	surname = other.surname;
	name = other.name;
	patronymic = other.patronymic;
	int i;
	for (i = 0; i < number; i++)
		phone[i] = other.phone[i];
	for (i = 0; i < date; i++)
		birth[i] = other.birth[i];
	favorite = other.favorite;
	return *this;
}
ostream& operator<<(ostream& place, const contact& c)
{
	// ���������� ������� ������, �������� ������ ���������
	place << c.surname << endl;
	place << c.name << endl;
	place << c.patronymic << endl;
	for (int i = 0; i < number; i++)
		place << c.phone[i];
	for (int i = 0; i < date; i++)
		place << c.birth[i];
	place << endl;
	if (c.favorite)
		place << '1' << endl;
	else
		place << '0' << endl;
	return place;
}
istream& operator>>(istream& place, contact& c)
{
	char ch;
	place.get();
	getline(place, c.surname);
	getline(place, c.name);
	getline(place, c.patronymic);
	for (int i = 0; i < number; i++)
		place >> c.phone[i];
	for (int i = 0; i < date; i++)
		place >> c.birth[i];
	place >> ch;
	if (ch == '1')
		c.favorite = true;
	else
		c.favorite = false;
	return place;
}
void contact::usualprintc(int i)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (favorite)
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | RED));
	else
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
	if (i > -1)
		cout << i << " ";
	cout << surname << " ";
	cout << name << " ";
	cout << patronymic << " ";
	for (int i = 0; i < number; i++)
		cout << phone[i];
	cout << endl;
}
void contact::specialprintc(int i)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (favorite)
		SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | RED));
	else
		SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | CYAN));
	if (i > -1)
		cout << i << " ";
	cout << surname << " ";
	cout << name << " ";
	cout << patronymic << " ";
	for (int i = 0; i < number; i++)
		cout << phone[i];
	cout << endl;
}

void getnums(char* s, const int l, const int r, const char ending = '9', const char opening = '0')//[l;r), [opening; ending]
{
	char c;
	for (int i = l; i < r; i++)
	{
		do
		{
			c = _getch();
		} while (c < opening || c>ending);
		s[i] = c;
		cout << c;
	}
}
inline void fio_err()
{
	cout << "������ ����� ��� �������� � ����������� ���\n";
}
void setstr(string& s)
{
	s.clear();
	cout << "������� ������, �� ����������� 32 ������� ��� �������� � ���� ������������, ����� ������� Enter\n";
	char get;
	for (int i = 0; i < 32; i++)
	{
		get = getchar();
		if (get == '\0' || get == '\n' || get == '\r' || get == ' ')
			break;
		s.push_back(get);
	}
}
class List
{
	int k;
	vector <contact> man;
	int contact_menu(contact& c, const int nomer);
	bool check(const contact& c);
	int _new(contact extra);
	void _delete(int i);
	bool find_word(const char ch);// ����� �������� �� �������� �����
	int find_fio(const string* fio);// ����� ������� �� ��� (������ ����������)
	bool find_phone(const char* phone_num);
	bool exitmenu();
public:
	List(int _k = 0) :k(_k)
	{

	}
	~List()
	{
		k = 0;
		man.clear();
	}
	void menu(bool isbasic);
};
bool List::find_word(const char ch)
{
	bool found = false;
	List list_word;
	for (int i = 0; i < k; i++)
		if (man[i].surname[0] == ch || man[i].name[0] == ch || man[i].patronymic[0] == ch)
		{
			found = true;
			list_word._new(man[i]);
		}
	list_word.menu(false);
	return found;
}
int List::find_fio(const string* fio)
{
	int i;
	for(i=0;i<k;i++)
		if (fio[0] == man[i].surname && fio[1] == man[i].name && fio[2] == man[i].patronymic)
		{			
			return i;
			break;
		}
	if (i == k)
		return -1;
}
bool List::find_phone(const char* phone_num)
{
	int i, j;
	bool found = false;
	int count = 0;
	List list_phone;
	for (i = 0; i < k; i++)
		for (j = 0; j < number; j++)
			if (man[i].phone[j] != phone_num[j])
			{
				break;
			}
			else
				if ((j == number - 1) && man[i].phone[j] == phone_num[j])
				{
					list_phone._new(man[i]);
					found = true;
				}
	list_phone.menu(false);
	return found;
}
int List::_new(contact extra)
{
	k++;
	int i;
	for (i = 0; i < k - 1; i++)
	{
		if (extra > man[i])
			break;
	}
	man.insert(man.begin() + i, extra);
	return i;
}
void List::_delete(int i)
{
	int j;
	k--;
	vector<contact> tmp(k);
	for (j = 0; j < i; j++)
		tmp[j] = man[j];
	int m = j + 1;
	for (j; j < k; j++, m++)
		tmp[j] = man[m];
	man = tmp;
}
int List::contact_menu(contact& c, int nomer)
{
	bool repeat = true;
	bool badsymb = true;
	int pointer = 0;
	int input;
	const int maxlist = 7;
	int ans;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
	const string menu_list[maxlist] = { "�������\n",  "���\n", "��������\n",  "����� ��������\n", "���� ��������\n", "�������� � ���������/������� �� ����������\n", "������� �������\n" };
	do
	{
		system("CLS");
		badsymb = true;
		for (int i = 0; i < 103; i++)
			cout << "=";
		cout << "\n���: ";
		cout << c.surname << " ";
		cout << c.name << " ";
		cout << c.patronymic << "\n";
		cout << "����� ��������: ";
		for (int i = 0; i < number; i++)
			cout << c.phone[i];
		int b1 = c.birth[2] - '0';
		int b2 = c.birth[3] - '0';
		int m = b1 * 10 + b2 - 1;
		cout << "\n���� ��������: ";
		if (m < 12 && m>-1)
			cout << c.birth[0] << c.birth[1] << " " << month[m] << " ";
		else
			cout << c.birth[0] << c.birth[1] << " " << "������������ ������" << " ";
		for (int i = 4; i < date; i++)
			cout << c.birth[i];
		cout << " " << "����\n";
		if (c.favorite)
			cout << "������� �������� � ���������\n";
		else
			cout << "������� �� �������� � ���������\n";
		for (int i = 0; i < 103; i++)
			cout << "=";
		cout << "\n���� �� ������ ������ ���������, �������� ��������������� �����: \n";
		int i;
		for (i = 0; i < pointer; i++)
			cout << menu_list[i];
		if (i < maxlist)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | CYAN));
			cout << menu_list[i];
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
			for (i = pointer + 1; i < maxlist; i++)
				cout << menu_list[i];
		}
		contact new_c = c;
		while (badsymb)
		{
			input = _getch();
			switch (input)
			{
			case w: case W:
				if (pointer > 0)
					pointer--;
				else
					pointer = maxlist - 1;
				badsymb = false;
				break;
			case s: case S:
				if (pointer < maxlist - 1)
					pointer++;
				else
					pointer = 0;
				badsymb = false;
				break;
			case esc:
				system("cls");
				return nomer;
			case _n:
				switch (pointer)
				{
				case 0:case 1: case 2:
					
					if (pointer == 0)
						setstr(new_c.surname);
					else
						if (pointer == 1)
							setstr(new_c.name);
						else
							setstr(new_c.patronymic);
					if (check(new_c))
					{
						string sssr[3];
						sssr[0] = c.surname;
						sssr[1] = c.name;
						sssr[2] = c.patronymic;
						_delete(find_fio(sssr));
						nomer = _new(new_c);
						contact_menu(man[nomer], nomer);
						return nomer;
					}
					else
					{
						fio_err();
						ans = _getch();
					}
					badsymb = false;
					break;
				case 3:
					cout << "������� ����� �������� �� ������ \"+\"\n";
					while ((c.phone[0] = _getch()) != '+')
						;
					cout << "+";
					getnums(c.phone, 1, number);
					break;
				case 4:
					cout << "������� �����, �����, ��� � ���� ����� ��� ������������.\n���� ����� ��� ����� ������ ������ 10, ������� ������� 0.\n��� ������� � ���� ������ ����\n";
					getnums(c.birth, 0, 1, '3');
					getnums(c.birth, 1, 2);
					getnums(c.birth, 2, 3, '1');
					getnums(c.birth, 3, 4);
					getnums(c.birth, 4, 5, '2', '1');
					getnums(c.birth, 5, date);
					badsymb = false;
					break;
				case 5:
					c.favorite = !c.favorite;
					break;
				case 6:
					cout << "���� �� ����� ������ ������� �������, ������� 0\n";
					if (!(ans = _getch() - '0'))
					{
						_delete(nomer);
						return nomer - 1;
					}
					else
						badsymb = false;
				}
				badsymb = false;
				break;
			}
		}
	} while (repeat);
	return nomer;
}
void List::menu(bool isbasic)
{
	ifstream fin;
	char word;
	if (isbasic)
	{
		fin.open("list.txt");
		if (fin.is_open())
		{
			contact in;
			fin >> k;
			for (int i = 0; i < k; i++)
				if (!fin.eof())
				{
					fin >> in;
					man.push_back(in);
				}
		}
		fin.close();
	}
	string s_[3];
	char ph_[number];
	contact extra;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
	system("cls");
	int i;
	int pointer = 0;
	int c;
	bool repeat = true;
	bool notnorm;
	const int out = 27;
	int screen = 0;
	do
	{
		SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
		notnorm = true;
		system("CLS");
		for (i = screen; i < pointer; i++)
			man[i].usualprintc(i);
		if (i < screen + out && i < k)
		{
			man[i].specialprintc(i);
			for (i = pointer + 1; i < k && i < screen + out; i++)
				man[i].usualprintc(i);
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
		}
		cout << " ����� ����� ���������: " << k << ". ���� ��������� ������ " << out - 1 << ", ������ ���������� ����� ���������� ����� � ������" << endl;
		while (notnorm)
		{
			c = _getch();
			switch (c)
			{
			case w:case W:
				if (pointer == screen)
					if (screen + out < k)
						pointer = screen + out - 1;
					else
						pointer = k - 1;
				else
					pointer--;
				notnorm = false;
				break;
			case s: case S:
				if (pointer < screen + out - 1 && pointer < k - 1)
					pointer++;
				else
					pointer = screen;
				notnorm = false;
				break;
			case _n:
				pointer = contact_menu(man[pointer], pointer);
				notnorm = false;
				break;
			case esc:
				if (isbasic)
					repeat = exitmenu();
				else
					return;
				if ((!repeat) && isbasic)
				{					
					ofstream fout;
					fout.open("list.txt");
					fout << k << endl;
					for (int i = 0; i < k; i++)
						fout << man[i];
					fout.close();
					cout << "������ ������� ��������� � ����" << endl;
				}
				notnorm = false;
				break;
			case a: case A:
				if (screen >= out)
				{
					pointer -= out;
					screen -= out;
				}
				else
				{
					screen = k / out;
					screen *= out;
					if (pointer + screen < k)
						pointer += screen;
					else
						pointer = k - 1;
				}
				notnorm = false;
				break;
			case D: case d:
				if (screen + out < k)
				{
					screen += out;
					if (pointer + out < k)
						pointer += out;
					else
						pointer = screen;
				}
				else
				{
					pointer -= screen;
					screen = 0;
				}
				notnorm = false;
				break;
			case '+':
				system("cls");
				cout << "�������:" << endl;
				setstr(extra.surname);
				cout << "���:" << endl;
				setstr(extra.name);
				cout << "��������:" << endl;
				setstr(extra.patronymic);
				if (check(extra))
					_new(extra);
				else
				{
					fio_err();
					_getch();
				}
				notnorm = false;
				break;
			case '0':				
				system("cls");
				cout << "�������:" << endl;
				setstr(s_[0]);
				cout << "���:" << endl;
				setstr(s_[1]);
				cout << "��������:" << endl;
				setstr(s_[2]);
				i = find_fio(s_);
				cout << endl;
				if (i > 0)
					man[i].usualprintc();
				else
					cout << "����� �� ��� �����������" << endl;
				word = _getch();
				notnorm = false;
				break;
			case '1':
				system("cls");
				cout << "������� ����� �������� �� ������ \"+\"\n";
				while ((ph_[0] = _getch()) != '+')
					;
				cout << "+";
				getnums(ph_, 1, number);
				cout << endl;
				if (!find_phone(ph_))
					cout << "����� �� ��� �����������" << endl;
				word = _getch();
				notnorm = false;
				break;
			case '2':
				system("cls");
				cout << "������� ������, � �������� ����� ���������� �������/���/��������\n";
				word = _getch();
				cout << word << endl;
				if (!find_word(word))
					cout << "����� �� ��� �����������" << endl;
				word = _getch();
				notnorm = false;
				break;
			}
		}
	} while (repeat);
}
bool List::check(const contact& c)//���������� true, ���� �� ������
{
	for (int i = 0; i < k; i++)
		if (man[i] == c)
			return false;
	return true;
}
bool List::exitmenu()
{
	enum point
	{
		yes, no
	};
	int c;
	bool repeat = true;
	bool badsymb = true;
	point choice = yes;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	do
	{
		system("CLS");
		cout << "�� �������, ��� ������ �����?" << endl;
		if (choice == yes)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | CYAN));
			cout << "��";
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
			cout << " ���" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
			cout << "�� ";
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | CYAN));
			cout << "���";
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
			cout << endl;
		}
		do
		{
			c = _getch();
			switch (c)
			{
			case a: case A:
			case d: case D:
				if (choice == yes)
					choice = no;
				else
					choice = yes;
				badsymb = false;
				break;
			case _n:
				if (choice == yes)
					return false;//���������� ������� ���������� ����������� � �������� false
				else
					return true;//���������� ������� ���������� ����������� � �������� true
			case esc:
				return true;//���������� ������� ���������� ����������� � �������� false
			default:
				badsymb = true;
			}
		} while (badsymb);
	} while (repeat);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color AE");
	List list;
	cout << "���������, ��� � ��� �� ���������� ������ ������� ���������" << endl;
	cout << "�������� �������:" << endl;
	cout << "����� �������� �� ���: 0" << endl;
	cout << "����� �������� �� ������ ��������: 1" << endl;
	cout << "����� ��������� �� �����: 2" << endl;
	cout << "�������� ����� �������: +" << endl;
	system("pause");
	list.menu(true);
	system("pause");
}