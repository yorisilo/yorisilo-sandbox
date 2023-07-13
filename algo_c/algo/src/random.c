/***********************************************************
	random.c -- �J�C2�敪�z
	         -- �K���}���z
	         -- �O�p���z
	         -- �w�����z
	         -- ���K���z
	         -- �x�[�^���z
	         -- �ݏ敪�z
	         -- ���W�X�e�B�b�N���z
	         -- ���C�u�����z
	         -- Cauchy (�R�[�V�[) ���z
	         -- F���z
	         -- t���z
***********************************************************/

/***** ��l���� (���`�����@) ******************************/

#include <limits.h>
static unsigned long seed = 1;  /* �C�� */

void init_rnd(unsigned long x)
{
	seed = x;
}

unsigned long irnd(void)
{
	seed = seed * 1566083941UL + 1;
	return seed;
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
	return (1.0 / (ULONG_MAX + 1.0)) * irnd();
}

/**********************************************************/

#include <math.h>
#define PI 3.141592653589793238
#define E  2.718281828459045235

double triangular_rnd(void)  /* �O�p���z */
{
	return rnd() - rnd();
}

double power_rnd1(int n)  /* �ݏ敪�z 1 */
{
	int i;
	double p, r;

	p = rnd();
	for (i = 0; i < n; i++)
		if ((r = rnd()) > p) p = r;
	return p;
}

double power_rnd(double n)  /* �ݏ敪�z 2 */
{
	return pow(rnd(), 1.0 / (n + 1));
}

double exp_rnd(void)  /* �w�����z */
{
	return -log(1 - rnd());
}

double Cauchy_rnd1(void)  /* Cauchy (�R�[�V�[) ���z 1 */
{
	return tan(PI * rnd());
}

double Cauchy_rnd(void)  /* Cauchy (�R�[�V�[) ���z 2 */
{
	double x, y;

	do {
		x = 1 - rnd();  y = 2 * rnd() - 1;
	} while (x * x + y * y > 1);
	return y / x;
}

double nrnd1(void)  /* ���K���z 1 */
{
	return rnd() + rnd() + rnd() + rnd() + rnd() + rnd()
		 + rnd() + rnd() + rnd() + rnd() + rnd() + rnd() - 6;
}

double nrnd2(void)  /* ���K���z 2 */
{
	static int sw = 0;
	static double t, u;

	if (sw == 0) {
		sw = 1;
		t = sqrt(-2 * log(1 - rnd()));  u = 2 * PI * rnd();
		return t * cos(u);
	} else {
		sw = 0;
		return t * sin(u);
	}
}

double nrnd(void)  /* ���K���z 3 */
{
	static int sw = 0;
	static double r1, r2, s;

	if (sw == 0) {
		sw = 1;
		do {
			r1 = 2 * rnd() - 1;
			r2 = 2 * rnd() - 1;
			s = r1 * r1 + r2 * r2;
		} while (s > 1 || s == 0);
		s = sqrt(-2 * log(s) / s);
		return r1 * s;
	} else {
		sw = 0;
		return r2 * s;
	}
}

double gamma_rnd1(int two_a)  /* �K���}���z */
{
	int i;
	double x, r;

	x = 1;
	for (i = two_a / 2; i > 0; i--) x *= rnd();
	x = -log(x);
	if ((two_a & 1) != 0) {  /* if two_a is odd */
		r = nrnd();  x += 0.5 * r * r;
	}
	return x;
}

double gamma_rnd(double a)  /* �K���}���z, a > 0 */
{
	double t, u, x, y;

	if (a > 1) {
		t = sqrt(2 * a - 1);
		do {
			do {
				/* ���̂S�s�� y = tan(PI * rnd()) �Ɠ��l */
				do {
					x = 1 - rnd();  y = 2 * rnd() - 1;
				} while (x * x + y * y > 1);
				y /= x;
				x = t * y + a - 1;
			} while (x <= 0);
			u = (a - 1) * log(x / (a - 1)) - t * y;
		} while (u < -50 || rnd() > (1 + y * y) * exp(u));
	} else {
		t = E / (a + E);
		do {
			if (rnd() < t) {
				x = pow(rnd(), 1 / a);  y = exp(-x);
			} else {
				x = 1 - log(rnd());  y = pow(x, a - 1);
			}
		} while (rnd() >= y);
	}
	return x;
}

double beta_rnd1(double a, double b)  /* �x�[�^���z 1 */
{
	double x, y;

	do {
		x = pow(rnd(), 1 / a);  y = pow(rnd(), 1 / b);
	} while (x + y > 1);
	return x / (x + y);
}

double beta_rnd(double a, double b)  /* �x�[�^���z 2 */
{
	double temp;

	temp = gamma_rnd(a);
	return temp / (temp + gamma_rnd(b));
}

double chisq_rnd1(int n)  /* �J�C2�敪�z */
{
	int i;
	double s, t;

	s = 0;
	for (i = 0; i < n; i++) {  t = nrnd();  s += t * t;  }
	return s;
}

double chisq_rnd(double n)  /* �J�C2�敪�z */
{
	return 2 * gamma_rnd(0.5 * n);
}

double F_rnd(double n1, double n2)  /* F���z */
{
	return (chisq_rnd(n1) * n2) / (chisq_rnd(n2) * n1);
}

double t_rnd(double n)  /* t���z */
{
	double a, b, c;

	if (n <= 2) return nrnd() / sqrt(chisq_rnd(n) / n);
	do {
		a = nrnd();
		b = a * a / (n - 2);
		c = log(1 - rnd()) / (1 - 0.5 * n);
	} while (exp(-b-c) > 1 - b);
	return a / sqrt((1 - 2.0 / n) * (1 - b));
}

double logistic_rnd(void)  /* ���W�X�e�B�b�N���z */
{
	double r;

	r = rnd();
	return log(r / (1 - r));
}

double Weibull_rnd(double alpha)  /* Weibull (���C�u��) ���z */
{
	return pow(-log(1 - rnd()), 1 / alpha);
}

/**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i, choice, ix, n, histo[20];
	double a, b, x, s1, s2;

	init_rnd((unsigned long) time(NULL));  /* ������ */

	printf("***** ���j���[ *****\n");
	printf("  1: �O�p���z\n");
	printf("  2: �ݏ敪�z 1\n");
	printf("  3: �ݏ敪�z 2\n");
	printf("  4: �w�����z\n");
	printf("  5: �R�[�V�[���z 1\n");
	printf("  6: �R�[�V�[���z 2\n");
	printf("  7: ���K���z 1\n");
	printf("  8: ���K���z 2\n");
	printf("  9: ���K���z 3\n");
	printf(" 10: �K���}���z 1\n");
	printf(" 11: �K���}���z 2\n");
	printf(" 12: �x�[�^���z 1\n");
	printf(" 13: �x�[�^���z 2\n");
	printf(" 14: �J�C�Q�敪�z 1\n");
	printf(" 15: �J�C�Q�敪�z 2\n");
	printf(" 16: F���z\n");
	printf(" 17: t���z\n");
	printf(" 18: ���W�X�e�B�b�N���z\n");
	printf(" 19: ���C�u�����z\n");
	printf("? ");  scanf("%d", &choice);

	switch(choice) {
	case 2: case 3: case 10: case 11: case 14: case 15: case 17: case 19:
		printf("���� (1��)? ");  scanf("%lf", &a);  break;
	case 12: case 13: case 16:
		printf("���� (2��)? ");  scanf("%lf%lf", &a, &b);  break;
	}
	printf("��? ");  scanf("%d", &n);

	for (i = 0; i < 20; i++) histo[i] = 0;
	s1 = s2 = 0;
	for (i = 0; i < n; i++) {
		switch(choice) {
		case 1: x = triangular_rnd();  break;
		case 2: x = power_rnd1(a);  break;
		case 3: x = power_rnd(a);  break;
		case 4: x = exp_rnd();  break;
		case 5: x = Cauchy_rnd1();  break;
		case 6: x = Cauchy_rnd();  break;
		case 7: x = nrnd1();  break;
		case 8: x = nrnd2();  break;
		case 9: x = nrnd();  break;
		case 10: x = gamma_rnd1(a);  break;
		case 11: x = gamma_rnd(a);  break;
		case 12: x = beta_rnd1(a, b);  break;
		case 13: x = beta_rnd(a, b);  break;
		case 14: x = chisq_rnd1(a);  break;
		case 15: x = chisq_rnd(a);  break;
		case 16: x = F_rnd(a, b);  break;
		case 17: x = t_rnd(a);  break;
		case 18: x = logistic_rnd();  break;
		case 19: x = Weibull_rnd(a);  break;
		}
		ix = (int) floor(2 * x) + 10;
		if (ix >= 0 && ix < 20) histo[ix]++;
		s1 += x;  s2 += x * x;
	}

	for (i = 0; i < 20; i++)
		printf("%4.1f -- %4.1f: %5.1f%%\n",
			0.5 * (i - 10), 0.5 * (i - 9), 100.0 * histo[i] / n);
	s1 /= n;  s2 = sqrt((s2 - n * s1 * s1) / (n - 1));
	printf("���� %g  �W���΍� %g\n", s1, s2);

	return EXIT_SUCCESS;
}
