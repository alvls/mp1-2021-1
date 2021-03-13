#pragma once

class Calendar
{
private:
	int size;
	int counter;
	Date* arr; //Для хранения событий
public:
	//Конструктор
	Calendar();

	//Конструктор копирования
	Calendar(const Calendar& other);

	//Геттеры
	int GetSize() { return size; }
	int GetCounter() { return counter; }

	//Сеттеры
	void SetCounterPlusOne() { counter++; }

	//Вывод на экран 
	void PrintCalendar();

	//Проерка на существование последнего добавленного события
	int ExistLastDate();

	//Удаление последнего добавленного события
	void DeleteLastDate();

	//Увеличение памяти
	void Calendar::AddMemory();

	//Операторы
	Calendar& operator= (const Calendar& other);
	Date& operator[] (const int index);

	//Деструктор
	~Calendar();
};
