/***********************************************************
	lagrange.c -- Lagrange (���O�����W��) ���
***********************************************************/
#define  N  5                                              /* �f�[�^�_�̐� */
double x[N] = {   0,      10,     20,     30,     40   },
       y[N] = { 610.66, 1227.4, 2338.1, 4244.9, 7381.2 };  /* �f�[�^ */

double lagrange(double t)
{
	int i, j;
	double sum, prod;

	sum = 0;
	for (i = 0; i < N; i++) {
		prod = y[i];
		for (j = 0; j < N; j++)
			if (j != i) prod *= (t - x[j]) / (x[i] - x[j]);
		sum += prod;
	}
	return sum;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;

	for (i = 10; i <= 30; i++)
		printf("%3d %6.1f\n", i, lagrange(i));
	return EXIT_SUCCESS;
}
