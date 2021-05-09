#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <cstring>
#include <time.h>	
using namespace std;
#define ALL 7

class storage//����� ����� �������
{
protected:
	char names[ALL][20] = { "AMD RADEON RX580", "NVIDIA GTX1050", "NVIDIA GTX1050TI", "AMD RADEON RX460", "NVIDIA GTX1660", "NVIDIA GT710", "NVIDIA RTX3090" };
	char codes[ALL][5] = { "1243","5136","5128","3014","8391","5814","2631" };
	float prices[ALL] = { 19990 ,7650 ,13020 ,6340 ,19720 ,3220 ,190000 };//��������� ������
	float discount[ALL] = { 0.1,0.05,0.2,0.1,0.25,0.05,0.5 };//������ ������ �� ������ �����
public:
	void printlist()//����� �� ������� ������ ������� �� ������
	{
		int j = 0;
		for (j = 0; j < 17; j++)
			cout << "-";
		cout << "������ � �������";
		for (j = 0; j < 17; j++)
			cout<<"-";
		cout << endl;
	 cout << setiosflags(ios::left) << setw(17) << "�����-���" << setw(24) << "��������" << "���������" << endl;
	 for(j=0;j<ALL;j++)
		 cout << setiosflags(ios::left) << setw(17) << codes[j] << setw(24) << names[j] << prices[j] << endl;
	}
	void printunit(int i)//����� �� ������� ������ � �����������
	{
		cout << "���������� " << setw(24) << names[i] << "����(���)=" << prices[i] << endl << "������ �� ����� ����������: " << setw(2) << discount[i] * 100 << setw(5) << "%";
	}
};

void timesec()//������� ��� ������ ������� � ���
{
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &result);
	cout << str;
}

class cashbox:public storage//����� �����(������� ������ �����, � ����� ������������ ��� �� �����, �� �������� �����������)
{
private:
	int kol[ALL] = {0};//������ ��� ������������� ���-�� ������� � �������
	char code [5];//����� ���� ��� ������������ ������
public:
	void read()//��������� �������� ��� ���������� ����(�� ��������� ��������� ����� 4 ��������)
	{
		char s;
		int i = 0;
		while (i != 5)
		{
			s = _getch();
			switch (s) 
			{
			case '\r':
				code[i] = '\0';
				return;
			case '\b':
				i--;
				if (i < 0)
					i++;
				else cout << "\b \b";
				break;
			default:
				if (i != 4)
				{
					code[i] = s;
					cout << code[i];
					i++;
				}
			}
		}
	}
	void check()//�������� ������� ����(4 ������� �� 0 �� 9)
	{
		bool flag = false;
		int i = 0;
		for (i = 0; i < 4; i++)
				if ((code[i] >= '0') && (code[i] <= '9'))//�������� �� ������������ �������� �����-����
					flag = true;
				else
				{
					throw 1.5;
				}
	}
	void addunit()//���������� ������ � �������
	{
		int i = 0;
	v:	bool flag = false;
		cout << "������� ��� ������ ��� ������� 1 ��� ������" << endl;
		read();
		cout << endl;
		if ((code[0] == '1') && (code[1] == '\0'))//�������� �� ���� 1
			return;
		try
		{
			check();
		}
		catch(double)
		{
			cout << "�������� ������ ����" << endl;
			goto v;
		}
		for (i = 0; i < ALL; i++)//����� ������ �� ������
		{
			if (strcmp(code, codes[i]) == 0)
			{
				kol[i]++;
				printunit(i);
				cout << endl << "����� �������� � �������" << endl;
				flag = true;
			}
		}
		if (flag == false)
		{
			cout << "���� " << code << " ��� � ���� ������" << endl;
			goto v;
		}
	}
	void printshoppinglist()//����� �� ������� �������(��� �������� ������)
	{
		bool flag = false;
		int i = 0;
		for (i = 0; i < ALL; i++)
			if (kol[i] > 0)
			{
				if (flag == false)
					cout << "������ � �������:" << endl;
				flag = true;
				printunit(i);
				cout  <<"���:"<<setw(8)<<codes[i]<< "����������: " << kol[i] << endl;
			}
		if (flag == false)
			throw 1;//������ � main
	}
	void deleteunit()//�������� ������ �� �������
	{
		int i = 0, poz = 0, n = 0;
		printshoppinglist();
		bool flag = false;
	y:	cout << "������� ��� ������, ������� ��������� ������� ��� ������� 1 ��� ������" << endl;
		read();
		cout << endl;
		if ((code[0] == '1') && (code[1] == '\0'))
			return;
		try
		{
			check();
		}
		catch(double)
		{
			cout << "�������� ������ ����" << endl;
			goto y;
		}
		for (i = 0; i < ALL; i++)
		{
			if ((strcmp(code, codes[i]) == 0) && (kol[i]!=0))//����� ������ � �������
			{
				poz = i;
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			cout << "����� � ����� " << code << " �� ������ � �������" << endl;
			goto y;
		}
		cout << "������� ���������� ������, ������� ���������� �������(�� ����� "<< kol[poz] << ")" << endl;
		cin >> n;
		while ((kol[poz] > 0) && (n > 0))
		{
			kol[poz]--;
			n--;
		}
		cout << "����� ������" << endl;
	}
	void printreceipt()//�������� � ����� ���� � �������
	{
		int i = 0, j = 0;
		double fp = 0, fd = 0, pr = 0;//fp-����� ��������� �������,fd- ������ ������ �������, pr-��������� ������� � ����
		bool flag = false;
		for (i = 0; i < ALL; i++)
			if (kol[i] != 0)
				flag = true;
		if (flag == false)
			throw 1;//������ � main
		system("cls");
		for (j = 0; j < 22; j++)//����������
			cout << "-";
		cout<<"���";
		for (j = 0; j < 23; j++)
			cout<<"-";
		cout << endl;
		for (i=0; i<ALL; i++)
			if (kol[i]!=0)
			{
				pr = kol[i] * prices[i] * (1 - discount[i]);
				fp += pr;
				fd+=prices[i] * kol[i] - pr;
				cout << setw(20) << names[i] << "X" << setw(7) << kol[i] <<"����(���/��)="<<prices[i]<< endl << "������=" << setw(2) << discount[i] * 100 << setw(11) << "%"<< "����� ������c��(���)=" << pr << endl;
			}
		for (j = 0; j < 48; j++)//����������
			cout<<"-";
		cout << endl;
		cout << "����� �������(���)=" << fp << endl;
		cout << "����� ������(���)=" << fd << endl;
		timesec();
		for (j = 0; j < 48; j++)//����������
			cout << "-";
		cout<<"\n";
	}
};

int menu()//����� ���� � �������
{
	int m;
	cout << "�������� ���������� ��������" << endl;
	cout << "1.������������� ����� �����\n" << "2.������� ����� �� �������\n" << "3.������������ ��� �� �������\n"<<"0.�����"<<endl;
	cin >> m;
	return m;
}

void main()
{
u:	SetConsoleCP(1251);//������� ���� ��� ����� � �������
	SetConsoleOutputCP(1251);
	cashbox k;
	int m, n=0;
l:	m = menu();
	switch (m)
	{
	case 1://���������� ������ � �������
		if(n%5==0)// ������ 5 ������� ������ ������� �� ������ ��������� � �������
		k.printlist();
			k.addunit();
		cout << endl;
		n++;
		break;
	case 2://�������� ������ �� �������
		try
		{
			k.deleteunit();
		}
		catch (int)
		{
			cout << "������� � ������� �� �������"<<endl;
			goto l;
		}
		break;
	case 3://������ ����
		try
		{
			k.printreceipt();
		}
		catch (int)
		{
			cout << "������� � ������� �� �������" << endl;
			goto l;
		}
		cout << "��� �������� ������ ���� ������� 1, ��� ������ �� ��������� ������� ����� �������" << endl;
		cin >> m;
		if (m == 1)
		{
			system("cls");
			goto u;
		}
		else
			return;
		break;
	case 0:
		return;
	}
	goto l;	
}
