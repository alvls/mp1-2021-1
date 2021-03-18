#include "_menu.h"
using namespace std;

void main()
{
	char choice;
	setlocale(LC_ALL, "Russian");
	Menu first(4);
	first.SetAct(0,'1' ,"Продолжить");
	first.SetAct(1, '2', "Новая игра");
	first.SetAct(2, '3', "Настройки");
	first.SetAct(3, 'e', "Выход");
	cout << "Количество пунктов в меню: " << first.GetCountActs() << endl;
	first.PrintMenu(55,3);
	cin >> choice;
	first.Choice(choice);
	while (first.GetLastChoice() == -1)
	{
		if(first.GetLastChoice() == -1)
			cout << "Ошибка выбора" << endl;
		cin >> choice;
		first.Choice(choice);
	}
	cout << "Номер пункта меню последнего выбора пользователя: " << first.GetLastChoice() << endl;
	cout << "Имя пункта последнего выбора пользователя: "; 
	first.PrintChoicedAct();
	cin >> choice;
	first.Choice(choice);
	while (first.GetLastChoice() == -1)
	{
		if (first.GetLastChoice() == -1)
			cout << "Ошибка выбора" << endl;
		cin >> choice;
		first.Choice(choice);
	}
	cout << "Номер пункта меню последнего выбора пользователя: " << first.GetLastChoice() << endl;
	cout << "Имя пункта последнего выбора пользователя: ";
	first.PrintChoicedAct();
	system("pause");
}