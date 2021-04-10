#pragma once

void cleaner(); // Очищает поток ввода

int GetDigit(const char LeftBound = '0', const char RightBound = '9');

int GetNumber(const int NumberOfDigits, const int TypeOfRead = 0);

void gotoxy(const int x, const int y);
