#include <math.h>
#include "all.h"
void head(double x, operation funk)
{
	int i;
	printf("============================ РЕЗУЛЬТАТ =============================\n");
	printf("\nЭталонное значение, вычисленное профессионалами: ");
	if (funk == sqrt || funk == log)
		printf("%lf\n\n", funk(x + 1.0));
	else
		printf("%lf\n\n", funk(x));
	printf("ЧИСЛО СЛАГАЕМЫХ");
	for (i = 0; i < 5; i++)
		printf(" ");
	printf("ЗНАЧЕНИЕ РЯДА");
	for (i = 0; i < 5; i++)
		printf(" ");
	printf("МОДУЛЬ РАЗНОСТИ");
	printf("\n");
	for (i = 0; i < 23; i++)
		printf(" ");
	printf("ТЕЙЛОРА");
	for (i = 0; i < 8; i++)
		printf(" ");
	printf("РЯДА И ЭТАЛОНА");
	printf("\n");
}
void printer(int count, db x, db Teilor, db(*etalon)(db))
{
	int i;
	db module;// модуль разности эталонного значения и оценки значения функции
	int sec = count;//для расчёта отступа
	long long secT = Teilor;//для больших значений суммы получить хороший пробел
	int mod_gap;//пробел для модуля
	secT = abs(secT);
	if (etalon != sqrt && etalon != log)
		module = etalon(x);
	else
		module = etalon(1 + x);
	module -= Teilor;
	if (module < 0.0)
		module *= -1;
	for (i = 0; i < 5; i++)
		printf(" ");
	for (i = 0; sec > 0; i++)
		sec /= 10;
	for (sec = 0; sec <= 3 - i; sec += 2)
		printf(" ");
	printf("%d", count);/////////////////////////////////сделано написание count
	if (3 - i)
		printf(" ");
	sec = 5;
	i = 1;
	while (secT >= 100000)
	{
		secT /= 10;
		if (i % 2)
			sec--;
		i++;
	}
	if (Teilor < 0.0)
		sec--;
	mod_gap = sec;
	if (count > 999)
		sec--;
	for (i = 0; i < sec; i++)
		printf(" ");
	secT = (int)Teilor;
	if (secT < 0)
		secT *= -1;
	if (secT == 0)
		secT++;
	for (i = 0; secT > 0; i++)
		secT /= 10;
	for (sec = 0; sec <= 16 - i / 2; sec += 2)
	{
		printf(" ");
		if (!(sec % 2))
			mod_gap--;
	}
	printf("%0.6lf", Teilor);/////////////////////////////////сделано написание Teilor
	for (sec = 0; sec < 13 - i; sec += 2)
		printf(" ");
	sec = (int)module;
	for (i = 0; sec > 0; i++)
		sec /= 10;
	for (sec = 0; sec <= 7 - i; sec += 2)
		printf(" ");
	printf("%-1.6lf", module);///////////////////////////////сделано полностью написание
	printf("\n");
}