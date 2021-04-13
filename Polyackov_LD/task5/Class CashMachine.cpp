
#include "all.h"

CashMachine::CashMachine(ProcessingCenter* _data)
{
	pCenter = _data;
	pCard = nullptr;
	int tmpNominalValues[6] = { 100, 200, 500, 1000, 2000, 5000 };
	for (size_t i = 0; i < 6; i++)
	{
		QuantityOfMoney tmp;
		tmp.ValueOfMoney = tmpNominalValues[i];
		tmp.quantity = SIZECASSETTE;
		sizes.push_back(tmp);
	}
	AdditionalSize = 0;
	AccessToFunct = false;
}

CashMachine::~CashMachine()
{
	delete pCenter;
	delete pCard;
}

void CashMachine::SetCard(int id) // Проверка на заблокированность карты
{
	pCard = pCenter->GetCard(id);
	if (pCard == nullptr)
		throw exception(" Ошибка считывания id карты");
}

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

// Вернуть карту клиенту
void CashMachine::BackCard()
{
	pCard = nullptr; 
	AccessToFunct = false;
}
