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
    //Конструкторы
    OneCard();

    //Геттеры
    Name GetName() { return fullname; }
    int GetCardID() { return cardID; }
    int GetPINcode() { return PINcode; }
    int GetMoney() { return money; }
    bool GetLocked() { return locked; }

    // Изменение денежных средств
    void AddMoney(const int value) { money += value; }
    void DeductMoney(const int value) { money -= value; }

    //Блокировка карты
    void BlockCard() { locked = true; }

    //Операторы
    friend istream& operator>> (istream& in, OneCard& information);
    friend ostream& operator<< (ostream& out, const OneCard& information);
};

