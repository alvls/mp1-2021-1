#pragma once

class ProcessingCenter
{
private:
	vector<OneCard> DataCenter;
public:
	// �����������
	ProcessingCenter();

	// ����� �����
	OneCard* GetCard(int);

	// ������
	vector<OneCard> GetDataCenter() { return DataCenter; }
	// ��������
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
};
