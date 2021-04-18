
#include "all.h"

ostream& operator<< (ostream& out, const QuantityOfNominalValue& information)
{
	out << information.ValueOfMoney << " руб. - " << information.quantity << "шт.\n";
	return out;
}

NominalValues::NominalValues(const int quantity)
{
	int tmpNominalValues[6] = { 5000, 2000, 1000, 500, 200 , 100 };
	for (size_t i = 0; i < 6; i++)
	{
		QuantityOfNominalValue tmp;
		tmp.ValueOfMoney = tmpNominalValues[i];
		tmp.quantity = quantity;
		pack.push_back(tmp);
	}
}
