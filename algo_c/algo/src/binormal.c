/***********************************************************
	binormal.c -- 2�ϗʐ��K���z
***********************************************************/

/***** ��l���� (���`�����@) ******************************/

#include <limits.h>
static unsigned long seed = 1;  /* �C�� */

void init_rnd(unsigned long x)
{
	seed = x;
}

unsigned long irnd(void)
{
	seed = seed * 1566083941UL + 1;
	return seed;
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
	return (1.0 / (ULONG_MAX + 1.0)) * irnd();
}

/**********************************************************/

void binormal_rnd(double r, double *x, double *y)  /* 2�ϗʐ��K���z�̗��� */
{
	double r1, r2, s;

	do {
		r1 = 2 * rnd() - 1;
		r2 = 2 * rnd() - 1;
		s = r1 * r1 + r2 * r2;
	} while (s > 1 || s == 0);
	s = - log(s) / s;
	r1 = sqrt((1 + r) * s) * r1;
	r2 = sqrt((1 - r) * s) * r2;
	*x = r1 + r2;  *y = r1 - r2;
}

/**********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	double x, y;

	for (i = 0; i < 20; i++) {
		binormal_rnd(0.5, &x, &y);
		printf("%10.5f %10.5f\n", x, y);
	}
	return EXIT_SUCCESS;
}
