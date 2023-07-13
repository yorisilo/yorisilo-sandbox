/***********************************************************
	sum.c -- ��񗎂�
***********************************************************/

float sum1(int n, float a[])  /* �ʏ�̕��@ */
{
	int i;
	float s;

	s = 0;
	for (i = 0; i < n; i++) s += a[i];
	return s;
}

float sum2(int n, float a[])  /* ��񗎂��΍� */
{
	int i;
	float r, s, t;

	r = 0;  s = 0;    /* s �͘a, r �͐ςݎc�� */
	for (i = 0; i < n; i++) {
		r += a[i];    /* �ςݎc�� + ���������l */
		t = s;        /* �O��܂ł̘a */
		s += r;       /* �a���X�V */
		t -= s;       /* ���ۂɐς܂ꂽ�l�̕�����ς������� */
		r += t;       /* �ςݎc�� */
	}
	return s;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	static float a[10001];

	printf("1 + 0.0001 + ... + 0.0001 = 2\n");
	a[0] = 1;
	for (i = 1; i <= 10000; i++) a[i] = 0.0001;
	printf("���@1: %.6f\n", sum1(10001, a));
	printf("���@2: %.6f\n", sum2(10001, a));
	return EXIT_SUCCESS;
}
