/***********************************************************
	inssort.c -- �}���\�[�g
***********************************************************/

typedef int keytype;  /* ����L�[�̌^ */

void inssort(int n, keytype a[])  /* a[0..n-1] �������� */
{
	int i, j;
	keytype x;

	for (i = 1; i < n; i++) {
		x = a[i];
		for (j = i - 1; j >= 0 && a[j] > x; j--)
			a[j + 1] = a[j];
		a[j + 1] = x;
	}
}

#if 0  /***** a[N] ��Ԑl�Ƃ��Ďg�� **************/

#include <limits.h>  /* INT_MAX �̒�`���܂ރt�@�C�� */

void inssort(int n, keytype a[])
{
	int i, j;
	keytype x;

	a[n] = INT_MAX;  /* �Ԑl */
	for (i = n - 2; i >= 0; i--) {
		x = a[i];
		for (j = i + 1; a[j] < x; j++)
			a[j - 1] = a[j];
		a[j - 1] = x;
	}
}

#endif  /*****************************************/

#include <stdio.h>
#include <stdlib.h>

#define N 20
int a[N + 1];  /* �Ԑl���g��Ȃ��Ȃ� a[N] �ł悢 */

int main()
{
	int i;

	printf("Before:");
	for (i = 0; i < N; i++) {
		a[i] = rand() / (RAND_MAX / 100 + 1);
		printf(" %2d", a[i]);
	}
	printf("\n");
	inssort(N, a);
	printf("After: ");
	for (i = 0; i < N; i++) printf(" %2d", a[i]);
	printf("\n");
	return EXIT_SUCCESS;
}
