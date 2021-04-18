#pragma once

struct QuantityOfNominalValue
{
    int ValueOfMoney;
    int quantity;

    // Сумма
    int Sum() { return ValueOfMoney * quantity; }

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

    // Добавить метод, подсчитывающий сумму всех денег

    // Операторы
    QuantityOfNominalValue operator[] (const int ind) { return pack.at(ind); }
    // Перегрузить operator=, чтобы не было проблем
};
