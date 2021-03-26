		//����������� ����� ��������� �������.
//����� ������ ��������� ��������� ������������� ������������ ������� ����� ����������, �������� � ���� ������� ����� C++.
//����� ������ ��������� ����������� ��������� ������(������������, ���������� � ��.).
//����� ������ ������������� ��������� �������� : 1) ������ ������� �������, 2) ������ ������� ����� ����� �������������, 
//3) ������ ������� ����� ����� �������������, 4) ������ ������� �������������, 
//5) ������ ������� �������������, 6) ��������� ������������� �������, 7) ������ ���������� �������������, 
//8) ��������� ���������� ������������� � ����.

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
		//�������� �� ������������
		//������.���� �� � � ������� ������������ ������ ������������? - ���, �� ������ ��� ������!
		leftbound = lbound;
		rightbound = rbound;
	}
	void SetNumPoints(int npoints)
	{
		//�������� �� ������������
		numpoints = npoints;
		DeleteArrays();
		CreateArrays();
	}
	int GetNumPoints() {return numpoints;}

	void SaveInFile()
	{
		string a;
		ofstream fout("������������������������������.txt");
		if (!fout)
		{
			cout << "��������� �������������� ������!" << endl;
			exit(1);
		}
		else
		{
			fout << "\t\t���������� ������������� �������:\n\n�������� ��������� x\t\t�������� ������� y\n";
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
			cout << "(" << i + 1 << ") �������� ������� ���������� = " << Arrarg[i] << endl;
			cout << "(" << i + 1 << ") �������� ������� �������� = " << Arrfunvalue[i] << endl;
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
//� ���������� ���������, ��� � ��� ���������, ��������� �� ���������
//��������� ��� ����
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
	cout << "\t������ ��������������� � ��������� �������:" << endl;
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
			cout << "������!������� ��� ����� ������� �� ����������! ��������� ����!" << endl;
		}
	}
	switch (choice)
	{
	case 1:
		f.SetFunction(MySin);
		cout << "������� " << Arrmanesfun[choice - 1] << " ������� �����������!" << endl;
		break;
	case 2:
		f.SetFunction(MyCos);
		cout << "������� " << Arrmanesfun[choice - 1] << " ������� �����������!" << endl;
		break;
	case 3:
		f.SetFunction(MyExp);
		cout << "������� " << Arrmanesfun[choice - 1] << " ������� �����������!" << endl;
		break;
	case 4:
		f.SetFunction(MyModul);
		cout << "������� " << Arrmanesfun[choice - 1] << " ������� �����������!" << endl;
		break;
	case 5:
		f.SetFunction(MySquare);
		cout << "������� " << Arrmanesfun[choice - 1] << " ������� �����������!" << endl;
		break;
	case 6:
		f.SetFunction(MyBisector);
		cout << "������� " << Arrmanesfun[choice - 1] << " ������� �����������!" << endl;
		break;
	case 7:
		f.SetFunction(MySh);
		cout << "������� " << Arrmanesfun[choice - 1] << " ������� �����������!" << endl;
		break;
	case 8:
		f.SetFunction(MyCh);
		cout << "������� " << Arrmanesfun[choice - 1] << " ������� �����������!" << endl;
		break;
	default:
		break;
	}
	return choice;
}

void Menu()
{
	cout << "  ������������, ��������� ������������, � ��������� �������� ��������� �����������:\n\t(1) ������ ������� �������.\n\t(2) ������ ������� ����� ����� �������������.\n\t(3) ������ ������� ����� ����� �������������.\n\t(4) ������ ������� �������������.\n\t(5) ������ ������� �������������.\n\t(6) ��������� ������������� �������.\n\t(7) ������ ���������� �������������.\n\t(8) ��������� ���������� ������������� � ����.\n\t(0) ����� �� ���������.\n";
}
//������� �����������, ������������ � �����, ���������� - �������� 
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
		cout << "������� ����� ������, ������� �� ������ �������: " << endl;
		choice = -1;
		while ((choice < 0) || (choice > 8))
		{
			cin >> choice;
			if ((choice < 0) || (choice > 8))
			{
				cout << "�� ����� �������� �����, ��������� ����!" << endl;
			}
		}
		switch (choice)
		{
		case 1:
			choicefun = ChoiceFun(fun);
			cout << "������� ������� �����������!" << endl;
			control = true;
			system("pause");
			break;
		case 2:
			cout << "������� ����� ����� �������������: " << endl;
			numpoints = 1;
			while (numpoints < 2)
			{
				cin >> numpoints;
				if (numpoints < 2)
				{
					cout << "������������ ���������� ����� �������������, �� ����� ���� ������� ���!" << endl;
				}
			}
			fun.SetNumPoints(numpoints);
			cout << "�������� ������� �����������!" << endl;
			system("pause");
			break;
		case 3:
			numpoints = fun.GetNumPoints();
			cout << "�������� ����� ����� ������������� = " << numpoints << endl;
			system("pause");
			break;
		case 4:
			cout << "������� ����� � ������ ������� �������: " << endl;
			lbound = 1, rbound = 0;
			while (lbound >= rbound)
			{
				cin >> lbound >> rbound;
				if (lbound >= rbound)
				{
					cout << "������! �� ��������� ������ ������������ ������ (����� ������� ������ ���� ������ ������ ������).��������� ����" << endl;
				}
			}
			fun.SetBounds(lbound, rbound);
			cout << "�������� ������� �����������!" << endl;
			system("pause");
			break;
		case 5:
			bounds = fun.GetFunSegment();
			cout << "������� �������������: �� " << bounds.leftb << " �� " << bounds.rightb << endl;
			system("pause");
			break;
		case 6:
			if (!control) {
				cout << "�� �� ������� ������� ��� ������� ����� ��������� �������������!" << endl;
				system("pause");
				break;
			}
			else
			{
				fun.MakeTabFunctiion();
				cout << "������������� ������� " << Arrmanesfun[choicefun - 1] << " ������� ���������" << endl;
				system("pause");
				break;
			}
		case 7:
			if (!control) {
				cout << "�� �� ������� ������� ��� ������� ����� ��������� �������������!" << endl;
				system("pause");
				break;
			}
			else
			{
				fd = fun.GetDataTabul();
				for (int i = 0; i < numpoints; i++)
				{
					cout << "�������� �������" << Arrmanesfun[choicefun - 1] << " =  " << fd.ArrArgsPointer[i];
					cout << "\t�������� ������� " << Arrmanesfun[choicefun - 1] << " = " << fd.ArrFunValuePointer[i] << endl;
				}
				system("pause");
				break;
			}
		case 8:
			if (!control) {
				cout << "�� �� ������� ������� ��� ������� ����� ��������� �������������!" << endl;
				system("pause");
				break;
			}
			else
			{
				fun.SaveInFile();
				cout << "������ ����������� ������������� ������� " << Arrmanesfun[choicefun - 1] << " � ���� ������ �c�����!" << endl;
				system("pause");
				break;
			}
		default:
			cout << "��������� ��������� ���� ������. ����� ��������, ����������!" << endl;
			system("pause");
			ex = false;
			break;
		}
		system("cls");
	}
}