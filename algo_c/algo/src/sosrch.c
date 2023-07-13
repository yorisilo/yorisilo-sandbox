/***********************************************************
	sosrh.c -- ���ȑg�D���T��
***********************************************************/
/* �u���@ */

#define NOT_FOUND (-1)
typedef int keytype;

int sosrch(keytype x, keytype a[], int imin, int imax)
{
	int i;

	if (imin > imax) return NOT_FOUND;
	a[imax + 1] = x;  /* �Ԑl */
	i = imin;  while (a[i] != x) i++;
	if (i > imax) return NOT_FOUND;
	if (i != imin) {
		a[i] = a[i - 1];  i--;  a[i] = x;  /* ��O�ƌ��� */
	}
	return i;
}

#include <stdio.h>
#include <stdlib.h>
#define N 8

int main()  /* �e�X�g�p */
{
	int i, x, a[N + 1];

	for (i = 0; i < N; i++) a[i] = rand() / (RAND_MAX / 100 + 1);
	for ( ; ; ) {
		for (i = 0; i < N; i++) printf("  a[%d]=%d", i, a[i]);
		printf("\n�ǂ��T���܂���? ");
		scanf("%d", &x);  if (x < 0) break;
		i = sosrch(x, a, 0, N - 1);
		if (i != NOT_FOUND) printf("i = %d\n", i);
		else printf("������܂���.\n");
	}
	return EXIT_SUCCESS;
}
