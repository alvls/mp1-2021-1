#pragma once

int check(int a, int b); //��������� �������� ����� + �������� �� ����� ����������� ��������

size_t check(size_t a, size_t b); //��������� �������� ����� + �������� �� ����� ����������� ��������

void cleaner(); // ������� ����� �����

bool leap(int month, int year); // �������� �� ������������

int MonthDays(int month, int year); //���������� ���������� ���� � ������

OneDay CreateNewOneDay(); // �������� ���������� � ����� ����

Date CreateNewDate(); // ������� ����� ����

Count CreateNewCount(); // ������� ����� �������

Time CreateTimeBound(); // ������� ����� ��������� �������
