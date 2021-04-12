#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	int size100, size200, size500, size1000, size2000, size5000, AdditionalSize;
	ProcessingCenter* pCenter;
	OneCard* pCard;
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
