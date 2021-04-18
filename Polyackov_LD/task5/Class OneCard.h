#pragma once

struct Name
{
    string surname;
    string name;
    string patronymic;
};

class OneCard
{
private:
    Name fullname;
    int cardID;
    int PINcode;
    int money;
    bool locked;
public:
    //������������
    OneCard();

    //�������
    Name GetName() { return fullname; }
    int GetCardID() { return cardID; }
    int GetPINcode() { return PINcode; }
    int GetMoney() { return money; }
    bool GetLocked() { return locked; }

    // ��������� �������� �������
    void AddMoney(const int value) { money += value; }
    void DeductMoney(const int value) { money -= value; }

    //���������� �����
    void BlockCard() { locked = true; }

    //���������
    friend istream& operator>> (istream& in, OneCard& information);
    friend ostream& operator<< (ostream& out, const OneCard& information);
};

