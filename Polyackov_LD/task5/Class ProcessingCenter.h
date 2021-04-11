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

	// ������������� �����
	void BlockCard(OneCard*);

	//��������� PIN-���
	bool CheckPIN(int, OneCard*);

	// ������
	vector<OneCard> GetDataCenter() { return DataCenter; }
	// ��������
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
};
