/***********************************************************
	egypfrac.c -- �G�W�v�g�̕���
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int m, n, q;

	printf(" ���q m = ");  scanf("%d", &m);
	printf(" ���� n = ");  scanf("%d", &n);
	printf("%d/%d = ", m, n);
	while (n % m != 0) {
		q = n / m + 1;
		printf("1/%d + ", q);
		m = m * q - n;  n *= q;
	}
	printf("1/%d\n", n / m);
	return EXIT_SUCCESS;
}
