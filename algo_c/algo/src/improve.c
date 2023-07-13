/***********************************************************
	improve.c -- �����̉��ǖ@
***********************************************************/

/***** �K���ȗ������[�`�� *********************************/

#include <limits.h>
static unsigned long seed = 1;

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

#define POOLSIZE  97  /* ���Ƃ��� */
static double pool[POOLSIZE];

void init_better_rnd(void)
{
	int i;

	for (i = 0; i < POOLSIZE; i++) pool[i] = rnd();
}

double better_rnd(void)
{
	static int i = POOLSIZE - 1;
	double r;

	i = (int)(POOLSIZE * pool[i]);
	r = pool[i];  pool[i] = rnd();
	return r;
}

/**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	unsigned long i, n;
	double r, s1, s2, x, x0, xprev;

	printf("�����̎�? ");  scanf("%lu", &i);
	init_rnd(i);  /* �C�ӂ� unsigned long �ŏ�����. */
	printf("��? ");  scanf("%lu", &n);

	init_better_rnd();
	s1 = x0 = xprev = better_rnd() - 0.5;  s2 = x0 * x0;  r = 0;
	for (i = 1; i < n; i++) {
		x = better_rnd() - 0.5;
		s1 += x;  s2 += x * x;  r += xprev * x;  xprev = x;
	}
	r = (n * (r + x * x0) - s1 * s1) / (n * s2 - s1 * s1);

	printf("�ȉ��͊��Ғl�Ƃ̍���W���덷�Ŋ���������.\n");
	printf("20��19��́}2�ȓ��ɓ���͂�.\n");
	printf("���ϒl�c�c�c�c�c�c %6.3f\n", s1 * sqrt(12.0 / n));
	printf("�ד��m�̑��֌W���c %6.3f\n",
		((n - 1) * r + 1) * sqrt((n + 1.0) / (n * (n - 3.0))));

	return EXIT_SUCCESS;
}
