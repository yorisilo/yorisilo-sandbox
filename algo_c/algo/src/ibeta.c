/***********************************************************
	ibeta.c -- �s���S�x�[�^�֐�
***********************************************************/
#include <stdio.h>
#include <math.h>

/************ loggamma(x) -- gamma.c ���Čf *************/

#define PI      3.14159265358979324  /* $\pi$ */
#define LOG_2PI 1.83787706640934548  /* $\log 2\pi$ */
#define N       8

#define B0  1                 /* �ȉ���Bernoulli�� */
#define B1  (-1.0 / 2.0)
#define B2  ( 1.0 / 6.0)
#define B4  (-1.0 / 30.0)
#define B6  ( 1.0 / 42.0)
#define B8  (-1.0 / 30.0)
#define B10 ( 5.0 / 66.0)
#define B12 (-691.0 / 2730.0)
#define B14 ( 7.0 / 6.0)
#define B16 (-3617.0 / 510.0)

double loggamma(double x)  /* �K���}�֐��̑ΐ� */
{
	double v, w;

	v = 1;
	while (x < N) {  v *= x;  x++;  }
	w = 1 / (x * x);
	return ((((((((B16 / (16 * 15))  * w + (B14 / (14 * 13))) * w
	            + (B12 / (12 * 11))) * w + (B10 / (10 *  9))) * w
	            + (B8  / ( 8 *  7))) * w + (B6  / ( 6 *  5))) * w
	            + (B4  / ( 4 *  3))) * w + (B2  / ( 2 *  1))) / x
	            + 0.5 * LOG_2PI - log(v) - x + (x - 0.5) * log(x);
}

/**********************************************************/

double p_beta(double x, double a, double b)
{
	int k;
	double p1, q1, p2, q2, d, previous;

	if (a <= 0) return HUGE_VAL;
	if (b <= 0) {
		if (x <  1) return 0;
		if (x == 1) return 1;
		/* else */  return HUGE_VAL;
	}
	if (x > (a + 1) / (a + b + 2))
		return 1 - p_beta(1 - x, b, a);
	if (x <= 0)  return 0;
	p1 = 0;  q1 = 1;
	p2 = exp(a * log(x) + b * log(1 - x)
		+ loggamma(a + b) - loggamma(a) - loggamma(b)) / a;
	q2 = 1;
	for (k = 0; k < 200; ) {
		previous = p2;
		d = - (a + k) * (a + b + k) * x
			/ ((a + 2 * k) * (a + 2 * k + 1));
		p1 = p1 * d + p2;  q1 = q1 * d + q2;
		k++;
		d = k * (b - k) * x / ((a + 2 * k - 1) * (a + 2 * k));
		p2 = p2 * d + p1;  q2 = q2 * d + q1;
		if (q2 == 0) {
			p2 = HUGE_VAL;  continue;
		}
		p1 /= q2;  q1 /= q2;  p2 /= q2;  q2 = 1;
		if (p2 == previous) return p2;
	}
	printf("p_beta: �������܂���.\n");
	return p2;
}

double q_beta(double x, double a, double b)
{
	return 1 - p_beta(x, a, b);
}

#if 0  /***** �Q�l: �����W�J�ɂ��� *****/

double p_beta2(double x, double a, double b)
{
	int k;
	double result, term, previous;

	if (a <= 0) return HUGE_VAL;
	if (b <= 0) {
		if (x <  1) return 0;
		if (x == 1) return 1;
		/* else */  return HUGE_VAL;
	}
	if (x > a / (a + b)) return 1 - p_beta2(1 - x, b, a);
	if (x <= 0)  return 0;
	term = exp(a * log(x) + b * log(1 - x)
		+ loggamma(a + b) - loggamma(a) - loggamma(b)) / a;
	result = term;
	for (k = 1; k < 1000; k++) {
		term *= (a + b + k - 1) * x / (a + k);
		previous = result;  result += term;
		if (result == previous) return result;
	}
	fprintf(stderr, "p_beta2: �������܂���.\n");
	return result;
}
#endif  /* �����W�J�ɂ��� */

double p_t(double t, int df)  /* t ���z�̉����m�� */
{
	return 1 - 0.5 * p_beta(df / (df + t * t), 0.5 * df, 0.5);
}

double q_t(double t, int df)  /* t ���z�̏㑤�m�� */
{
	return 0.5 * p_beta(df / (df + t * t), 0.5 * df, 0.5);
}

double p_f(double f, int df1, int df2)  /* F ���z�̉����m�� */
{
	if (f <= 0) return 0;
	return p_beta(df1 / (df1 + df2 / f), 0.5 * df1, 0.5 * df2);
}

double q_f(double f, int df1, int df2)  /* F ���z�̏㑤�m�� */
{
	if (f <= 0) return 1;
	return p_beta(df2 / (df2 + df1 * f), 0.5 * df2, 0.5 * df1);
}

double p_binomial(int n, double p, int k) /* 2�����z B(n,p) �� X <= k �̊m�� */
{
	if (k <  0) return 0;
	if (k >= n) return 1;
	return p_beta(1 - p, k + 1, n - k);
}

double q_binomial(int n, double p, int k) /* 2�����z B(n,p) �� X >= k �̊m�� */
{
	if (k <= 0) return 1;
	if (k >  n) return 0;
	return p_beta(p, k, n - k + 1);
}

#include <stdlib.h>

int main()  /* �኱�̃e�X�g */
{
	int i;
	double x, a, b;

	printf("(1) �s���S�x�[�^�֐� I_x(a,b), 1 - I_x(a,b)\n");
	printf("(2) t���z�̉��E�㑤�m��\n");
	printf("(3) F���z�̉��E�㑤�m��\n");
	printf("(4) 2�����z B(p,k) �� X <= k,  X >= k �̊m��\n");
	printf("�ǂ�ɂ��܂���? ");  scanf("%d", &i);
	switch (i) {
	case 1:
		printf("a? ");  scanf("%lf", &a);
		printf("b? ");  scanf("%lf", &b);
		for (i = 0; i <= 20; i++) {
			x = i / 20.0;
			printf("%4.2f %20.15f %20.15f\n",
				x, p_beta(x, a, b), q_beta(x, a, b));
		}
		break;
	case 2:
		printf("���R�x? ");  scanf("%lf", &a);
		for (i = 0; i <= 20; i++) {
			x = i / 5.0;
			printf("%3.1f %20.15f %20.15f\n",
				x, p_t(x, (int)a), q_t(x, (int)a));
		}
		break;
	case 3:
		printf("���R�x df1 ? ");  scanf("%lf", &a);
		printf("���R�x df2 ? ");  scanf("%lf", &b);
		for (x = 0; x <= 10; x++)
			printf("%4.1f %20.15f %20.15f\n",
				x, p_f(x, (int)a, (int)b),
				   q_f(x, (int)a, (int)b));
		break;
	case 4:
		printf("n? ");  scanf("%lf", &a);
		printf("p? ");  scanf("%lf", &x);
		for (i = 0; i <= (int)a; i++)
			printf("%3d %20.15f %20.15f\n",
				i, p_binomial((int)a, x, i),
				   q_binomial((int)a, x, i));
		break;
	}
	return EXIT_SUCCESS;
}
