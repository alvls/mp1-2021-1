/*
- Разработать классы Кредит и Процессинговый центр.
- Класс Кредит должен имитировать работу интернет-банка в части управления кредитом для зарплатных клиентов банка
(тех, чья зарплата перечисляется работодателем на счета работников, открытые в данном банке).
Кредит может выдаваться клиенту на выбранный им срок.
Возможные варианты: 1 год, 2 года, 3 года, 5 лет, 15 лет.
Считать, что процентные ставки по кредитам зависят только от срока и суммы кредита.
Диапазоны сумм: до 100 тыс. рублей, от 100 до 500 тыс. рублей, от 500 тыс. до 1 млн рублей, от 1 до 3 млн рублей.
Процентные ставки указываются за 1 год (например, 12% годовых по кредиту на 3 года на сумму от 500 тыс. до 1 млн рублей
или 15% годовых по кредиту на 1 год на сумму от 100 до 500 тыс. рублей).
Выплаты по кредиту начисляются клиенту раз в месяц.
Клиент может выплатить сумму большую или равную начисленной.
Клиент может досрочно погасить кредит. Считать, что кредит одобряется банком клиенту,
если текущая сумма на его зарплатном счету достаточна для шести ежемесячных выплат по кредиту.
После одобрения банком сумма кредита перечисляется на зарплатный счет клиента.
- База клиентов хранится в классе Процессинговый центр.
Считать, что информация о клиенте состоит из номера зарплатного счета (для упрощения – номер счета от «0001» до «9999»),
ФИО владельца, суммы на зарплатном счету, (для упрощения – без копеек),
информации о кредите, пароля (произвольная строка, выбранная пользователем, с длиной больше 3 символов).
Считать, что авторизация клиента в интернет-банке происходит по номеру зарплатного счета и паролю.
- Класс Кредит должен предоставлять следующие операции:
1) + авторизовать клиента,
2) + показать информацию о доступных клиенту кредитах
3) + проверить наличие взятого в банке кредита,
4) + проверить возможность получения выбранного кредита,
5) + получить выбранный кредит,
6) + показать текущее состояние кредита,
7) погасить начисления по кредиту,
8) досрочно погасить кредит.
- Все операции должны сопровождаться необходимыми проверками на указанные выше ограничения.
- Класс Процессинговый центр должен использоваться для поддержки работы класса Кредит и может быть разработан в минимально-необходимом варианте.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <clocale> 
#include <windows.h>
#include <fstream> //для работы с файлами
#include <sstream> //для рабрты с файлами
#include <cctype> 
#include <cstring>
#include <locale>
#include <string>
using namespace std;
int DAY;
int MONTH;
int YEAR;

void setDate(int _day, int _month, int _year) {
	DAY = _day;
	MONTH = _month;
	YEAR = _year;
}

struct informationAboutCredit
{
	int day;//дата открытия
	int month;
	int year;
	int loan;//сумма кредита
	int amountWithInterest; //сумма с процентами
	int amount; //сумма остатка выплат
	int monthlyPayment; //ежемесячная выплата
	double percent;//процент
	int debt;//задолженность
	bool status;//статус(открыт/закрыт)
	int endday;//дата закрытия 
	int endmonth;
	int endyear;
};

struct Client
{
	string login;//номер счета
	string pass;//пароль
	string lastName;//фамилия
	string firstName;//имя
	string middleName;//отчество
	int pay;//сумма на зарплатном счете
	informationAboutCredit infCredit;//информация о кредите
};

class ProcessingCenter
{
	vector <Client> Baza;
	Client user;
public:
	ProcessingCenter(string file)
	{
		ifstream in(file);
		string line;
		string _login;//номер счета
		string _pass;//пароль
		string _lastName;//фамилия
		string _firstName;//имя
		string _middleName;//отчество
		int _pay;//сумма на зарплатном счете
		int _day;//дата открытия
		int _month;
		int _year;
		int _loan;//сумма кредита
		int _amountWithInterest; //сумма с процентами
		int _amount; //сумма остатка выплат
		int _monthlyPayment; //ежемесячная выплата
		double _percent;//процент
		int _debt;//срок
		bool _status;//статус(открыт/закрыт)
		int _endday;//дата закрытия 
		int _endmonth;
		int _endyear;

		while (getline(in, line))
		{
			istringstream ist(line);
			ist >> _login;//номер счета
			ist >> _pass;//пароль
			ist >> _lastName;//фамилия
			ist >> _firstName;//имя
			ist >> _middleName;//отчество
			ist >> _pay;//сумма на зарплатном счете
			ist >> _day;//дата открытия
			ist >> _month;
			ist >> _year;
			ist >> _loan;//сумма кредита
			ist >> _amountWithInterest; //сумма с процентами
			ist >> _amount; //сумма остатка выплат
			ist >> _monthlyPayment; //ежемесячная выплата
			ist >> _percent;//процент
			ist >> _debt;//срок
			ist >> _status;//статус(открыт/закрыт)
			ist >> _endday;//дата закрытия 
			ist >> _endmonth;
			ist >> _endyear;

			user.login = _login;
			user.pass = _pass;
			user.lastName = _lastName;
			user.firstName = _firstName;
			user.middleName = _middleName;
			user.pay = _pay;
			user.infCredit.day = _day;
			user.infCredit.month = _month;
			user.infCredit.year = _year;
			user.infCredit.loan = _loan;
			user.infCredit.amountWithInterest = _amountWithInterest;
			user.infCredit.amount = _amount;
			user.infCredit.monthlyPayment = _monthlyPayment;
			user.infCredit.percent = _percent;
			user.infCredit.debt = _debt;
			user.infCredit.status = _status;
			user.infCredit.endday = _endday;
			user.infCredit.endmonth = _endmonth;
			user.infCredit.endyear = _endyear;
			Baza.push_back(user);
		}
	}

	ProcessingCenter() {};

	void NewClient(string _login, string _lastName, string _firstName, string _middleName, int _pay, string _pass)
	{
		user.login = _login;
		user.pass = _pass;
		user.lastName = _lastName;
		user.firstName = _firstName;
		user.middleName = _middleName;
		user.pay = _pay;
		user.infCredit.day = 0;
		user.infCredit.month = 0;
		user.infCredit.year = 0;
		user.infCredit.loan = 0;
		user.infCredit.amountWithInterest = 0;
		user.infCredit.amount = 0;
		user.infCredit.monthlyPayment = 0;
		user.infCredit.percent = 0;
		user.infCredit.debt = 0;
		user.infCredit.status = 0;
		user.infCredit.endday = 0;
		user.infCredit.endmonth = 0;
		user.infCredit.endyear = 0;
		Baza.push_back(user);
		saveFile();
	};

	~ProcessingCenter() {};

	void saveFile()
	{
		ofstream file;
		file.open("База.txt");
		if (!file.is_open())
		{
			cout << "Файл не открылся. " << endl;
		}
		for (size_t i = 0; i < Baza.size(); i++)
		{
			file << Baza[i].login << " " << Baza[i].pass << " " << Baza[i].lastName << " " << Baza[i].firstName << " "
				<< Baza[i].middleName << " " << Baza[i].pay << " " << Baza[i].infCredit.day << " " << Baza[i].infCredit.month << " "
				<< Baza[i].infCredit.year << " " << Baza[i].infCredit.loan << " " << Baza[i].infCredit.amountWithInterest << " "
				<< Baza[i].infCredit.amount << " " << Baza[i].infCredit.monthlyPayment << " " << Baza[i].infCredit.percent << " "
				<< Baza[i].infCredit.debt << " " << Baza[i].infCredit.status << " " << Baza[i].infCredit.endday << " "
				<< Baza[i].infCredit.endmonth << " " << Baza[i].infCredit.endyear << " " << endl;
		}
		file.close();
	}
	string GetPasword(int i)
	{
		return Baza[i].pass;
	}

	void clientUpdate(Client client)
	{
		for (int i = 0; i < Baza.size(); i++)
		{
			if ((Baza[i].login == client.login) && (Baza[i].pass == client.pass))
			{
				Baza[i] = client;
				saveFile();
			}
		}
	}

	int getNumberClient(string _login)
	{
		for (int i = 0; i < Baza.size(); i++)
		{
			if (_login == Baza[i].login)
			{
				return i;
			}
		}
	}

	Client getClient(int i)
	{
		return Baza[i];
	}

	bool SearchPerson(string _num)
	{
		for (int i = 0; i < Baza.size(); i++)
		{
			if (_num == Baza[i].login)
			{
				cout << "Здравствуйте, " << Baza[i].firstName << " " << Baza[i].middleName << endl;
				return true;
			}
		}
		return false;
	}

};

class Credit : public ProcessingCenter
{
private:
	Client Person;
public:
	Credit() {};
	~Credit() {};

	double Percent[8] = { 0.05, 0.07, 0.1, 0.11, 0.13, 0.15, 0.17, 0.2 };

	void Authorization(Client client)
	{
		Person = client;
	}

	bool getAvailabilityCredit()
	{
		return Person.infCredit.status;
	}

	void ShowPerson()
	{
		cout << "ФИО: " << Person.lastName << " " << Person.firstName << " " << Person.middleName << endl;
		cout << "Номер клиента: " << Person.login << endl;
		cout << "Баланс: " << Person.pay << endl;
	}

	void AvailableCredits()
	{
		cout << "Варианты кредитов, предоставляемые банком: " << endl;
		cout << "1. 1 год (от 100 тыс до 1 млн - 15%; от 1 млн - 13%)" << endl;
		cout << "2. 2 года(от 100 тыс до 1 млн - 13 %; от 1 млн - 10 %)" << endl;
		cout << "3. 3 года(от 100 тыс до 1 млн - 12 %; от 1 млн - 11 %)" << endl;
		cout << "4. 5 лет(от 100 тыс до 1 млн - 10 %; от 1 млн - 9 %)" << endl;
		cout << "5. 15 лет(от 100 тыс до 1 млн - 8 %; от 1 млн - 7 %)" << endl;
	}
	int calculatingPresent(int _sum, int _years)
	{
		if (_years == 1)
		{
			if (_sum >= 100000 && _sum <= 1000000)
				return 15;
			if (_sum > 1000000 && _sum <= 3000000)
				return 13;
		}
		if (_years == 2)
		{
			if (_sum >= 100000 && _sum <= 1000000)
				return 13;
			if (_sum > 1000000 && _sum <= 3000000)
				return 10;
		}
		if (_years == 3)
		{
			if (_sum >= 100000 && _sum <= 1000000)
				return 12;
			if (_sum > 1000000 && _sum <= 3000000)
				return 11;
		}
		if (_years == 5)
		{
			if (_sum >= 100000 && _sum <= 1000000)
				return 10;
			if (_sum > 1000000 && _sum <= 3000000)
				return 9;
		}
		if (_years == 15)
		{
			if (_sum >= 100000 && _sum <= 1000000)
				return 8;
			if (_sum > 1000000 && _sum <= 3000000)
				return 7;
		}
	}

	bool bankApproval(int _sum, int _years) //одобрение банка
	{
		int month = _years * 12;
		double present = calculatingPresent(_sum, _years);
		double interestRate = present / 1200; //процентная ставка на каждый месяц
		double monthlyPayment = (_sum * interestRate) / (1 - (1 / pow(1 + interestRate, month))); //ежемесячная выплата
		cout << "Ежемесячная выплата: " << monthlyPayment << endl;
		int sum = monthlyPayment * 6;
		if (sum > Person.pay)
			return false;
		if (sum <= Person.pay)
			return true;
	}

	void creditRegistration(int _sum, int _years)
	{
		int month = _years * 12;
		double present = calculatingPresent(_sum, _years);
		double interestRate = present / 1200; //процентная ставка на каждый месяц
		double monthlyPayment = (_sum * interestRate) / (1 - (1 / pow(1 + interestRate, month))); //ежемесячная выплата
		int sum = monthlyPayment * month;
		Person.pay += _sum;
		Person.infCredit.loan = _sum;
		Person.infCredit.amountWithInterest = sum;
		Person.infCredit.amount = sum;
		Person.infCredit.day = DAY;
		Person.infCredit.month = MONTH;
		Person.infCredit.year = YEAR;
		Person.infCredit.endday = DAY;
		Person.infCredit.endmonth = MONTH;
		Person.infCredit.endyear = YEAR + _years;
		Person.infCredit.percent = present;
		Person.infCredit.status = true;
		Person.infCredit.monthlyPayment = monthlyPayment;
	}

	Client getClient()
	{
		return Person;
	}

	bool getStatusCredit()
	{
		return Person.infCredit.status;
	}

	void showTheCreditStatus()
	{
		cout << "Дата открытия кредита: " << Person.infCredit.day << "." << Person.infCredit.month << "." << Person.infCredit.year << endl;
		cout << "Сумма кредита: " << Person.infCredit.loan << " руб." << endl;
		cout << "Сумма с начисленными процентами: " << Person.infCredit.amountWithInterest << " руб." << endl;
		cout << "Оставшаяся сумма до полного погашения кредита: " << Person.infCredit.amount << " руб." << endl;
		cout << "Задолжность на данный момент: -" << Person.infCredit.debt << " руб." << endl;
		cout << "Сумма ежемесячных выплат: " << endl;
		cout << "Дата закрытия кредита: " << Person.infCredit.endday << "." << Person.infCredit.endmonth << "." << Person.infCredit.endyear << endl;
	}

	int сreditAccrual()
	{
		if (DAY >= Person.infCredit.day)
			Person.infCredit.debt += Person.infCredit.monthlyPayment;
		return Person.infCredit.debt;
	}

	void repaymentOfCreditAccrual(int sumAccrual)
	{
		Person.pay -= sumAccrual;
		Person.infCredit.amount -= sumAccrual;
		Person.infCredit.debt = 0;
	}

	int getAmount()
	{
		return Person.infCredit.amount;
	}

	void earlyRepaymentOfCredit(int _sum)
	{
		Person.pay -= _sum;
		Person.infCredit.amount = 0;
		Person.infCredit.status = false;
		Person.infCredit.endday = DAY;
		Person.infCredit.endmonth = MONTH;
		Person.infCredit.endyear = YEAR;
	}

	int getDebt()
	{
		return Person.infCredit.debt;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	int balance, time, sum = 0;
	string num;
	string pas;
	string name;
	int choice;
	string lastName;//фамилия
	string firstName;//имя
	string middleName;//отчество
	ProcessingCenter objPerson("База.txt");
	Credit objCredit;
	SYSTEMTIME st;
	GetLocalTime(&st);
	setDate(st.wDay, st.wMonth, st.wYear);
	cout << "Программа Интернет-банка" << endl;
	cout << endl << "МЕНЮ:" << endl << "1 - Регистрация" << endl << "2 - Авторизация" << endl;
	cin >> choice;
	while (choice != 1 && choice != 2)
	{
		cout << "Такого пункта нет, введите ещё раз: " << endl;
		cin >> choice;
	}
	switch (choice)
	{
	case 1:
	{
		cout << "Введите номер счета от 0001 до 9999: " << endl;
		cin >> num;
		while (num.length() != 4)
		{
			cout << "Это число не четырехзначное." << endl;
			cout << "Введите номер счета от 0001 до 9999: " << endl;
			cin >> num;
		}
		cout << "Введите вашу фамилию: " << endl;
		cin >> lastName;

		cout << "Введите ваше имя: " << endl;
		cin >> firstName;

		cout << "Введите ваше отчество: " << endl;
		cin >> middleName;

		cout << "Придумайте пароль (больше трех символов): " << endl;
		cin >> pas;
		while (pas.length() < 4)
		{
			cout << "Этот пароль содержит больше трех символов. Придумайте другой пароль: " << endl;
			cin >> pas;
		}

		cout << "Введите сумму на зарплатном счету: " << endl;
		cin >> balance;
		while (balance < 0)
		{
			cout << "Это значение меньше нуля, введите сумму на зарплатном счету ещё раз: " << endl;
			cin >> balance;
		}
		objPerson.NewClient(num, lastName, firstName, middleName, balance, pas);
		objCredit.Authorization(objPerson.getClient(objPerson.getNumberClient(num)));
		break;
	}
	case 2:
	{
		string pas;
		string login;
		cout << "Введите логин: ";
		cin >> login;
		if (objPerson.SearchPerson(login) == true)
		{
			cout << "Введите пароль: ";
			cin >> pas;
			while (pas != objPerson.GetPasword(objPerson.getNumberClient(login)))
			{
				cout << "Неверный пароль" << endl;
				cin >> pas;
			}
		}
		objCredit.Authorization(objPerson.getClient(objPerson.getNumberClient(login)));
		objCredit.ShowPerson();
		break;
	}
	}
	choice = 1;
	cout << "Программа Интернет-банка\n";
	while (choice != 0)
	{
		cout << endl << "МЕНЮ:" << endl << "1 - Проверка наличия кредита" << endl << "2 - Информация о доступных кредитах" << endl
			<< "3 - Оформление кредита" << endl << "4 - Текущее состояние кредита" << endl << "5 - Погасить начисления по кредиту" << endl
			<< "6 - Досрочно погасить кредит" << endl << "7 - Выход" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			if (objCredit.getAvailabilityCredit() == 0)
			{
				cout << "Действующего кредита не найдено." << endl;
			}
			if (objCredit.getAvailabilityCredit() == 1)
			{
				cout << "Имеется действующий кредит." << endl;
			}
			break;
		}
		case 2:
		{
			objCredit.AvailableCredits();
			break;
		}
		case 3:
		{
			cout << "Введите период времени (на сколько лет), на который Вы планируете взять кредит, возможные варианты (ввести нужно лишь цифру):"
				<< endl << "- 1 год" << endl << "- 2 года " << endl << "- 3 года" << endl << "- 5 лет" << endl << "- 15 лет" << endl;
			cin >> time;
			while (time != 1 && time != 2 && time != 3 && time != 5 && time != 15)
			{
				cout << "На такой срок банк кредит не выдает. Выберите ещё раз: " << endl;
				cin >> time;
			}
			cout << "Введите сумму кредита: " << endl;
			cin >> sum;
			if (objCredit.bankApproval(sum, time) == true)
			{
				int choice;
				cout << "Банк готов Вам одобрить этот кредит." << endl;
				cout << "Готовы оформить данный кредит сейчас?" << endl;
				cout << "1. - да" << endl;
				cout << "2. - нет" << endl;
				cin >> choice;
				while (choice != 1 && choice != 2)
				{
					cout << "Такого пункта нет, введите ещё раз: " << endl;
					cin >> choice;
				}
				if (choice == 1)
				{
					objCredit.creditRegistration(sum, time);
					objPerson.clientUpdate(objCredit.getClient());
				}
				if (choice == 2)
					break;
			}
			else
				cout << "Банк не готов Вам одобрить этот кредит." << endl;
			break;
		}
		case 4:
		{
			if (objCredit.getStatusCredit() == true)
				objCredit.showTheCreditStatus();
			else
				cout << "На данный момент у Вас нет действующего кредита в нашем банке. " << endl;
			break;
		}
		case 5:
		{
			if (objCredit.getStatusCredit() == true)
			{
				int сreditDebt = objCredit.getDebt();
				cout << "На данный момент Ваша задолжность по кредиту: -" << сreditDebt << endl;
				int choice;
				int sumAccrual;
				cout << "Готовы погасить задолжность сейчас?" << endl;
				cout << "1. - да" << endl;
				cout << "2. - нет" << endl;
				cin >> choice;
				while (choice != 1 && choice != 2)
				{
					cout << "Такого пункта нет, введите ещё раз: " << endl;
					cin >> choice;
				}
				if (choice == 1)
				{
					cout << "Ведите сумму, которую Вы хотите заплатить: " << endl;
					cin >> sumAccrual;
					while (sumAccrual < сreditDebt)
					{
						cout << "Эта сумма меньше ежемесячных выплат, введите сумму ещё раз: " << endl;
						cin >> sumAccrual;
					}
					objCredit.repaymentOfCreditAccrual(sumAccrual);
					objPerson.clientUpdate(objCredit.getClient());
				}
				if (choice == 2)
					break;
			}
			else
				cout << "На данный момент у Вас нет действующего кредита в нашем банке. " << endl;
			break;
		}
		case 6:
		{
			if (objCredit.getStatusCredit() == true)
			{
				int amount = objCredit.getAmount();
				int choice;
				int sumAmount;
				cout << "На данный момент Ваша задолжность по кредиту: " << amount << endl;
				cout << "Готовы её погасить? " << endl;
				cout << "1. - да" << endl;
				cout << "2. - нет" << endl;
				cin >> choice;
				while (choice != 1 && choice != 2)
				{
					cout << "Такого пункта нет, введите ещё раз: " << endl;
					cin >> choice;
				}
				if (choice == 1)
				{
					cout << "Ведите сумму, которую Вы хотите заплатить: " << endl;
					cin >> sumAmount;
					while (sumAmount < amount)
					{
						cout << "Эта сумма меньше ежемесячных выплат, введите сумму ещё раз: " << endl;
						cin >> sumAmount;
					}
					objCredit.earlyRepaymentOfCredit(sumAmount);
					objPerson.clientUpdate(objCredit.getClient());
				}
				if (choice == 2)
					break;
			}
			else
				cout << "На данный момент у Вас нет действующего кредита в нашем банке. " << endl;
			break;
		}
		case 7:
		{
			choice = 0;
		}
		}
	}
};