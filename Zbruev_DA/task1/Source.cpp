
#include <clocale>
#include <iostream>
#include <cmath>
#define N 5//число пунктов в меню 
void showmenu()
{
	char* menu[N] = { "Установить время (по умолчанию стоит время 0:0:0)", "Узнать время", "Вычислить разницу между заданным временем и установленным (в часах, минутах и секундах)", "Сдвинуть время на заданное смещение", "Выход"};//массив с названиями операций
	short int menu_number[N] = { 1, 2, 3, 4, 0};//массив с номерами каждого пункта меню
	int i;
	std::cout << "Операции: "<<'\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i]<<". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "Введите номер операции, которую необходимо выполнить: ";
}
class Time
{
	int seconds;
	int minutes;
	int hours;
public:
	Time(int h, int m, int s)//конструктор
	{
		seconds = s;
		minutes = m;
		hours = h;
	}
	int getseconds() { return seconds; }
	int getminutes() {return minutes;}
	int gethours() {return hours; }//функции для работы с данными класса(узнать время)
	void settime(int h, int m, int s)//установка времени
	{
		seconds = s;
		minutes = m;
		hours = h;
	}
	
	int raznica(int h, int m, int s)//вычисление разницы
	{
		int sum1=0;
		int sum2 = 0;
		sum1 = h * 3600 + m * 60 + s;//число секунд для времени, хранящегося в классе 
		sum2 = hours * 3600 + minutes * 60 + seconds;//число секунд для времени, введенного с клавиатуры
		return (sum1-sum2);//возвращает разницу в секундах 
	}
	int move(int h, int m, int s, bool flag)//сдвиг времени
	{
		while (((flag==1)&&((hours+h) >= 24)) || ((flag == 0) && (((hours - h) < 0))))
		{
			return 1;//по возвращенному числу алгоритм в main понимает, введены ли верно данные (часы, минуты, секунды) 
		}
		while (((flag == 1) && ((minutes + m) >= 60)) || ((flag == 0) && ((minutes - m) < 0)))
		{
			return 2;
		}

		while (((flag == 1) && ((seconds + s) >= 60)) || ((flag == 0) && ((seconds - s) < 0)))
		{
			return 3;
		}

		if (flag == 1)
		{
			seconds = seconds + s;
			minutes = minutes + m;
			hours = hours + h;
			return 0;//если все хорошо, возвращает 0
		}
		else
		{
			seconds = seconds - s;
			minutes = minutes - m;
			hours = hours - h;
			return 0;//если все хорошо, возвращает 0
		}
	}
};
void main()
{
	int  num, s=0, m=0, h=0, sum=0;
	bool flag = 1;//флаг для меню
	bool f;//флаг для 4 режима
	setlocale(LC_ALL, "Russian");
	Time t(s, m, h);//вызываем конструктор
	while (flag == 1)
	{
		showmenu();
		std::cin >> num;
		switch (num)
		{
		case 1: //устанавливаем воемя 
			std::cout << "Введите время - сначала час, затем минуту и секунду, каждый раз нажимая enter: ";
			std::cin >> h >> m >> s;
			while ((h >= 24) || (h < 0))//всевозможные проверки
			{
				std::cout << "Неверно введен час, попытайтесь заново: ";
				std::cin >> h;
			}
			while ((m >= 60) || (m < 0))
			{
				std::cout << "Неверно введена минута, попытайтесь заново: ";
				std::cin >> m;
			}
			while ((s >= 60) || (s < 0))
			{
				std::cout << "Неверно введена секунда, попытайтесь заново: ";
				std::cin >> s;
			}
			t.settime(h, m, s);
			break;
		case 2://узнать время 
			std::cout << "Текущее время: " << t.gethours() << ":" << t.getminutes() << ":" << t.getseconds() << '\n';
			break;
		case 3://вычисление разницы
			std::cout << "Введите время - сначала час, затем минуту и секунду, каждый раз нажимая enter: ";
			std::cin >> h >> m >> s;
			while ((h >= 24) || (h < 0))
			{
				std::cout << "Неверно введен час, попытайтесь заново: ";
				std::cin >> h;
			}
			while ((m >= 60) || (m < 0))
			{
				std::cout << "Неверно введена минута, попытайтесь заново: ";
				std::cin >> m;
			}
			while ((s >= 60) || (s < 0))
			{
				std::cout << "Неверно введена секунда, попытайтесь заново: ";
				std::cin >> s;
			}
			sum=t.raznica(h, m, s);
			h = sum / 3600;
			sum = sum % 3600;
			if (h > 23)
				h = h % 24;
			m = sum / 60;
			sum = sum % 60;
			s = sum;
			std::cout << "Разница: " << h <<':'<<m<< ':'<< s<<'\n';
			break;
		case 4://сдвиг времени
			std::cout << "Если хотите сместить время в большую сторону, введите 1, если в меньшую введите 0: ";
			std::cin >> f;
			std::cout << "Введите смещение времени - сначала час, затем минуту и секунду, каждый раз нажимая enter: ";
			std::cin >> h >> m >> s;
			while ((h >= 24) || (h < 0))
			{
				std::cout << "Неверно введен час, попытайтесь заново: ";
				std::cin >> h;
			}
			while ((m >= 60) || (m < 0))
			{
				std::cout << "Неверно введена минута, попытайтесь заново: ";
				std::cin >> m;
			}
			while ((s >= 60) || (s < 0))
			{
				std::cout << "Неверно введена секунда, попытайтесь заново: ";
				std::cin >> s;
			}
			t.move(s, m, h, f);

			while (t.move(h, m, s, f) != 0)
			{
				if(t.move(h, m, s, f)==1)
				{
					std::cout << "введен слишком большой сдвиг по часам, попытайтесь заново: ";
					std::cin >> h;
				}
				if (t.move(h, m, s, f) == 2)
				{
					std::cout << "введен слишком большой сдвиг по минутам, попытайтесь заново: ";
					std::cin >> m;
				}
				if (t.move(h, m, s, f) == 3)
				{
					std::cout << "введен слишком большой сдвиг по секундам, попытайтесь заново: ";
					std::cin >> s;
				}
			}
			break;
		case 0:
			flag = 0;
		}
	}	
	system("pause");
}