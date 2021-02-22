
#include <iostream>
#include <cmath>
using namespace std;
class Time 
{
private:
	int m_hours;
	int m_minutes;
	int m_seconds;
public:
	Time(int a, int b, int c)//конструктор
	{
		m_hours = a;
		m_minutes = b;
		m_seconds = c;
	}
	void Setime(int hours, int minutes, int seconds)//функция установки времени
	{
		m_hours = hours;
		m_minutes = minutes;
		m_seconds = seconds;
	}

	void Print()//функция вывода установленного времени в консоль
	{
		cout << "Часы" <<'\t'<< "Минуты" << '\t'<<"Секунды" << endl;
		cout << m_hours <<'\t'<< m_minutes << '\t'<<m_seconds <<endl;
	}

	int difference(int a, int b, int c)//функция вычисления разницы установленного и заданного времени
	{
		int priv, zadan, diff;
		priv = (m_hours * 3600) + (m_minutes * 60) + m_seconds;
		zadan= (a * 3600) + (b* 60) + c;
		diff = abs(priv - zadan);
		return diff;
	}
	void offset(int a, int b, int c, int m)//функция сдвига времени на заданное смещение
	{
		int priv, zadan, diff;
		priv = (m_hours * 3600) + (m_minutes * 60) + m_seconds;
		zadan = (a * 3600) + (b * 60) + c;
		if (m == 1)
		{
			diff = priv + zadan;
			while (diff > 86400)
				diff = diff - 86400;
		
		}
		if (m == 2)
		{
			diff = priv - zadan;
			while (diff < 0)
				diff = 86400 + diff;
		}
		m_hours = diff / 3600;
		diff = diff - m_hours * 3600;
		m_minutes = diff / 60;
		diff = diff - m_minutes * 60;
		m_seconds = diff;
	}




};
int menu()//Вывод меню на консоль
{
	int a;
	cout << "Выберите дальнейшее действие"<<endl;
	cout << "1.Установить время" << endl << "2.Узнать время" << endl << "3.Вычислить разницу между заданным временем и установленным" << endl << "4.Сдвинуть время"<<endl <<"0.Выйти"<< endl;

	cin >> a;
	return a;
}


void main()
{
	setlocale(LC_ALL, "Russian");
	Time k(0,0,0);
d:
	int a, b, c;
	int m,diff;
	m = menu();
	switch (m)
	{
	case 1://установка времени
	l:
		cout << "Установите время (формат: часы, минуты, секунды)" << endl;
		cin >> a >> b >> c;
		if ((a >= 24) || (a < 0) || (b >= 60) || (c >= 60) || (b < 0) || (c < 0))
		{
			cout << "Неверный формат, попробуйте снова" << endl;
			goto l;
		}
		else
		{
			k.Setime(a, b, c);
			cout << "Время успешно установлено" << endl;
		}
		break;

	case 2://вывод времени на консоль
		k.Print();
		break;
	case 3:// вычисления разницы установленного и заданного времени
	k:
		cout << "Задайте время для вычисления разницы (формат: часы, минуты, секунды)" << endl;
		cin >> a >> b >> c;
		if ((a >= 24) || (a < 0) || (b >= 60) || (c >= 60) || (b < 0) || (c < 0))
		{
			cout << "Неверный формат, попробуйте снова" << endl;
			goto k;
		}
		diff = k.difference(a, b, c);
		a = diff / 3600;
		diff = diff - a * 3600;
		b = diff / 60;
		diff = diff - b * 60;
		c = diff;
		cout << "Разница составляет:" << endl;
		cout << "Часы" << '\t' << "Минуты" << '\t' << "Секунды" << endl;
		cout << a << '\t' << b << '\t' << c << endl;
		break;

	case 4://смещение времени
	p:
		cout << "Введите смещение (формат: часы, минуты, секунды)" << endl;
		cin >> a >> b >> c;
		if ( (a < 0) || (b >= 60) || (c >= 60) || (b < 0) || (c < 0))
		{
			cout << "Неверный формат, попробуйте снова" << endl;
			goto p;
		}
		cout << "В какую сторону смещать:" << endl << "1.В большую\n2.В меньшую" << endl;
		cin >> m;
		k.offset(a, b, c,m);
		cout << "Операция выполнена успешно" << endl;
		break;
	case 0://выход из программы
		return;
		break;


	
	}
	goto d;




	
	
	
	


}