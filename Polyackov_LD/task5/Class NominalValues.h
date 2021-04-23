#pragma once

class QuantityOfNominalValue
{
private:
    int ValueOfMoney;
    int quantity;
public:
    QuantityOfNominalValue(int val = 0, int q = 0) : ValueOfMoney(val), quantity(q) {}
    QuantityOfNominalValue(const QuantityOfNominalValue& other);
    // �������
    void SetValueOfMoney(int val) { ValueOfMoney = val; }

    // �������
    int GetValueOfMoney() { return ValueOfMoney; }
    int GetQuantity() { return quantity; }
    int GetSum() { return ValueOfMoney * quantity; }

    // �������� ������
    void AddQuantity(int value) { quantity += value; }

    // ���������
    friend ostream& operator<< (ostream& out, const QuantityOfNominalValue& information);
    QuantityOfNominalValue& operator= (const QuantityOfNominalValue& other);
};

class NominalValues
{
private:
    vector<QuantityOfNominalValue> pack;
public:
    // �����������
    NominalValues(const int quantity = 0);
    NominalValues(const NominalValues& other);

    // �������

    // �����, ���������� � pack
    int GetSum();

    // ���������� �����, ���������� � pack
    int GetQuantity();

    size_t NumOfElements() { return pack.size(); }

    // �������� ������ � ���������
    void AddQuantity(size_t ind, int value = 1) { pack[ind].AddQuantity(value); }

    // ���������
    QuantityOfNominalValue& operator[] (const size_t ind) { return pack[ind]; }
    NominalValues& operator= (const NominalValues& other);
    friend ostream& operator<< (ostream& out, const NominalValues& information);
};
