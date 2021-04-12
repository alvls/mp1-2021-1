#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	int size100, size200, size500, size1000, size2000, size5000, AdditionalSize;
	ProcessingCenter* pData;
	OneCard* pCard;
public:
	//Конструктор
	CashMachine(ProcessingCenter* _data);

	bool IsOpenCard() { return pCard == nullptr ? false : true; } // Возвращает есть ли карта в банкомате

	void SetCard(int);

	//Проверка PIN-кода
	bool CheckPINcode(int);

	// Вернуть карту клиенту
	void BackCard() { pCard = nullptr; }

	// Заблокировать карту
	void BlockCard() { pData->BlockCard(pCard); }

	// Изменение денежных средств
	void AddMoney(const unsigned int value) { pData->AddMoney(value, pCard); } // Добавить реализацию получения купюр
	void DeductMoney(const unsigned int value) { pData->DeductMoney(value, pCard); } // Добавить реализацию получения купюр

	//Получить карту

	//Деструктор
	~CashMachine();
};

// Создать в процессинговом центре нужные функции, отправлять в него указатель на нужную карту
// У нас же процессинговый центр обрабатывает все процессы, а не банкомат
// Банкомат посылает лишь запрос на какие-то действия
