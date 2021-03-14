#include <iostream>
#include "_menu.h"


void main()
{
	char choice;
	setlocale(LC_ALL, "Russian");
	Menu first(4);
	first.SetChoice(0,'1' ,"Продолжить");
	first.SetChoice(1, '2', "Новая игра");
	first.SetChoice(2, '3', "Настройки");
	first.SetChoice(3, '0', "Выход");
	first.PrintMenu(50,3);
	cin >> choice;
	first.Choice(choice);
	first.PrintChoicedAct();
	cin >> choice;
	first.Choice(choice);
	first.PrintChoicedAct();
	system("pause");
}