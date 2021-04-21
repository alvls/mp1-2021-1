#pragma once

class QuantityOfNominalValue
{
private:
    int ValueOfMoney;
    int quantity;
public:
    QuantityOfNominalValue(int val = 0, int q = 0) : ValueOfMoney(val), quantity(q) {}
    // Сеттеры
    void SetValueOfMoney(int val) { ValueOfMoney = val; }
    void SetQuantity(int q) { quantity = q; }

    // Геттеры
    int GetValueOfMoney() { return ValueOfMoney; }
    int GetQuantity() { return quantity; }
    int GetSum() { return ValueOfMoney * quantity; }

    // Операторы
    friend ostream& operator<< (ostream& out, const QuantityOfNominalValue& information);
};

class NominalValues
{
private:
    vector<QuantityOfNominalValue> pack;
public:
    // Конструктор
    NominalValues(const int quantity = 0);
    NominalValues(const NominalValues& NomVal);

    // Сумма, хранящаяся в pack
    int sum();

    size_t size() { return pack.size(); }

    // Операторы
    QuantityOfNominalValue operator[] (const size_t ind) { return pack[ind]; }
    // Перегрузить operator=, чтобы не было проблем
};
