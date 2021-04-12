
#include "all.h"

ProcessingCenter::ProcessingCenter()
{
	fstream fs;
	fs.open("Data.txt", fstream::in);
	if (!fs.is_open())
		throw exception("Не удалось связаться с сервером для получения информации!");
	while (true)
	{
		OneCard tmpcard;
		fs >> tmpcard;
		if (fs.eof())
			break;
		DataCenter.push_back(tmpcard);
	}
	fs.close();
}

OneCard* ProcessingCenter::GetCard(int id)
{
	for (size_t i = 0; i < DataCenter.size(); i++)
		if (id == DataCenter[i].GetCardID())
			return &DataCenter[i];
	return nullptr;
}

void ProcessingCenter::SaveInFile()
{
	fstream fs;
	fs.open("Pedometer.txt", fstream::out);
	if (!fs.is_open())
		throw exception("Не удалось связаться с сервером для получения информации!");
	fs << this;
	fs.close();
}

ostream& operator<<(ostream& out, const ProcessingCenter& data)
{
	for (size_t i = 0; i < data.DataCenter.size(); i++)
		out << data.DataCenter[i] << "\n";
	return out;
}

istream& operator>> (istream& in, ProcessingCenter& data)
{
	data.DataCenter.clear();
	while (true)
	{
		OneCard tmpcard;
		in >> tmpcard;
		if (EOF)
			break;
		data.DataCenter.push_back(tmpcard);
	}
	return in;
}
