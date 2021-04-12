
#include "all.h"

CashMachine::CashMachine(ProcessingCenter* _data)
{
	pData = _data;
	pCard = nullptr;
	AdditionalSize = 0;
	size100 = size200 = size500 = size1000 = size2000 = size5000 = SIZECASSETTE;
}

CashMachine::~CashMachine()
{
	delete pData;
	delete pCard;
}

void CashMachine::SetCard(int id) // Проверка на заблокированность карты
{
	pCard = pData->GetCard(id);
	if (pCard == nullptr)
		throw exception(" Ошибка считывания id карты");
}

bool CashMachine::CheckPINcode(int code)
{
	static int attempts = 1;
	if (pData->CheckPIN(code, pCard))
	{
		attempts = 1;
		return true;
	}
	else
		attempts++;
	if (attempts == 3)
		BlockCard();
}
