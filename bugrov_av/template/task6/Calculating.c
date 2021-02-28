#include<stdio.h>
#include<math.h>
#define pi 3.14159265358979323846
#define T 2*pi
#include "all.h"
int proverka(db acc, db x, db Teilor, operation etalon)
{
	if (acc < 0.000001)
		return 1;
	x = etalon(x);
	x -= Teilor;
	if (x < 0.0)
		x *= -1.0;
	return (x > acc) ? 1 : 0;
}
sum polinom(db acc, int count, db x, operation etalon)
{
	long long int i;
	long long fact = 1;//факториал
	sum Teilor;//значение ряда Тейлора
	int (*do_it)(db, db, db, operation) = proverka;
	db n;//для факториала (чтобы использовать факториал некого числа)
	db a;//слагаемое в формуле Тейлора
	Teilor.count = 0;//количество вычисленных слагаемых
	db minus = -1.0;//для знака слагаемого
	if (etalon == cos || etalon == sin || etalon == atanh || etalon == atan || etalon == sinh || etalon == cosh)
	{
		db sec = x;//второе значение икс для использования в проверке
		if (etalon == cos || etalon == sin)
			x = fmod(x, T);
		if (etalon == cos || etalon == cosh)
		{
			a = 1;
			n = 0.0;
		}
		else
		{
			n = 1;
			a = x;
		}
		Teilor.s = a;
		if (etalon == atanh)
			for (i = 1, n = 3.0; i <= count && do_it(acc, sec, Teilor.s, etalon); i++, n += 2.0)
			{
				x *= sec * sec;
				Teilor.count++;
				a = x / n;
				Teilor.s += a;
			}
		else
			if (etalon == atan)
			{
				for (i = 1, n = 3.0; i <= count && do_it(acc, sec, Teilor.s, etalon); i++, n += 2)
				{
					x *= sec * sec;
					Teilor.count++;
					a = (minus * x) / n;
					Teilor.s += a;
					minus *= -1.0;
				}
			}
			else
			{
				if (etalon == cosh || etalon == sinh)
					minus = 1.0;
				for (i = 1, n; i <= count && do_it(acc, sec, Teilor.s, etalon); i++, n += 2.0)
				{
					Teilor.count++;
					a *= (minus * x * x) / ((n + 1) * (n + 2));
					Teilor.s += a;
				}
			}
	}
	else
	{
		Teilor.s = 1.0;
		a = 1.0;
		if (etalon == exp || etalon == log)
		{
			if (etalon == exp)
				for (i = 1; i <= count && do_it(acc, x, Teilor.s, etalon); i++)
				{
					Teilor.count++;
					a *= x / i;
					Teilor.s += a;
				}
			else
			{//из интернета узнал, что логарифм не должен быть точным по ряду Меркатора
				//я пробовал другой способ, но там точность с увеличением числа слагаемых уменьшается
				const db x1 = x;
				const db sec = x + 1.0;//второе значение икс для использования в проверке
				a = x;
				Teilor.s = x;
				for (i = 1; i <= count && do_it(acc, sec, Teilor.s, etalon); i++)
				{
					Teilor.count++;
					x *= x1;
					a *= (minus * x) / (i + 1);
					Teilor.s += a;
					a *= i + 1;
				}
			}
		}
		else
		{
			const db sec = x + 1.0;//второе значение икс для использования в проверке
			Teilor.count--;
			for (i = 0; i <= count && do_it(acc, sec, Teilor.s, etalon); i++)
			{
				Teilor.count++;
				a *= x * (0.5 - i) / (i + 1);
				Teilor.s += a;
			}
		}
	}
	return Teilor;
}
