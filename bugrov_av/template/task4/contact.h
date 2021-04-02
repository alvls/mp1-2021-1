#pragma once
class contact
{
	string surname;
	string name;
	string patronymic;
	char phone[number];
	bool favorite;
	char birth[date];
public:
	contact(string sur = "Ваш", string nam = "Безымянный", string pat = "Контакт", char* _phone = nullptr, char* _birth = nullptr);
	friend class List;
	bool operator==(const contact& other);
	bool operator!=(const contact& other);
	bool operator >(const contact& other);
	friend ostream& operator<<(ostream& place, const contact& c);
	void printc();
	void contact_menu();
};

