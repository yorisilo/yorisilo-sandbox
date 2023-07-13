/**************************************************************
	regula.c -- �͂��݂����@
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define samesign(x, y) (((x) > 0) == ((y) > 0))  /* �������Ȃ�^ */

double regula(double a, double b, double tolerance,
		double (*f)(double), int imax, char **error)
{
	int i;
	double c, fa, fb, fc;

	*error = NULL;
	if (tolerance < 0) tolerance = 0;
	if (b < a) {  c = a;  a = b;  b = c;  }
	fa = f(a);  if (fa == 0) return a;
	fb = f(b);  if (fb == 0) return b;
	if (samesign(fa, fb)) {
		*error = "��Ԃ̗��[�Ŋ֐��l���������ł�.";
		return 0;
	}
	for (i = 0; ; i++) {
		c = (a + b) / 2;
		if (c - a <= tolerance || b - c <= tolerance) break;
		if (i < imax) {
			c = (a * fb - b * fa) / (fb - fa);
			if      (c <= a) c = a + 0.6 * DBL_EPSILON * fabs(a);
			else if (c >= b) c = b - 0.6 * DBL_EPSILON * fabs(b);
		}
		fc = f(c);  if (fc == 0) return c;
		if (samesign(fc, fa)) {  a = c;  fa = fc;  }
		else                  {  b = c;  fb = fc;  }
	}
	return c;
}

int count;  /* �ďo���񐔂̃J�E���^ */
double func(double x)  /* �[���_�����߂�֐� */
{
	double value;

	value = x * x - 2;
	printf("%4d:  x = % -24.16g  f(x) = % .3g\n",
		++count, x, value);  /* �e�X�g�̂��ߌďo�������j�^�[���� */
	return value;
}

int main()  /* �e�X�g */
{
	char *error;
	double x;

	printf("2���@\n");  count = 0;
	x = regula(1, 2, 0, func, 0, &error);
	if (error) printf("%s\n", error);
	else printf("x = % -24.16g\n", x);

	printf("regula falsi�@\n");  count = 0;
	x = regula(1, 2, 0, func, 1000, &error);
	if (error) printf("%s\n", error);
	else printf("x = % -24.16g\n", x);

	return EXIT_SUCCESS;
}
