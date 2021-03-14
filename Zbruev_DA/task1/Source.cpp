
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
		return (sum1-sum2);//возвращает разницу в секундах, затем в main переводится в привычное время 
	}
	void move(int h, int m, int s, bool flag)//сдвиг времени. flag-в какую сторону сдвигаем время (1 - в положительную сторону, 0 - в отрицательную сторону)
	{
		if (flag == 1)
		{
			seconds = seconds + s;
			minutes = minutes + m;
			hours = hours + h;
		}
		if (flag == 0)
		{
			seconds = seconds - s;
			minutes = minutes - m;
			hours = hours - h;
		}

		if ((flag == 1) && ((seconds + s) > 60))//обработка положительного переполнения для секунд
		{
			minutes = minutes + seconds / 60;
			seconds = seconds % 60;
		}
		else 
			if ((flag == 1) && ((seconds + s) < 0))//обработка отрицательного переполнения для секунд
			{
				minutes = minutes - abs(seconds) / 60;
				seconds = 60-abs(seconds) % 60;
			}

		if ((flag == 0) && ((seconds - s) > 60))//обработка положительного переполнения для секунд
		{
			minutes = minutes + seconds / 60;
			seconds = seconds % 60;
		}
		else 
			if ((flag == 0) && ((seconds - s) < 0))//обработка отрицательного переполнения для секунд
			{
				minutes = minutes - abs(seconds) / 60;
				seconds = 60-abs(seconds) % 60;
			}

		if ((flag == 1) && ((minutes + m) > 60))//обработка положительного переполнения для минут
		{
				hours = hours + minutes / 60;
				minutes = minutes % 60;
		}
		else 
			if ((flag == 1) && ((minutes + m) < 0))//обработка отрицательного переполнения для минут
			{
				hours = hours - abs(minutes) / 60;
				minutes = 60-abs(minutes) % 60;
			}

		if ((flag == 0) && ((minutes - m) > 60))//обработка положительного переполнения для минут
		{
			hours = hours + minutes / 60;
			minutes = minutes % 60;
		}
		else
			if ((flag == 0) && ((minutes - m) < 0))//обработка отрицательного переполнения для минут
			{
				hours = hours - abs(minutes) / 60;
				minutes = 60-abs(minutes) % 60;
			}

		if ((flag == 1) && ((hours + h) > 24))//обработка положительного переполнения для часа
		{
			if (hours % 24 == 0)
				hours = 0;
			else
				hours = hours % 24;
		} 
		else 
			if ((flag == 1) && ((hours + h) < 0))//обработка отрицательного переполнения для часа
			{
				if (hours % 24 == 0)
					hours = 0;
				else
					hours = 24-abs(hours) % 24;
			}
		if ((flag == 0) && ((hours - h) > 24))//обработка положительного переполнения для часа
		{
			if (hours % 24 == 0)
				hours = 0;
			else
				hours = hours % 24;
		}
		else 
			if ((flag == 0) && ((hours - h) < 0))//обработка отрицательного переполнения для часа
			{
				if (hours % 24 == 0)
					hours = 0;
				else
					hours = 24 - abs(hours) % 24;
			}
	}
};
void main()
{
	int  num, s=0, m=0, h=0, sum=0;
	bool flag = 1;//флаг для меню
	bool f;//флаг для 4 режима
	setlocale(LC_ALL, "Russian");
	Time t(h, m, s);//вызываем конструктор
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
			t.move(h, m, s, f);
			break;
		case 0:
			flag = 0;
		}
	}	
	system("pause");
}