#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	NominalValues cassettes;
	ProcessingCenter* pCenter; // ��������� ����� ��������, ������� � ����������� �� ����� ������������ delete
	OneCard* pCard; // ��������� ����� ��������, ������� � ����������� �� ����� ������������ delete
	NominalValues AdditionalCassette; // �������������� �������, � ������� ����� ����������� ������ 
	bool AccessToFunct; // ������ � ����������� ��� �����, ����������� � ���������
public:
	//�����������
	CashMachine(ProcessingCenter* _data);

	bool IsCardOpen() { return pCard == nullptr ? false : true; } // ���������� ���� �� ����� � ���������
	bool IsCodeEntered() { return AccessToFunct; }
	bool IsCardBlocked() { return pCenter->IsCardBlocked(pCard); }

	// �������� ����� �� ������� 
	void SetCard(int id);

	// �������� PIN-����
	bool CheckPINcode(int code, int & CurrentAttempts);

	// ������� ����� �������
	void BackCard();

	// ������������� �����
	void BlockCard() { pCenter->BlockCard(pCard); }

	// ��������� �������� �������
	void TakeMoney(NominalValues add);
	NominalValues GiveMoney(const int value);

	// ���������
	friend ostream& operator<< (ostream& out, const CashMachine& box);
};
