//����������� ������ ��������������� ����� � ����������� �������� ������.
//����� ��������������� ����� ������ ����������� ������ ����� �� ������� ������� �� ������ ������ �������� � ������.
//�������, ��� ������� ������� ���������� �� ������ � �������� 30 ���� �� ������� ����.
//�������, ��� �� �������� ������ �������� � ������ ��������� ��� ���������� ������ ���������, ���� ��������� � ���� ������ ����� � ����� � ������ �����������.
//��� ������ � ������� ��������� ��������� � �������� �� 100 ������� ����.
///� ��������� � ������ ������� ������ ���� ����� : 
///�����������(27 �������, 27 ������ ����),
///��������(18 �������, 18 ������ ����), 
///��(18 ������ ����).
//����� ������� � ������� ��������� � 8. 
///� ��������� ������
/// - 2 ������ ��, 
/// - 6 �������� �������, 
/// - 4 ����������� ������.
///� ������ ������ � 4 �������� ������, 8 ����������� �������.
//������ ���������������� ��������(������ ������� �� ��������� �� 1 �� 100), ������ � ��������(����� ����� �� 1 �� 12), ����� � ��������(����� ����� �� 1 �� ��������� ��� ������� ���� ������).
//���������� � ���� ������� � ���� ��������� ������� �������� � ������ ����������� �������� ������.��� ������� ������, ������� ���� ������ � ������� ���� ����� ����������� ��������� ������.
//�������, ��� ��� ������ �� ������ ������������� ��������� �� ��������.
//����� ��������������� ����� ������ ������������� ��������� �������� : 
//1) ������� ������ ���������� : ����, �����, ��� ������(���� ���� �����), ���������� ������� ������� ���������� ����(���� ���� �����), ��� ���������� 
//2) ��������� ������� ��������� ���� �� ������� ����������(��� ������������� ������ ��� ������ � ����� ������, ������� ����� ������������), 
//3) ��������������� �����,
//4) ���������� ����� ��������� �������, 
//5) �������� ����� �������, 
//6) ������������ ������(������ ����� �������� : ����, ����� ������, ����� ������, ����� �����, ��� ���������, ������� �����������, ������� ��������).
//����� ����������� �������� ������ ������ �������������� ��� ��������� ������ ������ ��������������� ����� � ����� ���� ���������� � ���������� - ����������� ��������.
#include <vector>
#include <iostream>
using namespace std;
class firm
{
	const int COMRESSLEEP[3] = { 6,4,2 };
	int compartment[6];
	int reserved[4];
	int sleeping[2];
	friend class railway;
};
class speed
{
	const int COMRESS[3] = { 4,8 };
	int compartment[4];
	int reserved[8];
	int sleeping[2];
	friend class railway;
};
class swallow
{
	int vagon[8] = { 100,100, 100, 100, 100, 100, 100, 100 };
	friend class railway;
};
class railway
{
	const int COMPMAX = 18;
	const int RESMAX = 27;
	const int SLEEPMAX = 18;
	swallow swtrain[3];
	speed strain;
	firm ftrain;
public:
	railway()
	{
		int i, j;
		for (i = 0; i < strain.COMRESS[0]; i++)
			strain.compartment[i] = COMPMAX;
		for (i = 0; i < strain.COMRESS[1]; i++)
			strain.reserved[i] = RESMAX;
		for (i = 0; i < ftrain.COMRESSLEEP[0]; i++)
			ftrain.compartment[i] = COMPMAX;
		for (i = 0; i < ftrain.COMRESSLEEP[1]; i++)
			ftrain.reserved[i] = RESMAX;
		for (i = 0; i < ftrain.COMRESSLEEP[2]; i++)
			ftrain.reserved[i] = SLEEPMAX;

	}
};
class box_office
{

};