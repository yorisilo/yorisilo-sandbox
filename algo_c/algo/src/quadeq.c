/***********************************************************
	quadeq.c -- 2��������
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
	double a, b, c, d, x;

	printf("a = ");  scanf("%lf", &a);
	printf("b = ");  scanf("%lf", &b);
	printf("c = ");  scanf("%lf", &c);
	if (a != 0) {
		b /= a;  c /= a;     /* $a$ �Ŋ����� $x^2 + bx + c = 0$ �̌`�ɂ��� */
		if (c != 0) {
			b /= 2;          /* $x^2 + 2b'x + c = 0$ */
			d = b * b - c;   /* ���ʎ� $D / 4$ */
			if (d > 0) {
				if (b > 0) x = -b - sqrt(d);
				else       x = -b + sqrt(d);
				printf("x = %g, %g\n", x, c / x);
			} else if (d < 0)
				printf("x = %g +- %g i\n", -b, sqrt(-d));
			else
				printf("x = %g\n", -b);
		} else printf("x = %g, 0\n", -b);
	} else if (b != 0) printf("x = %g\n", -c / b);
	else if (c != 0) printf("���Ȃ�.\n");
	else printf("�s��.\n");
	return EXIT_SUCCESS;
}
