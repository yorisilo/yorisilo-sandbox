/***********************************************************
	meansd3.c -- ���ϒl�E�W���΍�
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int n;
	float x, s1, s2;

	s1 = s2 = n = 0;
	while (scanf("%f", &x) == 1) {
		n++;                        /* �� */
		x -= s1;                    /* �����ςƂ̍� */
		s1 += x / n;                /* ���� */
		s2 += (n - 1) * x * x / n;  /* �����a */
	}
	s2 = sqrt(s2 / (n - 1));  /* �W���΍� */
	printf("��: %d  ����: %g  �W���΍�: %g\n", n, s1, s2);
	return EXIT_SUCCESS;
}
