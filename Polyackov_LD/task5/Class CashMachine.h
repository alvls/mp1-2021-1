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

	bool GetStatus() { return pCard == nullptr ? true : false; } // Возвращает есть ли карта в банкомате

	void SetCard(int);

	//Получить карту

	//Деструктор
	~CashMachine();
};
