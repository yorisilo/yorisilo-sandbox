/***********************************************************
	matinv.c -- �t�s��
***********************************************************/
#include "matutil.c"  /* �s�񑀍�p������W */
#include <math.h>

double lu(int n, matrix a, int *ip)  /* LU���� */
{
	int i, j, k, ii, ik;
	double t, u, det;
	vector weight;

	weight = new_vector(n);    /* weight[0..n-1] �̋L���̈�m�� */
	det = 0;                   /* �s�� */
	for (k = 0; k < n; k++) {  /* �e�s�ɂ��� */
		ip[k] = k;             /* �s�������̏����l */
		u = 0;                 /* ���̍s�̐�Βl�ő�̗v�f�����߂� */
		for (j = 0; j < n; j++) {
			t = fabs(a[k][j]);  if (t > u) u = t;
		}
		if (u == 0) goto EXIT; /* 0 �Ȃ�s���LU�����ł��Ȃ� */
		weight[k] = 1 / u;     /* �ő��Βl�̋t�� */
	}
	det = 1;                   /* �s�񎮂̏����l */
	for (k = 0; k < n; k++) {  /* �e�s�ɂ��� */
		u = -1;
		for (i = k; i < n; i++) {  /* ��艺�̊e�s�ɂ��� */
			ii = ip[i];            /* �d�݁~��Βl ���ő�̍s�������� */
			t = fabs(a[ii][k]) * weight[ii];
			if (t > u) {  u = t;  j = i;  }
		}
		ik = ip[j];
		if (j != k) {
			ip[j] = ip[k];  ip[k] = ik;  /* �s�ԍ������� */
			det = -det;  /* �s����������΍s�񎮂̕������ς�� */
		}
		u = a[ik][k];  det *= u;  /* �Ίp���� */
		if (u == 0) goto EXIT;    /* 0 �Ȃ�s���LU�����ł��Ȃ� */
		for (i = k + 1; i < n; i++) {  /* Gauss�����@ */
			ii = ip[i];
			t = (a[ii][k] /= u);
			for (j = k + 1; j < n; j++)
				a[ii][j] -= t * a[ik][j];
		}
	}
EXIT:
	free_vector(weight);  /* �L���̈����� */
	return det;           /* �߂�l�͍s�� */
}

double matinv(int n, matrix a, matrix a_inv)
{
	int i, j, k, ii;
	double t, det;
	int *ip;   /* �s�����̏�� */

	ip = malloc(sizeof(int) * n);
	if (ip == NULL) error("�L���̈�s��");
	det = lu(n, a, ip);
	if (det != 0)
		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				ii = ip[i];  t = (ii == k);
				for (j = 0; j < i; j++)
					t -= a[ii][j] * a_inv[j][k];
				a_inv[i][k] = t;
			}
			for (i = n - 1; i >= 0; i--) {
				t = a_inv[i][k];  ii = ip[i];
				for (j = i + 1; j < n; j++)
					t -= a[ii][j] * a_inv[j][k];
				a_inv[i][k] = t / a[ii][i];
			}
		}
	free(ip);
	return det;
}

/************* �ȉ��̓e�X�g�p ****************/

#include <limits.h>

double rnd(void)  /* ����  0 < rnd() < 1 */
{
	static unsigned long seed = 123456789UL;  /* � */

	return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main()
{
	int i, j, k, n;
	matrix a, asave, a_inv;
	double s, t;

	printf("n = ");  scanf("%d", &n);
	a = new_matrix(n, n);  asave = new_matrix(n, n);
	a_inv = new_matrix(n, n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = asave[i][j] = rnd() - rnd();
	printf("A\n");
	matprint(a, n, 7, "%10.6f");
	s = matinv(n, a, a_inv);
	printf("�s�� = %g\n", s);
	printf("A^{-1}\n");
	matprint(a_inv, n, 7, "%10.6f");
	t = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			s = (i == j);
			for (k = 0; k < n; k++)
				s -= asave[i][k] * a_inv[k][j];
			t += s * s;
		}
	printf("A A^{-1} �̐����̓�敽�ό덷 %g\n",
		sqrt(t / (n * n)));
	t = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			s = (i == j);
			for (k = 0; k < n; k++)
				s -= a_inv[i][k] * asave[k][j];
			t += s * s;
		}
	printf("A^{-1} A �̐����̓�敽�ό덷 %g\n",
		sqrt(t / (n * n)));
	return EXIT_SUCCESS;
}
