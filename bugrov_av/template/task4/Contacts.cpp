#include <iostream>
#include <string>
using namespace std;
//����������� ����� ��������.
//����� ������ ������� ���������� � ��������� ���������.
//������ ������� �������� ��������� ������ : 
//�������; 
//���;
//��������;
//�������;
//���� ��������(����, �����, ���);
//�������, ��������� �� ������� � ���������.
//�������� �������� ������������ �� �������, �����, ��������.
//�������, ���, ��������(���) �������� ������������� ������.������ �������� �� ������� �����.
//����� ������ ��������� ����������� ��������� ������.
//����� ������ ������������� ��������� �������� : 
//1) ������� ����� �������,
//2) �������� ��������� �������, 
//3) ����� ������� �� ���,
//4) ����� ������� �� ��������, 
//5) ������ ��� �������� �� �������� �����, 
//6) ������ ������� ����� ���������, 
//7) ������ ������� � ������ ���������,
//8) ������� ������� �� ������ ���������,
//9) ������ ��� ��������� ��������, 
//10) ������� �������, 
//11) ��������� �������� � ����, 
//12) ������� �������� �� �����.
//�������� �� ������ ��������� ���� � �� �� ���	
const string month[12] = { "������", "�������", "����", "������", "���", "����", "������", "��������", "�������", "������", "�������" };
const int number = 12;//����� �������� � ������ ��������
const int date = 8;//����� �������� � ���� ��������
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
//����� �������� ��� ������� �������, ����� ���� � ������, �������� �� ���
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
	//������ ����� �������
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
	//�������� ��������� �������
	void change_contact(contact dif)
	{

	}
	//����� ������� �� ���
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
	//����� ������� �� ��������
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
	//������ �������� �� ������ �����
	string* letter_get()
	{

	}
	//������� ����� ���������
	int getk()
	{
		return k;
	}
	/// <summary>
	///
	/// </summary>
	/// ������� ������� ���������
	void favour(contact )
	{
		
	}
	//������� �� ���������
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
	//������� ��� ��������� ��������???
	contact* getfav()
	{
		int i;
		int n=0;//���������� ��������� ���������
		for (i = 0; i < k; i++)
		{
			if (man[i].favorite)
				n++;
		}

	}
	//������� �������
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
