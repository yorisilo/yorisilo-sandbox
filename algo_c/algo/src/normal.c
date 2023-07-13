/***********************************************************
	normal.c -- ���K���z
***********************************************************/
#include <math.h>
#define PI  3.14159265358979323846264

double p_nor(double z)  /* ���K���z�̉����m�� */
{
	int i;
	double z2, prev, p, t;

	z2 = z * z;
	t = p = z * exp(-0.5 * z2) / sqrt(2 * PI);
	for (i = 3; i < 200; i += 2) {
		prev = p;  t *= z2 / i;  p += t;
		if (p == prev) return 0.5 + p;
	}
	return (z > 0);
}

double q_nor(double z)  /* ���K���z�̏㑤�m�� */
{
	return 1 - p_nor(z);
}

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i;
	double z;

	printf("���K���z�̉����m��\n");
	for (i = 0; i <= 20; i++) {
		z = 0.2 * i;
		printf("%3.1f %16.14f\n", z, p_nor(z));
	}
	return EXIT_SUCCESS;
}
