#include <iostream>

using namespace std;

class ConversionTemperature
{
private:
	double tektemp;
	double anothertemp;
public:
	ConversionTemperature()
	{
		tektemp = 21;
		/*cout << "Здесь заработал констурктор!" << endl;
		cout << "Текущее значение температуры = " << tektemp << endl;*/
	}
	double SetTekTemp()
	{
		cout << "Введите число (в градусах Цельсия): ";
		cin >> tektemp;
		anothertemp = tektemp;
		return anothertemp;
	}
	void ReturnDefVal(double deftemp)
	{
		tektemp = deftemp;
	}
	void GetTekTemp(string namestr)
	{
		cout << "Текущее значение температуры  = " << tektemp << " " << namestr << endl;
	}
	void TempKelvin()
	{
		tektemp += 273.15;
	}
	void TempFar()
	{
		tektemp = ((9 * tektemp) / 5) + 32;
	}
	void TempReor()
	{
		tektemp = tektemp * 0.8;
	}
	void TempRo()
	{
		tektemp = (21 * tektemp / 40) + 7.5;
	}
	void TempRan()
	{
		tektemp = (tektemp + 273.15) * 9 / 5;
	}
};

int ChoiceTransl();
void Menu();
void Repete(int* i);

ConversionTemperature a;
int temp = 0;
double cormis = 21;

int main()
{
	setlocale(LC_ALL, "Rus");
	int i;
	string namec;
	//небольшая менюшка для 3 режимов (их описание)
	Menu();
	cout << "Введите номер: ";
	cin >> i;
	switch (i)
	{
		case 1:
			//установить температуру.
			cormis = a.SetTekTemp();
			break;
		case 2:
			//получить знания о тек переменной.
			namec = "Градусов Цельсия";
			a.ReturnDefVal(cormis);
			a.GetTekTemp(namec);
			break;
		case 3:
			//Перевести в другую шкалу температуры.
			if (temp != 0 )
			{
				a.ReturnDefVal(cormis);
				temp = 0;
			}
			i = ChoiceTransl();
			temp++;
			break;
	default:
		cout << "Такой позиции в программе не доступно, всего доброго!";
		break;
	}
	//temp++;
	Repete(&i);
	/*cout << "Программа завершила свою работу!" << endl;*/
	return 0;
}

int ChoiceTransl()
{
	int i = 0;
	string name;
	cout << "Доступны следующие шкалы температур:\n\t(1) - Кельвины\n\t(2) - Фаренгейты\n\t(3) - Реомюры\n\t(4) - Рёмеры\n\t(5) - Ранкины" << endl;
	cout << "Введите цифру, в которой хотите узнать данное значение температуры: ";
	cin >> i;
	//Выбор в какую шкалу температур перевести.
	switch (i)
	{
	case 1:
		a.TempKelvin();
		name = "Кельвинов";
		a.GetTekTemp(name);
		break;
	case 2:
		a.TempFar();
		name = "градусов по Фаренгейту";
		a.GetTekTemp(name);
		break;
	case 3:
		a.TempReor();
		name = "градусов Реомюра";
		a.GetTekTemp(name);
		break;
	case 4:
		a.TempRo();
		name = "градусов Рёмера";
		a.GetTekTemp(name);
		break;
	case 5:
		a.TempRan();
		name = "градусов Ранкина";
		a.GetTekTemp(name);
		break;
	default:
		cout << "Такой позиции в программе не доступно, всего доброго!";
		break;
	}
	return 3;
}

void Menu()
{
	cout << "  Здравствуйте, уважаемый пользователь, в программе доступны следующие возможности:\n\t(1)Установить свою температуру.\n\t(2)Получить знания о установленной сейчас температуре.\n\t(3)Узнать текущую температуру в другой системе измерения температуры.\n";
}

void Repete(int *i)
{
	int j = -1;
	if ((*i == 1)||(*i == 2))
	{
		if (*i == 1)
		{
			cout << "Ваше значение температуры успешно установлено!\n";
		}
		system("pause");
		system("cls");
		main();
	}
	else
	{
		cout << "\nХотите ли вы продолжить работу с программой? Если да, то введите 1, если хотите завершить работу нажмите 0\n";
		while ((j < 0) || (j > 1))
		{
			cout << "Введите число:";
			cin >> j;
			if ((j < 0) || (j > 1))
			{
				cout << "Вы ввели неверное число, повторите ввод!\n";
			}
		}
	}
	if (j == 1)
	{
		system("cls");
		main();
	}
}