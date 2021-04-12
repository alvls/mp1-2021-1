#pragma once

class CashMachine
{
private:
	enum { MAXQUANTITY = 40 , SIZECASSETTE = 2000 };
	int size100, size200, size500, size1000, size2000, size5000, AdditionalSize;
	ProcessingCenter* pData;
	OneCard* pCard;
public:
	//�����������
	CashMachine(ProcessingCenter* _data);

	bool IsOpenCard() { return pCard == nullptr ? false : true; } // ���������� ���� �� ����� � ���������

	void SetCard(int);

	//�������� PIN-����
	bool CheckPINcode(int);

	// ������� ����� �������
	void BackCard() { pCard = nullptr; }

	// ������������� �����
	void BlockCard() { pData->BlockCard(pCard); }

	// ��������� �������� �������
	void AddMoney(const unsigned int value) { pData->AddMoney(value, pCard); } // �������� ���������� ��������� �����
	void DeductMoney(const unsigned int value) { pData->DeductMoney(value, pCard); } // �������� ���������� ��������� �����

	//�������� �����

	//����������
	~CashMachine();
};

// ������� � �������������� ������ ������ �������, ���������� � ���� ��������� �� ������ �����
// � ��� �� �������������� ����� ������������ ��� ��������, � �� ��������
// �������� �������� ���� ������ �� �����-�� ��������
