/***********************************************************
	simplex.c -- ���`�v��@
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define EPS     1E-6	/* ������ */
#define LARGE   1E+30	/* ������ */
#define MMAX    20		/* �s (����) �̐��̏�� */
#define NMAX    100		/* �� (�ϐ�) �̐��̏�� */

float a[MMAX + 1][NMAX + 1],	/* �������̌W�� */
      c[NMAX + 1],				/* �ړI�֐��̌W�� */
      q[MMAX + 1][MMAX + 1],	/* �ϊ��s�� */
      pivotcolumn[MMAX + 1];	/* �s�{�b�g�� */
int m, n,		/* �s (����), �� (�ϐ�) �̐� */
    n1,			/* {\tt n} $+$ ���̃X���b�N�ϐ��̐� */
    n2,			/* {\tt n1} $+$ ���̃X���b�N�ϐ��̐� */
    n3,			/* {\tt n2} $+$ �l�וϐ��̐� */
    jmax,		/* �ŉE��̔ԍ� */
    col[MMAX + 1],	/* �e�s�̊��ϐ��̔ԍ� */
    row[NMAX + 2*MMAX + 1],
                /* ���̗񂪊��Ȃ�Ή���������̔ԍ�, �����łȂ����0 */
    nonzero_row[NMAX + 2*MMAX + 1]; /* �X���b�N�E�l�וϐ���0�łȂ��s */
char inequality[MMAX + 1];	/*  <, >, =  */

void error(char *message)  /* �G���[�\��, �I�� */
{
	fprintf(stderr, "\n%s\n", message);  exit(EXIT_FAILURE);
}

double getnum(void)  /* ������W�����͂���ǂ� */
{
	int r;
	double x;

	while ((r = scanf("%lf", &x)) != 1) {
		if (r == EOF) error("���̓G���[");
		scanf("%*[^\n]");  /* �G���[�񕜂̂��ߍs���܂œǂݔ�΂� */
	}
	return x;
}

void readdata(void)  /* �f�[�^��ǂ� */
{
	int i, j;
	char s[2];

	m = (int)getnum();  n = (int)getnum();
	if (m < 1 || m > MMAX || n < 1 || n > NMAX)
		error("�����̐� m �܂��͕ϐ��̐� n ���͈͊O�ł�");
	for (j = 1; j <= n; j++) c[j] = getnum();
	c[0] = -getnum();  /* {\tt c[0]}�̕������t�ɂ��� */
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) a[i][j] = getnum();
		if (scanf(" %1[><=]", s) != 1) error("���̓G���[");
		inequality[i] = s[0];
		a[i][0] = getnum();
		if (a[i][0] < 0) {
			if      (inequality[i] == '>') inequality[i] = '<';
			else if (inequality[i] == '<') inequality[i] = '>';
			for (j = 0; j <= n; j++) a[i][j] = -a[i][j];
		} else if (a[i][0] == 0 && inequality[i] == '>') {
			inequality[i] = '<';
			for (j = 1; j <= n; j++) a[i][j] = -a[i][j];
		}
	}
}

void prepare(void)  /* ���� */
{
	int i;

	n1 = n;
	for (i = 1; i <= m; i++)
		if (inequality[i] == '>') {  /* �W����$-1$�̃X���b�N�ϐ� */
			n1++;  nonzero_row[n1] = i;
		}
	n2 = n1;
	for (i = 1; i <= m; i++)
		if (inequality[i] == '<') {  /* �W����$+1$�̃X���b�N�ϐ� */
			n2++;  col[i] = n2;
			nonzero_row[n2] = row[n2] = i;
		}
	n3 = n2;
	for (i = 1; i <= m; i++)
		if (inequality[i] != '<') {  /* �l�וϐ� */
			n3++;  col[i] = n3;
			nonzero_row[n3] = row[n3] = i;
		}
	for (i = 0; i <= m; i++) q[i][i] = 1;
}

double tableau(int i, int j)
{
	int k;
	double s;

	if (col[i] < 0) return 0;  /* �������s */
	if (j <= n) {
		s = 0;
		for (k = 0; k <= m; k++) s += q[i][k] * a[k][j];
		return s;
	}
	s = q[i][nonzero_row[j]];
	if (j <= n1) return -s;
	if (j <= n2 || i != 0) return s;
	return s + 1;  /* j > n2 && i == 0 */
}

void writetableau(int ipivot, int jpivot)
	/* �f�����X�g���[�V�����̂��߃V���v���b�N�X�\���o�� */
{
	int i, j;

	for (i = 0; i <= m; i++)
		if (col[i] >= 0) {
			printf("%2d: ", i);
			for (j = 0; j <= jmax; j++)
				printf("%7.2f%c", tableau(i, j),
					(i == ipivot && j == jpivot) ? '*' : ' ');
			printf("\n");
		}
}

void pivot(int ipivot, int jpivot)  /* �|���o�� */
{
	int i, j;
	double u;

	printf("�s�{�b�g�ʒu (%d, %d)\n", ipivot, jpivot);
	u = pivotcolumn[ipivot];
	for (j = 1; j <= m; j++) q[ipivot][j] /= u;
	for (i = 0; i <= m; i++)
		if (i != ipivot) {
			u = pivotcolumn[i];
			for (j = 1; j <= m; j++)
				q[i][j] -= q[ipivot][j] * u;
		}
	row[col[ipivot]] = 0;
	col[ipivot] = jpivot;  row[jpivot] = ipivot;
}

void minimize(void)  /* �ŏ��� */
{
	int i, ipivot, jpivot;
	double t, u;

	for ( ; ; ) {
		/* �s�{�b�g�� jpivot �������� */
		for (jpivot = 1; jpivot <= jmax; jpivot++)
			if (row[jpivot] == 0) {
				pivotcolumn[0] = tableau(0, jpivot);
				if (pivotcolumn[0] < -EPS) break;
			}
		if (jpivot > jmax) break;  /* �ŏ������� */
		/* �s�{�b�g�s ipivot �������� */
		u = LARGE;  ipivot = 0;
		for (i = 1; i <= m; i++) {
			pivotcolumn[i] = tableau(i, jpivot);
			if (pivotcolumn[i] > EPS) {
				t = tableau(i, 0) / pivotcolumn[i];
				if (t < u) {  ipivot = i;  u = t;  }
			}
		}
		if (ipivot == 0) {
			printf("�ړI�֐��͉���������܂���\n");
			exit(EXIT_SUCCESS);
		}
		writetableau(ipivot, jpivot);
		pivot(ipivot, jpivot);
	}
	writetableau(-1, -1);
	printf("�ŏ��l�� %g �ł�\n", -tableau(0, 0));
}

void phase1(void)  /* �t�F�[�Y�P */
{
	int i, j;
	double u;

	printf("�t�F�[�Y�P\n");
	jmax = n3;
	for (i = 0; i <= m; i++)
		if (col[i] > n2) q[0][i] = -1;
	minimize();
	if (tableau(0, 0) < -EPS) {
		printf("�\�ȉ��͂���܂���\n");
		exit(EXIT_SUCCESS);
	}
	for (i = 1; i <= m; i++)
		if (col[i] > n2) {
			printf("���� %d �͏璷�ł�\n", i);
			col[i] = -1;
		}
	q[0][0] = 1;
	for (j = 1; j <= m; j++) q[0][j] = 0;
	for (i = 1; i <= m; i++)
		if ((j = col[i]) > 0 && j <= n && (u = c[j]) != 0)
			for (j = 1; j <= m; j++)
				q[0][j] -= q[i][j] * u;
}

void phase2(void)
{
	int j;

	printf("�t�F�[�Y�Q\n");  jmax = n2;
	for (j = 0; j <= n; j++) a[0][j] = c[j];  /* �ړI�֐� */
	minimize();
}

void report(void)  /* ���ʂ̏o�� */
{
	int i, j;

	printf("0 �łȂ��ϐ��̒l:\n");
	for (j = 1; j <= n; j++)
		if ((i = row[j]) != 0)
			printf("x[%d] = %g\n", j, tableau(i, 0));
}

int main()
{
	readdata();					/* �f�[�^��ǂ� */
	prepare();					/* �������炦 */
	if (n3 != n2) phase1();	    /* �t�F�[�Y1 */
	phase2();					/* �t�F�[�Y2 */
	report();					/* ���ʂ̏o�� */
	return EXIT_SUCCESS;
}
