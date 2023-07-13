/***********************************************************
	binomial.c -- 2�����z
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error(char *s)
{
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}

int main()
{
	int k, n;
	double p, q, s, t;

	printf("n, p? ");  scanf("%d%lf", &n, &p);
	q = 1 - p;  s = t = pow(q, n);
	if (s == 0) error("n �� p ���傫�����܂�");
	for (k = 0; k < n; k++) {
		printf("%4d %7.4f\n", k, s);
		t *= (n - k) * p / ((k + 1) * q);
		s += t;
	}
	printf("%4d %7.4f\n", n, s);
	return EXIT_SUCCESS;
}
