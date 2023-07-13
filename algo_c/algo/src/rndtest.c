/***********************************************************
	rndtest.c -- ����
***********************************************************/
/* �����̂����ȒP�ȃe�X�g */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define rnd() (1.0 / (RAND_MAX + 1.0)) * rand()

int main()
{
	unsigned seed;
	unsigned long i, n;
	double r, s1, s2, x, x0, xprev;

	printf("�����̎�? ");  scanf("%u", &seed);
	srand(seed);  /* �C�ӂ� unsigned int �ŏ�����. */
	printf("��? ");  scanf("%lu", &n);

	s1 = x0 = xprev = rnd() - 0.5;  s2 = x0 * x0;  r = 0;
	for (i = 1; i < n; i++) {
		x = rnd() - 0.5;
		s1 += x;  s2 += x * x;  r += xprev * x;  xprev = x;
	}
	r = (n * (r + x * x0) - s1 * s1) / (n * s2 - s1 * s1);

	printf("�ȉ��͊��Ғl�Ƃ̍���W���덷�Ŋ���������.\n");
	printf("20��19��́}2�ȓ��ɓ���͂�.\n");
	printf("���ϒl�c�c�c�c�c�c�c %6.3f\n", s1 * sqrt(12.0 / n));
	printf("�ׂǂ����̑��֌W���c %6.3f\n",
		((n - 1) * r + 1) * sqrt((n + 1.0) / (n * (n - 3.0))));

	return EXIT_SUCCESS;
}
