
#include "all.h"

// QuantityOfNominalValue

QuantityOfNominalValue::QuantityOfNominalValue(const QuantityOfNominalValue& other)
{
	ValueOfNominal = other.ValueOfNominal;
	quantity = other.quantity;
}

QuantityOfNominalValue& QuantityOfNominalValue::operator= (const QuantityOfNominalValue& other)
{
	if (this == &other)
		return *this;
	ValueOfNominal = other.ValueOfNominal;
	quantity = other.quantity;
	return *this;
}

QuantityOfNominalValue& QuantityOfNominalValue::operator+= (const QuantityOfNominalValue& other)
{
	quantity += other.quantity;
	return *this;
}

QuantityOfNominalValue& QuantityOfNominalValue::operator-= (const QuantityOfNominalValue& other)
{
	quantity -= other.quantity;
	return *this;
}

QuantityOfNominalValue operator+ (const QuantityOfNominalValue& other1, const QuantityOfNominalValue& other2)
{
	QuantityOfNominalValue res(other1);
	res += other2;
	return res;
}

QuantityOfNominalValue operator- (const QuantityOfNominalValue& other1, const QuantityOfNominalValue& other2)
{
	QuantityOfNominalValue res(other1);
	res -= other2;
	return res;
}

ostream& operator<< (ostream& out, const QuantityOfNominalValue& information)
{
	out << information.ValueOfNominal << " руб. : " << information.quantity << " шт.\n ";
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

NominalValues& NominalValues::operator+= (const NominalValues& other)
{
	for (size_t i = 0; i < NumOfElements(); i++)
		pack[i] += other.pack[i];
	return *this;
}

NominalValues& NominalValues::operator-= (const NominalValues& other)
{
	for (size_t i = 0; i < NumOfElements(); i++)
		pack[i] -= other.pack[i];
	return *this;
}

NominalValues operator+ (const NominalValues& other1, const NominalValues& other2)
{
	NominalValues res(other1);
	res += other2;
	return res;
}

NominalValues operator- (const NominalValues& other1, const NominalValues& other2)
{
	NominalValues res(other1);
	res += other2;
	return res;
}

ostream& operator<< (ostream& out, const NominalValues& information)
{
	int i = 0;
	for (auto& tmp : information.pack)
		out << ++i << ") " << tmp;
	return out;
}

bool NominalValues::is_null()
{
	for (auto& tmp : pack)
		if (tmp.GetQuantity() != 0)
			return false;
	return true;
}
