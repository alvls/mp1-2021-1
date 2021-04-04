#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#define number 12//число символов в номере телефона
#define date 8//число символов в дате рождения
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
const string month[12] = { "января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря" };
//Разработать класс Контакты.
//Класс должен хранить информацию о контактах владельца.
//Каждый контакт содержит следующие данные : 
//фамилия; 
//имя;
//отчество;
//телефон;
//день рождения(день, месяц, год);
//признак, относится ли контакт к избранным.
//Контакты хранятся упорядоченно по фамилии, имени, отчеству.
//Фамилия, имя, отчество(ФИО) являются обязательными полями.
//Данные вводятся на русском языке.
//Класс должен содержать необходимые служебные методы.
//Класс должен предоставлять следующие операции : 
/// 
/// поиск:
/// контакт по фио
/// контакт по телефону
/// все контакты на эту букву
/// 
//1) создать новый контакт,+
//2) изменить выбранный контакт, +
//3) найти контакт по ФИО,+
//4) найти контакт по телефону, +
//5) выдать все контакты на заданную букву, +
//6) узнать текущее число контактов, +
//7) внести контакт в список избранных,+
//8) удалить контакт из списка избранных,+
//9) выдать все избранные контакты, +
//10) удалить контакт, +
//11) сохранить контакты в файл, +
//12) считать контакты из файла.+
//КОНТАКТЫ НЕ ДОЛЖНЫ СОДЕРЖАТЬ ОДНО И ТО ЖЕ ФИО+

class contact
{
	string surname;
	string name;
	string patronymic;
	char phone[number];
	char birth[date];
	bool favorite;
public:
	contact(string sur = "Ваш", string nam = "Безымянный", string pat = "Контакт", char* _phone = nullptr, char* _birth = nullptr);
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
	bool ans = true;
	if (name == other.name && surname == other.surname && patronymic == other.patronymic)
	{
		/*for (int i = 0; i < number; i++)
		{
			if (phone[i] != other.phone[i])
			{
				ans = false;
				break;
			}
		}
		for (int i = 0; i < date && ans; i++)
		{
			if(birth[i]!=other.birth[i])
			{
				ans = false;
				break;
			}
		}*/
		return ans;
	}
	return false;
}
bool contact::operator>(const contact& other)
{
	if (surname > other.surname)
		return true;
	else
		if (surname < other.surname)
			return false;
		else
			if (name > other.name)
				return true;
			else
				if (name < other.name)
					return false;
				else
					if (patronymic > other.patronymic)
						return true;
					else
						return false;
}// для сортировки
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
////////////////////////////////////////////////
ostream& operator<<(ostream& place, const contact& c)
{
	// Достаточно вывести данные, понятные только программе
	place << c.surname << endl;
	place << c.name << endl;
	place << c.patronymic << endl;
	for (int i = 0; i < number; i++)
		place << c.phone[i];
	for (int i = 0; i < date; i++)
		place << c.birth[i];
	place << endl;
	if (c.favorite)//cout << "Контакт обавлен в избранные\n";
		place << '+' << endl;
	else
		place << '-' << endl;
	return place;
}
istream& operator>>(istream& place, contact& c)
{
	char ch;
	place >> c.surname;
	place >> c.name;
	place >> c.patronymic;
	for (int i = 0; i < number; i++)
		place >> c.phone[i];
	place >> ch;
	for (int i = 0; i < date; i++)
		place >> c.birth[i];
	place >> ch;
	place >> ch;
	if (ch == '+')
		c.favorite = true;
	else
		c.favorite = false;
}
/////////////////////////////////////////////////////////
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
inline void good_change()
{
	cout << "Данные успешно изменены\n";
}
inline void fio_err()
{
	cout << "Нельзя иметь два контакта с одинаковыми ФИО\n";
}
void setstr(string& s)
{
	cout << "Введите строку, не превышающую 32 символа без пробелов и иных разделителей, затем нажмите Enter\n";
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
	void contact_menu(contact& c, const int nomer);
	bool check(const contact& c);
	void sort(int num);
public:
	List(int _k = 1) :k(_k)
	{
		contact c;
		man.resize(k);
		for (int i = 0; i < k; i++)
			man[i] = c;
	}
	~List()
	{
		k = 0;
		man.clear();
	}
	//Создаёт новый контакт +
	void _new(contact extra);
	void _delete(int i);
	//Вывести число контактов +
	int getk()
	{
		return k;
	}
	//Вывести все избранные контакты
	void getfav()
	{
		for (int i = 0; i < k; i++)
			if (man[i].favorite)
				man[i].usualprintc(i);
	}
	//Удалить контакт
	void setlist();//вывести данные в файл
	void getlist();//получить данне из файла

	bool find_word(const char ch);// найти контакты на заданную букву
	int  find_fio(const string* fio);// найти контакт по фио (полное совпадение)
	bool find_phone(const char* phone_num);
	void menu();
	bool exitmenu();
};
bool List::find_word(const char ch)
{
	bool found = false;
	for (int i = 0; i < k; i++)
		if (man[i].surname[0] == ch || man[i].name[0] == ch || man[i].patronymic[0] == ch)
		{
			found = true;
			man[i].usualprintc(i);
		}
	return found;
}
int List::find_fio(const string* fio)
{
	int i;
	for (i = 0; i < k; i++)
		if (fio[0] == man[i].surname)
			if (fio[1] == man[i].name)
				if (fio[2] == man[i].patronymic)
					return i;
	if (i == k)
		return -1;
}
bool List::find_phone(const char* phone_num)
{
	int i, j;
	bool found = false;
	for (i = 0; i < k; i++)
		for (j = 0; j < number; j++)
			if (man[i].phone[j] != phone_num[j])
			{
				break;
			}
			else
				if ((j == number - 1) && man[i].phone[j] == phone_num[j])
				{
					man[i].usualprintc(i);
					found = true;
				}
	return found;
}
/// <summary>
/// 
/// сделать проверку на равенство фио для _new
/// 
/// </summary>
/// <param name="extra"></param>
void List::_new(contact extra)
{
	k++;
	vector<contact> ext_vec(k);
	int i = 0;
	while ((ext_vec[i] = man[i]) > extra)
		i++;
	ext_vec[i] = extra;
	i++;
	int j = i - 1;
	for (i; i < k; i++, j++)
	{
		ext_vec[i] = man[j];
	}
	man = ext_vec;
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
void List::contact_menu(contact& c, const int nomer)
{
	bool repeat = true;
	bool badsymb = true;
	int pointer = 0;
	int input;
	const int maxlist = 7;
	int ans;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
	const string menu_list[maxlist] = { "Фамилия\n",  "Имя\n", "Отчество\n",  "Номер телефона\n", "Дата рождения\n", "Добавить в избранное/удалить из избранного\n", "Удалить контакт\n" };
	do
	{
		system("CLS");
		badsymb = true;
		for (int i = 0; i < 103; i++)
			cout << "=";
		cout << "\nФИО: ";
		cout << c.surname << " ";
		cout << c.name << " ";
		cout << c.patronymic << "\n";
		cout << "Номер телефона: ";
		for (int i = 0; i < number; i++)
			cout << c.phone[i];
		int b1 = c.birth[2] - '0';
		int b2 = c.birth[3] - '0';
		int m = b1 * 10 + b2 - 1;
		cout << "\nДата рождения: ";
		if (m < 12 && m>-1)
			cout << c.birth[0] << c.birth[1] << " " << month[m] << " ";
		else
			cout << c.birth[0] << c.birth[1] << " " << "неизвестного месяца" << " ";
		for (int i = 4; i < date; i++)
			cout << c.birth[i];
		cout << " " << "года\n";
		if (c.favorite)
			cout << "Контакт добавлен в избранные\n";
		else
			cout << "Контакт не добавлен в избранные\n";
		for (int i = 0; i < 103; i++)
			cout << "=";
		cout << "\nЕсли вы хотите внести изменения, выберите соответствующий пункт: \n";
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
		string str;
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
				repeat = false;
				badsymb = false;
				return;
				break;
			case _n:
				switch (pointer)
				{
				case 0:case 1: case 2:
					setstr(str);
					if (pointer == 0)
						new_c.surname = str;
					else
						if (input == 1)
							new_c.name = str;
						else
							new_c.patronymic = str;
					if (check(new_c))
					{
						c = new_c;
						sort(pointer);
					}
					else
					{
						fio_err();
						_getch();
					}
					break;
				case 3:
					cout << "Введите номер телефона со знаком \"+\"\n";
					while ((c.phone[0] = _getch()) != '+')
						;
					cout << "+";
					getnums(c.phone, 1, number);
					break;
				case 4:
					cout << "Введите число, месяц, год в виде чисел без разделителей.\nЕсли число или номер месяца меньше 10, ставить вначале 0.\nГод вводить в виде четырёх цифр\n";
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
					cout << "Если вы точно хотите удалить контакт, нажмите 0\n";
					if (!(ans = _getch() - '0'))
					{
						_delete(nomer);
						cout << "Номер удалён\n";
						return;
					}
					else
						badsymb = false;
				}
				badsymb = false;
				break;
			}
		}
	} while (repeat);
}
void List::sort(int num)
{
	int i;
	vector <contact> tmp(k);
	/*for (i = 0; i < k; i++)
		if (tmp[num] > man[i])
			break;
	tmp[i] = tmp[num];
	int j = i + 1;
	for (i; i < k; i++)
		if (man[i] != man[num])
			tmp[j] = man[i];
		else
			i++;*/
	for (i = 0; i < k; i++)
		if (man[i] > man[num])
			tmp[i] = man[i];
		else
			if (man[i] == man[num])
			{
				for (int j = i + 1; j < k; j++, i++)
				{
					if (man[i] > man[num])
						tmp[i] = man[j];
					else
					{
						tmp[i] = man[num];
						i++;
						for (i; i < k; i++)
							tmp[i] = man[i];
						break;
					}
				}
				break;
			}
			else
			{
				int j = i + 1;
				tmp[j] = man[num];
				for (i; i < k; i++, j++)
					if (man[i] != man[num])
						tmp[j] = man[i];
					else
						i++;
			}
	man = tmp;
	tmp.clear();
}
void List::menu()
{
	int i;
	int pointer = 0;
	int c;
	bool repeat = true;
	bool notnorm;
	const char arrow = 17;
	char like = 3;
	const int out = 27;
	int screen = 0;
	ifstream fin("list.txt");
	ofstream fout("list.txt");
	contact extra;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
	cout << "УБЕДИТЕСЬ, ЧТО У ВАС НА КЛАВИАТУРЕ СЕЙЧАС РУССКАЯ РАСКЛАДКА" << endl;
	cout << "Полезные клавиши:" << endl;
	cout << "Поиск контакта по ФИО: 0" << endl;
	string s_[3];
	cout << "Поиск контакта по номеру телефона: 1" << endl;
	char ph_[number];
	cout << "Поиск контактов по букве: 2" << endl;
	char word;
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
		cout << " Общее число контактов: " << getk() << ". Если контактов больше " << out - 1 << ", можете переходить между страницами влево и вправо" << endl;
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
				contact_menu(man[pointer], pointer);
				break;
			case esc:
				repeat = exitmenu();
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
				cout << "Фамилия:" << endl;
				setstr(extra.surname);
				cout << "Имя:" << endl;
				setstr(extra.name);
				cout << "Отчество:" << endl;
				setstr(extra.patronymic);
				_new(extra);
				notnorm = false;
			case '0':				
				system("cls");
				cout << "Фамилия:" << endl;
				setstr(s_[0]);
				cout << "Имя:" << endl;
				setstr(s_[1]);
				cout << "Отчество:" << endl;
				setstr(s_[2]);
				find_fio(s_);
				notnorm = false;
			case '1':
				system("cls");
				cout << "Введите номер телефона со знаком \"+\"\n";
				while ((ph_[0] = _getch()) != '+')
					;
				cout << "+";
				getnums(ph_, 1, number);
				notnorm = false;
			case '2':
				system("cls");
				cout << "Введите символ, с которого может начинаться фамилия/имя/отчество\n";
				word = _getch();
				cout << word << endl;

				notnorm = false;
			}
		}
	} while (repeat);
}
bool List::check(const contact& c)//возвращает true, если всё хорошо
{
	int j = 0;
	for (int i = 0; i < k; i++)
		if (man[i] == c)
			if (!j)
				j++;
			else
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
		cout << "Вы уверены, что хотите выйти?" << endl;
		if (choice == yes)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | CYAN));
			cout << "Да";
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
			cout << " Нет";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
			cout << "Да ";
			SetConsoleTextAttribute(hConsole, (WORD)((YELLOW << 4) | CYAN));
			cout << "Нет";
			SetConsoleTextAttribute(hConsole, (WORD)((LIGHTGREEN << 4) | YELLOW));
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
					return false;//перемещает булевую переменную продолжения в значение false
				else
					return true;//перемещает булевую переменную продолжения в значение true
			case esc:
				return true;//перемещает булевую переменную продолжения в значение false
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
	List list;
	list.menu();
	cout << "\n";
	system("pause");
}