#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	NominalValues cassettes;
	ProcessingCenter* pCenter; // Указатель будет присвоен, поэтому в деструкторе не нужно использовать delete
	OneCard* pCard; // Указатель будет присвоен, поэтому в деструкторе не нужно использовать delete
	NominalValues AdditionalCassette; // Дополнительная кассета, в которую будут сохраняться деньги 
	bool AccessToFunct; // Доступ к функционалу для карты, находящейся в банкомате
public:
	//Конструктор
	CashMachine(ProcessingCenter* _data);

	bool IsCardOpen() { return pCard == nullptr ? false : true; } // Возвращает есть ли карта в банкомате
	bool IsCodeEntered() { return AccessToFunct; }
	bool IsCardBlocked() { return pCenter->IsCardBlocked(pCard); }

	// Получить карту от клиента 
	void SetCard(int id);

	// Проверка PIN-кода
	bool CheckPINcode(int code, int & CurrentAttempts);

	// Вернуть карту клиенту
	void BackCard();

	// Заблокировать карту
	void BlockCard() { pCenter->BlockCard(pCard); }

	// Изменение денежных средств
	void TakeMoney(NominalValues add);
	NominalValues GiveMoney(const int value);

	// Операторы
	friend ostream& operator<< (ostream& out, const CashMachine& box);
};
