/*
    Разработать класс Конвертер температур.
    Класс должен хранить температуру в градусах Цельсия и предоставлять методы по его преобразованию в другие единицы измерения (Фаренгейт, Кельвин, Ранкин, …).
    Класс должен предоставлять операции: 1) установить текущую температуру в градусах Цельсия, 2) узнать текущую температуру в градусах Цельсия, 3) узнать текущую температуру в выбранной единице измерения (из списка поддерживаемых).
    Класс должен содержать все необходимые конструкторы, а также «уметь» выводить себя на консоль.
*/

#include <iostream>
#include <limits>
using namespace std;

class Temperature
{
private:
	double tcelc; //температура в цельсиях
public:
	//Все возможные конструкторы
	Temperature() 
	{
		tcelc = DBL_MIN;
	}
	//Геттеры и сеттеры
	double Get_tcelc()
	{
		return tcelc;
	}
	void Set_tcelc(double value_tcelc)
	{
		tcelc = value_tcelc;
	}
	//Проверка на объявление
	bool exist()
	{
		if (tcelc == DBL_MIN)
			return false;
		else
			return true;
	}
	//Конвертер
	double Fahrenheit()
	{
		return tcelc * 9 / 5 + 32;
	}
	double Kelvin()
	{
		return tcelc + 273.15;
	}
	double Rankine()
	{
		return (tcelc + 273.15) * 9 / 5;
	}
	double Delisle()
	{
		return (100 - tcelc) * 3 / 2;
	}
	double Newton()
	{
		return tcelc * 33 / 100;
	}
	double Reaumur()
	{
		return tcelc * 4 / 5;
	}
	double Romer()
	{
		return tcelc * 21 / 40 + 7.5;
	}
};	

int proverka(int a, int b)
{
	int vibor = -1;
	while ((vibor < a) || (vibor > b))
	{
		cin >> vibor;
		if ((vibor < a) || (vibor > b))
		{		
			cout << "Введено неверное число. Данная функция не предусмотрена программой." << endl;
			cin.clear();
		}
	}
	return vibor;
}

void main()
{
	Temperature t;
	int vibor[2] = { -1, -1 };
	bool exit = false;
	setlocale(LC_ALL, "Ru");
	cout << "\n Приветствую Вас! Я - конвертер температур!";
	while (exit == false)
	{
		cout << "\n Сейчас Вы находитесь в меню. Выберите, что нужно сделать :\n\t(1) Установить текущую температуру в градусах Цельсия\n\t(2) Узнать текущую температуру в градусах Цельсия\n\t(3) Узнать текущую температуру в нужной Вам единице измерения\n\t(0) Выйти из программы" << endl;
		vibor[0] = proverka(0, 3);
		system("cls");
		switch (vibor[0])
		{
		case 1: //Установить текущую температуру в градусах Цельсия
			double temp;
			cout << "\n Введите значение текущей температуры в градусах Цельсия.\n Для нецелых значений применяется \".\" в качестве разделителя." << endl;
			cin >> temp;
			t.Set_tcelc(temp);
			temp = DBL_MIN;
			break;
		case 2: //Узнать текущую температуру в градусах Цельсия
			if (t.exist())
				cout << "\n Текущая температура в градусах Цельсия: " << t.Get_tcelc() << " C" << endl;
			else
				cout << "\n Текущая температура в градусах Цельсия не была задана" << endl;
			break;
		case 3: //Узнать текущую температуру в нужной единице измерения
			if (t.exist() == false)
				cout << "\n Текущая температура в градусах Цельсия не была задана" << endl;
			else
			{
				cout << "\n В какую единицу измерения следует перевести текущую температуру?\n\t(1) Фаренгейт\n\t(2) Кельвин\n\t(3) Ранкин\n\t(4) Делиль\n\t(5) Ньютон\n\t(6) Реомюр\n\t(7) Рёмер" << endl;
				vibor[1] = proverka(1, 7);
				system("cls");
				switch (vibor[1])
				{
				case 1:
					cout << "\n Текущая температура в градусах Фаренгейта: " << t.Fahrenheit() << " F" << endl;
					break;
				case 2:
					cout << "\n Текущая температура в градусах Кельвина: " << t.Kelvin() << " K" << endl;
					break;
				case 3:
					cout << "\n Текущая температура в градусах Ранкина: " << t.Rankine() << " R" << endl;
					break;
				case 4:
					cout << "\n Текущая температура в градусах Делиля: " << t.Delisle() << " De" << endl;
					break;
				case 5:
					cout << "\n Текущая температура в градусах Ньютона: " << t.Newton() << " N" << endl;
					break;
				case 6:
					cout << "\n Текущая температура в градусах Реомюра: " << t.Reaumur() << " Re" << endl;
					break;
				case 7:
					cout << "\n Текущая температура в градусах Рёмера: " << t.Romer() << " Ro" << endl;
					break;
				default:
					cout << "\n Непредвиденная ошибка." << endl;
					exit = true;
					break;
				}
			}
			break;
		case 0:
			exit = true;
			break;
		default:
			cout << "\n Непредвиденная ошибка." << endl;
			exit = true;
			break;
		}
		system("pause");
		system("cls");
		vibor[0] = -1;
		vibor[1] = -1;
	}
}
