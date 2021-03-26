#include <iostream>
#include <string>
using namespace std;
//Разработать класс Контакты.
//Класс должен хранить информацию о контактах владельца.
//Каждый контакт содержит следующие данные : 
//фамилия; 
//имя;
//отчество;
//телефон;
//день рождения(день, месяц, год);
//признак, относится ли контакт к избранным.
//Контакты хранятся упорядоченно по фамилии, имени, отчеству.
//Фамилия, имя, отчество(ФИО) являются обязательными полями.Данные вводятся на русском языке.
//Класс должен содержать необходимые служебные методы.
//Класс должен предоставлять следующие операции : 
//1) создать новый контакт,
//2) изменить выбранный контакт, 
//3) найти контакт по ФИО,
//4) найти контакт по телефону, 
//5) выдать все контакты на заданную букву, 
//6) узнать текущее число контактов, 
//7) внести контакт в список избранных,
//8) удалить контакт из списка избранных,
//9) выдать все избранные контакты, 
//10) удалить контакт, 
//11) сохранить контакты в файл, 
//12) считать контакты из файла.
//КОНТАКТЫ НЕ ДОЛЖНЫ СОДЕРЖАТЬ ОДНО И ТО ЖЕ ФИО	
const string month[12] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
const int number = 12;//число символов в номере телефона
const int date = 8;//число символов в дате рождения
struct contact
{
	string name;
	string surname;
	string patronymic;
	char phone[number];
	bool favorite = false;
	char birth[date];
	bool operator==(const contact& other)
	{
		bool ans = true;
		if (name == other.name && surname == other.surname && patronymic == other.patronymic)
		{
			/*for (int i = 0; i < number; i++)
			{
				if (phone[i] != other.phone[i])
				{
					ans = false;
					break;
				}
			}
			for (int i = 0; i < date && ans; i++)
			{
				if(birth[i]!=other.birth[i])
				{
					ans = false;
					break;
				}
			}*/
			return ans;
		}
		return false;
	}
	bool operator!=(const contact& other)
	{
		if (name != other.name || surname != other.surname || patronymic != other.patronymic)
			return true;
		else
			return false;
	}
};
//Нужна проверка для номеров месяцев, числа дней в месяце, проверка на год
class Contacts
{
	/*string* name;
	string* surname;
	string* patronymic;
	char* phone;
	bool* favorite;
	int birth[8];*/
	contact* man;
	int k;
	void sort();
public:
	Contacts()
	{
		k = 0;
		man = nullptr;
		//name = surname = patronymic = nullptr;
	}
	~Contacts()
	{
		k = 0;
		delete[] man;
	}
	//Создаёт новый контакт
	void newcontact(contact extra)
	{
		int i;
		contact* tmp = new contact[k + 1];
		for (i = 0; i < k; i++)
		{
			tmp[i] = man[i];
		}
		tmp[i] = extra;
		k++;
		man = new contact[k];
		for (i = 0; i < k; i++)
		{
			man[i] = tmp[i];
		}
		delete[] tmp;
	}
	//Изменить выбранный контакт
	void change_contact(contact dif)
	{

	}
	//Найти контакт по ФИО
	contact& findfio(string*, int quan = 3)
	{
		switch (quan)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
		}
	}
	//Найти контакт по телефону
	contact find_phone(char* _phone)
	{
		int j;
		int i;
		bool found = false;
		for (i = 0; i < k; i++)
		{
			for (j = 0; j < number; j++)
				if (man[i].phone[j] != _phone[j])
					break;
			if (j >= number)
			{
				found = true;
				break;
			}
		}
		if (found)
			return man[i];
		//else//////////////////////////////////////////
	}
	//Выдать контакты на данную букву
	string* letter_get()
	{

	}
	//Вывести число контактов
	int getk()
	{
		return k;
	}
	/// <summary>
	///
	/// </summary>
	/// Сделать контакт избранным
	void favour(contact )
	{
		
	}
	//Удалить из избранных
	void dis_favor(contact dis)
	{
		for (int i = 0; i < k; i++)
		{
			if (man[i] == dis)
			{
				man[i].favorite = false;
			}
		}
	}
	//Вывести все избранные контакты???
	contact* getfav()
	{
		int i;
		int n=0;//количество избранных контактов
		for (i = 0; i < k; i++)
		{
			if (man[i].favorite)
				n++;
		}

	}
	//Удалить контакт
	void _delete(contact deleted)
	{
		int i, j = 0, num;
		contact* tmp = new contact[k-1];
		for (i = 0; i < k; i++)
			if (man[i] != deleted)
			{
				tmp[j] = man[i];
				j++;
			}
			else
				num = i;
		k--;
		man = new contact[k];
		for (i = 0; i < k; i++)
		{
			man[i] = tmp[i];
		}
		delete[] tmp;
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
}
