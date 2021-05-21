#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

struct date//��������� ���� ������ ������ � ������
{
	int year;
	int mon;
	int day;
	void setdate(char* dat)//�������������� ������ � ��������� date
	{
		int i = 0, b = 0, k = 1;
		while (dat[i] != '\0')
		{
			if (dat[i] != '.')
				b = b * 10 + (dat[i] - 48);
			else
			{
				switch (k)
				{
				case 1:
					day = b;
					break;
				case 2:
					mon = b;
					break;
				}
				k++;
				b = 0;
			}
			i++;
		}
		year = b;
	}
	bool operator !=( const date& a)//�������� != ��� ���������
	{
		return(year != a.year && mon != a.mon && day != a.day);
	}
};

class Film//����� �����-������� ������ �����������
{
private:
	string name;
	string producer;
	string scen;
	string compos;
	int boxoffice;
	date ready;
	int k=1, p=5;
	int m = k + p;
public:
	void setfilm(string _name, string _producer, string _scen, string _compos, int _boxoffice, date a)
	{
		name = _name;
		producer = _producer;
		scen = _scen;
		compos = _compos;
		boxoffice = _boxoffice;
		ready = a;
	}
	void printconsole()//����� ������ �� ������� ��� ��������� ������� ������ ���������, ��� �������� ������ ������������� ������ �� ��� ������
	{
		cout << setiosflags(ios::left)<< setw(25) << name << setw(25) << producer << setw(25) << scen << setw(25) << compos <<setw(18)<< boxoffice<< ready.day << "." << ready.mon << "." << ready.year << endl;
	}
	friend class filmoteka;
};

int toint(char* a)//�������������� ������ � int
{
	int b = 0;
	int i = 0;
	while (a[i] > 47 && a[i] < 58)
	{
		b = b*10 + (a[i]-48);
		i++;
	}
	return b;
}

void delspace(char* a)//�������������� ������, ��������� �� �����
{
	int i = 0;
	for (i = 0; i < strlen(a); i++)
	{
		if ((a[i]==' ')&&(a[i+1]==' '))
			a[i]='\0';
	}
}

class filmoteka//����� ���������� �� ������� � �����(��� ������ addfilm)
{
private:
	vector <Film> vecfilm;
	bool flag = 0;
public:
	void addfilm(const Film & a)//�������� ����� � ����������
	{
		if (flag == 0)
		{
			vecfilm.push_back(a);
			flag = 1;
		}
		else
		{
			string ad = a.name;
			string pub;
			int size = vecfilm.size()-1;
			pub = vecfilm[size].name;
			while ((ad.compare(pub)<0)&&(size>=0))
			{
				size--;
				if (size!=-1)
				pub = vecfilm[size].name;
			}
			if (size==-1)
			vecfilm.insert(vecfilm.begin() + 0, a);
			else vecfilm.insert(vecfilm.begin() + size+1 , a);
		}
	}
	int getsize()//������� ��������
	{
		int size;
		size = vecfilm.size();
		return size;
	}
	void deletefilm(int a)//�������� ������ �� ��� ������ � ����������
	{
		if (a > vecfilm.size())
			throw 1;
		vecfilm.erase(vecfilm.begin() + a-1);		
	}
	void ptint()//����� �� ������� ���������� ��� ��������� ������� ������ ���������
	{
		cout << setiosflags(ios::left) << setw(27) << "  ��������" << setw(25) << "�������� " << setw(25) << "��������� " << setw(25) << "����������" << setw(18) << "�����(���. ���)" << "���� ������ � ������" << endl;
	for (int i = 0; i < vecfilm.size(); i++)
		{
			cout << i+1 << ".";
			vecfilm[i].printconsole();
		}
	}
	void change(int ind, const Film & a)//��������� ������ � ���������� �� ��� ������
	{
		vecfilm[ind - 1] = a;
	}
	Film search(string _name, date a)//����� ������ �� ������ � ����
	{
		int i = 0;
		string pub;
		date tmp = vecfilm[0].ready;
		pub = vecfilm[0].name;
		while (((_name.compare(pub)!=0) || (tmp != a)) && (i != vecfilm.size()))
		{
			i++;
			if (i != vecfilm.size())
			{
				pub = vecfilm[i].name;
				tmp = vecfilm[i].ready;
			}
		}
		if ((i == vecfilm.size()))
			throw 1;
		return(vecfilm[i]);
	}
	filmoteka prod(string _producer)//����� ������� ��������� ���������
	{
		filmoteka result;
		int i = 0;
		string prod;
		while (i < vecfilm.size())
		{
			prod = vecfilm[i].producer;
			if (_producer.compare(prod) == 0)
			{
				result.addfilm(vecfilm[i]);
			}
			i++;
		}
		if (result.vecfilm.size()==0)
			throw 1;
		return result;
	}
	filmoteka year(int year)//����� �������, �������� � ������������ ����
	{
		filmoteka result;
		int i = 0;
		while (i < vecfilm.size())
		{
			if (vecfilm[i].ready.year == year)
			{
				result.addfilm(vecfilm[i]);
			}
			i++;
		}
		if (result.vecfilm.size() == 0)
			throw 1;
		return result;
	}
	filmoteka box(int n)//������� ��������� ���������� ������� � ����������� �������
	{
		Film tmp;
		filmoteka result;
		result = *this;
		int size = result.vecfilm.size();
		if (n > size)
			throw 1;
		int i, j, k;
		for (i = 0; i < size; i++)
		{
			tmp = result.vecfilm[i]; 
			k = i;
			for (j = i + 1; j < size; j++)
				if (result.vecfilm[j].boxoffice > tmp.boxoffice)
				{
					k = j;
					tmp = result.vecfilm[j];
				}
			result.vecfilm[k] = result.vecfilm[i];
			result.vecfilm[i] = tmp;
		}
		result.vecfilm.resize(n);
		return result;
	}
	void ptrintinfile()//���������� ����������� � ����
	{
		ofstream fout("filmoteka.txt"); 
		for (int i = 0; i < vecfilm.size(); i++)
		{
			fout << i + 1 << ".";
			fout << setiosflags(ios::left) << setw(25) << vecfilm[i].name <<"|"<< setw(25) << vecfilm[i].producer <<"|"<< setw(25) << vecfilm[i].scen<<"|" << setw(25) << vecfilm[i].compos <<"|"<<setw(10) << vecfilm[i].boxoffice <<"|"<< vecfilm[i].ready.day << "." << vecfilm[i].ready.mon << "." << vecfilm[i].ready.year <<"|"<< endl; // ������ ������ � ����
		}
		fout.close(); // ��������� ����
	}
	void readfromfile(filmoteka &a)//������ ���������� �� �����
	{
		char tmp[30];
		date res;
		Film temp;
		a.vecfilm.clear();
		a.flag = 0;
		int i = 0;
		ifstream fin("filmoteka.txt");
		while (i < INT_MAX)
		{
			fin.get();
			fin.get();
			fin.getline(tmp, 30, '|');
			if (strlen(tmp) == 0)
				break;
			delspace(tmp);
			temp.name = string(tmp);
			fin.getline(tmp, 30, '|');
			delspace(tmp);
			temp.producer = string(tmp);
			fin.getline(tmp, 30, '|');
			delspace(tmp);
			temp.scen = string(tmp);
			fin.getline(tmp, 30, '|');
			delspace(tmp);
			temp.compos = string(tmp);
			fin.getline(tmp, 30, '|');
			temp.boxoffice = toint(tmp);
			fin.getline(tmp, 30, '|');
			res.setdate(tmp);
			temp.ready = res;
			//temp.printconsole();
			a.addfilm(temp);
			i++;
			fin.get();
		}
	fin.close();
	}
};

int menu()//����� ���� � �������
{
	int a;
	cout << "�������� ���������� ��������" << endl;
	cout << "1.�������� �����" << endl << "2.�������� ������ ���������� ������" << endl << "3.����� ����� �� �������� � ����" << endl << "4.������ ��� ������ ��������� ���������" << endl <<
		"5.������ ��� ������, �������� � ������ � ���� ����" << endl << "6.������ �������� ����� ������� � ����������� �������" << endl <<"7.������ �������� ����� ������� � ����������� ������� � ��������� ����"<<endl<<
		"8.������ ������ ����� �������"<<endl<<"9.������� �����"<<endl<<"10.��������� ���������� � ����"<<endl<<"11.������� ���������� �� �����"<<endl<<"0.�����" << endl;
	cin >> a;
	return a;
}

void main()
{
	SetConsoleCP(1251);//������� ���� ��� ����� � �������
	SetConsoleOutputCP(1251);
	Film tmp;//��������� ���������� tmp
	filmoteka funct;//��������� ���������� funct
	filmoteka a;//�������� �����������
	string name;//������ ��� ������ �������� � �������
	string producer;//������ ��� ������ ��������� � �������
	string scen;//������ ��� ������ ���������� � �������
	string compos;//������ ��� ������ ����������� � �������
	int box;//�������� ��� ������ ������ � �������
	date flm;//��������� ��� ���� 
	char dat[11];//������ ��� ������ ���� � �������
	int m, k, p, n;//��������� ����������
l:
	m = menu();
	switch (m)
	{
	case 1://���������� ������
		cin.clear();
		while (cin.get() != '\n');
		cout << "������� �������� ������"<<endl;
		getline(cin, name);
		cout << "������� ���������" << endl;
		getline(cin, producer);
		cout << "������� ����������" << endl;
		getline(cin, scen);
		cout << "������� �����������" << endl;
		getline(cin, compos);
		cout << "������� ����� ������ � ��������� ������" << endl;
		cin >> box;
		cout << "������� ���� ������" << endl;
		cin >> dat;
		flm.setdate(dat);
		tmp.setfilm(name, producer, scen, compos, box, flm);
		a.addfilm(tmp);
		break;
	case 2://��������� ������
		a.ptint();
	v:
		cout << "������� ����� ������, ������ �������� ���������� ��������(������� 0 ��� ������):" << endl;
		cin >> k;
		if ((k < 0) || (k > a.getsize()))
		{
			cout << "����� �� ������� ����������" << endl;
			goto v;
		}
		if (k == 0)
			break;
		cout << "������� ����� ������ ������:" << endl;
		cin.clear();
		while (cin.get() != '\n');
		cout << "������� �������� ������" << endl;
		getline(cin, name);
		cout << "������� ���������" << endl;
		getline(cin, producer);
		cout << "������� ����������" << endl;
		getline(cin, scen);
		cout << "������� �����������" << endl;
		getline(cin, compos);
		cout << "������� ����� ������ � ��������� ������" << endl;
		cin >> box;
		cout << "������� ���� ������" << endl;
		cin >> dat;
		flm.setdate(dat);
		tmp.setfilm(name, producer, scen, compos, box, flm);
		a.change(k,tmp);
		break;
	case 3://����� �� �������� � ����
	q:
		cin.clear();
		while (cin.get() != '\n');
		cout << "������� �������� ������" << endl;
		getline(cin, name);
		cout << "������� ��� ������� ������" << endl;
		cin >> dat;
		flm.setdate(dat);
		try 
		{
			tmp = a.search(name, flm);
		}
		catch (int)
		{
			cout << "����� �� ������" << endl;
			goto q;
		}
		cout << "������ �����:" << endl;
		cout << setiosflags(ios::left) << setw(25) << "��������" << setw(25) << "�������� " << setw(25) << "��������� " << setw(25) << "����������" << setw(18) << "�����(���. ���)" << "���� ������ � ������" << endl;
		tmp.printconsole();
		break;
	case 4://������ �� ���������
		cin.clear();
		while (cin.get() != '\n');
	w:		cout << "������� ��� ���������" << endl;
		getline(cin, producer);
		try 
		{
			funct = a.prod(producer);
		}
		catch(int)
		{
			cout << "������� �� �������, ���������� �����" << endl;
			goto w;
		}
		cout << "������ ������:" << endl;
		funct.ptint();
		break;
	case 5://������ �� ����
    e:
		cin.clear();
		while (cin.get() != '\n');
		cout << "������� ���" << endl;
		cin >> k;
		try
		{
			funct = a.year(k);
		}
		catch (int)
		{
			cout << "������� �� �������, ���������� �����" << endl;
			goto e;
		}
		cout << "������ ������:" << endl;
		funct.ptint();
		break;
	case 6://������ � ����������� �������
	y:	
		cin.clear();
		while (cin.get() != '\n');
		k = a.getsize();
		cout << "������� ���������� �������(�� ����� " << k << ")"<<endl;
		cin >> p;
		try 
		{
			funct = a.box(p);
		}
		catch (int)
		{
			cout << "����� �� ������� ����������" << endl;
			goto y;
		}
		cout << "������ ������:" << endl;
		funct.ptint();
		break;
	case 7://������ � ����������� ������� � ��������� ����
	u:
		cin.clear();
		while (cin.get() != '\n');
		cout << "������� ���" << endl;
		cin >> k;
		try
		{
			funct = a.year(k);
		}
		catch (int)
		{
			cout << "������� �� �������, ���������� �����" << endl;
			goto u;
		}
		n = funct.getsize();
	z:	cout << "������� ���������� �������(�� ����� " << n << ")" << endl;
		cin >> p;
		try
		{
			funct = funct.box(p);
		}
		catch (int)
		{
			cout << "����� �� ������� ����������" << endl;
			goto z;
		}
		funct.ptint();
		break;
	case 8://����� ������� � �����������
		n = a.getsize();
		cout << "���������� ������� � ����������:  " << n << endl;
		break;
	case 9://�������� ������
	x:
		cin.clear();
		while (cin.get() != '\n');
		a.ptint();
		cout << "������� ����� ������, ������� ������ �������" << endl;
		cin >> n;
		try 
		{
			a.deletefilm(n);
		}
		catch(int)
		{
		cout<<"����� �� ������� ����������" << endl;
		goto x;
		}
		cout << "����� ������" << endl;
		break;
	case 10://���������� ���������� � ����
		a.ptrintinfile();
		cout << "����� ���������� � ���� ����������" << endl;
		break;
	case 11://���������� ����������� � �����
		a.readfromfile(a);
		cout << "���� ������" << endl;
			break;
	case 0://����� �� ���������
		return;
		break;
	}
	goto l;
}