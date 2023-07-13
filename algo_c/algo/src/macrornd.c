/***********************************************************
	macrornd.c -- ���`�����@
***********************************************************/
/* C����̃}�N���Ŏ��������ȒP�Ȑ��`�����@����. */

#include <limits.h>
static unsigned long seed = 1;  /* � */
#define rnd() (seed *= 69069UL, seed / (ULONG_MAX + 1.0))
#define init_rnd(x) (seed = (unsigned long)(x) | 1)

/************ �ȉ��̓e�X�g�p *************************************/

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

	s1 = x0 = xprev = rnd() - 0.5;  s2 = x0 * x0;  r = 0;
	for (i = 1; i < n; i++) {
		x = rnd() - 0.5;
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
