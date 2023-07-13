/***********************************************************
	randvect.c -- �P�ʋ���̃����_���ȓ_
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

/***** ���K���z�̗��� *************************************/

#include <math.h>

double nrnd(void)  /* ���K���z */
{
	static int sw = 0;
	static double r1, r2, s;

	if (sw == 0) {
		sw = 1;
		do {
			r1 = 2 * rnd() - 1;
			r2 = 2 * rnd() - 1;
			s = r1 * r1 + r2 * r2;
		} while (s > 1 || s == 0);
		s = sqrt(-2 * log(s) / s);
		return r1 * s;
	} else {
		sw = 0;
		return r2 * s;
	}
}

/**********************************************************/

void rnd_vect1(int n, double v[])
{
	int i;
	double r;

	do {
		r = 0;
		for (i = 0; i < n; i++) {
			v[i] = 2 * rnd() - 1;  r += v[i] * v[i];
		}
	} while (r > 1);
	r = sqrt(r);
	for (i = 0; i < n; i++) v[i] /= r;
}

void rnd_vect2(int n, double v[])
{
	int i;
	double r;

	r = 0;
	for (i = 0; i < n; i++) {
		v[i] = nrnd();  r += v[i] * v[i];
	}
	r = sqrt(r);
	for (i = 0; i < n; i++) v[i] /= r;
}

/**********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	double v[5];

	printf("�����_���ȒP�ʋ���̓_ 1\n");
	rnd_vect1(5, v);
	for (i = 0; i < 5; i++) printf("%10.5f", v[i]);
	printf("\n");

	printf("�����_���ȒP�ʋ���̓_ 2\n");
	rnd_vect2(5, v);
	for (i = 0; i < 5; i++) printf("%10.5f", v[i]);
	printf("\n");

	return EXIT_SUCCESS;
}
