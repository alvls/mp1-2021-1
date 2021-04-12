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

	bool IsBlockedCard(OneCard* card) { return card->GetLocked(); }

	// ������������� �����
	void BlockCard(OneCard* card) { card->BlockCard(); }

	//��������� PIN-���
	bool CheckPIN(int tmpPIN, OneCard* card) { return card->GetPINcode() == tmpPIN ? true : false; }

	// ��������� �������� �������
	void AddMoney(const unsigned int value, OneCard* card) { card->AddMoney(value); }
	void DeductMoney(const unsigned int value, OneCard* card) { card->DeductMoney(value); }

	// ��������� � ����
	void SaveInFile();

	// ������
	vector<OneCard> GetDataCenter() { return DataCenter; }
	// ��������
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
	friend ostream& operator<< (ostream& out, const ProcessingCenter& data);
	friend istream& operator>> (istream& in, ProcessingCenter& data);

};
