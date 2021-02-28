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
		tektemp = -273.15;
		/*cout << "����� ��������� �����������!" << endl;
		cout << "������� �������� ����������� = " << tektemp << endl;*/
	}
	double SetTekTemp(double temper)
	{
		tektemp = temper;
		anothertemp = tektemp;
		return anothertemp;
	}
	void ReturnDefVal(double deftemp)
	{
		tektemp = deftemp;
	}
	void GetTekTemp(string namestr)
	{
		cout << "������� �������� �����������  = " << tektemp << " " << namestr << endl;
	}
	double TempKelvin()
	{
		tektemp += 273.15;
		return tektemp;
	}
	double TempFar()
	{
		tektemp = ((9 * tektemp) / 5) + 32;
		return tektemp;
	}
	double TempReor()
	{
		tektemp = tektemp * 0.8;
		return tektemp;
	}
	double TempRo()
	{
		tektemp = (21 * tektemp / 40) + 7.5;
		return tektemp;
	}
	double TempRan()
	{
		tektemp = (tektemp + 273.15) * 9 / 5;
		return tektemp;
	}
};

int ChoiceTransl();
void Menu();
void Repete(int* i);

ConversionTemperature a;
int temp = 0;
double cormis = -273.15;

int main()
{
	setlocale(LC_ALL, "Rus");
	int i;
	double temperature;
	string namec;
	//��������� ������� ��� 3 ������� (�� ��������)
	Menu();
	cout << "������� �����: ";
	cin >> i;
	switch (i)
	{
		case 1:
			//���������� �����������.
			cout << "������� ����� (� �������� �������): ";
			cin >> temperature;
			cormis = a.SetTekTemp(temperature);
			break;
		case 2:
			//�������� ������ � ��� ����������.
			namec = "�������� �������";
			a.ReturnDefVal(cormis);
			a.GetTekTemp(namec);
			break;
		case 3:
			//��������� � ������ ����� �����������.
			if (temp != 0 )
			{
				a.ReturnDefVal(cormis);
				temp = 0;
			}
			i = ChoiceTransl();
			temp++;
			break;
	default:
		cout << "����� ������� � ��������� �� ��������, ����� �������!";
		break;
	}
	//temp++;
	Repete(&i);
	/*cout << "��������� ��������� ���� ������!" << endl;*/
	return 0;
}

int ChoiceTransl()
{
	int i = 0;
	double valuetemperature;
	string name;
	cout << "�������� ��������� ����� ����������:\n\t(1) - ��������\n\t(2) - ����������\n\t(3) - �������\n\t(4) - и����\n\t(5) - �������" << endl;
	cout << "������� �����, � ������� ������ ������ ������ �������� �����������: ";
	cin >> i;
	//����� � ����� ����� ���������� ���������.
	switch (i)
	{
	case 1:
		valuetemperature = a.TempKelvin();
		name = "���������";
		a.GetTekTemp(name);
		break;
	case 2:
		valuetemperature = a.TempFar();
		name = "�������� �� ����������";
		a.GetTekTemp(name);
		break;
	case 3:
		valuetemperature = a.TempReor();
		name = "�������� �������";
		a.GetTekTemp(name);
		break;
	case 4:
		valuetemperature = a.TempRo();
		name = "�������� и����";
		a.GetTekTemp(name);
		break;
	case 5:
		valuetemperature = a.TempRan();
		name = "�������� �������";
		a.GetTekTemp(name);
		break;
	default:
		cout << "����� ������� � ��������� �� ��������, ����� �������!";
		break;
	}
	return 3;
}

void Menu()
{
	cout << "  ������������, ��������� ������������, � ��������� �������� ��������� �����������:\n\t(1)���������� ���� �����������.\n\t(2)�������� ������ � ������������� ������ �����������.\n\t(3)������ ������� ����������� � ������ ������� ��������� �����������.\n";
}

void Repete(int *i)
{
	int j = -1;
	if ((*i == 1)||(*i == 2))
	{
		if (*i == 1)
		{
			cout << "���� �������� ����������� ������� �����������!\n";
		}
		system("pause");
		system("cls");
		main();
	}
	else
	{
		cout << "\n������ �� �� ���������� ������ � ����������? ���� ��, �� ������� 1, ���� ������ ��������� ������ ������� 0\n";
		while ((j < 0) || (j > 1))
		{
			cout << "������� �����:";
			cin >> j;
			if ((j < 0) || (j > 1))
			{
				cout << "�� ����� �������� �����, ��������� ����!\n";
			}
		}
	}
	if (j == 1)
	{
		system("cls");
		main();
	}
}