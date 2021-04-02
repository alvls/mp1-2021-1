#include "All.h"
bool contact::operator!=(const contact& other)
{
	if (name != other.name || surname != other.surname || patronymic != other.patronymic)
		return true;
	else
		return false;
}
bool contact:: operator==(const contact& other)
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
bool contact::operator>(const contact& other)
{
	if (surname > other.surname)
		return true;
	else
		if (surname < other.surname)
			return false;
		else
			if (name > other.name)
				return true;
			else
				if (name < other.name)
					return false;
				else
					if (patronymic > other.patronymic)
						return true;
					else
						return false;
}// для сортировки
contact::contact(string sur, string nam, string pat, char* _phone, char* _birth): name(nam), surname(sur), patronymic(pat)
{
	if (_phone == nullptr)
	{
		for (int i = 0; i < number; i++)
			phone[i] = '0';
	}
	else
		for (int i = 0; i < number; i++)
			phone[i] = _phone[i];
	if (_birth == nullptr)
	{
		birth[0] = '0';
		birth[1] = '1';
		for (int i = 2; i < date; i++)
			birth[i] = '0';
	}
	else
		for (int i = 0; i < date; i++)
			birth[i] = _birth[i];
	favorite = false;
}
ostream& operator<<(ostream& place, const contact& c)
{
	// Достаточно вывести данные, понятные только программе
	place << c.surname << " ";
	place << c.name << " ";
	place << c.patronymic << " ";
	for (int i = 0; i < number; i++)
		place << c.phone[i];
	int b1 = c.birth[2] - '0';
	int b2 = c.birth[3] - '0';
	int m = b1 * 10 + b2;
	cout << "\nДата рождения: ";
	cout << c.birth[0] << c.birth[1] << " " << month[m] << " ";
	for (int i = 4; i < date; i++)
		cout << c.birth[i];
	cout << " " << "года\n";
	if (c.favorite)
		cout << "Контакт обавлен в избранные\n";
	return place;
}
void contact::contact_menu()
{
	bool repeat;
	bool badsymb;
	int pointer;
	int c;
	system("CLS");
	enum contactdata
	{
		_surname,
		_name,
		_patronymic,
		_phone,
		_birth,
		_favorite
	};
	contactdata point = _surname;
	bool notfound;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((DARKGRAY << 4) | YELLOW));
	do
	{
		notfound = false;
		badsymb = true;
		switch (point)
		{
		case _surname:
			break;
		case _name:
			break;
		case _patronymic:
			break;
		case _phone:
			break;
		case _birth:
			break;
		case _favorite:
			break;
		default:
			break;
		}
		cout << surname << "\n";
		cout << name << "\n";
		cout << patronymic << "\n";
		for (int i = 0; i < number; i++)
			cout << phone[i];
		int b1 = birth[2] - '0';
		int b2 = birth[3] - '0';
		int m = b1 * 10 + b2;
		cout << "\nДата рождения: ";
		cout << birth[0] << birth[1] << " " << month[m] << " ";
		for (int i = 4; i < date; i++)
			cout << birth[i];
		cout << " " << "года\n";
		if (favorite)
			cout << "Контакт добавлен в избранные\n";
		while (badsymb)
		{
			c = _getch();
			switch (c)
			{
			case a: case A:
				break;
			default:
				break;
			}
		}
		repeat = false;
	} while (repeat);
}
void contact::printc()
{
	cout << surname << " ";
	cout << name << " ";
	cout << patronymic << " ";
	for (int i = 0; i < number; i++)
		cout << phone[i];
	cout << endl;
}