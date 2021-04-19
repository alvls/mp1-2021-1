#pragma once

struct QuantityOfNominalValue
{
    int ValueOfMoney;
    int quantity;

    // Сумма
    int sum() { return ValueOfMoney * quantity; }

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

    // Операторы
    QuantityOfNominalValue operator[] (const int ind) { return pack.at(ind); }
    // Перегрузить operator=, чтобы не было проблем
};
