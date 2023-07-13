/***********************************************************
	rank1.c -- ���ʂÂ�
***********************************************************/

int rank1(int i, int n, int a[])  /* a[i] �̏��� (�w�̓e�X�g) */
{
	int k, r, x;

	r = 1;  x = a[i];
	for (k = 0; k < n; k++)
		if (a[k] > x) r++;
	return r;
}

float rank2(int i, int n, int a[])  /* a[i] �̏��� (���v�w) */
{
	int k, n_eq, n_lt, x;

	n_eq = 1;  n_lt = 0;  x = a[i];
	for (k = 0; k < n; k++)
		if (a[k] < x) n_lt++;
		else if (a[k] == x) n_eq++;
	return n_lt + 0.5 * n_eq;
}

#include <stdio.h>
#include <stdlib.h>
#define N    20  /* �l�� */
#define MAX 100  /* ���_ */

int main()
{
	int i, a[N];

	for (i = 0; i < N; i++)
		a[i] = (MAX + 1.0) / (RAND_MAX + 1.0) * rand();
	printf("    score rank1 rank2\n");
	for (i = 0; i < N; i++)
		printf("%2d: %5d %5d %5.1f\n",
			i, a[i], rank1(i, N, a), rank2(i, N, a));
	return EXIT_SUCCESS;
}
