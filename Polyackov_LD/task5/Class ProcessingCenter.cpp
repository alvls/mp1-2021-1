
#include "all.h"

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

ProcessingCenter::ProcessingCenter()
{
	fstream fs;
	fs.open("Data.txt", fstream::in);
	if (!fs.is_open())
		throw exception("Не удалось связаться с сервером для получения информации!");
	ReadFromStream(fs);
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
		throw exception("Не удалось связаться с сервером для обработки информации!");
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
	return data.ReadFromStream(in);
}
