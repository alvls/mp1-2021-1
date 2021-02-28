#ifndef __SCREEN_H__
#define __SCREEN_H__
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "all.h"
void menu();
db db_cleaner(db min);
int cleaner(int min, int max);
operation choice();
void mode(int a);
#endif
