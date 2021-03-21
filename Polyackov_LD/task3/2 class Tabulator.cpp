
#include "all.h"

//private:

//������������ ����� �����
int Tabulator::MaxLengthX(int quantity)
{
	int len = 0;
	double value;
	fabs(TabData[0].x) >= fabs(TabData[quantity - 1].x) ? value = TabData[0].x : value = TabData[quantity - 1].x;
	if (value < 0) {
		value *= -1;
		len++;
	}
	while (value >= 1) {
		value /= 10;
		len++;
	}
	return len;
}

//public:

//�����������
Tabulator::Tabulator(int _Points, double _LeftBound, double _RightBound) : Points(_Points), LeftBound(_LeftBound), RightBound(_RightBound)
{
	func = nullptr;
	TabData = nullptr;
}

//�������
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

// �������� ����������, ���� �� ������ � TabData
bool Tabulator::TabDataExist()
{
	if (TabData == nullptr)
		return false;
	return true;
}

//�������
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
		func = new Arcsin;
		break;
	case 5:
		func = new Arccos;
		break;
	case 6:
		func = new Arctan;
		break;
	case 7:
		func = new Sinh;
		break;
	case 8:
		func = new Cosh;
		break;
	case 9:
		func = new Tanh;
		break;
	case 10:
		func = new Asinh;
		break;
	case 11:
		func = new Acosh;
		break;
	case 12:
		func = new Atanh;
		break;
	case 13:
		func = new XPowTwo;
		break;
	case 14:
		func = new XPowThree;
		break;
	case 15:
		func = new Sqrt;
		break;
	case 16:
		func = new Cbrt;
		break;
	case 17:
		func = new TwoPowX;
		break;
	case 18:
		func = new ExpPowX;
		break;
	case 19:
		func = new TenPowX;
		break;
	case 20:
		func = new Log2;
		break;
	case 21:
		func = new Loge;
		break;
	case 22:
		func = new Log10;
		break;
	case 23:
		func = new FractPart;
		break;
	case 24:
		func = new Floor;
		break;
	case 25:
		func = new Abs;
		break;
	default:
		func = nullptr;
		break;
	}
}

//���������
void Tabulator::TabFunc()
{
	double x = LeftBound;
	double Step = abs(RightBound - LeftBound) / (double(Points) - 1);
	TabData = new TabPoint[Points];
	for (int i = 0; i < Points - 1; i++)
	{
		TabData[i].x = x;
		TabData[i].y = counter(x);
		x += Step;
	}
	TabData[Points - 1].x = RightBound;
	TabData[Points - 1].y = counter(x);
}

//�������� ������������ ������
void Tabulator::DeleteTabData()
{
	if (TabData != nullptr)
	{
		delete[] TabData;
		TabData = nullptr;
	}
}

//������� ������ �� �����
void Tabulator::PrintData()
{
	int lengthx = MaxLengthX(Points) + 9;
	cout << "\n ����������� x � y" << endl << endl;
	for (int i = 0; i < Points; i++)
		cout << " " << left << setw(lengthx) << TabData[i].x << "| " << TabData[i].y << endl;
}

void Tabulator::PrintData(int quantity)
{
	int lengthx = MaxLengthX(quantity) + 9;
	cout << "\n ����������� x � y" << endl << endl;
	for (int i = 0; i < quantity; i++)
		cout << " " << left << setw(lengthx) << TabData[i].x << "| " << TabData[i].y << endl;
}

//��������� ������ � ����
void Tabulator::SaveData()
{
	char* tmpstr = new char[MAX_SYMB];
	int lengthx;
	time_t seconds = time(NULL);
	strftime(tmpstr, MAX_SYMB, "tabfunction (%H.%M.%S).txt", localtime(&seconds)); //%H - ����, %M - ������, %S - �������
	ofstream fout;
	fout.open(tmpstr);
	delete[] tmpstr;
	tmpstr = nullptr;
	if (!fout.is_open())
		throw exception(" ������ �������� �����!");
	lengthx = MaxLengthX(Points) + 9;
	fout << "\n ����������� x � y" << endl << endl;
	for (int i = 0; i < Points; i++)
		fout << " " << left << setw(lengthx) << TabData[i].x << "| " << TabData[i].y << endl;
	fout.close();
}

//����������
Tabulator::~Tabulator()
{
	if (func != nullptr)
		delete func;
	if (TabData != nullptr)
		delete[] TabData;
}
