
#include "all.h"

// private:
// Считать из потока

istream& ProcessingCenter::ReadFromStream(istream& in)
{
	while (true)
	{
		OneCard tmpcard;
		in >> tmpcard;
		if (in.eof())
			break;
		DataCenter.push_back(tmpcard);
	}
	return in;
}

// Конструктор

ProcessingCenter::ProcessingCenter()
{
	fstream fs;
	fs.open("Data.txt", fstream::in);
	if (!fs.is_open())
		throw exception("Не удалось связаться с сервером для получения информации!");
	ReadFromStream(fs);
	fs.close();
}

// Поиск карты

OneCard* ProcessingCenter::GetCard(int id)
{
	for (size_t i = 0; i < DataCenter.size(); i++)
		if (id == DataCenter[i].GetCardID())
			return &DataCenter[i];
	return nullptr;
}

// Заблокировать карту

void ProcessingCenter::BlockCard(OneCard* card)
{
	card->BlockCard();
	SaveInFile();
}

// Изменение денежных средств

void ProcessingCenter::AddMoney(const int value, OneCard* card)
{
	card->AddMoney(value);
	SaveInFile();
}

void ProcessingCenter::CheckDeductMoney(const int value, OneCard* card)
{
	if (card->GetMoney() < value)
		throw exception("Недостаточно средств на счёте для проведения данной операции!");
}

void ProcessingCenter::DeductMoney(const int value, OneCard* card)
{
	card->DeductMoney(value);
	SaveInFile();
}

// Сохранить в файл

void ProcessingCenter::SaveInFile()
{
	fstream fs;
	fs.open("Data.txt", fstream::out);
	if (!fs.is_open())
		throw exception("Не удалось связаться с сервером для обработки информации!");
	fs << *this;
	fs.close();
}

// Операторы

ostream& operator<< (ostream& out, const ProcessingCenter& data)
{
	for (size_t i = 0; i < data.DataCenter.size(); i++)
		out << data.DataCenter[i];
	return out;
}

istream& operator>> (istream& in, ProcessingCenter& data)
{
	data.DataCenter.clear();
	return data.ReadFromStream(in);
}
