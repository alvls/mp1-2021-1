
#include "all.h"

ProcessingCenter::ProcessingCenter()
{
	fstream fs;
	fs.open("Data.txt", fstream::in);
	if (!fs.is_open())
		throw exception("Не удалось связаться с сервером для получения информации!");
	size_t tmpsize;
	fs >> tmpsize;
	OneCard tmpcard;
	for (size_t i = 0; i < tmpsize; i++)
	{
		fs >> tmpcard;
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
