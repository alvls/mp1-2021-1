
#include "all.h"

ProcessingCenter::ProcessingCenter()
{
	fstream fs;
	fs.open("Data.txt", fstream::in);
	if (!fs.is_open())
		throw exception("�� ������� ��������� � �������� ��� ��������� ����������!");
	while (!fs.eof())
	{
		OneCard tmpcard;
		fs.clear();
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

void ProcessingCenter::BlockCard(OneCard* card)
{
	card->ChangeLockedStatus();
}

//��������� PIN-���
bool ProcessingCenter::CheckPIN(int tmpPIN,OneCard* card)
{
	return card->GetPINcode() == tmpPIN ? true : false;
}
