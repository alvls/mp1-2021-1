#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <windows.h>
#include <conio.h>

using namespace std;

struct DepositInfromation
{
	int dayStart, monthStart, yearStart;
	int dayEnd, monthEnd, yearEnd;
	int sumStart;
	double procent;
	string time;
	bool status;
	int profitDeposit;
	int dayWithdraw, monthWithdraw, yearWithdraw;
	void ClearInformation()
	{
		dayStart = 0;
		monthStart = 0;
		yearStart = 0;
		dayEnd = 0;
		monthEnd = 0;
		yearEnd = 0;
		sumStart = 0;
		procent = 0;
		time = "";
		status = 0;
		profitDeposit = 0;
		dayWithdraw = 0;
		monthWithdraw = 0;
		yearWithdraw = 0;
	}
	void AddInformation(int _dayStart, int _monthStart, int _yearStart, int _dayEnd, int _monthEnd, int _yearEnd, int _sumStart, double _procent, string _time, bool _status, int _profitDeposit, int _dayWithdraw, int _monthWithdraw, int _yearWithdraw)
	{
		dayStart = _dayStart;
		monthStart = _monthStart;
		yearStart = _yearStart;
		dayEnd = _dayEnd;
		monthEnd = _monthEnd;
		yearEnd = _yearEnd;
		sumStart = _sumStart;
		procent = _procent;
		time = _time;
		status = _status;
		profitDeposit = _profitDeposit;
		dayWithdraw = _dayWithdraw;
		monthWithdraw = _monthWithdraw;
		yearWithdraw = _yearWithdraw;
	}
	void UpdatePayment(int sum, int day, int month, int year)
	{
		profitDeposit += sum;
		dayWithdraw = day;
		monthWithdraw = month;
		yearWithdraw = year;
	}
	friend ostream& operator<<(ostream& show, DepositInfromation& info)
	{
		show << "\nДата открытия: " << setw(2) << setfill('0') << info.dayStart << "." << setw(2) << setfill('0') << info.monthStart << "." << info.yearStart << endl;
		show << "Ваш вклад: " << info.sumStart << " руб." << " под " << info.procent << "% годовых " << "на " << info.time << endl;
		show << "Начисленные проценты по депозиту: " << info.profitDeposit << " руб." << endl;
		show << "Дата закрытия: " << setw(2) << setfill('0') << info.dayEnd << "." << setw(2) << setfill('0') << info.monthEnd << "." << info.yearEnd;
		return show;
	}
};

struct InformationClient
{
	string accountNumber;
	string fullName;
	string password;
	int sum;
	DepositInfromation infoDeposit;
	void AddClient(string account, string passwordClient, string fullNameClient, int sumClient)
	{
		accountNumber = account;
		password = passwordClient;
		fullName = fullNameClient;
		sum = sumClient;
	}
};

class ProcessingCenter
{
private:
	vector <InformationClient> client;
public:
	friend class Deposit;
	void ReadClientBaseFile()
	{
		int i, j, count = 0, profitDeposit;
		int dayWithdraw, monthWithdraw, yearWithdraw;
		bool status;
		double procent;
		string str, strAccount, strPassword, strSurname, strName, strPatronymic, strFullName, strSum, strDate, strDayStart, strMonthStart, strYearStart, strDayEnd, strMonthEnd, strYearEnd, strStartSum, strTime, strDayWithdraw, strMonthWithdraw, strYearWithdraw;
		ifstream file;
		file.open("DataBase.txt");
		while (getline(file, str))
		{
			istringstream newStr(str);
			strAccount = ""; strTime = ""; strPassword = ""; strSurname = ""; strName = ""; strPatronymic = ""; strFullName = ""; strDate = ""; strDayStart = ""; strMonthStart = "";strYearStart = "";
			strDayEnd = ""; strMonthEnd = ""; strYearEnd = ""; strStartSum = ""; procent = 0; strTime = "", strDayWithdraw = "", strMonthWithdraw = "", strYearWithdraw = "";
			newStr >> strAccount;
			newStr >> strPassword;
			newStr >> strSurname;
			newStr >> strName;
			newStr >> strPatronymic;
			strFullName += strSurname + ' ' + strName + ' ' + strPatronymic;
			newStr >> strSum;
			InformationClient newClient;
			newClient.AddClient(strAccount, strPassword, strFullName, stoi(strSum));
			newStr >> strDate;
			for (i = 0; i < strDate.size(); i++)
			{
				if (strDate[i] == '.')
				{
					count++;
				}
				if (strDate[i] != '.' && count == 0)
				{
					strDayStart += strDate[i];
				}
				else if (strDate[i] != '.' && count == 1)
				{
					strMonthStart += strDate[i];
				}
				else if (strDate[i] != '.' && count == 2)
				{
					strYearStart += strDate[i];
				}
			}
			count = 0;
			newStr >> strDate;
			for (i = 0; i < strDate.size(); i++)
			{
				if (strDate[i] == '.')
				{
					count++;
				}
				if (strDate[i] != '.' && count == 0)
				{
					strDayEnd += strDate[i];
				}
				else if (strDate[i] != '.' && count == 1)
				{
					strMonthEnd += strDate[i];
				}
				else if (strDate[i] != '.' && count == 2)
				{
					strYearEnd += strDate[i];
				}
			}
			count = 0;
			newStr >> strStartSum;
			newStr >> procent;
			newStr >> strDate;
			strTime += strDate;
			newStr >> strDate;
			strTime += ' ' + strDate;
			newStr >> status;
			newStr >> profitDeposit;
			newStr >> strDate;
			for (i = 0; i < strDate.size(); i++)
			{
				if (strDate[i] == '.')
				{
					count++;
				}
				if (strDate[i] != '.' && count == 0)
				{
					strDayWithdraw += strDate[i];
				}
				else if (strDate[i] != '.' && count == 1)
				{
					strMonthWithdraw += strDate[i];
				}
				else if (strDate[i] != '.' && count == 2)
				{
					strYearWithdraw += strDate[i];
				}
			}
			count = 0;
			newClient.infoDeposit.AddInformation(stoi(strDayStart), stoi(strMonthStart), stoi(strYearStart), stoi(strDayEnd), stoi(strMonthEnd), stoi(strYearEnd), stoi(strStartSum), procent, strTime, status, profitDeposit, stoi(strDayWithdraw), stoi(strMonthWithdraw), stoi(strYearWithdraw));
			client.push_back(newClient);
		}
		file.close();
	}
	void SaveClientBaseFile()
	{
		ofstream file;
		file.open("DataBase.txt");
		for (size_t i = 0; i < client.size(); i++)
		{
			if (client[i].infoDeposit.status == true)
			{
				file << client[i].accountNumber << " " << client[i].password << " " << client[i].fullName << " " << client[i].sum << " " <<
					setw(2) << setfill('0') << client[i].infoDeposit.dayStart << "." << setw(2) << setfill('0') << client[i].infoDeposit.monthStart << "." << client[i].infoDeposit.yearStart <<
					" " << setw(2) << setfill('0') << client[i].infoDeposit.dayEnd << "." << setw(2) << setfill('0') << client[i].infoDeposit.monthEnd << "." << client[i].infoDeposit.yearEnd <<
					" " << client[i].infoDeposit.sumStart << " " << client[i].infoDeposit.procent << " " << client[i].infoDeposit.time << " " << client[i].infoDeposit.status << " " << client[i].infoDeposit.profitDeposit <<
					" " << setw(2) << setfill('0') << client[i].infoDeposit.dayWithdraw << "." << setw(2) << setfill('0') << client[i].infoDeposit.monthWithdraw << "." << setw(4) << setfill('0') << client[i].infoDeposit.yearWithdraw << endl;;
			}
			else
			{
				file << client[i].accountNumber << " " << client[i].password << " " << client[i].fullName << " " << client[i].sum << " " <<
					setw(2) << setfill('0') << client[i].infoDeposit.dayStart << "." << setw(2) << setfill('0') << client[i].infoDeposit.monthStart << "." << setw(4) << setfill('0') << client[i].infoDeposit.yearStart <<
					" " << setw(2) << setfill('0') << client[i].infoDeposit.dayEnd << "." << setw(2) << setfill('0') << client[i].infoDeposit.monthEnd << "." << setw(4) << setfill('0') << client[i].infoDeposit.yearEnd <<
					" " << client[i].infoDeposit.sumStart << " " << client[i].infoDeposit.procent << " " << "0" << " " << "0" << " " << client[i].infoDeposit.status << " " << client[i].infoDeposit.profitDeposit <<
					" " << setw(2) << setfill('0') << client[i].infoDeposit.dayWithdraw << "." << setw(2) << setfill('0') << client[i].infoDeposit.monthWithdraw << "." << setw(4) << setfill('0') << client[i].infoDeposit.yearWithdraw << endl;
			}
		}
		file.close();
	}
};

class Deposit : public ProcessingCenter
{
private:
	InformationClient clientAuthorization;
	int dayToday, monthToday, yearToday;
	int sumDeposit[3] = { 100000, 500000, 1000000 };
	double procentDeposit[14] = { 2.5, 3, 3.2, 3.5, 4, 4.2, 4.5, 4.7, 4.9, 5.2, 5.5, 6.2, 6.6, 6.9 };
	string timeDeposit[5] = { "3 months", "6 months", "1 year", "2 years", "3 years" };
	void UpdateClient(InformationClient clientT)
	{
		for (size_t i = 0; i < client.size(); i++)
		{
			if (clientT.accountNumber == client[i].accountNumber)
			{
				client[i].infoDeposit = clientT.infoDeposit;
			}
		}
	}
	void PaymentDeposit()
	{
		int countMonth = 0, paymentSum = 0;
		if (clientAuthorization.infoDeposit.status != 0)
		{
			if (clientAuthorization.infoDeposit.dayWithdraw != 0 && clientAuthorization.infoDeposit.monthWithdraw != 0 && clientAuthorization.infoDeposit.yearWithdraw != 0)
			{
				countMonth = CountMonth(clientAuthorization.infoDeposit.dayWithdraw, clientAuthorization.infoDeposit.monthWithdraw, clientAuthorization.infoDeposit.yearWithdraw);
			}
			else
			{
				countMonth = CountMonth(clientAuthorization.infoDeposit.dayStart, clientAuthorization.infoDeposit.monthStart, clientAuthorization.infoDeposit.yearStart);
			}
			paymentSum = clientAuthorization.infoDeposit.sumStart * countMonth * clientAuthorization.infoDeposit.procent / 12 / 100;
			clientAuthorization.infoDeposit.UpdatePayment(paymentSum, 0, 0, 0);
			UpdateClient(clientAuthorization);
		}
	}
	int CountMonth(int day, int month, int year)
	{
		int countMonth = 0;
		if (year == yearToday)
		{
			if (day > dayToday)
			{
				countMonth = monthToday - month - 1;
			}
			else
			{
				countMonth = monthToday - month;
			}
		}
		if ((yearToday - year) == 1)
		{
			if (day > dayToday)
			{
				countMonth = 12 - month + monthToday - 1;
			}
			else
			{
				countMonth = 12 - month + monthToday;
			}
		}
		if ((yearToday - year) == 2)
		{
			if (day > dayToday)
			{
				countMonth = 12 - month + 12 + monthToday - 1;
			}
			else
			{
				countMonth = 12 - month + 12 + monthToday;
			}
		}
		if ((yearToday - year) == 3)
		{
			if (day > dayToday)
			{
				countMonth = 12 - month + 24 + monthToday - 1;
			}
			else
			{
				countMonth = 12 - month + 24 + monthToday;
			}
		}
		return countMonth;
	}
public:
	Deposit() {}
	~Deposit() {}
	void SetTodayDate(int d, int m, int y)
	{
		dayToday = d;
		monthToday = m;
		yearToday = y;
	}
	bool CheckClient(string _accountNumber, string _password)
	{
		for (int i = 0; i < client.size(); i++)
		{
			if (client[i].accountNumber == _accountNumber && client[i].password == _password)
			{
				clientAuthorization = client[i];
				PaymentDeposit();
				return true;
			}
		}
		return false;
	}
	string HelloUser()
	{
		return clientAuthorization.fullName;
	}
	int SumUser()
	{
		return clientAuthorization.sum;
	}
	bool CheckOpenDeposit()
	{
		if (clientAuthorization.infoDeposit.status == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void ShowInformationDeposit()
	{
		if (clientAuthorization.infoDeposit.status == true)
		{
			cout << clientAuthorization.infoDeposit << endl;
		}
		else
		{
			cout << "\nУ вас нет открытого депозита.." << endl;
		}
	}
	void ShowAvailableDeposits()
	{
		if (clientAuthorization.infoDeposit.status == true)
		{
			cout << "На вашем счете уже открыт депозит!" << endl;
		}
		else
		{
			cout << "Вам доступны следующие депозиты: " << endl;
			if (clientAuthorization.sum > sumDeposit[0] || clientAuthorization.sum <= sumDeposit[0])
			{
				cout << "\nНа сумму до " << sumDeposit[0] << " руб." << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << "На срок " << timeDeposit[i] << " под " << procentDeposit[i] << " % годовых" << endl;
				}
			}
			if (clientAuthorization.sum >= sumDeposit[0] || clientAuthorization.sum >= sumDeposit[1])
			{
				cout << "\nНа сумму от " << sumDeposit[0] << " до " << sumDeposit[1] << " руб." << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << "На срок " << timeDeposit[i] << " под " << procentDeposit[i + 3] << " % годовых" << endl;
				}
			}
			if (clientAuthorization.sum >= sumDeposit[1] || clientAuthorization.sum >= sumDeposit[2])
			{
				cout << "\nНа сумму от " << sumDeposit[1] << " до " << sumDeposit[2] << " руб." << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << "На срок " << timeDeposit[i] << " под " << procentDeposit[i + 6] << " % годовых" << endl;
				}
			}
			if (clientAuthorization.sum >= sumDeposit[2])
			{
				cout << "\nНа сумму от " << sumDeposit[2] << " руб." << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << "На срок " << timeDeposit[i] << " под " << procentDeposit[i + 9] << " % годовых" << endl;
				}
			}
		}
	}
	void OpenDeposit(int sumStart, string time)
	{
		double procentToSave;
		int dayEnd, monthEnd, yearEnd;
		if (clientAuthorization.infoDeposit.status == true)
		{
			cout << "На вашем счете уже открыт депозит!" << endl;
		}
		else
		{
			if (sumStart > clientAuthorization.sum)
			{
				cout << "У вас нет такой суммы на счете, открыть депозит невозможно!" << endl;
			}
			else
			{
				clientAuthorization.sum = clientAuthorization.sum - sumStart;
				if (sumStart > sumDeposit[0] || sumStart <= sumDeposit[0])
				{
					for (int i = 0; i < 5; i++)
					{
						if (time == timeDeposit[i])
						{
							procentToSave = procentDeposit[i];
						}
					}
				}
				if (sumStart >= sumDeposit[0] || sumStart >= sumDeposit[1])
				{
					for (int i = 0; i < 5; i++)
					{
						if (time == timeDeposit[i])
						{
							procentToSave = procentDeposit[i + 3];
						}
					}
				}
				if (sumStart >= sumDeposit[1] || sumStart >= sumDeposit[2])
				{
					for (int i = 0; i < 5; i++)
					{
						if (time == timeDeposit[i])
						{
							procentToSave = procentDeposit[i + 6];
						}
					}
				}
				if (sumStart >= sumDeposit[2])
				{
					for (int i = 0; i < 5; i++)
					{
						if (time == timeDeposit[i])
						{
							clientAuthorization.infoDeposit.procent = procentDeposit[i + 9];
						}
					}
				}
				dayEnd = dayToday;
				monthEnd = monthToday;
				yearEnd = yearToday;
				if (time == timeDeposit[0])
				{
					monthEnd += 3;
					if (monthEnd > 12)
					{
						monthEnd %= 12;
						yearEnd++;
					}
				}
				if (time == timeDeposit[1])
				{
					monthEnd += 6;
					if (monthEnd > 12)
					{
						monthEnd %= 12;
						yearEnd++;
					}
				}
				if (time == timeDeposit[2])
				{
					yearEnd++;
				}
				if (time == timeDeposit[3])
				{
					yearEnd += 2;
				}
				if (time == timeDeposit[4])
				{
					yearEnd += 3;
				}
				clientAuthorization.infoDeposit.AddInformation(dayToday, monthToday, yearToday, dayEnd, monthEnd, yearEnd, sumStart, procentToSave, time, true, 0, 0, 0, 0);
				UpdateClient(clientAuthorization);
				cout << "\nДепозит успешно создан! Спасибо, что доверяете нам!" << endl;
			}
		}
	}
	void CloseDeposit()
	{
		if (clientAuthorization.infoDeposit.status == true)
		{
			if ((clientAuthorization.infoDeposit.dayEnd == dayToday && clientAuthorization.infoDeposit.monthEnd == monthToday && clientAuthorization.infoDeposit.yearEnd == yearToday) ||
				(clientAuthorization.infoDeposit.dayEnd <= dayToday && clientAuthorization.infoDeposit.monthEnd <= monthToday && clientAuthorization.infoDeposit.yearEnd == yearToday))
			{
				clientAuthorization.sum += clientAuthorization.infoDeposit.sumStart;
				if (clientAuthorization.infoDeposit.profitDeposit != 0)
				{
					clientAuthorization.sum += clientAuthorization.infoDeposit.profitDeposit;
					cout << "\nДепозит закрыт!\nНе снятые проценты в размере " << clientAuthorization.infoDeposit.profitDeposit << " рублей переведены на ваш счет.." << endl;
					clientAuthorization.infoDeposit.ClearInformation();
				}
				else
				{
					clientAuthorization.infoDeposit.ClearInformation();
					cout << "\nДепозит закрыт!" << endl;
				}
				UpdateClient(clientAuthorization);
			}
			else
			{
				cout << "\nЗакрыть депозит невозможно, срок депозита не вышел!" << endl;
			}
		}
		else
		{
			cout << "\nУ вас нет открытых депозитов.." << endl;
		}
	}
	void WithdrawProcent()
	{
		clientAuthorization.sum += clientAuthorization.infoDeposit.profitDeposit;
		clientAuthorization.infoDeposit.dayWithdraw = dayToday;
		clientAuthorization.infoDeposit.monthWithdraw = monthToday;
		clientAuthorization.infoDeposit.yearWithdraw = yearToday;
		cout << "Проценты в количестве " << clientAuthorization.infoDeposit.profitDeposit << " руб. перечислены на ваш счет!" << endl;
		clientAuthorization.infoDeposit.profitDeposit = 0;
		UpdateClient(clientAuthorization);
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	bool end = true, endLogin = true;
	string accountNumber, password, timeDeposit;
	int indexMenu, indexDeposit, sumStart, symbol;
	Deposit networkBank;
	networkBank.ReadClientBaseFile();
	SYSTEMTIME(todayDate);
	GetLocalTime(&todayDate);
	networkBank.SetTodayDate(todayDate.wDay, todayDate.wMonth, todayDate.wYear);
	while (endLogin)
	{
		cout << "Номер счета: ";
		cin >> accountNumber;
		cout << "Пароль: ";
		while (true)
		{
			symbol = _getch();
			if (symbol == 13)
			{
				break;
			}
			else if (symbol == 8)
			{
				if (!password.empty())
				{
					cout << (char)8 << " " << (char)8;
					password.erase(password.length() - 1);
				}
			}
			else
			{
				cout << "*";
				password += (char)symbol;
			}
		}
		if (networkBank.CheckClient(accountNumber, password) == true)
		{
			endLogin = false;
		}
		else
		{
			cout << "Данный пользователь не существует, пожалуйста, попробуйте еще раз!" << endl << endl;
		}
	}
	cout << "\nДобро пожаловать " << networkBank.HelloUser() << "!" << endl;
	while (end)
	{
		cout << "\nПрограмма умеет: \n" << "1. Узнать сумму на счете;"
			<< "\n2. Показать информацию о доступных клиенту депозитах, исходя из суммы на его зарплатном счету;\n"
			<< "3. Проверить наличие открытого депозита;\n"
			<< "4. Открыть депозит (переведя указанную сумму с зарплатного счета на депозит);\n" << "5. Показать состояние депозита;\n"
			<< "6. Снять проценты;\n" << "7. Закрыть депозит;\n"
			<< "0. Выйти из программы.\n" << endl;
		cout << "Выберите пункт меню: ";
		cin >> indexMenu;
		switch (indexMenu)
		{
		case 1:
		{
			cout << "\nВаша сумма на счету: " << networkBank.SumUser() << " руб." << endl;
			break;
		}
		case 2:
		{
			networkBank.ShowAvailableDeposits();
			break;
		}
		case 3:
		{
			if (networkBank.CheckOpenDeposit() != true)
			{
				cout << "\nУ вас нет открытых депозитов.." << endl;
			}
			else
			{
				cout << "\nУ вас есть открытый депозит.." << endl;
			}
			break;
		}
		case 4:
		{
			if (networkBank.CheckOpenDeposit() != true)
			{
				cout << "\nВведите сумму депозита: ";
				cin >> sumStart;
				cout << "\nВыберите срок депозита:\n" << "1. 3 months;\n" << "2. 6 months;\n" << "3. 1 year;\n" << "4. 2 years;\n" << "5. 3 years;\n" << "Введите пункт меню: ";
				cin >> indexDeposit;
				switch (indexDeposit)
				{
				case 1:
				{
					timeDeposit = "3 months";
					break;
				}
				case 2:
				{
					timeDeposit = "6 months";
					break;
				}
				case 3:
				{
					timeDeposit = "1 year";
					break;
				}
				case 4:
				{
					timeDeposit = "2 years";
					break;
				}
				case 5:
				{
					timeDeposit = "3 years";
					break;
				}
				default:
				{
					cout << "Такого пункта меню не существует, пожалуйста, попробуйте еще раз!" << endl;
					break;
				}
				}
				networkBank.OpenDeposit(sumStart, timeDeposit);
			}
			else
			{
				cout << "\nУ вас уже есть открытый депозит.." << endl;
			}
			break;
		}
		case 5:
		{
			networkBank.ShowInformationDeposit();
			break;
		}
		case 6:
		{
			networkBank.WithdrawProcent();
			break;
		}
		case 7:
		{
			networkBank.CloseDeposit();
			break;
		}
		case 0:
		{
			cout << "\nДо свидания! Спасибо что воспользовались нашей программой!\n" << endl;
			end = false;
			break;
		}
		default:
		{
			cout << "\nДанный пункт меню не найден, попробуйте еще раз!" << endl << endl;
			break;
		}
		}
	}
	networkBank.SaveClientBaseFile();
	system("pause");
	return 0;
}