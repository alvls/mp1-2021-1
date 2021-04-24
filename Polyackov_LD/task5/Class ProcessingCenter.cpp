
#include "all.h"

// private:
// ������� �� ������

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

// �����������

ProcessingCenter::ProcessingCenter()
{
	fstream fs;
	fs.open("Data.txt", fstream::in);
	if (!fs.is_open())
		throw exception("�� ������� ��������� � �������� ��� ��������� ����������!");
	ReadFromStream(fs);
	fs.close();
}

// ����� �����

OneCard* ProcessingCenter::GetCard(int id)
{
	for (size_t i = 0; i < DataCenter.size(); i++)
		if (id == DataCenter[i].GetCardID())
			return &DataCenter[i];
	return nullptr;
}

// ������������� �����

void ProcessingCenter::BlockCard(OneCard* card)
{
	card->BlockCard();
	SaveInFile();
}

// ��������� �������� �������

void ProcessingCenter::AddMoney(const int value, OneCard* card)
{
	card->AddMoney(value);
	SaveInFile();
}

void ProcessingCenter::CheckDeductMoney(const int value, OneCard* card)
{
	if (card->GetMoney() < value)
		throw exception("������������ ������� �� ����� ��� ���������� ������ ��������!");
}

void ProcessingCenter::DeductMoney(const int value, OneCard* card)
{
	card->DeductMoney(value);
	SaveInFile();
}

// ��������� � ����

void ProcessingCenter::SaveInFile()
{
	fstream fs;
	fs.open("Data.txt", fstream::out);
	if (!fs.is_open())
		throw exception("�� ������� ��������� � �������� ��� ��������� ����������!");
	fs << *this;
	fs.close();
}

// ���������

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
