#pragma once

bool menu(); //Меню

void CheckingForExistence(Calendar& list); //Проверяет на возможность существования последнее созданное событие

void MemoryAssistant(Calendar& list); //Следит за потребностью в дополнительной памяти, если нужно, удваивает выделяемую память

void rezhim1(Calendar& list); //Реализация получения информации от пользователя для 1 режима

void rezhim2(Calendar& list); //Реализация получения информации от пользователя для 2 режима

void rezhim3(Calendar& list); //Реализация получения информации от пользователя для 3 режима

void rezhim4(Calendar& list); //Реализация получения информации от пользователя для 4 режима
