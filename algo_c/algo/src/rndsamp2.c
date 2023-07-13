/***********************************************************
	rndsamp2.c -- ����ג��o
***********************************************************/

/***** ��l���� (���`�����@) ******************************/

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

#include <stdio.h>

int rndsamp(int m, int s[])
{
	int i, n, x;

	n = 0;
	while (scanf("%d", &x) == 1) {
		if (++n <= m) s[n - 1] = x;
		else {
			i = (int)(n * rnd());
			if (i < m) s[i] = x;
		}
	}
	return n;
}

#include <stdlib.h>
#include <time.h>
#define M 1000

int main()
{
	int i, n, m;
	static int s[M];

	init_rnd((unsigned long) time(NULL));
	fprintf(stderr, "�W�����͂���, �W�{�̑傫���ƕ�W�c�̗v�f (�����l)"
		"��ǂݍ���, �W���o�͂ɕW�{�̗v�f���o�͂��܂�.\n");
	if (scanf("%d", &m) != 1) return EXIT_FAILURE;
	fprintf(stderr, "�W�{�̑傫�� = %d\n", m);
	if (m > M) {
		fprintf(stderr, "�W�{�̑傫���� %d �ȉ��łȂ���΂Ȃ�܂���\n", M);
		return EXIT_FAILURE;
	}
	n = rndsamp(m, s);
	fprintf(stderr, "��W�c�̑傫�� = %d\n", n);
	for (i = 0; i < m && i < n; i++)
		printf("%8d", s[i]);
	printf("\n");

	return EXIT_SUCCESS;
}
