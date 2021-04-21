
#include "all.h"

NominalValues::NominalValues(const int quantity)
{
	int tmpNominalValues[6] = { 5000, 2000, 1000, 500, 200 , 100 };
	for (size_t i = 0; i < 6; i++)
		pack.push_back(QuantityOfNominalValue(tmpNominalValues[i], quantity));
}

NominalValues::NominalValues(const NominalValues& NomVal)
{
	pack = NomVal.pack;
}

int NominalValues::sum()
{
	int sum = 0;
	for (QuantityOfNominalValue& tmp : pack)
		sum += tmp.GetSum();
	return sum;
}

ostream& operator<< (ostream& out, const QuantityOfNominalValue& information)
{
	out << information.ValueOfMoney << " ���. - " << information.quantity << "��.\n";
	return out;
}
