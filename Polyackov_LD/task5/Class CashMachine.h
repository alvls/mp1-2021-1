#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	NominalValues cassettes;
	ProcessingCenter* pCenter;
	OneCard* pCard;
	NominalValues AdditionalSize; // Дополнительная кассета, в которую будут сохраняться деньги 
	bool AccessToFunct; // Доступ к функционалу для карты, находящейся в банкомате
public:
	//Конструктор
	CashMachine(ProcessingCenter* _data);

	bool IsOpenCard() { return pCard == nullptr ? false : true; } // Возвращает есть ли карта в банкомате
	bool IsCodeEntered() { return AccessToFunct; }
	bool IsBlockedCard() { return pCenter->IsBlockedCard(pCard); }

	// Получить карту от клиента 
	void SetCard(int id);

	// Проверка PIN-кода
	bool CheckPINcode(int code, int & CurrentAttempts);

	// Вернуть карту клиенту
	void BackCard();

	// Заблокировать карту
	void BlockCard() { pCenter->BlockCard(pCard); }

	// Изменение денежных средств
	void TakeMoney(const NominalValues add);
	NominalValues GiveMoney(const unsigned int value);

	// Операторы
	friend ostream& operator<< (ostream& out, const CashMachine& box);

	//Деструктор
	~CashMachine();
};
