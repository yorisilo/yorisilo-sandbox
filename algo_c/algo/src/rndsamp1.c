/***********************************************************
	rndsamp1.c -- ����ג��o
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i, n, m;

	init_rnd((unsigned long) time(NULL));
	printf("��W�c�̑傫��? ");  scanf("%d", &n);
	printf("�W�{�̑傫��?   ");  scanf("%d", &m);
	for (i = 0; i < n; i++)
		if ((n - i) * rnd() < m) {
			printf("%8d", i + 1);
			if (--m <= 0) break;
		}
	printf("\n");
	return EXIT_SUCCESS;
}
