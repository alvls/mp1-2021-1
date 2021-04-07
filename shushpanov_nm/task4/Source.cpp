#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

struct Date
{
	int day, month, year;
	Date(int _day = 0, int _month = 0, int _year = 0) : day(_day), month(_month), year(_year) {};
	Date& operator=(const Date& date)
	{
		day = date.day;
		month = date.month;
		year = date.year;
		return *this;
	}
	friend ostream& operator<<(ostream& startDate, const Date& date)
	{
		startDate << setw(2) << setfill('0') << date.day << "." << setw(2) << setfill('0') << date.month << "." << date.year;
		return startDate;
	}
};
struct Weight
{
	double weight;
	Date measurementDate;
	Weight(double _weight, Date _measurementDate) : weight(_weight), measurementDate(_measurementDate) {};
	friend ostream& operator<<(ostream& weightDate, Weight& weightInfo)
	{
		weightDate << setw(2) << setfill('0') << weightInfo.measurementDate.day << "." << setw(2) << setfill('0') << weightInfo.measurementDate.month << "." << weightInfo.measurementDate.year << "\n" << weightInfo.weight << endl;
		return weightDate;
	}
};

struct PersonalData
{
	string name;
	vector <Weight> familyNumberMember;
	PersonalData(string nameFamilyMember) : name(nameFamilyMember) {};
	PersonalData(string nameFamilyMember, vector <Weight> numberMember) : name(nameFamilyMember), familyNumberMember(numberMember) {};
	PersonalData& operator=(const PersonalData& numberMember)
	{
		name = numberMember.name;
		familyNumberMember = numberMember.familyNumberMember;
		return *this;
	}
	friend ostream& operator<<(ostream& personalData, PersonalData& person)
	{
		personalData << person.name << endl;
		return personalData;
	}
	void SetObservation(int day, int month, int year, double weight)
	{
		if (SearchObservationData(day, month, year) == -1)
		{
			Date newDate(day, month, year);
			Weight newWeight(weight, newDate);
			familyNumberMember.push_back(newWeight);
		}
		else
		{
			familyNumberMember[SearchObservationData(day, month, year)].weight = weight;
		}
	}
	int SearchObservationData(int day, int month, int year)
	{
		int i;
		for (i = 0; i < familyNumberMember.size(); i++)
		{
			if (familyNumberMember[i].measurementDate.day == day && familyNumberMember[i].measurementDate.month == month && familyNumberMember[i].measurementDate.year == year)
			{
				return i;
			}
		}
		return -1;
	}
};

class Scales
{
private:
	int size;
	Date weightStartDate;
	vector <PersonalData> dimension;
public:
	Scales() {}
	Scales(int size, Date _weightStartDate, vector <PersonalData> _dimension) : size(0), weightStartDate(weightStartDate), dimension(_dimension) {}
	Scales(vector <PersonalData> constructor)
	{
		dimension = constructor;
	}
	void SetWeightStartDate(int day, int month, int year)
	{
		weightStartDate.day = day;
		weightStartDate.month = month;
		weightStartDate.year = year;
	}
	Date GetWeightStartDate()
	{
		return weightStartDate;
	}
	bool CheckDate(int day, int month, int year)
	{
		if (year >= weightStartDate.year)
		{
			if (month >= weightStartDate.month)
			{
				if (day >= weightStartDate.day)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool CheckFamilyMember(string name)
	{
		int i;
		for (i = 0; i < dimension.size();i++)
		{
			if (dimension[i].name == name)
			{
				return true;
			}
		}
		return false;
	}
	void SetFamilyMember(string name)
	{
		PersonalData familyMember(name);
		dimension.push_back(familyMember);
		size++;
	}
	int GetSizePersonalData()
	{
		return size;
	}
	void SetObservationMember(string name, int day, int month, int year, double weight)
	{
		int i;
		for (i = 0; i < dimension.size(); i++)
		{
			if (dimension[i].name == name)
			{
				dimension[i].SetObservation(day, month, year, weight);
			}
		}
	}
	double GetObservationMember(string name, int day, int month, int year)
	{
		int i;
		if (dimension.size() > 0)
		{
			for (i = 0; i < dimension.size(); i++)
			{
				if (dimension[i].name == name)
				{
					return dimension[i].familyNumberMember[dimension[i].SearchObservationData(day, month, year)].weight;
				}
			}
		}
		else
		{
			return 0;
		}
	}
	double SearchAverageWeight(string name, int month, int year, int paramFunction)
	{
		double averageWeight = 0;
		int i, j, count = 0;
		if (paramFunction == 1)
		{
			for (i = 0; i < dimension.size(); i++)
			{
				if (dimension[i].name == name)
				{
					for (j = 0;j < dimension[i].familyNumberMember.size(); j++)
					{
						if ((dimension[i].familyNumberMember[j].measurementDate.month == month) && (dimension[i].familyNumberMember[j].measurementDate.year == year))
						{
							averageWeight += dimension[i].familyNumberMember[j].weight;
							count++;
						}
					}
				}
			}
		}
		else
		{
			for (i = 0; i < dimension.size(); i++)
			{
				if (dimension[i].name == name)
				{
					for (j = 0;j < dimension[i].familyNumberMember.size(); j++)
					{
						averageWeight += dimension[i].familyNumberMember[j].weight;
						count++;
					}
				}
			}
		}
		if (count != 0)
		{
			return round((averageWeight / count) * 100) / 100;
		}
		else
		{
			return 0;
		}
	}
	double SearchMinimalWeight(string name, int month, int year, int paramFunction)
	{
		double minimalWeight = 0;
		int i, j, count = 1;
		if (paramFunction == 1)
		{
			for (i = 0; i < dimension.size(); i++)
			{
				if (dimension[i].name == name)
				{
					for (j = 0; j < dimension[i].familyNumberMember.size(); j++)
					{
						if (count == 1)
						{
							minimalWeight = dimension[i].familyNumberMember[j].weight;
							count = 0;
						}
						else
						{
							if ((dimension[i].familyNumberMember[j].measurementDate.month == month) && (dimension[i].familyNumberMember[j].measurementDate.year == year))
							{
								if (dimension[i].familyNumberMember[j].weight < minimalWeight)
								{
									minimalWeight = dimension[i].familyNumberMember[j].weight;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			for (i = 0; i < dimension.size(); i++)
			{
				if (dimension[i].name == name)
				{
					for (j = 0; j < dimension[i].familyNumberMember.size(); j++)
					{
						if (count == 1)
						{
							minimalWeight = dimension[i].familyNumberMember[j].weight;
							count = 0;
						}
						else
						{
							if (dimension[i].familyNumberMember[j].weight < minimalWeight)
							{
								minimalWeight = dimension[i].familyNumberMember[j].weight;
							}
						}
					}
				}
			}
		}
		return minimalWeight;
	}
	double SearchMaximumWeight(string name, int month, int year, int paramFunction)
	{
		double maximumWeight = 0;
		int i, j, count = 1;
		if (paramFunction == 1)
		{
			for (i = 0; i < dimension.size(); i++)
			{
				if (dimension[i].name == name)
				{
					for (j = 0; j < dimension[i].familyNumberMember.size(); j++)
					{
						if (count == 1)
						{
							maximumWeight = dimension[i].familyNumberMember[j].weight;
							count = 0;
						}
						else
						{
							if ((dimension[i].familyNumberMember[j].measurementDate.month == month) && (dimension[i].familyNumberMember[j].measurementDate.year == year))
							{
								if (dimension[i].familyNumberMember[j].weight > maximumWeight)
								{
									maximumWeight = dimension[i].familyNumberMember[j].weight;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			for (i = 0; i < dimension.size(); i++)
			{
				if (dimension[i].name == name)
				{
					for (j = 0; j < dimension[i].familyNumberMember.size(); j++)
					{
						if (count == 1)
						{
							maximumWeight = dimension[i].familyNumberMember[j].weight;
							count = 0;
						}
						else
						{
							if (dimension[i].familyNumberMember[j].weight > maximumWeight)
							{
								maximumWeight = dimension[i].familyNumberMember[j].weight;
							}
						}
					}
				}
			}
		}
		return maximumWeight;
	}
	void SaveScalesInFile()
	{
		int i, j;
		ofstream file;
		file.open("Scales.txt");
		file << "Start date: " << weightStartDate << endl;
		for (i = 0; i < dimension.size(); i++)
		{
			for (j = 0; j < dimension[i].familyNumberMember.size(); j++)
			{
				file << dimension[i].name << " " << setw(2) << setfill('0') << dimension[i].familyNumberMember[j].measurementDate.day << "." << setw(2) << setfill('0') << dimension[i].familyNumberMember[j].measurementDate.month << "." << dimension[i].familyNumberMember[j].measurementDate.year << " " << dimension[i].familyNumberMember[j].weight << endl;;
			}
		}
		file.close();
	}
	void ReadScalesFile()
	{
		int i, j, l, cout = 1, countDate = 0, countLoadData = 0, day = 0, month = 0, year = 0;
		double weight;
		string str, subStr, strName, strDate, strWeight;
		ifstream file;
		file.open("Scales.txt");
		size = 0;
		dimension.clear();
		while (getline(file, str))
		{
			if (cout == 1)
			{
				for (l = 0; l < str.size(); l++) {
					if ((str[l] >= 'a' && str[l] <= 'z') || (str[l] >= 'A' && str[l] <= 'Z') || (str[l] == ' ') || (str[l] == ':'))
					{
						str.erase(l, 1);
						l--;
					}
				}
				for (l = 0; l < str.size(); l++)
				{
					if (str[l] != '.')
					{
						subStr += str[l];
					}
					else if (str[l] == '.' && countDate == 0)
					{
						weightStartDate.day = stoi(subStr);
						countDate++;
						subStr.clear();
					}
					else if (str[l] == '.' && countDate == 1)
					{
						weightStartDate.month = stoi(subStr);
						countDate++;
						subStr.clear();
					}
				}
				weightStartDate.year = stoi(subStr);
				countDate = 0;
				subStr.clear();
				cout = 0;
			}
			else
			{
				istringstream newStr(str);
				newStr >> strName;
				newStr >> strDate;
				newStr >> strWeight;
				for (l = 0; l < strDate.size(); l++)
				{
					if (strDate[l] != '.')
					{
						subStr += strDate[l];
					}
					else if (strDate[l] == '.' && countDate == 0)
					{
						day = stoi(subStr);
						countDate++;
						subStr.clear();
					}
					else if (strDate[l] == '.' && countDate == 1)
					{
						month = stoi(subStr);
						countDate++;
						subStr.clear();
					}
				}
				year = stoi(subStr);
				countDate = 0;
				subStr.clear();
				if (CheckFamilyMember(strName) != true)
				{
					SetFamilyMember(strName);
				}
				for (i = 0; i < dimension.size(); i++)
				{
					if (dimension[i].name == strName)
					{
						weight = round(stod(strWeight) * 100) / 100;
						dimension[i].SetObservation(day, month, year, weight);
					}
				}
			}
		}
		file.close();
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	bool end = true;
	int indexMenu, indexFunction, day, month, year;
	string name;
	double weight;
	Scales weightScale;
	cout << "����� ����������!" << endl;
	while (end)
	{
		cout << "\n��������� �����: \n" << "1. �������� ����� �����;\n" << "2. ���������� ��������� ���� ����������;\n" << "3. ������ ��������� ���� ����������;\n" << "4. ������ ����������;\n"
			<< "5. ������ ��� � ��������� ����������;\n" << "6. ����� ������� ��� ����� ����� � ��������� ������ ��� �� ��� ������� ����������;\n"
			<< "7. ����� ����������� ��� ����� ����� � ��������� ������ ��� �� ��� ������� ���������� � ����, ����� �� ����������;\n"
			<< "8. ����� ������������ ��� ����� ����� � ��������� ������ ��� �� ��� ������� ���������� � ����, ����� �� ����������;\n"
			<< "9. ��������� ������� ���������� � ����;\n" << "10. ������� ������� ���������� �� �����;\n"
			<< "0. ����� �� ���������.\n" << endl;
		cout << "�������� ����� ����: ";
		cin >> indexMenu;
		switch (indexMenu)
		{
			case 1:
			{
				if (weightScale.GetSizePersonalData() == 5)
				{
					cout << "������� ������������ ���������� ������ �����! �������� 5 �������." << endl;
				}
				else
				{
					cout << "������� ��� ����� �����: ";
					cin >> name;
					weightScale.SetFamilyMember(name);
				}
				break;
			}
			case 2:
			{
				cout << "������� ���� ������� (dd.mm.year/08.03.2000): ";
				cin >> day;
				cin.ignore();
				cin >> month;
				cin.ignore();
				cin >> year;
				weightScale.SetWeightStartDate(day, month, year);
				break;
			}
			case 3:
			{
				if (weightScale.GetWeightStartDate().day == 0 && weightScale.GetWeightStartDate().month == 0 && weightScale.GetWeightStartDate().year == 0)
				{
					cout << "��������� ���� ���������� ��� �� ���� �����������!" << endl;
				}
				else
				{
					cout << "��������� ���� ����������: " << weightScale.GetWeightStartDate() << endl;
				}
				break;
			}
			case 4:
			{
				if ((weightScale.GetSizePersonalData() == 0) && (weightScale.GetWeightStartDate().day == 0 && weightScale.GetWeightStartDate().month == 0 && weightScale.GetWeightStartDate().year == 0))
				{
					cout << "�������� ���� �� ������ ��������, ����� ������� ���������� ��� ���������� ��������� ���� ����������! " << endl;
					break;
				}
				else
				{
					cout << "������� ��� ����� �����: ";
					cin >> name;
					if (weightScale.CheckFamilyMember(name) == true)
					{
						cout << "������� ���� ������� (dd.mm.year/08.03.2000): ";
						cin >> day;
						cin.ignore();
						cin >> month;
						cin.ignore();
						cin >> year;
						if (weightScale.CheckDate(day, month, year) == true)
						{
							cout << "������� ���: ";
							cin >> weight;
							weight = round(weight * 100) / 100;
							weightScale.SetObservationMember(name, day, month, year, weight);
						}
						else
						{
							cout << "���� ���������� �� ����� ���� ������ ���� ������ ����������! " << endl;
						}
						break;
					}
					else
					{
						cout << "������ ���� ����� �� ������, ���������� ���������� ��� ���!" << endl;
						break;
					}
				}
			}
			case 5:
			{
				if (weightScale.GetSizePersonalData() == 0)
				{
					cout << "����������� ������ � ������ �����. " << endl;
					break;
				}
				else
				{
					cout << "������� ��� ����� �����: ";
					cin >> name;
					if (weightScale.CheckFamilyMember(name) == true)
					{
						cout << "������� ���� ������� (dd.mm.year/08.03.2000): ";
						cin >> day;
						cin.ignore();
						cin >> month;
						cin.ignore();
						cin >> year;
						if (weightScale.GetObservationMember(name, day, month, year) == 0)
						{
							cout << "���� ����� �� ������, ����������, ���������� ��� ���! " << endl;
							break;
						}
						else
						{
							cout << "��� � ������ ����������: " << weightScale.GetObservationMember(name, day, month, year) << endl;
							break;
						}
					}
					else
					{
						cout << "������ ���� ����� �� ������, ���������� ���������� ��� ���!" << endl;
						break;
					}
				}
			}
			case 6:
			{
				cout << "������� ��� ����� �����: ";
				cin >> name;
				if (weightScale.CheckFamilyMember(name) == true)
				{
					cout << "\n�������� �����: \n" << "1. ����� �� ��������� �����;\n" << "2. ����� �� ��� ������� ����������;\n" << endl;
					cout << "������� �����: ";
					cin >> indexFunction;
					if (weightScale.GetSizePersonalData() == 0)
					{
						cout << "����������� ���������� � ����� �����! " << endl;
						break;
					}
					else
					{
						switch (indexFunction)
						{
							case 1:
							{
								cout << "������� ���� ������� (mm.year/03.2000): ";
								cin >> month;
								cin.ignore();
								cin >> year;
								cout << "������� ��� �� ��������� �����: " << weightScale.SearchAverageWeight(name, month, year, indexFunction) << "��. " << endl;
								break;
							}
							case 2:
							{
								cout << "������� ��� �� ��� ������� ����������: " << weightScale.SearchAverageWeight(name, month, year, indexFunction) << "��. " << endl;
								break;
							}
							default:
							{
								cout << "������ ����� �� ������, ����������, ���������� ��� ���! " << endl;
								break;
							}
						}
					}
				}
				else
				{
					cout << "������ ���� ����� �� ������, ���������� ���������� ��� ���!" << endl;
					break;
				}
			}
			case 7:
			{
				cout << "������� ��� ����� �����: ";
				cin >> name;
				if (weightScale.CheckFamilyMember(name) == true)
				{
					cout << "\n�������� �����: \n" << "1. ����� �� ��������� �����;\n" << "2. ����� �� ��� ������� ����������;\n" << endl;
					cout << "������� �����: ";
					cin >> indexFunction;
					if (weightScale.GetSizePersonalData() == 0)
					{
						cout << "����������� ���������� � ����� �����! " << endl;
						break;
					}
					else
					{
						switch (indexFunction)
						{
							case 1:
							{
								cout << "������� ���� ������� (mm.year/03.2000): ";
								cin >> month;
								cin.ignore();
								cin >> year;
								cout << "����������� ��� �� ��������� �����: " << weightScale.SearchMinimalWeight(name, month, year, indexFunction) << "��. " << endl;
								break;
							}
							case 2:
							{
								cout << "����������� ��� �� ��� ������� ����������: " << weightScale.SearchMinimalWeight(name, month, year, indexFunction) << "��. " << endl;
								break;
							}
							default:
							{
								cout << "������ ����� �� ������, ����������, ���������� ��� ���! " << endl;
								break;
							}
						}
					}
				}
				else
				{
					cout << "������ ���� ����� �� ������, ���������� ���������� ��� ���!" << endl;
					break;
				}
			}
			case 8:
			{
				cout << "������� ��� ����� �����: ";
				cin >> name;
				if (weightScale.CheckFamilyMember(name) == true)
				{
					cout << "\n�������� �����: \n" << "1. ����� �� ��������� �����;\n" << "2. ����� �� ��� ������� ����������;\n" << endl;
					cout << "������� �����: ";
					cin >> indexFunction;
					if (weightScale.GetSizePersonalData() == 0)
					{
						cout << "����������� ���������� � ����� �����! " << endl;
						break;
					}
					else
					{
						switch (indexFunction)
						{
							case 1:
							{
								cout << "������� ���� ������� (mm.year/03.2000): ";
								cin >> month;
								cin.ignore();
								cin >> year;
								cout << "������������ ��� �� ��������� �����: " << weightScale.SearchMaximumWeight(name, month, year, indexFunction) << "��. " << endl;
								break;
							}
							case 2:
							{
								cout << "������������ ��� �� ��� ������� ����������: " << weightScale.SearchMaximumWeight(name, month, year, indexFunction) << "��. " << endl;
								break;
							}
							default:
							{
								cout << "������ ����� �� ������, ����������, ���������� ��� ���! " << endl;
								break;
							}
						}
					}
				}
				else
				{
					cout << "������ ���� ����� �� ������, ���������� ���������� ��� ���!" << endl;
					break;
				}
			}
			case 9:
			{
				weightScale.SaveScalesInFile();
				cout << "������ ��������� � ����! " << endl;
				break;
			}
			case 10:
			{
				weightScale.ReadScalesFile();
				cout << "������ ��������� �� �����! " << endl;
				break;
			}
			case 0:
			{
				cout << "�� ��������! ������� ��� ��������������� ����� ����������!\n" << endl;
				end = false;
				break;
			}
			default:
			{
				cout << "������ ����� ���� �� ������, ���������� ��� ���!" << endl << endl;
				break;
			}
		}
	}
	system("pause");
	return 0;
}