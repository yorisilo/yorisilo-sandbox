/***********************************************************
	permfac.c -- ����
***********************************************************/
/* �K��i�@�Ƃ̑��ݕϊ� */

#define N 4
int a[N + 1];

void encode(void)
{
	int j, k;

	for (j = N - 1; j > 0; j--)
		for (k = 0; k < j; k++)
			if (a[k] > a[j]) a[k]--;
}

void decode(void)
{
	int j, k;

	for (j = 1; j < N; j++)
		for (k = j - 1; k >= 0; k--)
			if (a[k] >= a[j]) a[k]++;
}

int nextperm(void)
{
	int i, j, t;

	i = 1;
	a[N] = -1;  /* �Ԑl */
	while (a[i] >= a[i - 1]) i++;
	if (i == N) return 0;  /* ���� */
	j = 0;
	while (a[i] >= a[j]) j++;
	t = a[i];  a[i] = a[j];  a[j] = t;
	i--;  j = 0;
	while (i > j) {
		t = a[i];  a[i] = a[j];  a[j] = t;  i--;  j++;
	}
	return 1;  /* ���� */
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, count;

	count = 0;
	for (i = 0; i < N; i++) a[i] = N - i - 1;
	do {
		count++;
		printf("%5d: ", count);
		for (i = N - 1; i >= 0; i--) printf("%4d", a[i]);
		printf("\n");
		encode();
		printf("%5d: ", count);
		for (i = N - 1; i > 0; i--) printf("%4d", a[i]);
		printf("\n");
		decode();
		printf("%5d: ", count);
		for (i = N - 1; i >= 0; i--) printf("%4d", a[i]);
		printf("\n\n");
	} while (nextperm());
	return EXIT_SUCCESS;
}
