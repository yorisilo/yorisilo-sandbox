/***********************************************************
	5num.c -- �ܐ��v��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *k1, const void *k2)  /* ��r */
{
	if (*((float *)k1) < *((float *)k2)) return -1;
	if (*((float *)k1) > *((float *)k2)) return  1;
	/* else */                           return  0;
}

void fivenum(int n, float x[])  /* �ܐ��v�� */
{
	int i, j;
	float t;

	qsort(x, n, sizeof(float), cmp);  /* �N�C�b�N�\�[�g */
	for (i = 0; i < 4; i++) {
		t = (n - 1.0) * i / 4.0;  j = (int)t;
		printf("%g ", x[j] + (x[j + 1] - x[j]) * (t - j));
	}
	printf("%g\n", x[n - 1]);
}

#include "statutil.c"
#define NMAX  5000

int main()
{
	int n;
	float t;
	static float x[NMAX];

	n = 0;
	while (! readerror(t = getnum(stdin)))
		if (missing(t)) continue;
		else if (n >= NMAX) error("�������܂�");
		else x[n++] = t;
	fivenum(n, x);
	return EXIT_SUCCESS;
}
