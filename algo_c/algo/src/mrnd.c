/***********************************************************
	mrnd.c -- M�n�񗐐�
***********************************************************/
#define M32(x)  (((1UL << 32) - 1) & (x))
static int jrnd;
static unsigned long x[521];

static void rnd521(void)
{
	int i;

	for (i =  0; i <  32; i++) x[i] ^= x[i + 489];
	for (i = 32; i < 521; i++) x[i] ^= x[i -  32];
}

void init_rnd(unsigned long seed)
{
	int i, j;
	unsigned long u;

	u = 0;
	for (i = 0; i <= 16; i++) {
		for (j = 0; j < 32; j++) {
			seed = seed * 1566083941UL + 1;
			u = (u >> 1) | (seed & (1UL << 31));
		}
		x[i] = u;
	}
	x[16] = M32(x[16] << 23) ^ (x[0] >> 9) ^ x[15];
	for (i = 17; i <= 520; i++)
		x[i] = M32(x[i-17] << 23) ^ (x[i-16] >> 9) ^ x[i-1];
	rnd521();  rnd521();  rnd521();  /* warm up */
	jrnd = 520;
}

unsigned long irnd(void)
{
	if (++jrnd >= 521) {  rnd521();  jrnd = 0;  }
	return x[jrnd];
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
	return (1.0 / (((1UL << 32) - 1) + 1.0)) * irnd();
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
	init_rnd(i);  /* �C�ӂ� unsigned long �ŏ�����. �ȗ��s��. */
	printf("��? ");  scanf("%lu", &n);

	s1 = x0 = xprev = rnd() - 0.5;  s2 = x0 * x0;  r = 0;
	for (i = 1; i < n; i++) {
		x = rnd() - 0.5;
		s1 += x;  s2 += x * x;  r += xprev * x;  xprev = x;
	}
	r = (n * (r + x * x0) - s1 * s1) / (n * s2 - s1 * s1);

	printf("�ȉ��͊��Ғl�Ƃ̍���W���덷�Ŋ���������.\n");
	printf("���ρ@�@: %.3f\n", s1 * sqrt(12.0 / n));
	printf("���֌W��: %.3f\n", (r+1.0/(n-1)) * sqrt((double)n));

	return EXIT_SUCCESS;
}
