#pragma once

class QuantityOfNominalValue
{
private:
    int ValueOfMoney;
    int quantity;
public:
    QuantityOfNominalValue(int val = 0, int q = 0) : ValueOfMoney(val), quantity(q) {}
    // �������
    void SetValueOfMoney(int val) { ValueOfMoney = val; }
    void SetQuantity(int q) { quantity = q; }

    // �������
    int GetValueOfMoney() { return ValueOfMoney; }
    int GetQuantity() { return quantity; }
    int GetSum() { return ValueOfMoney * quantity; }

    // ���������
    friend ostream& operator<< (ostream& out, const QuantityOfNominalValue& information);
};

class NominalValues
{
private:
    vector<QuantityOfNominalValue> pack;
public:
    // �����������
    NominalValues(const int quantity = 0);
    NominalValues(const NominalValues& NomVal);

    // �����, ���������� � pack
    int sum();

    size_t size() { return pack.size(); }

    // ���������
    QuantityOfNominalValue operator[] (const size_t ind) { return pack[ind]; }
    // ����������� operator=, ����� �� ���� �������
};
