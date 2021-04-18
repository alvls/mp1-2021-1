#pragma once

class ProcessingCenter
{
private:
	vector<OneCard> DataCenter;
	//������� �� ������
	istream& ReadFromStream(istream& in);
	ProcessingCenter(const ProcessingCenter&) = delete; 
	void operator= (const ProcessingCenter&) = delete;
public:
	// �����������
	ProcessingCenter();

	// ����� �����
	OneCard* GetCard(int id);

	//�������� �� ����������������� �����
	bool IsBlockedCard(OneCard* card) { return card->GetLocked(); }

	// ������������� �����
	void BlockCard(OneCard* card);

	// ��������� PIN-���
	bool CheckPIN(int tmpPIN, OneCard* card) { return card->GetPINcode() == tmpPIN ? true : false; }

	// ��������� �������� �������
	void AddMoney(const int value, OneCard* card);
	void CheckDeductMoney(const int value, OneCard* card);
	void DeductMoney(const int value, OneCard* card);

	// ��������� � ����
	void SaveInFile();

	// ���������
	OneCard& operator[] (const int index) { return DataCenter.at(index); }
	friend ostream& operator<< (ostream& out, const ProcessingCenter& data);
	friend istream& operator>> (istream& in, ProcessingCenter& data);

};
