
#include "all.h"

double** Tabulator::TabFunc(Function* func)
{
	double x = LeftBound;
	double Step = abs(RightBound - LeftBound) / (double(Points) - 1);
	double** tmp = new double* [Points];
	for (int i = 0; i < Points; i++)
	{
		tmp[i] = new double[2];
		tmp[i][0] = x;
		tmp[i][1] = counter(func, x);
		x += Step;
	}
	return tmp;
}

void Tabulator::SetFunc(int type)
{
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
		func = new ReturnX;
		break;
	}
}
