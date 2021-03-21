
#include "all.h"

//private:

//Максимальная длина числа
int Tabulator::MaxLengthX()
{
	double value = TabData[0].x;
	for (int i = 1; i < Points; i++)
		if (value < fabs(TabData[i].x))
			value = TabData[i].x;
	int len = 0;
	if (value < 0)
	{
		value = (-1) * value;
		len++;
	}
	while (value >= 1)
	{
		value /= 10;
		len++;
	}
	len += 4; //Для дробной части
	return len;
}

//public:

//Конструктор
Tabulator::Tabulator(int _Points, double _LeftBound, double _RightBound) : Points(_Points), LeftBound(_LeftBound), RightBound(_RightBound)
{
	func = nullptr;
	TabData = nullptr;
}

//Геттеры
double* Tabulator::GetBounds()
{
	double* tmparr = new double[2];
	tmparr[0] = LeftBound;
	tmparr[1] = RightBound;
	return tmparr;
}

double* Tabulator::GetTabPointData(int point)
{
	double* tmparr = new double[2];
	tmparr[0] = TabData[point].x;
	tmparr[1] = TabData[point].y;
	return tmparr;
}

//Сеттеры
void Tabulator::SetFunc(int type)
{
	if (func != nullptr)
		delete func;
	switch (type)
	{
	case 1:
		func = new Sin;
		break;
	case 2:
		func = new Cos;
		break;
	case 3:
		func = new Tan;
		break;
	case 4:
		func = new Cot;
		break;
	case 5:
		func = new Arcsin;
		break;
	case 6:
		func = new Arccos;
		break;
	case 7:
		func = new Arctan;
		break;
	case 8:
		func = new Arccot;
		break;
	case 9:
		func = new Sinh;
		break;
	case 10:
		func = new Cosh;
		break;
	case 11:
		func = new Tanh;
		break;
	case 12:
		func = new Cotanh;
		break;
	case 13:
		func = new Asinh;
		break;
	case 14:
		func = new Acosh;
		break;
	case 15:
		func = new Atanh;
		break;
	case 16:
		func = new Acotanh;
		break;
	case 17:
		func = new XPowTwo;
		break;
	case 18:
		func = new XPowThree;
		break;
	case 19:
		func = new Sqrt;
		break;
	case 20:
		func = new Cbrt;
		break;
	case 21:
		func = new TwoPowX;
		break;
	case 22:
		func = new ExpPowX;
		break;
	case 23:
		func = new TenPowX;
		break;
	case 24:
		func = new Log2;
		break;
	case 25:
		func = new Loge;
		break;
	case 26:
		func = new Log10;
		break;
	case 27:
		func = new FractPart;
		break;
	case 28:
		func = new Floor;
		break;
	case 29:
		func = new Abs;
		break;
	default:
		func = nullptr;
		break;
	}
}

//Табулятор
void Tabulator::TabFunc()
{
	double x = LeftBound;
	double Step = abs(RightBound - LeftBound) / (double(Points) - 1);
	TabData = new TabPoint[Points];
	for (int i = 0; i < Points; i++)
	{
		TabData[i].x = x;
		TabData[i].y = counter(x);
		x += Step;
	}
}

//Удаление неактуальной памяти
void Tabulator::DeleteTabData()
{
	if (TabData != nullptr)
	{
		delete[] TabData;
		TabData = nullptr;
	}
}

//Вывести данные на экран
void Tabulator::PrintData()
{
	int lengthx = MaxLengthX();
	cout << "\n x" << setfill(' ') << setw(lengthx) << "  | y" << endl << endl;
	for (int i = 0; i < Points; i++)
		cout << " " << left << setw(lengthx) << setprecision(4) << TabData[i].x << "| " << left << setprecision(4) << TabData[i].y << endl;
}

//Сохранить данные в файл
void Tabulator::SaveData()
{
	char* tmpstr = new char[MAX_SYMB];
	int lengthx;
	time_t seconds = time(NULL);
	strftime(tmpstr, MAX_SYMB, "tabfunction (%H.%M.%S).txt", localtime(&seconds)); //%H - часы, %M - минуты, %S - секунды
	ofstream fout;
	fout.open(tmpstr);
	delete[] tmpstr;
	tmpstr = nullptr;
	if (!fout.is_open())
		throw exception(" Ошибка открытия файла!");
	lengthx = MaxLengthX();
	fout << "\n x" << setfill(' ') << setw(lengthx) << "  | y" << endl << endl;
	for (int i = 0; i < Points; i++)
		fout << " " << left << setw(lengthx) << setprecision(4) << TabData[i].x << "| " << left << setprecision(4) << TabData[i].y << endl;
	fout.close();
}

//Деструктор
Tabulator::~Tabulator()
{
	if (func != nullptr)
		delete func;
	if (TabData != nullptr)
		delete[] TabData;
}
