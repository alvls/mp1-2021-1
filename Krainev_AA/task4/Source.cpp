#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <clocale> 
#include <windows.h>
#include <fstream> 
#include <sstream> 
#include <cctype> 
#include <cstring>
#include <locale>
using namespace std;
void printMenu();
void welcomeMessege();
struct Date {
	unsigned short int day;
	unsigned short int month;
	unsigned short int year;
	Date& operator=(const Date& date) { //присваивания
		if (this != &date) {
			day = date.day;
			month = date.month;
			year = date.year;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Date& date) {
		out << date.day << ' ' << date.month << ' ' << date.year;
		//out << date.day << ' ' << date.month << ' ' << date.year<<endl;
		return out;
	}
	//construct для задания Date
	Date(int otherDay = 0, int otherMonth = 0, int otherYear = 0) : year(otherYear), month(otherMonth), day(otherDay){ };
};

struct Weight {
	Date dateInWeight;
	double weightMember;
	//сделаем конструкторы для структуры
	Weight(Date otherDate, double otherWeight) :dateInWeight(otherDate), weightMember(otherWeight) {};
	Weight& operator=(const Weight& weight) {
		if (this != &weight) {
			dateInWeight = weight.dateInWeight;
			weightMember = weight.weightMember;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Weight& weight) {
		out << weight.dateInWeight.day << ' ' << weight.dateInWeight.month << ' ' << weight.dateInWeight.year << ' ' << weight.weightMember;
		return out;
	}
};
Date startDateOfObservations;
struct memberFamily {
	string name;
	vector <Weight> numberOfMemberFamily;
	memberFamily(string nameMember) { name = nameMember; };
	memberFamily& operator=(const memberFamily& member) {
		if (this != &member) {
			numberOfMemberFamily = member.numberOfMemberFamily;
			name = member.name;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, memberFamily& member) {
		out << member.name << endl;
		for (unsigned int i = 0; i < member.numberOfMemberFamily.size(); i++) {
			out << member.numberOfMemberFamily[i] << endl;
		}
		return out;
	}
	void Observation(unsigned short int otherDay, unsigned short int  otherMonth, unsigned short int otherYear, double otherWeight) {
		if (searchMember(otherDay, otherMonth, otherYear) == false) {
			Date date(otherDay, otherMonth, otherYear);
			Weight weight(date, otherWeight);
			numberOfMemberFamily.push_back(weight); //пуляем в конец вектора
		}
		else { numberOfMemberFamily[searchMember(otherDay, otherMonth, otherYear)].weightMember = otherWeight; }
	}
	int searchMember(unsigned short int otherDay, unsigned short int  otherMonth, unsigned short int otherYear) { //если такое уже есть то возвращаем номер члена семьи, иначе ложь
		for (unsigned int j = 0; j < numberOfMemberFamily.size(); j++) {
			if (numberOfMemberFamily[j].dateInWeight.day == otherDay\
				&& numberOfMemberFamily[j].dateInWeight.month == otherMonth && numberOfMemberFamily[j].dateInWeight.year == otherYear) {
				return j;
			}
		}
		return false;
	}
};
class floorScales { //класс напольные весы
private:
	vector <memberFamily> Scale;
public:

	floorScales() {};
	floorScales(vector <memberFamily> other) { Scale = other; }
	floorScales(string filename);
	void setNameMember(string nameMember);
	void setTheStartDateOfObservations(unsigned short int day, unsigned short int month, unsigned short int year);
	Date getTheStartDateOfObservations();
	void setObservation(unsigned short int day, unsigned short int month, unsigned short int year, double weight, string name);
	double getObservation(unsigned short int day, unsigned short int  month, unsigned short int year, string nameMember);
	double getAverageWeightOfFamilyMember(string NameMember);
	double getAverageWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear);
	double getMinimumWeightOfFamilyMember(string nameMember);
	double getMinimumWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear);
	double getMaximumWeightOfFamilyMember(string nameMember);
	double getMaximumWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear);
	void printDateOfMinimumWeightOfFamilyMember(string nameMember);
	void printDateOfMinimumWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear);
	void printDateOfMaximumWeightOfFamilyMember(string nameMember);
	void printDateOfMaximumWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear);
	void saveFile();
};
void floorScales::setNameMember(string nameMember) {
	memberFamily newMember(nameMember);
	//помещаем в конец вектора структуру с новым именем
	Scale.push_back(newMember);
}
void floorScales::setTheStartDateOfObservations(unsigned short int day, unsigned short int month, unsigned short int year) {
	if (startDateOfObservations.day == 0 && startDateOfObservations.month == 0 && startDateOfObservations.year == 0) {
		//cout << "Начальная дата измерения не была задана" << endl;
		startDateOfObservations.day = day;
		startDateOfObservations.month = month;
		startDateOfObservations.year = year;
	}
	else { cout << "Начальная дата измерений уже задана. Если вы хотите ее изменить, придется удалить файл. Данные будут потеряны! (Для этого выберите соотвествующий пункт меню)" << endl; }
}
int main() {
	setlocale(LC_ALL, "rus");
	welcomeMessege();
	int choice;
	string nameMember;
	string str = "Scales.txt";
	floorScales Scale(str);
	while (1) {
		printMenu();
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "Введите имя нового пользователя" << endl;
			cin >> nameMember;
			cout << nameMember << endl;
			Scale.setNameMember(nameMember);
			break;
		}
		case 2: {
			cout << "Установить начальную дату наблюдений" << endl;
			unsigned short int day, month, year;
			cout << "Введите день: " << endl;
			cin >> day;
			cout << "Введите месяц: " << endl;
			cin >> month;
			cout << "Введите год: " << endl;
			cin >> year;
			Scale.setTheStartDateOfObservations(day, month, year);
			break;
		}
		case 3: {
			cout << "Начальная дата наблюдений: " << endl;
			cout << Scale.getTheStartDateOfObservations() << endl;
			break; }
		case 4: {
			unsigned short int day, month, year;
			if (((startDateOfObservations.day == 0 && startDateOfObservations.month == 0) && startDateOfObservations.year == 0)) { cout << "Задайте сначала начальную дату наблюдений." << endl; }
			else {
				cout << "Сейчас вы сможете ввести новые измерения для пользователя " << endl;
				cout << "Введите имя: ";
				cin >> nameMember;
				cout << "Введите день : ";
				cin >> day;
				cout << "Введите месяц: ";
				cin >> month;
				cout << "Введите год: ";
				cin >> year;
				if ((year < startDateOfObservations.year) || (year == startDateOfObservations.year) && (month < startDateOfObservations.month)\
					|| (year == startDateOfObservations.year) && (month == startDateOfObservations.month) && (day < startDateOfObservations.day)) {
					cout << "Введенная дата раньше начала наблюдений." << endl;
				}
				else {
					cout << "Введите вес: ";
					double weight;
					cin >> weight;
					Scale.setObservation(day, month, year, weight, nameMember);
				}
			}
			break; }
		case 5: {
			unsigned short int day, month, year;
			cout << "А сейчас узнаем вес у пользователя в выбранную дату" << endl;
			cout << "Имя: ";
			cin >> nameMember;
			cout << "День: ";
			cin >> day;
			cout << "Месяц: ";
			cin >> month;
			cout << "год: ";
			cin >> year;
			cout <<"Вес в выбранную дату: "<< Scale.getObservation(day, month, year, nameMember) << " кг." <<endl;
			break;
		}
		case 6: {
			unsigned short int day, month, year;
			cout << "Найдем средний вес члена семьи в выбранном месяце или за всю историю наблюдений" << endl;
			cout << "Введите имя: " << endl;
			cin >> nameMember;
			cout << "Выберите промежуток времени " << endl;
			cout << "1. За все время" << endl;
			cout << "2. В выбранном месяце" << endl;
			cin >> choice;
			switch (choice) {
			case 1: {
				cout << "Средний вес за все время наблюдений: " << Scale.getAverageWeightOfFamilyMember(nameMember) << endl;
				break;
			}
			case 2: {
				cout << "Введите месяц: ";
				cin >> month;
				cout << "Введите год: ";
				cin >> year;
				cout << "Средний вес в выбранное время: " << Scale.getAverageWeightOfFamilyMember(nameMember, month, year) << endl;
				break;
			}
			}
			break;
		}
		case 7: {
			unsigned short int day, month, year;
			cout << "Введите имя: " << endl;
			cin >> nameMember;
			cout << "1. За все время" << endl;
			cout << "2. В выбранном месяце" << endl;
			cin >> choice;
			switch (choice) {
			case 1: {
				cout << "Минимальный вес за все время наблюдений: " << Scale.getMinimumWeightOfFamilyMember(nameMember) << endl;
				Scale.printDateOfMinimumWeightOfFamilyMember(nameMember);
				break;
			}
			case 2: {
				cout << "Введите месяц: ";
				cin >> month;
				cout << "Введите год: ";
				cin >> year;
				cout << "Минимальный вес в выбраное время: " << Scale.getMinimumWeightOfFamilyMember(nameMember, month, year) << endl;
				Scale.printDateOfMinimumWeightOfFamilyMember(nameMember, month, year);
				break;
			}
			}
			break;
		}
		case 8: {
			unsigned short int day, month, year;
			//найти максимальный вес члена семьи в выбранном месяце или за всю историю наблюдений и дату, когда он наблюдался,
			cout << "Введите имя: " << endl;
			cin >> nameMember;
			cout << "1. За все время" << endl;
			cout << "2. В выбранном месяце" << endl;
			cin >> choice;
			switch (choice) {
			case 1:
			{
				cout << "Максимальный вес за все время наблюдений: " << Scale.getMaximumWeightOfFamilyMember(nameMember) << endl;
				Scale.printDateOfMaximumWeightOfFamilyMember(nameMember);
				break;
			}
			case 2: {
				cout << "Введите месяц: ";
				cin >> month;
				cout << "Введите год: ";
				cin >> year;
				cout << "Максимальный вес в выбранное время: " << Scale.getMaximumWeightOfFamilyMember(nameMember, month, year) << endl;
				Scale.printDateOfMaximumWeightOfFamilyMember(nameMember, month, year);
				break;
			}
			}

			break;
		}
		case 9: {
			Scale.saveFile();
			break;
		}
		case 10: {//очищение файлика те его удаление
			if (remove("Scales.txt") != 0) { cout << "Ошибка удаления файла."; }
			else cout << "Файл очищен, перезапустите программу!" << endl;
			break;
		}
		case 11:
			cout << "До встречи!"<< endl;
			return 0;

		}
	}
}

floorScales::floorScales(string filename) {
	ifstream in(filename);
	unsigned short int startDay = 0; unsigned short int startMonth = 0;  unsigned short int startYear = 0;
	unsigned short int day; unsigned short int month;  unsigned short int year;
	double weight;
	string name;
	string line;
	string str1, str2, str3, str4;
	int countString = 0;
	startDateOfObservations.day = 0;
	startDateOfObservations.month = 0;
	startDateOfObservations.year = 0;
	while (getline(in, line)) {
		istringstream ist(line);
		if (countString == 0) {
			if (((startDateOfObservations.day == 0 && \
				startDateOfObservations.month == 0) && \
				startDateOfObservations.year == 0)) {
				//cout << "Запишем дату наблюдений\n";
				//istringstream ist(line);
				ist >> str1;
				//cout << "str1 " << str1 << endl;
				ist >> str2;
				//cout << "str2 " << str2 << endl;
				ist >> str3;
				//cout << "str3 " << str3 << endl;
				ist >> str4;
				//cout << "str4 " << str4 << endl;
				ist >> startDay;
				ist >> startMonth;
				ist >> startYear;
				startDateOfObservations.day = startDay;
				startDateOfObservations.month = startMonth;
				startDateOfObservations.year = startYear;
			}
			//if (in.peek() == EOF) { cout << "Файл пустой.\n"; } 
		}
		if (countString > 0) {
			ist >> name;
			ist >> day;
			ist >> month;
			ist >> year;
			ist >> weight;
			memberFamily newMember(name);
			//помещаем в конец вектора структуру с новым именем
			Scale.push_back(newMember);
			for (int i = 0; i < Scale.size(); i++) {
				if (Scale[i].name == name) {
					Scale[i].Observation(day, month, year, weight);
				}
			}
		}
		countString++;
	}
	in.close();
}


Date floorScales::getTheStartDateOfObservations() { return startDateOfObservations; }

void floorScales::setObservation(unsigned short int day, unsigned short int month, unsigned short int year, double weight, string otherNameMember) {
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == otherNameMember) { Scale[i].Observation(day, month, year, weight); }
	}
}

double floorScales::getObservation(unsigned short int day, unsigned short int month, unsigned short int year, string nameMember) {
	if (Scale.size() > 0) { // чтобы хоть что-то было
		for (unsigned int i = 0; i < Scale.size(); i++) {
			if (Scale[i].name == nameMember) {
				//cout << "Число взвешиваний у члена семьи: " << Scale[i].numberOfMemberFamily.size() << endl; //для отладки
				for (int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++)
					if (((Scale[i].numberOfMemberFamily[j].dateInWeight.month == month) && (Scale[i].numberOfMemberFamily[j].dateInWeight.year == year)\
						&& (Scale[i].numberOfMemberFamily[j].dateInWeight.day == day))) {
						return Scale[i].numberOfMemberFamily[j].weightMember;
					}

			}
		}
	}
	else { return 0; }
}

double floorScales::getAverageWeightOfFamilyMember(string nameMember) {
	double averageMeasurement = 0;
	int countingMeasurement = 0;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == nameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				averageMeasurement += Scale[i].numberOfMemberFamily[j].weightMember;
				countingMeasurement++;
			}

		}
	}
	if (countingMeasurement == 0) { return 0; } //чтобы на нолик не поделить 
	else { return averageMeasurement / countingMeasurement; }
}

double floorScales::getAverageWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear)
{
	double averageMeasurement = 0;
	int countingMeasurement = 0;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == otherNameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if ((Scale[i].numberOfMemberFamily[j].dateInWeight.month == otherMonth) && (Scale[i].numberOfMemberFamily[j].dateInWeight.year == otherYear)) {
					averageMeasurement += Scale[i].numberOfMemberFamily[j].weightMember;
					countingMeasurement++;
				}
			}
		}
	}
	if (countingMeasurement == 0) { return 0; }
	else { return averageMeasurement / countingMeasurement; }
}

double floorScales::getMinimumWeightOfFamilyMember(string nameMember) {
	double min = 200;// пусть весы будут до 200 кг
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == nameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if (Scale[i].numberOfMemberFamily[j].weightMember < min) {
					min = Scale[i].numberOfMemberFamily[j].weightMember;
					return min;
				}
			}
		}
	}

	return min;
}

double floorScales::getMinimumWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear) {
	double min = 1000;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == otherNameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if ((Scale[i].numberOfMemberFamily[j].dateInWeight.month == otherMonth) && (Scale[i].numberOfMemberFamily[j].dateInWeight.year == otherYear)) {
					if (Scale[i].numberOfMemberFamily[j].weightMember < min) { min = Scale[i].numberOfMemberFamily[j].weightMember; }
				}
			}
		}
	}
	return min;
}

double floorScales::getMaximumWeightOfFamilyMember(string nameMember) {
	double max = 0; // ну и соотвественно с 0
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == nameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if (Scale[i].numberOfMemberFamily[j].weightMember > max) { max = Scale[i].numberOfMemberFamily[j].weightMember; }
			}
		}
	}
	return max;
}

double floorScales::getMaximumWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear) {
	double max = 0;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == otherNameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if ((Scale[i].numberOfMemberFamily[j].dateInWeight.month == otherMonth) && (Scale[i].numberOfMemberFamily[j].dateInWeight.year == otherYear)) {
					if (Scale[i].numberOfMemberFamily[j].weightMember > max) { max = Scale[i].numberOfMemberFamily[j].weightMember; }
				}
			}
		}
	}
	return max;
}

void floorScales::printDateOfMinimumWeightOfFamilyMember(string nameMember) {
	double min = 200;// пусть весы будут до 200 кг
	int x = -1, y = -1;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == nameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if (Scale[i].numberOfMemberFamily[j].weightMember < min) { min = Scale[i].numberOfMemberFamily[j].weightMember; x = i; y = j; }
			}
		}
	}
	cout << "Дата этого наблюдения: " << Scale[x].numberOfMemberFamily[y].dateInWeight << endl;
}

void floorScales::printDateOfMinimumWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear) {
	double min = 1000;
	int x = -1; int y = -1;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == otherNameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if ((Scale[i].numberOfMemberFamily[j].dateInWeight.month == otherMonth) && (Scale[i].numberOfMemberFamily[j].dateInWeight.year == otherYear)) {
					if (Scale[i].numberOfMemberFamily[j].weightMember < min) { min = Scale[i].numberOfMemberFamily[j].weightMember; x = i; y = j; }
				}
			}
		}
	}
	cout << "Дата этого наблюдения: " << Scale[x].numberOfMemberFamily[y].dateInWeight << endl;
}

void floorScales::printDateOfMaximumWeightOfFamilyMember(string nameMember) {
	double max = 0; // ну и соотвественно с 0
	int x = -1; int y = -1;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == nameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if (Scale[i].numberOfMemberFamily[j].weightMember > max) { max = Scale[i].numberOfMemberFamily[j].weightMember; x = i; y = j; }
			}
		}
	}
	cout << "Дата этого наблюдения: " << Scale[x].numberOfMemberFamily[y].dateInWeight << endl;
}

void floorScales::printDateOfMaximumWeightOfFamilyMember(string otherNameMember, unsigned short int otherMonth, unsigned short int otherYear) {
	double max = 0;
	int x = -1; int y = -1;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		if (Scale[i].name == otherNameMember) {
			for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
				if ((Scale[i].numberOfMemberFamily[j].dateInWeight.month == otherMonth) && (Scale[i].numberOfMemberFamily[j].dateInWeight.year == otherYear)) {
					if (Scale[i].numberOfMemberFamily[j].weightMember > max) { max = Scale[i].numberOfMemberFamily[j].weightMember; x = i; y = j; }
				}
			}
		}
	}
	cout << "Дата этого наблюдения: " << Scale[x].numberOfMemberFamily[y].dateInWeight << endl;
}



void floorScales::saveFile() {
	//удаляю весь файл,  Зачем?   навсякий случай! 
	remove("Scales.txt");
	//if (remove("Scales.txt") != 0) { cout << "Ошибка удаления файла."; }
	//else { cout << "Файл успешно удалён" << endl; }
	ofstream file;
	file.open("Scales.txt");
	if (!file.is_open()) {
		std::cout << "File not open!" << std::endl;
	}
	file << "Задана начальная дата наблюдений: " << " " << startDateOfObservations << endl;
	for (unsigned int i = 0; i < Scale.size(); i++) {
		for (unsigned int j = 0; j < Scale[i].numberOfMemberFamily.size(); j++) {
			file << Scale[i].name << " " << Scale[i].numberOfMemberFamily[j] << endl;
		}
	}
	file.close();
}
void printMenu() {
	cout << "                   Меню:" << endl;
	cout << "1. Добавить нового пользователя" << endl;
	cout << "2. Установить начальную дату измерений" << endl;
	cout << "3. Посмотреть начальную дату измерений" << endl;
	cout << "4. Записать новое измерение" << endl;
	cout << "5. Узнать вес в выбранном измерении по дате и имени" << endl;
	cout << "6. Найти средний вес члена семьи в выбранном месяце или за всю историю наблюдений" << endl;
	cout << "7. Найти минимальный вес члена семьи в выбранном месяце или за всю историю наблюдений" << endl;
	cout << "8. Найти максимальный вес члена семьи в выбранном месяце или за всю историю наблюдений" << endl;
	cout << "9. Сохранить историю наблюдений в файл" << endl;
	cout << "10. Удалить файл и всю историю наблюдений!" << endl;
	cout << "11. Выход" << endl;
}

void welcomeMessege(){
	cout <<"Добро пожаловать в программу <Весы напольные>."<< endl;
	cout << "Считывание из файла происходит при запуске программы, не забудьте сохранить данные в файл по окончании работы." << endl;
}
