#pragma once

struct QuantityOfNominalValue
{
    int ValueOfMoney;
    int quantity;

    // �����
    int sum() { return ValueOfMoney * quantity; }

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

    // ���������
    QuantityOfNominalValue operator[] (const int ind) { return pack.at(ind); }
    // ����������� operator=, ����� �� ���� �������
};
