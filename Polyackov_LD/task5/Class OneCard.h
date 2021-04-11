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
    //Конструкторы
    OneCard();

    //Геттеры
    Name GetName() { return fullname; }
    int GetCardID() { return cardID; }
    int GetPINcode() { return PINcode; }
    unsigned int GetMoney() { return money; }

    void AddMoney(const unsigned int value);
    void DeductMoney(const unsigned int value);

    void ChangeLockedStatus();

    //Оператор
    friend istream& operator>> (istream& in, OneCard& datacenter);
};

