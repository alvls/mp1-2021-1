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

struct date//структура даты выхода фильма в прокат
{
	int year;
	int mon;
	int day;
	void setdate(char* dat)//преобразование строки в структуру date
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
	bool operator !=( const date& a)//оператор != для структуры
	{
		return(year != a.year && mon != a.mon && day != a.day);
	}
};

class Film//класс фильм-единица класса фильмиотека
{
private:
	string name;
	string producer;
	string scen;
	string compos;
	int boxoffice;
	date ready;
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
	void printconsole()//вывод фильма на консоль для некоторых пунктов работы программы, для удобства выбора определенного фильма по его номеру
	{
		cout << setiosflags(ios::left)<< setw(25) << name << setw(25) << producer << setw(25) << scen << setw(25) << compos <<setw(18)<< boxoffice<< ready.day << "." << ready.mon << "." << ready.year << endl;
	}
	friend class filmoteka;
};

int toint(char* a)//преобразование строки в int
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

void delspace(char* a)//преобразование строки, считанной из файла
{
	int i = 0;
	for (i = 0; i < strlen(a); i++)
	{
		if ((a[i]==' ')&&(a[i+1]==' '))
			a[i]='\0';
	}
}

class filmoteka//класс фильмотека из вектора и флага(для метода addfilm)
{
private:
	vector <Film> vecfilm;
	bool flag = 0;
public:
	void addfilm(const Film & a)//добавить фильм в фильмотеку
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
	int getsize()//возврат значения
	{
		int size;
		size = vecfilm.size();
		return size;
	}
	void deletefilm(int a)//удаление фильма по его номеру в фильмотеке
	{
		if (a > vecfilm.size())
			throw 1;
		vecfilm.erase(vecfilm.begin() + a-1);		
	}
	void ptint()//вывод на консоль фильмотеки для некоторых пунктов работы программы
	{
		cout << setiosflags(ios::left) << setw(27) << "  Название" << setw(25) << "Режиссер " << setw(25) << "Сценарист " << setw(25) << "Композитор" << setw(18) << "Сборы(млн. руб)" << "Дата выхода в прокат" << endl;
	for (int i = 0; i < vecfilm.size(); i++)
		{
			cout << i+1 << ".";
			vecfilm[i].printconsole();
		}
	}
	void change(int ind, const Film & a)//изменение фильма в фильмотеке по его номеру
	{
		vecfilm[ind - 1] = a;
	}
	Film search(string _name, date a)//поиск фильма по автору и году
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
	filmoteka prod(string _producer)//поиск фильмов заданного режиссера
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
	filmoteka year(int year)//поиск фильмов, вышедших в определенном году
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
	filmoteka box(int n)//возврат заданного количества фильмов с наибольшими сборами
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
	void ptrintinfile()//сохранение фильмиотеки в файл
	{
		ofstream fout("filmoteka.txt"); 
		for (int i = 0; i < vecfilm.size(); i++)
		{
			fout << i + 1 << ".";
			fout << setiosflags(ios::left) << setw(25) << vecfilm[i].name <<"|"<< setw(25) << vecfilm[i].producer <<"|"<< setw(25) << vecfilm[i].scen<<"|" << setw(25) << vecfilm[i].compos <<"|"<<setw(10) << vecfilm[i].boxoffice <<"|"<< vecfilm[i].ready.day << "." << vecfilm[i].ready.mon << "." << vecfilm[i].ready.year <<"|"<< endl; // запись строки в файл
		}
		fout.close(); // закрываем файл
	}
	void readfromfile(filmoteka &a)//чтение фильмотеки из файла
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

int menu()//вывод меню в консоль
{
	int a;
	cout << "Выберите дальнейшее действие" << endl;
	cout << "1.Добавить фильм" << endl << "2.Изменить данные выбранного фильма" << endl << "3.Найти фильм по названию и году" << endl << "4.Выдать все фильмы заданного режиссера" << endl <<
		"5.Выдать все фильмы, вышедшие в прокат в этом году" << endl << "6.Выдать заданное число фильмов с наибольшими сборами" << endl <<"7.Выдать заданное число фильмов с наибольшими сборами в выбранном году"<<endl<<
		"8.Узнать текщее число фильмов"<<endl<<"9.Удалить фильм"<<endl<<"10.Сохранить фильмотеку в файл"<<endl<<"11.Считать фильмотеку из файла"<<endl<<"0.Выход" << endl;
	cin >> a;
	return a;
}

void main()
{
	SetConsoleCP(1251);//русский язык при вводе в консоль
	SetConsoleOutputCP(1251);
	Film tmp;//служебная переменная tmp
	filmoteka funct;//служебная переменная funct
	filmoteka a;//основная фильмиотека
	string name;//строка для чтения названия с консоли
	string producer;//строка для чтения режиссера с консоли
	string scen;//строка для чтения сценариста с консоли
	string compos;//строка для чтения композитора с консоли
	int box;//значения для чтения сборов с консоли
	date flm;//структура для даты 
	char dat[11];//строка для чтения даты с консоли
	int m, k, p, n;//служебные переменные
l:
	m = menu();
	switch (m)
	{
	case 1://добавление фильма
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите название фильма"<<endl;
		getline(cin, name);
		cout << "Введите режиссера" << endl;
		getline(cin, producer);
		cout << "Введите сценариста" << endl;
		getline(cin, scen);
		cout << "Введите композитора" << endl;
		getline(cin, compos);
		cout << "Введите сборы фильма в миллионах рублей" << endl;
		cin >> box;
		cout << "Введите дату выхода" << endl;
		cin >> dat;
		flm.setdate(dat);
		tmp.setfilm(name, producer, scen, compos, box, flm);
		a.addfilm(tmp);
		break;
	case 2://изменение данных
		a.ptint();
	v:
		cout << "Укажите номер фильма, данные которого необходимо изменить(нажмите 0 для отмены):" << endl;
		cin >> k;
		if ((k < 0) || (k > a.getsize()))
		{
			cout << "Выход за пределы фильмотеки" << endl;
			goto v;
		}
		if (k == 0)
			break;
		cout << "Введите новые данные фильма:" << endl;
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите название фильма" << endl;
		getline(cin, name);
		cout << "Введите режиссера" << endl;
		getline(cin, producer);
		cout << "Введите сценариста" << endl;
		getline(cin, scen);
		cout << "Введите композитора" << endl;
		getline(cin, compos);
		cout << "Введите сборы фильма в миллионах рублей" << endl;
		cin >> box;
		cout << "Введите дату выхода" << endl;
		cin >> dat;
		flm.setdate(dat);
		tmp.setfilm(name, producer, scen, compos, box, flm);
		a.change(k,tmp);
		break;
	case 3://поиск по названию и году
	q:
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите название фильма" << endl;
		getline(cin, name);
		cout << "Введите год выпуска фильма" << endl;
		cin >> dat;
		flm.setdate(dat);
		try 
		{
			tmp = a.search(name, flm);
		}
		catch (int)
		{
			cout << "Фильм не найден" << endl;
			goto q;
		}
		cout << "Найден фильм:" << endl;
		cout << setiosflags(ios::left) << setw(25) << "Название" << setw(25) << "Режиссер " << setw(25) << "Сценарист " << setw(25) << "Композитор" << setw(18) << "Сборы(млн. руб)" << "Дата выхода в прокат" << endl;
		tmp.printconsole();
		break;
	case 4://фильмы по режиссеру
		cin.clear();
		while (cin.get() != '\n');
	w:		cout << "Введите имя режиссера" << endl;
		getline(cin, producer);
		try 
		{
			funct = a.prod(producer);
		}
		catch(int)
		{
			cout << "Фильмов не найдено, попробуйте снова" << endl;
			goto w;
		}
		cout << "Надены фильмы:" << endl;
		funct.ptint();
		break;
	case 5://фильмы по году
    e:
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите год" << endl;
		cin >> k;
		try
		{
			funct = a.year(k);
		}
		catch (int)
		{
			cout << "Фильмов не найдено, попробуйте снова" << endl;
			goto e;
		}
		cout << "Надены фильмы:" << endl;
		funct.ptint();
		break;
	case 6://фильмы с наибольшими сборами
	y:	
		cin.clear();
		while (cin.get() != '\n');
		k = a.getsize();
		cout << "Укажите количество фильмов(не более " << k << ")"<<endl;
		cin >> p;
		try 
		{
			funct = a.box(p);
		}
		catch (int)
		{
			cout << "Выход за пределы фильмотеки" << endl;
			goto y;
		}
		cout << "Надены фильмы:" << endl;
		funct.ptint();
		break;
	case 7://фильмы с наибольшими сборами в выбранном году
	u:
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите год" << endl;
		cin >> k;
		try
		{
			funct = a.year(k);
		}
		catch (int)
		{
			cout << "Фильмов не найдено, попробуйте снова" << endl;
			goto u;
		}
		n = funct.getsize();
	z:	cout << "Укажите количество фильмов(не более " << n << ")" << endl;
		cin >> p;
		try
		{
			funct = funct.box(p);
		}
		catch (int)
		{
			cout << "Выход за пределы фильмотеки" << endl;
			goto z;
		}
		funct.ptint();
		break;
	case 8://число фильмов в фильмиотеке
		n = a.getsize();
		cout << "Количество фильмов в фильмотеке:  " << n << endl;
		break;
	case 9://Удаление фильма
	x:
		cin.clear();
		while (cin.get() != '\n');
		a.ptint();
		cout << "Введите номер фильма, который хотите удалить" << endl;
		cin >> n;
		try 
		{
			a.deletefilm(n);
		}
		catch(int)
		{
		cout<<"Выход за пределы фильмотеки" << endl;
		goto x;
		}
		cout << "Фильм удален" << endl;
		break;
	case 10://сохранение фильмотеки в файл
		a.ptrintinfile();
		cout << "Вывод фильмотеки в файл произведен" << endl;
		break;
	case 11://считывание фильмиотеки с файла
		a.readfromfile(a);
		cout << "Файл считан" << endl;
			break;
	case 0://выход из программы
		return;
		break;
	}
	goto l;
}