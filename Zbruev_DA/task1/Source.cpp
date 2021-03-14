
#include <clocale>
#include <iostream>
#include <cmath>
#define N 5//����� ������� � ���� 
void showmenu()
{
	char* menu[N] = { "���������� ����� (�� ��������� ����� ����� 0:0:0)", "������ �����", "��������� ������� ����� �������� �������� � ������������� (� �����, ������� � ��������)", "�������� ����� �� �������� ��������", "�����"};//������ � ���������� ��������
	short int menu_number[N] = { 1, 2, 3, 4, 0};//������ � �������� ������� ������ ����
	int i;
	std::cout << "��������: "<<'\n';
	for (i = 0; i < N; i++)
	{
		std::cout << menu_number[i]<<". ";
		std::cout << menu[i] << '\n';
	}
	std::cout << "������� ����� ��������, ������� ���������� ���������: ";
}
class Time
{
	int seconds;
	int minutes;
	int hours;
public:
	Time(int h, int m, int s)//�����������
	{
		seconds = s;
		minutes = m;
		hours = h;
	}
	int getseconds() { return seconds; }
	int getminutes() {return minutes;}
	int gethours() {return hours; }//������� ��� ������ � ������� ������(������ �����)
	void settime(int h, int m, int s)//��������� �������
	{
		seconds = s;
		minutes = m;
		hours = h;
	}
	
	int raznica(int h, int m, int s)//���������� �������
	{
		int sum1=0;
		int sum2 = 0;
		sum1 = h * 3600 + m * 60 + s;//����� ������ ��� �������, ����������� � ������ 
		sum2 = hours * 3600 + minutes * 60 + seconds;//����� ������ ��� �������, ���������� � ����������
		return (sum1-sum2);//���������� ������� � ��������, ����� � main ����������� � ��������� ����� 
	}
	void move(int h, int m, int s, bool flag)//����� �������. flag-� ����� ������� �������� ����� (1 - � ������������� �������, 0 - � ������������� �������)
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

		if ((flag == 1) && ((seconds + s) > 60))//��������� �������������� ������������ ��� ������
		{
			minutes = minutes + seconds / 60;
			seconds = seconds % 60;
		}
		else 
			if ((flag == 1) && ((seconds + s) < 0))//��������� �������������� ������������ ��� ������
			{
				minutes = minutes - abs(seconds) / 60;
				seconds = 60-abs(seconds) % 60;
			}

		if ((flag == 0) && ((seconds - s) > 60))//��������� �������������� ������������ ��� ������
		{
			minutes = minutes + seconds / 60;
			seconds = seconds % 60;
		}
		else 
			if ((flag == 0) && ((seconds - s) < 0))//��������� �������������� ������������ ��� ������
			{
				minutes = minutes - abs(seconds) / 60;
				seconds = 60-abs(seconds) % 60;
			}

		if ((flag == 1) && ((minutes + m) > 60))//��������� �������������� ������������ ��� �����
		{
				hours = hours + minutes / 60;
				minutes = minutes % 60;
		}
		else 
			if ((flag == 1) && ((minutes + m) < 0))//��������� �������������� ������������ ��� �����
			{
				hours = hours - abs(minutes) / 60;
				minutes = 60-abs(minutes) % 60;
			}

		if ((flag == 0) && ((minutes - m) > 60))//��������� �������������� ������������ ��� �����
		{
			hours = hours + minutes / 60;
			minutes = minutes % 60;
		}
		else
			if ((flag == 0) && ((minutes - m) < 0))//��������� �������������� ������������ ��� �����
			{
				hours = hours - abs(minutes) / 60;
				minutes = 60-abs(minutes) % 60;
			}

		if ((flag == 1) && ((hours + h) > 24))//��������� �������������� ������������ ��� ����
		{
			if (hours % 24 == 0)
				hours = 0;
			else
				hours = hours % 24;
		} 
		else 
			if ((flag == 1) && ((hours + h) < 0))//��������� �������������� ������������ ��� ����
			{
				if (hours % 24 == 0)
					hours = 0;
				else
					hours = 24-abs(hours) % 24;
			}
		if ((flag == 0) && ((hours - h) > 24))//��������� �������������� ������������ ��� ����
		{
			if (hours % 24 == 0)
				hours = 0;
			else
				hours = hours % 24;
		}
		else 
			if ((flag == 0) && ((hours - h) < 0))//��������� �������������� ������������ ��� ����
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
	bool flag = 1;//���� ��� ����
	bool f;//���� ��� 4 ������
	setlocale(LC_ALL, "Russian");
	Time t(h, m, s);//�������� �����������
	while (flag == 1)
	{
		showmenu();
		std::cin >> num;
		switch (num)
		{
		case 1: //������������� ����� 
			std::cout << "������� ����� - ������� ���, ����� ������ � �������, ������ ��� ������� enter: ";
			std::cin >> h >> m >> s;
			while ((h >= 24) || (h < 0))//������������ ��������
			{
				std::cout << "������� ������ ���, ����������� ������: ";
				std::cin >> h;
			}
			while ((m >= 60) || (m < 0))
			{
				std::cout << "������� ������� ������, ����������� ������: ";
				std::cin >> m;
			}
			while ((s >= 60) || (s < 0))
			{
				std::cout << "������� ������� �������, ����������� ������: ";
				std::cin >> s;
			}
			t.settime(h, m, s);
			break;
		case 2://������ ����� 
			std::cout << "������� �����: " << t.gethours() << ":" << t.getminutes() << ":" << t.getseconds() << '\n';
			break;
		case 3://���������� �������
			std::cout << "������� ����� - ������� ���, ����� ������ � �������, ������ ��� ������� enter: ";
			std::cin >> h >> m >> s;
			sum=t.raznica(h, m, s);
			h = sum / 3600;
			sum = sum % 3600;
			if (h > 23)
				h = h % 24;
			m = sum / 60;
			sum = sum % 60;
			s = sum;
			std::cout << "�������: " << h <<':'<<m<< ':'<< s<<'\n';
			break;
		case 4://����� �������
			std::cout << "���� ������ �������� ����� � ������� �������, ������� 1, ���� � ������� ������� 0: ";
			std::cin >> f;
			std::cout << "������� �������� ������� - ������� ���, ����� ������ � �������, ������ ��� ������� enter: ";
			std::cin >> h >> m >> s;
			t.move(h, m, s, f);
			break;
		case 0:
			flag = 0;
		}
	}	
	system("pause");
}