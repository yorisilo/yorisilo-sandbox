/***********************************************************
	lu.c -- LU����
***********************************************************/
#include "matutil.c"  /* �s�񑀍�̏�����W */
#include <math.h>

double lu(int n, matrix a, int *ip)
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

void solve(int n, matrix a, vector b, int *ip, vector x)
{
	int i, j, ii;
	double t;

	for (i = 0; i < n; i++) {       /* Gauss�����@�̎c�� */
		ii = ip[i];  t = b[ii];
		for (j = 0; j < i; j++) t -= a[ii][j] * x[j];
		x[i] = t;
	}
	for (i = n - 1; i >= 0; i--) {  /* ��ޑ�� */
		t = x[i];  ii = ip[i];
		for (j = i + 1; j < n; j++) t -= a[ii][j] * x[j];
		x[i] = t / a[ii][i];
	}
}

double gauss(int n, matrix a, vector b, vector x)
{
	double det;  /* �s�� */
	int *ip;     /* �s�����̏�� */

	ip = malloc(sizeof(int) * n);         /* �L���̈�m�� */
	if (ip == NULL) error("�L���̈�s��");
	det = lu(n, a, ip);                   /* LU���� */
	if (det != 0) solve(n, a, b, ip, x);  /* LU�����̌��ʂ��g���ĘA�������������� */
	free(ip);                             /* �L���̈�̉�� */
	return det;                           /* �߂�l�͍s�� */
}

/********** �ȉ��̓e�X�g�p **********/

#include <limits.h>

double rnd(void)  /* ����  0 < rnd() < 1 */
{
	static unsigned long seed = 123456789UL;  /* � */

	return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main()
{
	int i, j, n;
	matrix a, asave;
	vector b, bsave, x;
	double s, det;

	printf("n = ");  scanf("%d", &n);  /* �s��̎�������� */
	a = new_matrix(n, n);  asave = new_matrix(n, n);
	b = new_vector(n);  bsave = new_vector(n);
	x = new_vector(n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = asave[i][j] = rnd() - rnd();
	printf("�W���s��\n");  matprint(a, n, 10, "%7.3f");
	for (i = 0; i < n; i++)
		b[i] = bsave[i] = rnd() - rnd();
	printf("�E��\n");  vecprint(b, n, 10, "%7.3f");
	det = gauss(n, a, b, x);  /* Gauss�@�� $Ax=b$ ������ */
	printf("�s�� = %g\n", det);
	printf("����, �����������Ƃ��̗��ӂ̍�\n");
	for (i = 0; i < n; i++) {
		s = bsave[i];
		for (j = 0; j < n; j++) s -= asave[i][j] * x[j];
		printf("%4d: %12.7f %12.7f\n", i, x[i], s);
	}
	return EXIT_SUCCESS;
}
