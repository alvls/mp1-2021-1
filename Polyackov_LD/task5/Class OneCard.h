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

    //��������
    friend istream& operator>> (istream& in, OneCard datacenter);
};

