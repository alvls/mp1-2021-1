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

	// Заблокировать карту
	void BlockCard(OneCard*);

	//Проверить PIN-код
	bool CheckPIN(int, OneCard*);

	// Геттер
	vector<OneCard> GetDataCenter() { return DataCenter; }
	// Оператор
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
};
