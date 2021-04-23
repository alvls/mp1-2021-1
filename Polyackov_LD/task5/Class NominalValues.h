#pragma once

class QuantityOfNominalValue
{
private:
    int ValueOfMoney;
    int quantity;
public:
    QuantityOfNominalValue(int val = 0, int q = 0) : ValueOfMoney(val), quantity(q) {}
    QuantityOfNominalValue(const QuantityOfNominalValue& other);
    // Сеттеры
    void SetValueOfMoney(int val) { ValueOfMoney = val; }

    // Геттеры
    int GetValueOfMoney() { return ValueOfMoney; }
    int GetQuantity() { return quantity; }
    int GetSum() { return ValueOfMoney * quantity; }

    // Добавить купюры
    void AddQuantity(int value) { quantity += value; }

    // Операторы
    friend ostream& operator<< (ostream& out, const QuantityOfNominalValue& information);
    QuantityOfNominalValue& operator= (const QuantityOfNominalValue& other);
};

class NominalValues
{
private:
    vector<QuantityOfNominalValue> pack;
public:
    // Конструктор
    NominalValues(const int quantity = 0);
    NominalValues(const NominalValues& other);

    // Геттеры

    // Сумма, хранящаяся в pack
    int GetSum();

    // Количество купюр, хранящихся в pack
    int GetQuantity();

    size_t NumOfElements() { return pack.size(); }

    // Добавить купюру в хранилище
    void AddQuantity(size_t ind, int value = 1) { pack[ind].AddQuantity(value); }

    // Операторы
    QuantityOfNominalValue& operator[] (const size_t ind) { return pack[ind]; }
    NominalValues& operator= (const NominalValues& other);
    friend ostream& operator<< (ostream& out, const NominalValues& information);
};
