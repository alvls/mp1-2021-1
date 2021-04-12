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
    bool GetLocked() { return locked; }

    // Изменение денежных средств
    void AddMoney(const unsigned int value) { money += value; }
    void DeductMoney(const unsigned int value) { money -= value; }

    //Блокировка карты
    void BlockCard() { locked = true; }

    //Оператор
    friend istream& operator>> (istream& in, OneCard& information);
    friend ostream& operator<< (ostream& out, const OneCard& information);

};

