#pragma once

void cleaner(); // Очищает поток ввода

int GetDigit(const char LeftBound = '0', const char RightBound = '9', const bool IsEnterActive = false, const bool IsBackspaceActive = false);

int GetNumber(const int NumberOfDigits, const int TypeOfRead = 0, const bool IsEnterActive = false);

void gotoxy(const int x, const int y);

void PrintStatus(const int type = 0);

void PrintCashMachine();

void waiting();

void PrintMenu();
