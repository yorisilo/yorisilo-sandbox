/***********************************************************
	neville.c -- Neville (�l���B��) ���
***********************************************************/
#define  N  5                                              /* �f�[�^�_�̐� */
double x[N] = {   0,      10,     20,     30,     40   },
       y[N] = { 610.66, 1227.4, 2338.1, 4244.9, 7381.2 };  /* �f�[�^ */

double neville(double t)
{
	int i, j;
	static double w[N];

	for (i = 0; i < N; i++) {
		w[i] = y[i];
		for (j = i - 1; j >= 0; j--)
			w[j] = w[j + 1] +
				  (w[j + 1] - w[j]) * (t - x[i]) / (x[i] - x[j]);
	}
	return w[0];
}

#if 0  /***** �Q�l: Aitken (�G�C�g�P��) ��� *****/
double aitken(double t)
{
	int i, j;
	static double w[N];

	for (i = 0; i <= N - 1; i++) w[i] = y[i];
	for (j = 1; j <= N - 1; j++)
		for (i = N - 1; i >= j; i--)
			w[i] = (w[i-1]*(x[i]-t) - w[i]*(x[i-j]-t))
				   / (x[i]-x[i-j]);
	return w[N - 1];
}
#endif

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;

	for (i = 10; i <= 30; i++)
		printf("%3d %6.1f\n", i, neville(i));
	return EXIT_SUCCESS;
}
