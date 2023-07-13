/***********************************************************
	newt1.c -- Newton (�j���[�g��) �@
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double b, c, d;

double f(double x)  /* $f(x) = 0$ �������֐� $f(x)$ */
{
	return ((b + x) * x + c) * x + d;
}

double f_prime(double x)  /* $f(x)$ �̓��֐� */
{
	return (2 * b + 3 * x) * x + c;
}

double newton(double x)  /* �����l $x$ ��^���� $f(x) = 0$ �̉���Ԃ� */
{
	double fx, fp, xprev;

	do {
		fx = f(x);
		printf("  x = % -24.16g  f(x) = % -.2g\n", x, fx);
		if ((fp = f_prime(x)) == 0) fp = 1;  /* �����ɂ��炷 */
		xprev = x;  x -= fx / fp;
	} while (x != xprev);
	return x;
}

int main()
{
	double a, x1, x2, x3;

	printf("ax^3+bx^2+cx+d=0�������܂�.\na b c d ? ");
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	b /= a;  c /= a;  d /= a;
	a = b * b - 3 * c;
	if (a > 0) {
		a = (2.0 / 3.0) * sqrt(a);
		x1 = newton(-a - b / 3);  /* �������� */
		printf("x1 = %g\n", x1);
		x2 = newton(a - b / 3);   /* �E������ */
		if (x2 == x1) return EXIT_SUCCESS;
		printf("x2 = %g\n", x2);
		x3 = newton(b / (-3));    /* �ϋȓ_���� */
		printf("x3 = %g\n", x3);
	} else {
		x1 = newton(0);           /* �K���ȓ_���� */
		printf("x = %g\n", x1);
	}
	return EXIT_SUCCESS;
}
