/***********************************************************
	newton.c -- Newton (�j���[�g��) ���
***********************************************************/
#define  N  5                                             /* �f�[�^�_�̐� */
double x[N] = {   0,      10,     20,     30,     40   },
       y[N] = { 610.66, 1227.4, 2338.1, 4244.9, 7381.2 },       /* �f�[�^ */
       a[N];                                          /* ��ԑ������̌W�� */

void maketable(void)
{
	int i, j;
	static double w[N];

	for (i = 0; i < N; i++) {
		w[i] = y[i];
		for (j = i - 1; j >= 0; j--)
			w[j] = (w[j + 1] - w[j]) / (x[i] - x[j]);
		a[i] = w[0];
	}
}

double interpolate(double t)
{
	int i;
	double p;

	p = a[N - 1];
	for (i = N - 2; i >= 0; i--)
		p = p * (t - x[i]) + a[i];
	return p;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;

	maketable();
	for (i = 10; i <= 30; i++)
		printf("%3d %6.1f\n", i, interpolate(i));
	return EXIT_SUCCESS;
}
