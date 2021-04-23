
#include "all.h"

// QuantityOfNominalValue

QuantityOfNominalValue::QuantityOfNominalValue(const QuantityOfNominalValue& other)
{
	ValueOfMoney = other.ValueOfMoney;
	quantity = other.quantity;
}

QuantityOfNominalValue& QuantityOfNominalValue::operator= (const QuantityOfNominalValue& other)
{
	if (this == &other)
		return *this;
	ValueOfMoney = other.ValueOfMoney;
	quantity = other.quantity;
	return *this;
}

ostream& operator<< (ostream& out, const QuantityOfNominalValue& information)
{
	out << information.ValueOfMoney << " руб. : " << information.quantity << " шт.\n ";
	return out;
}

// NominalValues

NominalValues::NominalValues(const int quantity)
{
	int tmpNominalValues[6] = { 5000, 2000, 1000, 500, 200 , 100 };
	for (size_t i = 0; i < 6; i++)
		pack.push_back(QuantityOfNominalValue(tmpNominalValues[i], quantity));
}

NominalValues::NominalValues(const NominalValues& other)
{
	pack = other.pack;
}

int NominalValues::GetSum()
{
	int sum = 0;
	for (QuantityOfNominalValue& tmp : pack)
		sum += tmp.GetSum();
	return sum;
}

int NominalValues::GetQuantity()
{
	int quantity = 0;
	for (QuantityOfNominalValue& tmp : pack)
		quantity += tmp.GetQuantity();
	return quantity;
}

NominalValues& NominalValues::operator= (const NominalValues& other)
{
	if (this == &other)
		return *this;
	pack = other.pack;
	return *this;
}

ostream& operator<< (ostream& out, const NominalValues& information)
{
	int i = 0;
	for (auto& tmp : information.pack)
		out << ++i << ") " << tmp;
	return out;
}
