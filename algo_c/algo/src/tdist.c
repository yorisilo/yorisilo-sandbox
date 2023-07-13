/***********************************************************
	tdist.c -- t���z
***********************************************************/
#include <math.h>
#define PI 3.14159265358979323846264

double p_t(int df, double t)  /* t���z�̉����ݐϊm�� */
{
	int i;
	double c2, p, s;

	c2 = df / (df + t * t);  /* cos^2 */
	s = sqrt(1 - c2);  if (t < 0) s = -s;  /* sin */
	p = 0;
	for (i = df % 2 + 2; i <= df; i += 2) {
		p += s;  s *= (i - 1) * c2 / i;
	}
	if (df & 1)		/* ���R�x��� */
		return 0.5+(p*sqrt(c2)+atan(t/sqrt(df)))/PI;
	else			/* ���R�x������ */
		return (1 + p) / 2;
}

double q_t(int df, double t)  /* t���z�̏㑤�ݐϊm�� */
{
	return 1 - p_t(df, t);
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	double t;

	printf("***** p_t(df, t) *****\n");
	printf("  t   %-16s %-16s %-16s %-16s\n",
		"df=1", "df=2", "df=5", "df=20");
	for (i = -10; i <= 10; i++) {
		t = 0.5 * i;
		printf("%4.1f %16.14f %16.14f %16.14f %16.14f\n",
			t, p_t(1, t), p_t(2, t), p_t(5, t), p_t(20, t));
	}
	return EXIT_SUCCESS;
}
