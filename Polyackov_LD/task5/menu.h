#pragma once

bool menu(CashMachine&); //Меню

void OpenCard(CashMachine& box);
void EnterPINcode(CashMachine& box);

//Реализация режимов

void mode1(CashMachine&);
void mode2(CashMachine&);
void mode3(CashMachine&);
void mode4(CashMachine&);
