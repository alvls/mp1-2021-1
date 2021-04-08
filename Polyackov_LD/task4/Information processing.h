#pragma once

int check(int a, int b); //Проверяет введённые числа + защищает от ввода посторонних символов

size_t check(size_t a, size_t b); //Проверяет введённые числа + защищает от ввода посторонних символов

void cleaner(); // Очищает поток ввода

bool leap(int month, int year); // Проверка на високосность

int MonthDays(int month, int year); //Возвращает количество дней в месяце

OneDay CreateNewOneDay(); // Записать информацию в новый день

Date CreateNewDate(); // Создать новую дату

Count CreateNewCount(); // Создать новый подсчёт

Time CreateTimeBound(); // Создать новые временные границы
