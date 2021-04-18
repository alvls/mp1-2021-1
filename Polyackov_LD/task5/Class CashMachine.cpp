
#include "all.h"

CashMachine::CashMachine(ProcessingCenter* _data)
{
	pCenter = _data;
	pCard = nullptr;
	cassettes = NominalValues(SIZECASSETTE);
	AdditionalSize = NominalValues();
	AccessToFunct = false;
}

// Получить карту от клиента 

void CashMachine::SetCard(int id) // Проверка на заблокированность карты
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
void CashMachine::TakeMoney(const NominalValues add)
{
	int value = 0;
	int quantity = 0;
	for (size_t i = 0; i < 6; i++)
	{
		//value += add[i].ValueOfMoney * add[i].quantity;
		//quantity += add[i].quantity;
	}
	// Добавить проверку на SIZECASSETTE
	if (quantity == 0 || quantity > MAXQUANTITY)
		throw exception(" Ошибка получения купюр!");
	pCenter->AddMoney(value, pCard);
}

NominalValues CashMachine::GiveMoney(const unsigned int value)  // Добавить реализацию получения купюр
{
	if (value % 100 != 0)
		throw exception(" Банкомат не может выдать данную сумму!");
	pCenter->CheckDeductMoney(value, pCard);
	NominalValues tmpvec;
	//for (size_t i = 0; i < )
	//Добавить магию на выдачу денег
	//Двойной for, в котором будет постепенно заполняться tmpvec - если ошибка, то сбросить tmpvec
	//Если нет возможности отдать даже сотнями, бросить исключение
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
