#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	vector<QuantityOfMoney> sizes;
	ProcessingCenter* pCenter;
	OneCard* pCard;
	int AdditionalSize; // �������������� �������, � ������� ����� ����������� ������ 
	bool AccessToFunct; // ������ � �����������
public:
	//�����������
	CashMachine(ProcessingCenter* _data);

	bool IsOpenCard() { return pCard == nullptr ? false : true; } // ���������� ���� �� ����� � ���������
	bool IsCodeEntered() { return AccessToFunct; }
	bool IsBlockedCard() { return pCenter->IsBlockedCard(pCard); }

	void SetCard(int id);

	//�������� PIN-����
	bool CheckPINcode(int code, int & CurrentAttempts);

	// ������� ����� �������
	void BackCard();

	// ������������� �����
	void BlockCard() { pCenter->BlockCard(pCard); }

	// ��������� �������� �������
	void AddMoney(const unsigned int value) { pCenter->AddMoney(value, pCard); } // �������� ���������� ��������� �����
	void DeductMoney(const unsigned int value) { pCenter->DeductMoney(value, pCard); } // �������� ���������� ��������� �����

	//�������� �����

	//����������
	~CashMachine();
};

// ������� � �������������� ������ ������ �������, ���������� � ���� ��������� �� ������ �����
// � ��� �� �������������� ����� ������������ ��� ��������, � �� ��������
// �������� �������� ���� ������ �� �����-�� ��������
