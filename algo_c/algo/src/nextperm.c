/***********************************************************
	nextperm.c -- ����
***********************************************************/
#define N 6
int p[N + 1];

int nextperm(void)  /* �����������Ŏ��̏��� */
{
	int i, j, t;

	i = N - 1;
	p[0] = 0;  /* �Ԑl */
	while (p[i] >= p[i + 1]) i--;
	if (i == 0) return 0;  /* ���� */
	j = N;
	while (p[i] >= p[j]) j--;
	t = p[i];  p[i] = p[j];  p[j] = t;
	i++;  j = N;
	while (i < j) {
		t = p[i];  p[i] = p[j];  p[j] = t;  i++;  j--;
	}
	return 1;  /* ���� */
}

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i, count;

	count = 0;
	for (i = 1; i <= N; i++) p[i] = i;
	do {
		printf("%5d: ", ++count);
		for (i = 1; i <= N; i++) printf("%4d", p[i]);
		printf("\n");
	} while (nextperm());
	return EXIT_SUCCESS;
}
