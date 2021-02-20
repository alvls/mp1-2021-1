
#include <clocale>
#include <iostream>
#include <cmath>
void clean(void);
void clean(void)//очищает поток ввода
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}
#define N 5
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
	Time(int s, int m, int h)//конструктор
	{
		seconds = s;
		minutes = m;
		hours = h;
	}
	int getseconds() { return seconds; }//операции?
	int getminutes() {
	return minutes;
	}//функции для работы с данными класса
	int gethours() { return hours; }
	void set_time() {//установка времени
		std::cout << "Введите время - сначала час, затем минуту и секунду, каждый раз нажимая enter: ";
		std::cin >> hours >> minutes >> seconds;
		while ((hours >= 24)||(hours<0))
		{
			std::cout << "Неверно введен час, попытайтесь заново: ";
			std::cin >> hours;
		}
		while ((minutes >= 60) || (minutes < 0))
		{
			std::cout << "Неверно введена минута, попытайтесь заново: ";
			std::cin >> minutes;
		}
		while ((seconds >= 60) || (seconds < 0))
		{
			std::cout << "Неверно введена секунда, попытайтесь заново: ";
			std::cin >> seconds;
		}
	}
	void raznica()//вычисление разницы
	{
		int s, m, h;
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
		std::cout <<"Разница: "<< abs(hours-h)<<":"<< abs(minutes - m) << ":"<<abs(seconds - s)<<'\n';
	}
	void move()//сдвиг времени
	{
		int s, m, h;
		bool flag;
		std::cout << "Если хотите сместить время в большую сторону, введите 1, если в меньшую введите 0: ";
		std::cin >> flag;
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

		while (((flag==1)&&((hours+h) >= 24)) || ((flag == 0) && (((hours - h) < 0))))
		{
			std::cout << "введен слишком большой сдвиг по часам, попытайтесь заново: ";
			std::cin >> h;
		}
		while (((flag == 1) && ((minutes + m) >= 60)) || ((flag == 0) && ((minutes - m) < 0)))
		{
			std::cout << "введен слишком большой сдвиг по минутам, попытайтесь заново: ";
			std::cin >> m;
		}

		while (((flag == 1) && ((seconds + s) >= 60)) || ((flag == 0) && ((seconds - s) < 0)))
		{
			std::cout << "введен слишком большой сдвиг по секундам, попытайтесь заново: ";
			std::cin >> s;
		}

		if (flag == 1)
		{
			seconds = seconds + s;
			minutes = minutes + m;
			hours = hours + h;
		}
		else
		{
			seconds = seconds - s;
			minutes = minutes - m;
			hours = hours - h;
		}
	}
};

void main()
{
	int  num, s=0, m=0, h=0;
	bool flag = 1;
	setlocale(LC_ALL, "Russian");
	Time t(s, m, h);//вызываем конструктор
	while (flag == 1)
	{
		showmenu();
		std::cin >> num;
		switch (num)
		{
		case 1:
			t.set_time();//инициализация
			break;
		case 2:
			std::cout << "Текущее время: " << t.gethours() << ":" << t.getminutes() << ":" << t.getseconds() << '\n';
			break;
		case 3:
			t.raznica();
			break;
		case 4:
			t.move();
			break;
		case 0:
			flag = 0;
		}
	}	
	system("pause");
}