/***********************************************************
	contour.c -- ������
***********************************************************/
#include "plotter.c"  /* ���[�W���f���ŃR���p�C�� */
#include <math.h>

void evaluate(double x, double y,
              double *f, double *fx, double *fy)  /* �� */
{
	*f = x * x + 4 * y * y;  /* $f(x, y) = x^2 + 4y^2$ */
	*fx = 2 * x;             /* $x$ �Ŕ�����������: $f_x(x, y) = 2x$ */
	*fy = 8 * y;             /* $y$ �Ŕ�����������: $f_y(x, y) = 8y$ */
}

#define sq(x) ((x) * (x))    /* $x^2$ */
#define EPS  0.001           /* ���e�덷 $\varepsilon$ */

void newton(double fc, double *x, double *y,
            double *fx, double *fy, double *grad2) /* Newton�@ */
{
	double f, t;

	do {
		evaluate(*x, *y, &f, fx, fy);
		*grad2 = sq(*fx) + sq(*fy);
		if (*grad2 < 1e-10) {  *x = 1e30;  return;  }
		t = (fc - f) / *grad2;
		*x += t * *fx;  *y += t * *fy;
	} while (t * t * *grad2 > EPS * EPS);
}

void contour(double fc, double x, double y, double step) /* ��������`�� */
{
	int i;
	double fx, fy, grad2, t, x0, y0;

	for (i = 0; ; i++) {
		newton(fc, &x, &y, &fx, &fy, &grad2);
		if (fabs(x) + fabs(y) > 1e10) return;
		if (i == 0) {  move(x, y);  x0 = x;  y0 = y;  }
		else draw(x, y);
		if (i > 2 && sq(x - x0) + sq(y - y0) < sq(step))
			break;
		t = step / sqrt(grad2);
		x += fy * t;  y += -fx * t;
	}
	draw(x0, y0);
}

int main()
{
	double fc, x, y, step;

	gr_on();  gr_window(-3, -2, 3, 2, 1, GREEN);
	for ( ; ; ) {
		printf("f(x, y) = ");                      /* �������̊֐��l */
		if (scanf("%lf", &fc) != 1) break;
		printf("initial x = ");  scanf("%lf", &x); /* $x$ �̏����l */
		printf("initial y = ");  scanf("%lf", &y); /* $y$ �̏����l */
		printf("step = ");  scanf("%lf", &step);   /* �X�e�b�v�T�C�Y */
		contour(fc, x, y, step);
	}
	printf("Hit any key.\n");  hitanykey();
	return EXIT_SUCCESS;
}
