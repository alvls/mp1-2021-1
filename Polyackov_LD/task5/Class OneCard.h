#pragma once

class OneCard
{
private:
    Name fullname;
    int cardID;
    int PINcode;
    unsigned int money;
    bool locked;
public:
    //������������
    OneCard();

    //�������
    Name GetName() { return fullname; }
    int GetCardID() { return cardID; }
    int GetPINcode() { return PINcode; }
    unsigned int GetMoney() { return money; }
    bool GetLocked() { return locked; }

    // ��������� �������� �������
    void AddMoney(const unsigned int value) { money += value; }
    void DeductMoney(const unsigned int value) { money -= value; }

    //���������� �����
    void BlockCard() { locked = true; }

    //��������
    friend istream& operator>> (istream& in, OneCard& information);
    friend ostream& operator<< (ostream& out, const OneCard& information);

};

