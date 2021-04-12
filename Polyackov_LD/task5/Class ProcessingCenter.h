#pragma once

class ProcessingCenter
{
private:
	vector<OneCard> DataCenter;
public:
	// Конструктор
	ProcessingCenter();

	// Поиск карты
	OneCard* GetCard(int);

	bool IsBlockedCard(OneCard* card) { return card->GetLocked(); }

	// Заблокировать карту
	void BlockCard(OneCard* card) { card->BlockCard(); }

	//Проверить PIN-код
	bool CheckPIN(int tmpPIN, OneCard* card) { return card->GetPINcode() == tmpPIN ? true : false; }

	// Изменение денежных средств
	void AddMoney(const unsigned int value, OneCard* card) { card->AddMoney(value); }
	void DeductMoney(const unsigned int value, OneCard* card) { card->DeductMoney(value); }

	// Сохранить в файл
	void SaveInFile();

	// Геттер
	vector<OneCard> GetDataCenter() { return DataCenter; }
	// Оператор
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
	friend ostream& operator<< (ostream& out, const ProcessingCenter& data);
	friend istream& operator>> (istream& in, ProcessingCenter& data);

};
