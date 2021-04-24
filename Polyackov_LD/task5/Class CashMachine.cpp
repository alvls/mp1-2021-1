
#include "all.h"

CashMachine::CashMachine(ProcessingCenter* _data)
{
	pCenter = _data;
	pCard = nullptr;
	cassettes = NominalValues(SIZECASSETTE);
	AdditionalCassette = NominalValues();
	AccessToFunct = false;
}

// �������� ����� �� ������� 

void CashMachine::SetCard(int id)
{
	pCard = pCenter->GetCard(id);
	if (pCard == nullptr)
		throw exception("������ ���������� id �����");
}

//�������� PIN-����

bool CashMachine::CheckPINcode(int code, int& CurrentAttempts)
{
	static int attempts = 0;
	if (pCenter->CheckPIN(code, pCard))
	{
		attempts = 0;
		AccessToFunct = true;
		return true;
	}
	else
		attempts++;
	CurrentAttempts = attempts;
	if (attempts == 3)
	{
		BlockCard();
		BackCard();
		attempts = 0;
	}
	return false;
}

// ������� ����� �������

void CashMachine::BackCard()
{
	pCard = nullptr; 
	AccessToFunct = false;
}

// ��������� �������� �������
void CashMachine::TakeMoney(NominalValues add)
{
	int value = add.GetSum();
	int quantity = add.GetQuantity();
	if (quantity == 0 || quantity > MAXQUANTITY || AdditionalCassette.GetQuantity() + quantity > SIZECASSETTE)
		throw exception("������ ��������� �����!");
	AdditionalCassette += add;
	pCenter->AddMoney(value, pCard);
}

NominalValues CashMachine::GiveMoney(const int value)
{
	pCenter->CheckDeductMoney(value, pCard);
	NominalValues tmpvec;
	size_t j = 0; 
	vector<int> VecOfUnusedQuantity(cassettes.NumOfElements());
	while (true)
	{
		int CurrentValue = value;
		for (size_t i = j; i < cassettes.NumOfElements(); i++)
		{
			int NominalsNeeded = CurrentValue / cassettes[i].GetValueOfNominal();
			int NominalsLeft = cassettes[i].GetQuantity();
			int quantity = NominalsLeft >= NominalsNeeded ? NominalsNeeded : NominalsLeft;
			quantity -= VecOfUnusedQuantity[i];
			if (i == j && quantity == 0)
				j++;
			tmpvec[i].AddQuantity(quantity);
			CurrentValue = value - tmpvec.GetSum();
		}
		if (CurrentValue == 0 && tmpvec.GetQuantity() <= MAXQUANTITY)
			break;
		if (tmpvec.is_null())
			throw exception("�������� �� ����� ������ ������ �����!");
		VecOfUnusedQuantity[j]++;
		tmpvec.clear();
	}
	pCenter->DeductMoney(value, pCard);
	cassettes -= tmpvec;
	return tmpvec;
}

ostream& operator<< (ostream& out, const CashMachine& box)
{
	out << "\n ��������:\n\n " << box.pCard->GetName() << "\n\n ID ***" << box.pCard->GetCardID() % 10 << "\n\n ������:\n\n " << box.pCard->GetMoney() << " ���.";
	return out;
}

CashMachine::~CashMachine()
{
	delete pCenter;
	delete pCard;
}
