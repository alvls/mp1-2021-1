#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	NominalValues cassettes;
	ProcessingCenter* pCenter;
	OneCard* pCard;
	NominalValues AdditionalSize; // �������������� �������, � ������� ����� ����������� ������ 
	bool AccessToFunct; // ������ � ����������� ��� �����, ����������� � ���������
public:
	//�����������
	CashMachine(ProcessingCenter* _data);

	bool IsOpenCard() { return pCard == nullptr ? false : true; } // ���������� ���� �� ����� � ���������
	bool IsCodeEntered() { return AccessToFunct; }
	bool IsBlockedCard() { return pCenter->IsBlockedCard(pCard); }

	// �������� ����� �� ������� 
	void SetCard(int id);

	// �������� PIN-����
	bool CheckPINcode(int code, int & CurrentAttempts);

	// ������� ����� �������
	void BackCard();

	// ������������� �����
	void BlockCard() { pCenter->BlockCard(pCard); }

	// ��������� �������� �������
	void TakeMoney(const NominalValues add);
	NominalValues GiveMoney(const unsigned int value);

	// ���������
	friend ostream& operator<< (ostream& out, const CashMachine& box);

	//����������
	~CashMachine();
};
