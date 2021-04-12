#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	int size100, size200, size500, size1000, size2000, size5000, AdditionalSize;
	ProcessingCenter* pCenter;
	OneCard* pCard;
	bool AccessToFunct; // Доступ к функционалу
public:
	//Конструктор
	CashMachine(ProcessingCenter* _data);

	bool IsOpenCard() { return pCard == nullptr ? false : true; } // Возвращает есть ли карта в банкомате
	bool IsCodeEntered() { return AccessToFunct; }
	bool IsBlockedCard() { return pCenter->IsBlockedCard(pCard); }

	void SetCard(int id);

	//Проверка PIN-кода
	bool CheckPINcode(int code, int & CurrentAttempts);

	// Вернуть карту клиенту
	void BackCard();

	// Заблокировать карту
	void BlockCard() { pCenter->BlockCard(pCard); }

	// Изменение денежных средств
	void AddMoney(const unsigned int value) { pCenter->AddMoney(value, pCard); } // Добавить реализацию получения купюр
	void DeductMoney(const unsigned int value) { pCenter->DeductMoney(value, pCard); } // Добавить реализацию получения купюр

	//Получить карту

	//Деструктор
	~CashMachine();
};

// Создать в процессинговом центре нужные функции, отправлять в него указатель на нужную карту
// У нас же процессинговый центр обрабатывает все процессы, а не банкомат
// Банкомат посылает лишь запрос на какие-то действия
