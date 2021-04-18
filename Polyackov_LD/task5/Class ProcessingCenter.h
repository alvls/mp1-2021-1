#pragma once

class ProcessingCenter
{
private:
	vector<OneCard> DataCenter;
	//Считать из потока
	istream& ReadFromStream(istream& in);
	ProcessingCenter(const ProcessingCenter&) = delete; 
	void operator= (const ProcessingCenter&) = delete;
public:
	// Конструктор
	ProcessingCenter();

	// Поиск карты
	OneCard* GetCard(int id);

	//Проверка на заблокированность карты
	bool IsBlockedCard(OneCard* card) { return card->GetLocked(); }

	// Заблокировать карту
	void BlockCard(OneCard* card);

	// Проверить PIN-код
	bool CheckPIN(int tmpPIN, OneCard* card) { return card->GetPINcode() == tmpPIN ? true : false; }

	// Изменение денежных средств
	void AddMoney(const int value, OneCard* card);
	void CheckDeductMoney(const int value, OneCard* card);
	void DeductMoney(const int value, OneCard* card);

	// Сохранить в файл
	void SaveInFile();

	// Операторы
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
	friend ostream& operator<< (ostream& out, const ProcessingCenter& data);
	friend istream& operator>> (istream& in, ProcessingCenter& data);

};
