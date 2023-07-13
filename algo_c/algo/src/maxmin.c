/***********************************************************
	maxmin.c -- �ő�l�E�ŏ��l
***********************************************************/
#define MAX2(x, y) ((x) > (y) ? (x) : (y))
#define MIN2(x, y) ((x) < (y) ? (x) : (y))

int findmax(int n, int a[])
{
	int i, max;

	max = a[0];
	for (i = 1; i < n; i++)
		if (a[i] > max) max = a[i];
	return max;
}

int findmin(int n, int a[])
{
	int i, min;

	min = a[0];
	for (i = 1; i < n; i++)
		if (a[i] < min) min = a[i];
	return min;
}

void findmaxmin(int n, int a[], int *pmax, int *pmin)
{
	int i, max, min, a1, a2;

	if (n & 1)               max = min = a[0];
	else if (a[0] > a[1]) {  max = a[0];  min = a[1];  }
	else                  {  max = a[1];  min = a[0];  }
	for (i = 2 - (n & 1); i < n; i += 2) {
		a1 = a[i];  a2 = a[i + 1];
		if (a1 > a2) {
			if (a1 > max) max = a1;
			if (a2 < min) min = a2;
		} else {
			if (a2 > max) max = a2;
			if (a1 < min) min = a1;
		}
	}
	*pmax = max;  *pmin = min;
}

#include <limits.h>
#include <stdarg.h>           /* �s��̈������g�� */

int maxn(int n, ...)          /* n �� int �̍ő�l */
{
	va_list ap;               /* �s��̈����ւ̃|�C���^ */
	int max, x;

	va_start(ap, n);          /* ap �̏����� */
	max = INT_MIN;
	while (--n >= 0) {
		x = va_arg(ap, int);  /* ap ���� int �����o�� */
		if (x > max) max = x;
	}
	va_end(ap);               /* ap �̌�n�� */
	return max;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int max, min;
	static int a[] = { 1, 7, 4 };

	printf("MAX2(1, 7) = %d\n", MAX2(1, 7));
	printf("MIN2(1, 7) = %d\n", MIN2(1, 7));

	printf("a[] = { 1, 7, 4 };\n");
	printf("findmax(3, a) = %d\n", findmax(3, a));
	printf("findmin(3, a) = %d\n", findmin(3, a));

	findmaxmin(3, a, &max, &min);
	printf("findmaxmin(3, a, &max, &min);\n");
	printf("max = %d, min = %d\n", max, min);

	printf("maxn(3, 1, 7, 4) = %d\n", maxn(3, 1, 7, 4));

	return EXIT_SUCCESS;
}
