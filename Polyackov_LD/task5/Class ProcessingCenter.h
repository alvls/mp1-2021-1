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

	// Геттер
	vector<OneCard> GetDataCenter() { return DataCenter; }
	// Оператор
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
};
