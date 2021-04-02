#include "All.h"
using namespace std;
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
//1) создать новый контакт,
//2) изменить выбранный контакт, 
//3) найти контакт по ФИО,
//4) найти контакт по телефону, 
//5) выдать все контакты на заданную букву, 
//6) узнать текущее число контактов, 
//7) внести контакт в список избранных,
//8) удалить контакт из списка избранных,
//9) выдать все избранные контакты, 
//10) удалить контакт, 
//11) сохранить контакты в файл, 
//12) считать контакты из файла.
//КОНТАКТЫ НЕ ДОЛЖНЫ СОДЕРЖАТЬ ОДНО И ТО ЖЕ ФИО	
///Список вопросов:
/// Как можно стирать только одну напечатанную строку?
/// Или как быстрее выводить строки и char'ы
//Нужна проверка для номеров месяцев, числа дней в месяце, проверка на год
class List
{
	contact* man;
	int k;
	void sort();
public:
	List(int _k = 0) :k(_k)
	{
		if (k)
			man = new contact[k];
		else
			man = nullptr;
		//name = surname = patronymic = nullptr;
	}
	~List()
	{
		k = 0;
		delete[] man;
	}
	//Создаёт новый контакт
	void _new(contact extra)
	{
		int i;
		contact* tmp = new contact[k + 1];
		for (i = 0; i < k; i++)
		{
			tmp[i] = man[i];
		}
		tmp[i] = extra;
		k++;
		man = new contact[k];
		for (i = 0; i < k; i++)
		{
			man[i] = tmp[i];
		}
		delete[] tmp;
		sort();
	}
	//Изменить выбранный контакт
	void change_contact(contact dif)
	{

	}
	//Вывести число контактов +
	int getk()
	{
		return k;
	}
	//+
	void favour(int point)
	{
		man[point].favorite = true;
	}
	//+
	void dis_favor(int point)
	{
		man[point].favorite = false;
	}
	//Вывести все избранные контакты???
	contact* getfav()
	{
		int i;
		int n=0;//количество избранных контактов
		for (i = 0; i < k; i++)
		{
			if (man[i].favorite)
				n++;
		}

	}
	//Удалить контакт
	void _delete(contact deleted)
	{
		int i, j = 0, num;
		contact* tmp = new contact[k-1];
		for (i = 0; i < k; i++)
			if (man[i] != deleted)
			{
				tmp[j] = man[i];
				j++;
			}
			else
				num = i;
		delete[] man;
		k--;
		man = new contact[k];
		for (i = 0; i < k; i++)
		{
			man[i] = tmp[i];
		}
		delete[] tmp;
		sort();
	}
	void setlist();//вывести данные в файл
	void getlist();//получить данне из файла
	void show();
	bool exitmenu();
	friend void menu();
};
void menu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
	List list(200);
	bool repeat = true;
	list.show();
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
			SetConsoleTextAttribute(hConsole, (WORD)((CYAN << 4) | YELLOW));
			cout << "Да";
			SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
			cout << " Нет";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
			cout << "Да ";
			SetConsoleTextAttribute(hConsole, (WORD)((CYAN << 4) | YELLOW));
			cout << "Нет";
			SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
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
			case 13:
				if (choice == yes)
					return false;//перемещает булевую переменную продолжения в значение false
				else
					return true;//перемещает булевую переменную продолжения в значение true
			case 27:
				return true;//перемещает булевую переменную продолжения в значение false
			default:
				badsymb = true;
			}
		} while (badsymb);
	} while (repeat);
}
void List::show()
{
	int i;
	int pointer = 0;
	int c;
	bool repeat = true;
	bool notnorm;
	const char arrow = 17;
	const char like = 3;
	const int out = 27;
	int screen = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	man[2].favorite = true;
	man[4].favorite = true;
	man[103].favorite = true;
	man[181].favorite = true;
	do
	{
		SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
		notnorm = true;
		system("CLS");
		cout << "УБЕДИТЕСЬ, ЧТО У ВАС НА КЛАВИАТУРЕ СЕЙЧАС РУССКАЯ РАСКЛАДКА" << endl;
		for (i = screen; i < pointer; i++)
			if (man[i].favorite) 
			{
				SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | RED));
				cout << like;
				SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
				cout << i << " ";
				man[i].printc();
			}
			else
			{
				SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
				cout << " ";
				cout << i << " ";
				man[i].printc();
			}
		if (man[i].favorite)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | RED));
			cout << like;
			SetConsoleTextAttribute(hConsole, (WORD)((CYAN << 4) | YELLOW));
			cout << i << " ";
			man[pointer].printc();
		}
		else
		{
			cout << " ";
			SetConsoleTextAttribute(hConsole, (WORD)((CYAN << 4) | YELLOW));	
			cout << i << " ";
			man[pointer].printc();
		}
		for (i = pointer + 1; i < k && i < screen + out; i++)
			if (man[i].favorite)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | RED));
				cout << like;
				SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
				cout << i << " ";
				man[i].printc();
			}
			else
			{
				SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
				cout << " ";
				cout << i << " ";
				man[i].printc();
			}
		SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
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
				man[pointer].contact_menu();
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
					screen *= k;
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
			}
		}
	} while (repeat);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	menu();
	system("pause");
}
