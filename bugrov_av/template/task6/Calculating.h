#ifndef __CALCULATING_H__
#define __CALCULATING_H__
#define _CRT_SECURE_NO_WARNINGS
#define pi 3.14159265358979323846
#define T 2*pi
#include "all.h"
int proverka(db acc, db x, db Teilor, operation etalon);
sum polinom(db acc, int count, db x, db(*etalon)(db));
#endif
