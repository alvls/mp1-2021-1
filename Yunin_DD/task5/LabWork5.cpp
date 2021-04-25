//Разработать классы Банкомат и Процессинговый центр.
//Класс Банкомат должен имитировать работу банкомата по приему и выдаче наличных денежных средств(в рублях).
//Класс должен поддерживать работу с купюрами в 100, 200, 500, 1000, 2000, 5000 рублей.
//Выдаваемая или принимаемая за одну операцию сумма ограничена 40 купюрами(независимо от их достоинства).
//Купюры каждого достоинства хранятся в отдельной кассете.Емкость каждой кассеты – 2000 купюр.
//Считать, что начальная загрузка банкомата составляет 80 % для каждой кассеты.
//Считать, что клиент банка идентифицируется по номеру пластиковой карты(для упрощения – номер карты от «0001» до «9999»).
//База клиентов хранится в классе Процессинговый центр.Номера выданных клиентам карт могут идти не подряд.
//Считать, что информация о клиенте состоит из номера карты, ФИО владельца, суммы на счету, (для упрощения – без копеек), 
//PIN - кода(последовательность из 4 - х цифр, каждая от 0 до 9).
//Класс Банкомат должен предоставлять следующие операции : 1) принять карту клиента, 2) найти клиента по номеру карты, 
//3) проверить PIN - код, 4) распечатать состояние счета клиента, 5) выдать клиенту наличные(списав выданную сумму со счета), 
//6) принять от клиента наличные(зачислив полученную сумму на счет), 
//7) заблокировать карту клиента, если до ее клиенту три раза подряд набран неверный PIN - код, 8) вернуть карту клиенту.
//Все операции должны сопровождаться необходимыми проверками на указанные выше ограничения.
//Класс Процессинговый центр должен использоваться для поддержки работы класса Банкомат и может быть разработан в минимально - необходимом варианте.

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <conio.h>

//А что если я создам в классе процесинговый центр динамический массив и потом с помощью метода присвою адрес в памяти этого массива указателю который хранится
//Или создать отдельный класс, называемый Сервером, который будет устанавливать эту связь между Банкоматом и Процессинговым центром,
//в классе банкомат, тем самым я настрою банкомат на процессинговый центр, а не наоборот. Перед этим этот массив в классе ПЦ я инициалирую из файла?
//Но тогда возникает вопрос, Будет ли нужен процессинговый центр - ну да, он нужен будет, ведь там будет хранится все статистические данные.

//Процессинговый центр - это и есть тот сервер, который как я думал будет связующим звеном. А новый класс - информация о пользователею

//В банкомате будет указатель на ПЦ, но для моей реализации, нужно чтобы Данные процессингова центра уже существовали перед использованием банкомата => класс процессинговый
//центр нужно использовать раннее. И будем инициализировать его с помощью взятия информации из файла. Следующий мув - присвоение этих данных указателю (указателю в классе банкомат мы присвоем место в памяти этого класса), который хранится
//в классе банкомат, посредством присвоения и создания определённых методов (в ПЦ или банкомате, пока не понял) и тогда мы будем сразу иметь доступ к операциям.

using namespace std;

const int NumKinds = 6;//Глобальная константа, отвечает за количество разных видов купюр.
const int LimitOfNotes = 40;//Глобальная константа, значение которой является потолком для выдачи купюр.
const int NumNotesInitially = 1600;//Глобальная константа, значение которой говорит о числе купюр каждого достоинтсва изначально.
const int LimitOfStore = 2000;//Глобальная константа, значение которой говорит о лимите хранения купюры.

int ArrOfParNotes[NumKinds] = { 100,200,500,1000,2000,5000 };//Глобальный массив значений купюр, ведь в каждой стране могут быть своё.

struct FIO
{
	string surname;
	string name;
	string patronymic;
};

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(Console, pos);
}

struct UserData
{
	FIO person;//фамилия, имя и отчество человека.
	string cardnum;//Поле класса, отвечающее за номер карты (состоит из 4 цифр).
	long summoney;//сумма денег на счету.
	string pincode;//ПИН-код карты.
};

//Функция для более удобного вывода на экран.
ostream& operator<<(ostream& out, const UserData& data)
{
	out << "ФИО клиента: " << data.person.surname << " " << data.person.name << " " << data.person.patronymic << endl << "Номер карты клиента: " << data.cardnum << endl << "Сумма денег клиента: " << data.summoney << endl << "Пин-Код клиента: " << data.pincode << endl;
	return out;
}

//Функция для удобного вывода ФИО.
ostream& operator<<(ostream& out, const FIO& fio)
{
	out << fio.surname << " " << fio.name << " " << fio.patronymic;
	return out;
}

class ProcessingCenter
{
private:
	UserData* persons;//Массив данных людей.
	bool* arrofaccess;//Масиив, хранящий информацию о доступе к использованию карты.
	int numpeople;//Количество людей, данные которых мы можем сохранить.
	int nownumpeole;//Количество людей, данные которых нам уже известны.

	//Метод создания массива, хранящего информацию о людях.
	void CreateArraysOfPersons()
	{
		persons = new UserData[numpeople];
		arrofaccess = new bool[nownumpeole];
	}

	//Метод считает количество пробелов в строке.
	int CountWhiteSymbols(string str)
	{
		int num = 0;
		size_t len;
		len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (str[i] == ' ')
			{
				num++;
			}
		}
		return num;
	}

	//Метод узнаёт количество людей, чьи данные уже есть в процессинговом центре.
	int GetNowNumPeopleFromStr(string& str)
	{
		int res = 0;
		size_t len;
		string temp = "Пустая строка";
		len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (str[i] == ' ')
			{
				res = stoi(temp);
				break;
			}
			temp[i] = str[i];
		}
		return res;
	}

	//Метод узнаёт данные человека, который уже есть в Прессинговом центре.
	UserData GetDataOfPerson(string& str)
	{
		UserData res;
		long num;
		size_t len, counterwords = 0, numchar;
		string temp;
		len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (str[i] == ' ')
			{
				if (counterwords == 0)
				{
					res.person.surname = temp;
				}
				else if (counterwords == 1)
				{
					res.person.name = temp;
				}
				else if (counterwords == 2)
				{
					res.person.patronymic = temp;
				}
				else if (counterwords == 3)
				{
					res.cardnum = temp;
				}
				else if (counterwords == 4)
				{
					num = stoi(temp);
					res.summoney = num;
				}
				else if (counterwords == 5)
				{
					res.pincode = temp;
				}
				temp.clear();
				counterwords++;
				i++;
			}
			temp.push_back(str[i]);
		}
		return res;
	}
	//Метод заполняет массив доступа к картам.
	void FillArrOfAccess()
	{
		for (size_t i = 0; i < nownumpeole; i++)
		{
			arrofaccess[i] = true;
		}
	}

public:
	//Конструктор по умолчанию.
	ProcessingCenter(): numpeople(100),nownumpeole(0)
	{
		CreateArraysOfPersons();
	}
	//Метод получения Пин-кода клиента.
	string GetPinCode(int i)
	{
		string temp;
		temp = persons[i].pincode;
		return temp;
	}
	//Метод устанавливает значение false в выбранный элемент массива bool.
	void SetElemOfArrAccess(int i)
	{
		arrofaccess[i] = false;
	}
	//Метод получения доступа к карте.
	bool GetElemOfArrAccess(int i)
	{
		return arrofaccess[i];
	}
	//Метод получение ФИО клиента.
	FIO GetFIO(int i)
	{
		FIO temp;
		temp = persons[i].person;
		return temp;
	}
	//Метод получения номера карты клиента.
	string GetNumOfCard(int i)
	{
		string temp;
		temp = persons[i].cardnum;
		return temp;
	}
	//Метод получения количества денежных средств на счёте клиента.
	int GetSumOfMoney(int i)
	{
		int temp;
		temp = persons[i].summoney;
		return temp;
	}
	//Функция заполняет массив данными.
	void FillArrOfDataFromFail()
	{
		int counter, countwhitesym, i = 0;
		ifstream fail("DataForProgram.txt");
		UserData data;
		while (fail)
		{
			string strInput;
			getline(fail, strInput);
			countwhitesym = CountWhiteSymbols(strInput);
			if (countwhitesym == 1)
			{
				nownumpeole = GetNowNumPeopleFromStr(strInput);
				FillArrOfAccess();
			}
			else if (countwhitesym == 6)
			{
				data = GetDataOfPerson(strInput);
				persons[i] = data;
				i++;
			}
		}
	}
	//Метод осуществляет поиск клиента по его номеру
	int SearchOfClient(const string& str)
	{
		int flag = -1;
		for (size_t i = 0; i < nownumpeole; i++)
		{
			if (persons[i].cardnum == str)
			{
				flag = i;
			}
		}
		return flag;
	}
	//Метод печатает информацию о клиентах на экран.(не забыть убрать в privatе, ведь это секретные данные).
	void PrintArray()
	{
		for (int i = 0; i < nownumpeole; i++)
		{
			cout << "\t\t\t Клиент № " << i + 1 << endl << persons[i] << endl;
		}
	}
	//Метод Вычитает определённую сумму
	void SubtractSum(int sum, int i)
	{
		persons[i].summoney -= sum;
	}
	//Метод зачисляет средства на счёт.
	void AddOnAccount(int sum, int i)
	{
		persons[i].summoney += sum;
	}
	//Деструктор
	~ProcessingCenter()
	{
		delete[] persons;
	}
};

class CashMachine
{
private:
	ProcessingCenter* server;//Класс банкомат таким образом будет обращаться к серверу.
	int numnotes;//Счётчик числа выданных и принятых купюр.
	int arrnumnotes[NumKinds];//Массив, в котором хранится количество купюр, которых осталось в банкомате (по условию каждый из элементов будет иметь значение)
	int arrparnotes[NumKinds];//Массив, в котором хранятся значения каждой из купюр.
	int sumtaken;//Переменная для зачисления суммы денег на счёт клиента.
	int index;//Нам нужен индекс, что при поиске клиента запомнить его расположение, чтобы сотню раз не обращаться к серверу.
	short counterpincodes;//Для подсчёта количества попыток ввода пин-кода.
	string numofcard;//Строка,хранящая номер карты клиента.

	//Инициализация массива количества купюр каждого достоинства.
	void InitArrNumNotes()
	{
		for (size_t i = 0; i < NumKinds; i++)
		{
			arrnumnotes[i] = NumNotesInitially;
		}
	}
	//Инициализация массива номинала каждой купюры.
	void InitArrParNotes()
	{
		for (size_t i = 0; i < NumKinds; i++)
		{
			arrparnotes[i] = ArrOfParNotes[i];
		}
	}
	//Метод запоминает текущий номер карты.
	void RememberNumOfCard(string& str)
	{
		numofcard = str;
	}
	//Метод осуществляет проверку на заполнения ящиков хранения купюр.
	bool CheckArrOfNotes(int num)
	{
		bool control = true;
		if (num > LimitOfStore)
		{
			control = false;
		}
		return control;
	}
	//Метод осуществляет проверку на количество купюр в одной транзакции.
	bool CheckNumNotes(int num)
	{
		bool control = true;
		if (num > LimitOfNotes)
		{
			control = false;
		}
		return control;
	}
	//Метод разбивает суммы на купюры.
	void SmashSum(int* arrnumtemp,int sum)
	{
		for (int i = 5; i > -1; i--)
		{
			while ((sum >= arrparnotes[i]) && (arrnumnotes[i] > 0))//Самый простой вариант, рассмотреть с учётом наблюдения количества купюр, которые имеются
			{
				sum -= arrparnotes[i];
				arrnumtemp[i]++;
				arrnumnotes[i]--;
			}
		}
	}
	//Метод разбивает суммы на купюры (В качестве демо-версии).
	void SmashSumTemp(int* arrnumtemp, int sum)
	{
		int arr[NumKinds] = { 0,0,0,0,0,0 };
		for (size_t i = 0; i < NumKinds; i++)
		{
			arr[i] = arrnumnotes[i];
		}
		for (int i = 5; i > -1; i--)
		{
			while ((sum > arrparnotes[i]) && (arr[i] > 0))//Самый простой вариант, рассмотреть с учётом наблюдения количества купюр, которые имеются
			{
				sum -= arrparnotes[i];
				arrnumtemp[i]++;
				arr[i]--;
			}
		}
	}
public:
	//Конструктор по умолчанию.
	CashMachine()
	{
		numnotes = 0;
		index = -1;
		counterpincodes = 0;
		sumtaken = 0;
		InitArrNumNotes();
		InitArrParNotes();
		numofcard = "d000";
	}
	//Метод проверки на блокировку.
	bool CheckOfBlock()
	{
		bool temp;
		temp = server->GetElemOfArrAccess(index);
		return temp;
	}
	//Метод связывает Процессинговый центр и банкомат.
	void LinkPrAndCM(ProcessingCenter* temp)
	{
		server = temp;
	}
	//Метод принимает карту клиента.
	void TakeCardOfClient(string& strofnum)
	{
		//Поскольку самой карты у нас нет, то в качестве её симулятора, пользователь должен будет ввести её номер.
		RememberNumOfCard(strofnum);
	}
	//Метод ищет клиента по номеру его карты.
	void FindClientWithNumOfCard()
	{
		index = server->SearchOfClient(numofcard);
	}
	//Метод осуществляет проверку наличия клиента у этого банка.
	bool CheckPresenceOfClient()
	{
		bool check = false;
		if (index > -1)
		{
			check = true;
		}
		return check;
	}
	//Метод проверяет Пин-Код клиента.
	bool CheckPinCode(string& pincode)
	{	
		bool check = true;
		string temp;
		temp = server->GetPinCode(index);
		if (temp != pincode)
		{
			check = false;
			counterpincodes++;
			if (counterpincodes == 3)
			{
				BlockCardOfClient();
			}
		}
		return check;
	}
	//Метод печатает состояние счёта клиента.
	void PrintAccountStatus()
	{
		FIO tempfio;
		int numofsum, i = 0,y = 10;
		string tempnumofcard;
		tempfio = server->GetFIO(index);
		numofsum = server->GetSumOfMoney(index);
		tempnumofcard = server->GetNumOfCard(index);
		gotoxy(10, y);
		y += 3;
		cout << "Состояние счёта клиента" << endl;
		while (i < 3)
		{
			gotoxy(5, y);
			if (i == 0)
			{
				cout << "ФИО клиента: " << tempfio;
			}
			if (i == 1)
			{
				cout << "Номер карты клиента: " << "**** **** **** " << tempnumofcard;
			}
			if (i == 2)
			{
				cout << "Количество денежных средств: " << numofsum << " -P-";
			}
			y++;
			i++;
		}
	}
	//Метод блокирует карту клиента.
	void BlockCardOfClient()
	{
		server->SetElemOfArrAccess(index);
		counterpincodes = 0;
	}
	//Метод выводит на экран, что введён неверный пинкод.
	void ShowIncorrectPinCode()
	{
		cout << "Вы ввели неверный пинкод" << endl;
	}
	//Метод возвращает карту клиенту.
	void GiveCardOfClient()
	{
		//в методе выдать карту клиента прорисовать в консоле модель карты.
		int y = 10;
		FIO temp;
		gotoxy(10, y);
		cout << "_______________________________________________________";
		for (size_t i = 0; i < 10; i++)
		{
			y++;
			gotoxy(10, y);
			cout << "|                                                     |";
		}
		gotoxy(10, y);
		cout << "-------------------------------------------------------";
		gotoxy(20, 13);
		cout << "1823 2000 0505 " << numofcard;
		gotoxy(15, 16);
		temp = server->GetFIO(index);
		cout << temp;
		gotoxy(0, y + 1);
	}
	//Метод принимает деньги клиента.
	int TakeMoney(int note)
	{
		int control = 2;
		for (size_t i = 0; i < NumKinds; i++)
		{
			if (note == arrparnotes[i])
			{
				if (!CheckArrOfNotes(arrnumnotes[i]))
				{
					control = 0;//Проверка на перерполнения хранения купюр.
					return control;
					//Проверить этот фрагмент.
				}
				arrnumnotes[i]++;
			}
		}
		if (!CheckNumNotes(numnotes))
		{
			control = 1;//Проверка на переполнения приёма купюр.
			return control;
		}
		numnotes++;
		sumtaken += note;
		return control;
	}
	//Метод осуществляет зачисления суммы на счёт.
	void SendInfoAboutMoney()
	{
		server->AddOnAccount(sumtaken, index);
		sumtaken = 0;
		numnotes = 0;
	}
	//Метод выдаёт деньги.
	int GiveMoneyToClient(int sum)
	{
		int arrnumtemp[NumKinds] = { 0,0,0,0,0,0 };
		int tempsum = 0, exitf = 3, tempval;
		tempval = server->GetSumOfMoney(index);
		if (sum > tempval)
		{
			exitf = 0;
			return exitf;
		}
		if (sum % 100 != 0)
		{
			exitf = 1;
			return exitf;
		}
		SmashSumTemp(arrnumtemp, sum);
		for (size_t i = 0; i < NumKinds; i++)
		{
			tempsum += arrnumtemp[i];
		}
		if (tempsum > LimitOfNotes)
		{
			exitf = 2;
			return exitf;
		}
		return exitf;
	}
	//Метод печатает число выданных купюр.
	void PrintNumOfNotes(int sum)
	{
		int arr[NumKinds] = { 0,0,0,0,0,0 };
		SmashSum(arr, sum);
		cout << "5000 P : " << arr[5] << " штук" << endl;
		cout << "2000 P : " << arr[4] << " штук" << endl;
		cout << "1000 P : " << arr[3] << " штук" << endl;
		cout << "500 P : " << arr[2] << " штук" << endl;
		cout << "200 P : " << arr[1] << " штук" << endl;
		cout << "100 P : " << arr[0] << " штук" << endl;
		server->SubtractSum(sum, index);
	}
	//Деструктор.
	~CashMachine()
	{}
};

void ShowMenu();
void showLogo();
void GetCard(CashMachine& bankcase);
bool CheckCode(CashMachine& bankcase);
void ReturnCard(CashMachine& bankcase);
void PrintBackgroundInformation();
void TakeMoney(CashMachine& bankcase);
void GiveMoney(CashMachine& bankcase);

int main()
{
	setlocale(LC_ALL, "Rus");
	ProcessingCenter center;
	center.FillArrOfDataFromFail();
	CashMachine bankcase;
	bankcase.LinkPrAndCM(&center);
	srand(time(0));
	system("color F0");
	system("cls");
	showLogo();
	const int NUM_MENU_ITEMS = 7;
	int activeMenuItem = 0;
	int ch = 0;
	bool exit = false, control1 = false, control2 = false;
	while (!exit)
	{
		ShowMenu();
		gotoxy(0, activeMenuItem);
		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}
		switch (ch)
		{
		case 27:
			exit = true;
			break;
		case 72:
			activeMenuItem--;
			break;
		case 80:
			activeMenuItem++;
			break;
		case 13:
			if (activeMenuItem == 0)
			{
				system("cls");
				GetCard(bankcase);
				system("cls");
				if (!bankcase.CheckPresenceOfClient())
				{
					cout << "Вы пока не являетесь клиентом нашего банка, поэтому у вас нет доступа. Всего хорошего" << endl;
					system("pause");
					system("cls");
					break;
				}
				else if (bankcase.CheckOfBlock())
				{
					control1 = true;
					cout << "Профиль найден." << endl;
					system("pause");
					system("cls");
				}
				else
				{
					cout << "Ваша карта заблокирована!" << endl;
					system("pause");
					system("cls");
				}
			}
			else if (activeMenuItem == 1)
			{
				system("cls");
				if (control1)
				{
					if (!CheckCode(bankcase))
					{
						bankcase.ShowIncorrectPinCode();
						if (!bankcase.CheckOfBlock())
						{
							control1 = false;
						}
						system("pause");
						break;
					}
					else
					{
						cout << "Добро пожаловать!" << endl;
						system("pause");
						control2 = true;
					}
				}
				else
				{
					cout << "Данная услуга вам не доступна, всего хорошего!" << endl;
					system("pause");
					system("cls");
				}
			}
			else if (activeMenuItem == 2)
			{
				if (control2)
				{		
					system("cls");
					bankcase.PrintAccountStatus();
					cout << "\n\n\n";
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "Данная услуга вам не доступна, всего хорошего!" << endl;
					system("pause");
					system("cls");
				}
			}
			else if (activeMenuItem == 3)
			{
				if (control2)
				{
					system("cls");
					PrintBackgroundInformation();
					TakeMoney(bankcase);
					system("pause");
				}
				else
				{
					system("cls");
					cout << "Данная услуга вам не доступна, всего хорошего!" << endl;
					system("pause");
					
				}
			}
			else if (activeMenuItem == 4)
			{
				if (control2)
				{
					system("cls");
					PrintBackgroundInformation();
					GiveMoney(bankcase);
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "Данная услуга вам не доступна, всего хорошего!" << endl;
					system("pause");
				}
			}
			else if (activeMenuItem == 5)
			{
				if (control2)
				{
					system("cls");
					ReturnCard(bankcase);
					system("pause");
				}
				else
				{
					system("cls");
					cout << "Данная услуга вам не доступна, всего хорошего!" << endl;
					system("pause");
				}
			}
			else if (activeMenuItem == 6)
			{
				exit = true;
			}
			break;
		}
		if (activeMenuItem < 0) activeMenuItem = 0;
		if (activeMenuItem > NUM_MENU_ITEMS - 1) activeMenuItem = NUM_MENU_ITEMS - 1;
		
	}
	system("cls");
	system("pause");
	return 0;
}

void ShowMenu()
{
	system("cls");
	cout << " 1. Принять карту клиента." << endl;
	cout << " 2. Проверить Пин-Код" << endl;
	cout <<	" 3. Вывести информацию о состоянии счёта" << endl;
	cout << " 4. Принять деньги" << endl;
	cout << " 5. Выдать деньги" << endl;
	cout << " 6. Выдать карту клиенту" << endl;
	cout << " 7. Закончить работу" << endl;
}

void ReturnCard(CashMachine& bankcase)
{
	bankcase.GiveCardOfClient();
}

void GiveMoney(CashMachine& bankcase)
{
	int sum = -1, counter;
	cout << "Введите сумму, которую хотите снять " << endl;
	while (sum <= 0)
	{
		cin >> sum;
	}
	counter = bankcase.GiveMoneyToClient(sum);
	if (counter == 0)
	{
		cout << "Недостаточно средств на счёте " << endl;
	}
	if (counter == 1)
	{
		cout << "Такую сумму невозможно выдать " << endl;
	}
	if (counter == 2)
	{
		cout << "Такую сумму невозможно выдать " << endl;
	}
	if (counter == 3)
	{
		bankcase.PrintNumOfNotes(sum);
	}
}


void TakeMoney(CashMachine& bankcase)
{
	int control2, i = 0, note, counter = -1;
	bool control = false, control1 = false;
	while (!control1)
	{
		while (!control)
		{
			cout << "Введите номинал купюры, которую хотите положить на счёт " << endl;
			cin >> note;
			i = 0;
			while (i != NumKinds)
			{
				if (note == ArrOfParNotes[i])
				{
					control = true;
					break;
				}
				i++;
			}
			if (!control)
			{
				cout << "Такую купюру банкомат не принимает " << endl;
			}
			else
			{
				control2 = bankcase.TakeMoney(note);
				if (control2 == 0)
				{
					cout << "Операция не может быть выполнена, произошло переполненние храния этого вида купюры " << endl;
				}
				else if (control2 == 1)
				{
					cout << "Операция не может быть выполнена, превышен лимит введённых купюр " << endl;
				}
				else
				{
					cout << "Операция прошла успешно!" << endl;
				}
			}
		}
		cout << "Если хотите продолжить зачисление денег нажмите 1, если хотите завершить ввод нажмите 0" << endl;
		while (counter < 0 || counter > 1)
		{
			cin >> counter;
			if (counter < 0 || counter > 1)
			{
				cout << "Такой функции не доступно в программе " << endl;
			}
		}
		if (counter == 0)
		{
			control1 = true;
		}
		else
		{
			control = false;
			counter = -1;
		}
	}
	bankcase.SendInfoAboutMoney();
}

bool CheckCode(CashMachine& bankcase)
{
	string temp;
	char symbol;
	cout << "Введите пароль:" << endl;
	for (size_t i = 0; i < 4; i++)
	{
		symbol = '/';
		while (symbol < 48 || symbol > 57)
		{
			cin >> symbol;
			if (symbol < 48 || symbol > 57)
			{
				cout << "Ошибка, можно вводить только цифры" << endl;
			}
		}
		temp += symbol;
	}
	return bankcase.CheckPinCode(temp);
}

void PrintBackgroundInformation()
{
	cout << "Банкомат принимает следующие купюры: 100 P, 200 P, 500 P, 1000 P, 2000 P, 5000 P, а значит может работать с суммами, которые могут быть получены и этиъ купюр." << endl;
}

void GetCard(CashMachine& bankcase)
{
	string temp;
	char symbol;
	cout << "Введите номер карты " << endl;
	for (size_t i = 0; i < 4; i++)
	{
		symbol = '/';
		while (symbol < 48 || symbol > 57)
		{
			cin >> symbol;
			if (symbol < 48 || symbol > 57)
			{
				cout << "Ошибка, можно вводить только цифры" << endl;
			}
		}
		temp += symbol;
	}
	bankcase.TakeCardOfClient(temp);
	bankcase.FindClientWithNumOfCard();
}

void showLogo()
{
	gotoxy(50, 15);
	cout << "Симулятор Банкомата" << endl;
	Sleep(1500);
}
