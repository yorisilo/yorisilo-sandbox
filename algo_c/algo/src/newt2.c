/***********************************************************
	newt2.c -- Newton (�j���[�g��) �@
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)  /* $f(x) = 0$ �������֐� $f(x)$ */
{
	return atan(x - 1);
}

double newton(double x)  /* �����l $x$ ���� $f(x) = 0$ �̉������߂� */
{
	int i;
	double h, fx, df, x_prev, fx_prev;

	fx = f(x);
	while (fx != 0) {
		df = f(x + fx) - fx;  h = fx * fx / df;
		x_prev = x;  fx_prev = fx;  i = 0;
		do {
			x = x_prev - h;  fx = f(x);  h /= 2;  i++;
			printf("(%d) x = % -24.16g  f(x) = % -.2g\n",
				i, x, fx);
		} while (fabs(fx) > fabs(fx_prev));
		if (i == 1 && x == x_prev) break;
	}
	return x;
}

int main()
{
	double x;

	printf("atan(x - 1) = 0 �������܂�.\n");
	printf("�����l = ");  scanf("%lf", &x);
	x = newton(x);
	printf("���� %g �ł�.\n", x);
	return EXIT_SUCCESS;
}
