#pragma once

class QuantityOfNominalValue
{
private:
    int ValueOfNominal;
    int quantity;
public:
    QuantityOfNominalValue(int val = 0, int q = 0) : ValueOfNominal(val), quantity(q) {}
    QuantityOfNominalValue(const QuantityOfNominalValue& other);
    // �������
    void SetValueOfNominal(int val) { ValueOfNominal = val; }

    // �������
    int GetValueOfNominal() { return ValueOfNominal; }
    int GetQuantity() { return quantity; }
    int GetSum() { return ValueOfNominal * quantity; }

    // �������� ������
    void AddQuantity(int value) { quantity += value; }

    // ���������
    friend ostream& operator<< (ostream& out, const QuantityOfNominalValue& information);
    QuantityOfNominalValue& operator+= (const QuantityOfNominalValue& other);
    QuantityOfNominalValue& operator-= (const QuantityOfNominalValue& other);
    friend QuantityOfNominalValue operator+ (const QuantityOfNominalValue& other1, const QuantityOfNominalValue& other2);
    friend QuantityOfNominalValue operator- (const QuantityOfNominalValue& other1, const QuantityOfNominalValue& other2);
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

    // ���������� ���������
    size_t NumOfElements() { return pack.size(); }

    // �������� �� ������������� ��������� ����
    bool is_null();

    // �������� ��� quantity � ������� ��������
    void clear() { *this -= *this; }

    // ���������
    QuantityOfNominalValue& operator[] (const size_t ind) { return pack[ind]; }
    NominalValues& operator= (const NominalValues& other);
    NominalValues& operator+= (const NominalValues& other);
    NominalValues& operator-= (const NominalValues& other);
    friend NominalValues operator+ (const NominalValues& other1, const NominalValues& other2);
    friend NominalValues operator- (const NominalValues& other1, const NominalValues& other2);
    friend ostream& operator<< (ostream& out, const NominalValues& information);
};
