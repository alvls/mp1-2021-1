
#include "all.h"

CashMachine::CashMachine(ProcessingCenter* _data)
{
	pCenter = _data;
	pCard = nullptr;
	cassettes = NominalValues(SIZECASSETTE);
	AdditionalSize = NominalValues();
	AccessToFunct = false;
}

// �������� ����� �� ������� 

void CashMachine::SetCard(int id) // �������� �� ����������������� �����
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
void CashMachine::TakeMoney(const NominalValues add)
{
	int value = 0;
	int quantity = 0;
	for (size_t i = 0; i < 6; i++)
	{
		//value += add[i].ValueOfMoney * add[i].quantity;
		//quantity += add[i].quantity;
	}
	// �������� �������� �� SIZECASSETTE
	if (quantity == 0 || quantity > MAXQUANTITY)
		throw exception(" ������ ��������� �����!");
	pCenter->AddMoney(value, pCard);
}

NominalValues CashMachine::GiveMoney(const unsigned int value)  // �������� ���������� ��������� �����
{
	if (value % 100 != 0)
		throw exception(" �������� �� ����� ������ ������ �����!");
	pCenter->CheckDeductMoney(value, pCard);
	NominalValues tmpvec;
	//for (size_t i = 0; i < )
	//�������� ����� �� ������ �����
	//������� for, � ������� ����� ���������� ����������� tmpvec - ���� ������, �� �������� tmpvec
	//���� ��� ����������� ������ ���� �������, ������� ����������
	pCenter->DeductMoney(value, pCard);
	return tmpvec;
}

ostream& CashMachine::cheque(ostream& out)
{
	out << pCard->GetMoney();
	return out;
}

CashMachine::~CashMachine()
{
	delete pCenter;
	delete pCard;
}
