#pragma once

void cleaner(); // Очищает поток ввода

int GetDigit();

int GetNumber(const int NumberOfDigits, const bool IsEnterActive = true, const int TypeOfWrite = 0);

void gotoxy(const int x, const int y);

void PrintStatus(const int type = 0);

void PrintCashMachine();

void waiting();

void PrintMenu();
