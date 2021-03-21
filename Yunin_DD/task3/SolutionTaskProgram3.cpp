		//Разработать класс Табулятор функции.
//Класс должен позволять выполнять табулирование произвольной функции одной переменной, заданной в виде функции языка C++.
//Класс должен содержать необходимые служебные методы(конструкторы, деструктор и пр.).
//Класс должен предоставлять следующие операции : 1) задать текущую функцию, 2) задать текущее число точек табулирования, 
//3) узнать текущее число точек табулирования, 4) задать отрезок табулирования, 
//5) узнать отрезок табулирования, 6) выполнить табулирование функции, 7) выдать результаты табулирования, 
//8) сохранить результаты табулирования в файл.

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int NumElemArray = 8;

string Arrmanesfun[NumElemArray] = {"Sin(x)", "Cos(x)", "Exp(x)","Abs(x)","Square(x)", "BisectorLine(x)","Sh(x)","Ch(x)"};

struct RetSeg
{
	double leftb;
	double rightb;
};

struct RetResultTub
{
	double* ArrArgsPointer;
	double* ArrFunValuePointer;
};

class TabulFunction
{
private:
	int numpoints;
	double leftbound;
	double rightbound;
	double(*funPtr)(double);
	double* Arrarg;
	double* Arrfunvalue;
	RetSeg Segment;
	RetResultTub GetResT;
	bool def = false;
	void FillSegment()
	{
		Segment.leftb = leftbound;
		Segment.rightb = rightbound;
	}

	void FillData()
	{
		GetResT.ArrArgsPointer = Arrarg;
		GetResT.ArrFunValuePointer = Arrfunvalue;
	}

	void DeleteArrays()
	{
		delete[] Arrarg; 
		delete[] Arrfunvalue;
	}

	void CreateArrays()
	{
		Arrarg = nullptr; Arrfunvalue = nullptr;
		Arrarg = new double[numpoints];
		Arrfunvalue = new double[numpoints];
	}
public:
	TabulFunction(int t_numpoints = 2, double t_leftbound = 0, double t_rightbound = 1)
		: numpoints(t_numpoints),leftbound(t_leftbound), rightbound(t_rightbound), funPtr(nullptr), Arrarg(nullptr),
		Arrfunvalue(nullptr), Segment{ t_leftbound,t_rightbound }, GetResT{ nullptr,nullptr } {}
	

	void SetFunction(double (*NowFunction)(double))
	{
		funPtr = NowFunction;
		if (def)
		{
			DeleteArrays();
		}
		CreateArrays();
		def = true;
	}
	void SetBounds(double lbound, double rbound)
	{
		//Проверка на корректность
		//Вопрос.Могу ли я в сеттере использовать список инциализации? - Нет, он только для класса!
		leftbound = lbound;
		rightbound = rbound;
	}
	void SetNumPoints(int npoints)
	{
		//Проверка на корректность
		numpoints = npoints;
		DeleteArrays();
		CreateArrays();
	}
	int GetNumPoints() {return numpoints;}

	void SaveInFile()
	{
		string a;
		ofstream fout("РезультатыТабулированияФункции.txt");
		if (!fout)
		{
			cout << "Случилась непредвиденная ошибка!" << endl;
			exit(1);
		}
		else
		{
			fout << "\t\tРезультаты табулирования функции:\n\nЗначение аргумента x\t\tЗначение функции y\n";
			for (int i = 0; i < numpoints; i++)
			{
				a = to_string(Arrarg[i]);
				fout << "\t" << Arrarg[i];
				a = to_string(Arrfunvalue[i]);
				fout << "\t\t\t\t" << setprecision(3) << Arrfunvalue[i] << endl;
			}
			fout.close();
		}
	}

	RetSeg GetFunSegment()
	{
		FillSegment();
		return Segment;
	}

	RetResultTub GetDataTabul()
	{
		FillData();
		return GetResT;
	}

	void MakeTabFunctiion()
	{
		double step,arg,funvalue;
		arg = leftbound;
		int i,counter;
		step = (rightbound - leftbound) / (((double)numpoints) - 1);
		for ( i = 0, counter = 0; counter < numpoints; i++,counter++)
		{
			funvalue = funPtr(arg);
			Arrarg[i] = arg;
			Arrfunvalue[i] = funvalue;
			arg += step;
		}
		/*for ( i = 0; i < numpoints; i++)
		{
			cout << "(" << i + 1 << ") Элемента массива аргументов = " << Arrarg[i] << endl;
			cout << "(" << i + 1 << ") Элемента массива значений = " << Arrfunvalue[i] << endl;
		}*/
	}
	~TabulFunction()
	{
		delete[] Arrarg;
		delete[] Arrfunvalue;
	}
};

double MySin(double x)
{
	return sin(x);
}

double MyCos(double x)
{
	return cos(x);
}

double MyExp(double x)
{
	return exp(x);
}

double MyModul(double x)
{
	return abs(x);
}

double MySquare(double x)
{
	return (x * x);
}

double MyBisector(double x)
{
	return x;
}

double MySh(double x)
{
	double y,y1,y2;
	y1 = exp(x); y2 = exp(-x);
	y = (y1 - y2) / 2.0;
	return y;
}

double MyCh(double x)
{
	double y, y1, y2;
	y1 = exp(x); y2 = exp(-x);
	y = (y1 + y2) / 2.0;
	return y;
}
//В инструкции прописать, где и что находится, параметры по умолчанию
//Помыслить над этим
//void gotoxy(int x, int y)
//{
//	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
//	if (!Console)
//		return;
//	COORD pos;
//	pos.X = x;
//	pos.Y = y;
//	SetConsoleCursorPosition(Console, pos);
//}

void PrintFun()
{
	cout << "\tСписок предоставленных в программе функций:" << endl;
	for (int i = 0; i < NumElemArray; i++)
	{
		cout << "(" << i + 1 << ") " << Arrmanesfun[i] << endl;
	}
}

int ChoiceFun(TabulFunction& f)
{
	int choice = 0;
	PrintFun();
	while ((choice < 1)||(choice > 8))
	{
		cin >> choice;
		if ((choice < 1) || (choice > 8))
		{
			cout << "Ошибка!Функции под таким номером не существует! Повторите ввод!" << endl;
		}
	}
	switch (choice)
	{
	case 1:
		f.SetFunction(MySin);
		cout << "Функция " << Arrmanesfun[choice - 1] << " успешно установлена!" << endl;
		break;
	case 2:
		f.SetFunction(MyCos);
		cout << "Функция " << Arrmanesfun[choice - 1] << " успешно установлена!" << endl;
		break;
	case 3:
		f.SetFunction(MyExp);
		cout << "Функция " << Arrmanesfun[choice - 1] << " успешно установлена!" << endl;
		break;
	case 4:
		f.SetFunction(MyModul);
		cout << "Функция " << Arrmanesfun[choice - 1] << " успешно установлена!" << endl;
		break;
	case 5:
		f.SetFunction(MySquare);
		cout << "Функция " << Arrmanesfun[choice - 1] << " успешно установлена!" << endl;
		break;
	case 6:
		f.SetFunction(MyBisector);
		cout << "Функция " << Arrmanesfun[choice - 1] << " успешно установлена!" << endl;
		break;
	case 7:
		f.SetFunction(MySh);
		cout << "Функция " << Arrmanesfun[choice - 1] << " успешно установлена!" << endl;
		break;
	case 8:
		f.SetFunction(MyCh);
		cout << "Функция " << Arrmanesfun[choice - 1] << " успешно установлена!" << endl;
		break;
	default:
		break;
	}
	return choice;
}

void Menu()
{
	cout << "  Здравствуйте, уважаемый пользователь, в программе доступны следующие возможности:\n\t(1) Задать текущую функцию.\n\t(2) Задать текущее число точек табулирования.\n\t(3) Узнать текущее число точек табулирования.\n\t(4) Задать отрезок табулирования.\n\t(5) Узнать отрезок табулирования.\n\t(6) Выполнить табулирование функции.\n\t(7) Выдать результаты табулирования.\n\t(8) Сохранить результаты табулирования в файл.\n\t(0) Выход из программы.\n";
}
//область определения, расположение в файле, инструкция - возможно 
int main()
{
	setlocale(LC_ALL, "Rus");
	TabulFunction fun;
	RetSeg bounds;
	RetResultTub fd;
	int choice, numpoints = 2, choicefun = 0;
	double lbound, rbound;
	bool ex = true, control = false;
	while (ex)
	{
		Menu();
		cout << "Введите номер режима, который вы хотите выбрать: " << endl;
		choice = -1;
		while ((choice < 0) || (choice > 8))
		{
			cin >> choice;
			if ((choice < 0) || (choice > 8))
			{
				cout << "Вы ввели неверный номер, повторите ввод!" << endl;
			}
		}
		switch (choice)
		{
		case 1:
			choicefun = ChoiceFun(fun);
			cout << "Функция успешно установлена!" << endl;
			control = true;
			system("pause");
			break;
		case 2:
			cout << "Введите число точек табулирования: " << endl;
			numpoints = 1;
			while (numpoints < 2)
			{
				cin >> numpoints;
				if (numpoints < 2)
				{
					cout << "Недопустимое количество точек табулирования, их может быть минимум две!" << endl;
				}
			}
			fun.SetNumPoints(numpoints);
			cout << "Значение успешно установлено!" << endl;
			system("pause");
			break;
		case 3:
			numpoints = fun.GetNumPoints();
			cout << "Заданное число точек табулирования = " << numpoints << endl;
			system("pause");
			break;
		case 4:
			cout << "Задайте левую и правую границы отрезка: " << endl;
			lbound = 1, rbound = 0;
			while (lbound >= rbound)
			{
				cin >> lbound >> rbound;
				if (lbound >= rbound)
				{
					cout << "Ошибка! Вы пытаетесь ввести некорректные данные (левая граница должна быть строго меньше правой).Повторите ввод" << endl;
				}
			}
			fun.SetBounds(lbound, rbound);
			cout << "Значения успешно установлены!" << endl;
			system("pause");
			break;
		case 5:
			bounds = fun.GetFunSegment();
			cout << "Отрезок табулирования: от " << bounds.leftb << " до " << bounds.rightb << endl;
			system("pause");
			break;
		case 6:
			if (!control) {
				cout << "Вы не выбрали функцию для которой будет проведено табулирование!" << endl;
				system("pause");
				break;
			}
			else
			{
				fun.MakeTabFunctiion();
				cout << "Табулирование функции " << Arrmanesfun[choicefun - 1] << " успешно проведено" << endl;
				system("pause");
				break;
			}
		case 7:
			if (!control) {
				cout << "Вы не выбрали функцию для которой будет проведено табулирование!" << endl;
				system("pause");
				break;
			}
			else
			{
				fd = fun.GetDataTabul();
				for (int i = 0; i < numpoints; i++)
				{
					cout << "Аргумент функции" << Arrmanesfun[choicefun - 1] << " =  " << fd.ArrArgsPointer[i];
					cout << "\tЗначения Функции " << Arrmanesfun[choicefun - 1] << " = " << fd.ArrFunValuePointer[i] << endl;
				}
				system("pause");
				break;
			}
		case 8:
			if (!control) {
				cout << "Вы не выбрали функцию для которой будет проведено табулирование!" << endl;
				system("pause");
				break;
			}
			else
			{
				fun.SaveInFile();
				cout << "Запись результатов табулирвоания функции " << Arrmanesfun[choicefun - 1] << " в файл прошла уcпешно!" << endl;
				system("pause");
				break;
			}
		default:
			cout << "Программа завершила свою работа. Всего хорошего, досвидания!" << endl;
			system("pause");
			ex = false;
			break;
		}
		system("cls");
	}
}