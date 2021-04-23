
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
	for (size_t i = 0; i < AdditionalCassette.NumOfElements(); i++)
		AdditionalCassette[i].AddQuantity(add[i].GetQuantity());
	pCenter->AddMoney(value, pCard);
}

NominalValues CashMachine::GiveMoney(const int value)  // �������� ���������� ��������� �����
{
	if (value % 100 != 0)
		throw exception("�������� �� ����� ������ ������ �����!");
	pCenter->CheckDeductMoney(value, pCard);
	NominalValues tmpvec;
	for (size_t i = 0; i < cassettes.NumOfElements(); i++)
	{

	}
	pCenter->DeductMoney(value, pCard);
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
