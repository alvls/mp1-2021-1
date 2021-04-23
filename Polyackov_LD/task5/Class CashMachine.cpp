
#include "all.h"

CashMachine::CashMachine(ProcessingCenter* _data)
{
	pCenter = _data;
	pCard = nullptr;
	cassettes = NominalValues(SIZECASSETTE);
	AdditionalCassette = NominalValues();
	AccessToFunct = false;
}

// Получить карту от клиента 

void CashMachine::SetCard(int id)
{
	pCard = pCenter->GetCard(id);
	if (pCard == nullptr)
		throw exception("Ошибка считывания id карты");
}

//Проверка PIN-кода

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

// Изменение денежных средств
void CashMachine::TakeMoney(NominalValues add)
{
	int value = add.GetSum();
	int quantity = add.GetQuantity();
	if (quantity == 0 || quantity > MAXQUANTITY || AdditionalCassette.GetQuantity() + quantity > SIZECASSETTE)
		throw exception("Ошибка получения купюр!");
	for (size_t i = 0; i < AdditionalCassette.NumOfElements(); i++)
		AdditionalCassette[i].AddQuantity(add[i].GetQuantity());
	pCenter->AddMoney(value, pCard);
}

NominalValues CashMachine::GiveMoney(const int value)  // Добавить реализацию получения купюр
{
	if (value % 100 != 0)
		throw exception("Банкомат не может выдать данную сумму!");
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
	out << "\n Владелец:\n\n " << box.pCard->GetName() << "\n\n ID ***" << box.pCard->GetCardID() % 10 << "\n\n Баланс:\n\n " << box.pCard->GetMoney() << " руб.";
	return out;
}

CashMachine::~CashMachine()
{
	delete pCenter;
	delete pCard;
}
