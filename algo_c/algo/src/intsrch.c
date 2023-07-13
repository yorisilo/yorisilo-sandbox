/***********************************************************
	intsrch.c -- ��ԒT��
***********************************************************/
#define NOT_FOUND (-1)
typedef int keytype;

int intsrch(keytype x, keytype a[], int left, int right)
{
	int mid;

	if (left == right) {
		if (a[left] == x) return left;  else return NOT_FOUND;
	} else if (left > right || a[left] > x || a[right] < x)
		return NOT_FOUND;
	for ( ; ; ) {
		mid = (int)((long)(x - a[left]) * (right - left)
				/ (a[right] - a[left])) + left;
		if (a[mid] < x) {
			left = mid + 1;
			if (a[left] > x) break;
		} else if (a[mid] > x) {
			right = mid - 1;
			if (a[right] < x) break;
		} else return mid;
	}
	return NOT_FOUND;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 20

int main()
{
	int i, x;
	double r;
	static int a[N];

	printf("��ԒT���f�����X�g���[�V����\n");
	srand((unsigned int) time(NULL));
	r = 1.0;
	for (i = N - 1; i >= 0; i--) {
		/* 1����0�ȏ�̈�l������r�ɍ~���ɍ�� */
		r *= pow(rand() / (RAND_MAX + 1.0), 1.0 / (i + 1));
		/* 0�ȏ�100�����̐����ɒ��� */
		a[i] = (int)(100.0 * r);
	}
	printf("  i : ");
	for (i = 0; i < N; i++) printf(" %2d", i);
	printf("\n");
	printf("a[i]: ");
	for (i = 0; i < N; i++) printf(" %2d", a[i]);
	printf("\n");

	printf("\n����T���܂���? ");
	scanf("%d", &x);

	i = intsrch(x, a, 0, N - 1);
	if (i != NOT_FOUND) printf("i = %d\n", i);
	else                printf("������܂���\n");

	return EXIT_SUCCESS;
}
