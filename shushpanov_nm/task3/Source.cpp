#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdio>
#include <string>

using namespace std;

class TaylorSeries
{
private:
	double x, referenceValue, calculationAccuracy;
	int numberOfMembers, paramFunction;
public:
	TaylorSeries(double newX = 1, int newNumberOfMembers = 1, int newParamFunction = 0, double newReferenceValue = 1, double newCalculationAccuracy = 0.01)
		: x(newX), numberOfMembers(newNumberOfMembers), paramFunction(newParamFunction), referenceValue(newReferenceValue), calculationAccuracy(newCalculationAccuracy) {}
	void SetFunction(int newParamFunction)
	{
		paramFunction = newParamFunction;
	}
	int GetFunction()
	{
		return paramFunction;
	}
	void SetTheNumberSeries(int newNumberOfMembers)
	{
		numberOfMembers = newNumberOfMembers;
	}
	int GetNumberSeries()
	{
		return numberOfMembers;
	}
	void SetValueX(double newX)
	{
		x = newX;
	}
	double GetValueX()
	{
		return x;
	}
	string GetSeriesFormula()
	{
		string formula;
		switch (paramFunction)
		{
			case 1:
			{
				formula = "sin(x) = x - (x^3)/(3!) + (x^5)/(5!) - ... + ((-1)^(n+1))*((x^(2*n-1))/(2*n-1)!";
			}
			case 2:
			{
				formula = "cos(x) = 1 - (x^2)/(2!) + (x^4)/(4!) - (x^6)/(6!) + ... + ((-1)^(n+1))*((x^(2*n))/(2*n)!";
			}
			case 3:
			{
				formula = "exp(x) = 1 + x/(1!) + (x^2)/(2!) + (x^3)/(3!) + ... + (x^n)/(n!)";
			}
		}
		return formula;
	}
	double FunctionSin(int paramCalc)
	{
		int i;
		double xRad = x * (M_PI / 180);
		double function = xRad, term = xRad, devation = 0;
		referenceValue = sin(xRad);
		for (i = 2; (i <= numberOfMembers) && (fabs(xRad - referenceValue) > calculationAccuracy); i++)
		{
			term *= (-1) * xRad * xRad / (2 * i * (2 * i + 1));
			function += term;
		}
		if (paramCalc == 0)
		{
			return term;
		}
		else if (paramCalc == 1)
		{
			return function;
		}
		else
		{
			devation = fabs(referenceValue - function);
			return devation;
		}
	}
	double FunctionCos(int paramCalc)
	{
		int i;
		double xRad = x * (M_PI / 180);
		double function = 1, term = 1, devation = 0;
		referenceValue = cos(xRad);
		for (i = 2; (i <= numberOfMembers) && (fabs(xRad - referenceValue) >= calculationAccuracy); i++)
		{
			term *= (-1) * xRad * xRad / ((2 * i - 2) * (2 * i - 3));
			function += term;
		}
		if (paramCalc == 0)
		{
			return term;
		}
		else if (paramCalc == 1)
		{
			return function;
		}
		else
		{
			devation = fabs(referenceValue - function);
			return devation;
		}
	}
	double FunctionExpiration(int paramCalc)
	{
		int i;
		double function = 1, term = 1, devation = 0;
		referenceValue = exp(x);
		for (i = 2; (i <= numberOfMembers) && (fabs(x - referenceValue) >= calculationAccuracy); i++)
		{
			term *= x / (i - 1);
			function += term;
		}
		if (paramCalc == 0)
		{
			return term;
		}
		else if (paramCalc == 1)
		{
			return function;
		}
		else
		{
			devation = fabs(referenceValue - function);
			return devation;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	bool end = true;
	double _x;
	int _numberOfMembers, indexMenu, indexFunction;
	cout << "Добро пожаловать!" << endl;
	TaylorSeries func;
	cout << "Введите значение x (Пример: 3.5): ";
	cin  >> _x;
	func.SetValueX(_x);
	while (end)
	{
		cout << "\nПрограмма умеет: \n" << "1. Задать значение x;\n" << "2. Задать текущую функцию;\n" << "3. Узнать текущую функцию;\n" << "4. Задать текущее число членов ряда;\n"
			<< "5. Узнать текущее число членов ряда;\n" << "6. Выдать формулу ряда для выбранной функции;\n"
			<< "7. Выдать значение заданного члена ряда;\n"
			<< "8. Рассчитать значение ряда в выбранной точке x;\n" << "9. Вывести отклонение значения ряда в выбранной точке от эталонного значения текущей функции в данной точке;\n" 
			<< "0. Выйти из программы.\n" << endl;
		cout << "Выберите пункт меню: ";
		cin >> indexMenu;
		switch (indexMenu)
		{
			case 1:
			{
				cout << "Введите значение x (Пример: 3.5): ";
				cin >> _x;
				func.SetValueX(_x);
				break;
			}
			case 2:
			{
				cout << "Выберите функцию: \n" << "1. sin(x);\n" << "2. cos(x);\n" << "3. exp(x);\n" << endl;
				cout << "Введите функцию: ";
				cin >> indexFunction;
				switch (indexFunction)
				{
					case 1:
					{
						func.SetFunction(indexFunction);
						cout << "Выбрана функция sin(x)." << endl;
						break;
					}
					case 2:
					{
						func.SetFunction(indexFunction);
						cout << "Выбрана функция cos(x)." << endl;
						break;
					}
					case 3:
					{
						func.SetFunction(indexFunction);
						cout << "Выбрана функция exp(x)." << endl;
						break;
					}
					default:
					{
						cout << "Данный пункт меню не найден, попробуйте еще раз!" << endl;
						break;
					}
				}
				break;
			}
			case 3:
			{
				indexFunction = func.GetFunction();
				switch(indexFunction)
				{
					case 1:
					{
						cout << "\nВыбрана функция sin(x)." << endl;
						break;
					}
					case 2:
					{
						cout << "\nВыбрана функция cos(x)." << endl;
						break;
					}
					case 3:
					{
						cout << "\nВыбрана функция exp(x)." << endl;
						break;
					}
					default:
					{
						cout << "\nФункция еще не была выбрана!" << endl;
						break;
					}
				}
				break;
			}
			case 4:
			{
				cout << "Введите число членов ряда: ";
				cin >> _numberOfMembers;
				func.SetTheNumberSeries(_numberOfMembers);
				break;
			}
			case 5:
			{
				cout << "Текущее число членов ряда: " << func.GetNumberSeries() << endl;
				break;
			}
			case 6:
			{
				if (func.GetSeriesFormula() != "")
				{
					cout << "\nФормула нахождения ряда Тейлора: " << func.GetSeriesFormula() << endl;
				}
				else
				{
					cout << "\nНе выбрана функция! Выберите функцию и попробуйте снова..." << endl;
				}
				break;
			}
			case 7:
			{
				switch (func.GetFunction())
				{
					case 1:
					{
						cout << "\nЗначение заданного члена ряда Тейлора от sin(" << func.GetValueX() << "): " << func.FunctionSin(0) << endl;
						break;
					}
					case 2:
					{
						cout << "\nЗначение заданного члена ряда Тейлора от cos(" << func.GetValueX() << "): " << func.FunctionCos(0) << endl;
						break;
					}
					case 3:
					{
						cout << "\nЗначение заданного члена ряда Тейлора от exp(" << func.GetValueX() << "): " << func.FunctionExpiration(0) << endl;
						break;
					}
					default:
					{
						cout << "\nФункция еще не была выбрана!" << endl;
						break;
					}
				}
				break;
			}
			case 8:
			{
				switch (func.GetFunction())
				{
				case 1:
				{
					cout << "\nЗначение ряда Тейлора от sin(" << func.GetValueX() << "): " << func.FunctionSin(1) << endl;
					break;
				}
				case 2:
				{
					cout << "\nЗначение ряда Тейлора от cos(" << func.GetValueX() << "): " << func.FunctionCos(1) << endl;
					break;
				}
				case 3:
				{
					cout << "\nЗначение ряда Тейлора от exp(" << func.GetValueX() << "): " << func.FunctionExpiration(1) << endl;
					break;
				}
				default:
				{
					cout << "\nФункция еще не была выбрана!" << endl;
					break;
				}
				}
				break;
			}
			case 9:
			{
				switch (func.GetFunction())
				{
				case 1:
				{
					cout << "\nОтклонение значение ряда Тейлора от sin(" << func.GetValueX() << "): " << func.FunctionSin(2) << endl;
					break;
				}
				case 2:
				{
					cout << "\nОтклонение значение ряда Тейлора от cos(" << func.GetValueX() << "): " << func.FunctionCos(2) << endl;
					break;
				}
				case 3:
				{
					cout << "\nОтклонение значение ряда Тейлора от exp(" << func.GetValueX() << "): " << func.FunctionExpiration(2) << endl;
					break;
				}
				default:
				{
					cout << "\nФункция еще не была выбрана!" << endl;
					break;
				}
				}
				break;
			}
			case 0:
			{
				cout << "До свидания! Спасибо что воспользовались нашей программой!\n" << endl;
				end = false;
				break;
			}
			default:
			{
				cout << "Данный пункт меню не найден, попробуйте еще раз!" << endl << endl;
				break;
			}
		}
	}
	system("pause");
	return 0;
}