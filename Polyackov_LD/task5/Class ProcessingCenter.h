#pragma once

class ProcessingCenter
{
private:
	vector<OneCard> DataCenter;
	//Считать из файла
	istream& ReadFromStream(istream& in);
public:
	// Конструктор
	ProcessingCenter();

	// Поиск карты
	OneCard* GetCard(int);

	bool IsBlockedCard(OneCard* card) { return card->GetLocked(); }

	// Заблокировать карту
	void BlockCard(OneCard* card) { card->BlockCard(); } // Добавить сохранение в файл

	//Проверить PIN-код
	bool CheckPIN(int tmpPIN, OneCard* card) { return card->GetPINcode() == tmpPIN ? true : false; }

	// Изменение денежных средств
	void AddMoney(const unsigned int value, OneCard* card) { card->AddMoney(value); } // Добавить сохранение в файл
	void DeductMoney(const unsigned int value, OneCard* card) { card->DeductMoney(value); } //Добавить обработку возможности вычитания суммы // Добавить сохранение в файл

	// Сохранить в файл
	void SaveInFile();

	// Геттер
	vector<OneCard> GetDataCenter() { return DataCenter; }
	// Оператор
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
	friend ostream& operator<< (ostream& out, const ProcessingCenter& data);
	friend istream& operator>> (istream& in, ProcessingCenter& data);

};
