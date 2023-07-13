/***********************************************************
	sweep.c -- SWEEP���Z�q�@
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define SCALAR double   /* �������s���Ȃ� float �� */
#include "statutil.c"   /* ���ϗʃf�[�^���̓��[�`�� */

int n, m, ndf;          /* �f�[�^�̌���, �ϐ��̐�, ���R�x */
char *added;            /* �����ϐ��ɍ̗p������ */
matrix a;               /* �Ϙa�s�� */

void sweep(int k)  /* �|���o�����Z */
{
	int i, j;
	double b, d;

	if ((d = a[k][k]) == 0) {
		printf("�ϐ� %d: �ꎟ�]��.\n", k);  return;
	}
	for (j = 0; j <= m; j++) a[k][j] /= d;
	for (j = 0; j <= m; j++) {
		if (j == k) continue;
		b = a[j][k];
		for (i = 0; i <= m; i++) a[j][i] -= b * a[k][i];
		a[j][k] = -b / d;
	}
	a[k][k] = 1 / d;
	if (added[k]) {  added[k] = 0;  ndf++;  }
	else          {  added[k] = 1;  ndf--;  }
}

void regress(int k)  /* ��ϐ� k �ɂ��ĉ�A�W���Ȃǂ��o�� */
{
	int j;
	double s, rms;

	if (added[k]) {  printf("???\n");  return;  }
	rms = (ndf > 0 && a[k][k] >= 0) ? sqrt(a[k][k] / ndf) : 0;
	printf("�ϐ�  ��A�W��       �W���덷        t\n");
	for (j = 0; j <= m; j++) {
		if (! added[j]) continue;
		s = (a[j][j] >= 0) ? sqrt(a[j][j]) * rms : 0;
		printf("%4d  % #-14g % #-14g", j, a[j][k], s);
	      	if (s > 0) printf("  % #-11.3g", fabs(a[j][k] / s));
		printf("\n");
	}
	printf("��ϐ�: %d  �c��2��a: %g  ���R�x: %d  "
	       "�c��RMS: %g\n", k, a[k][k], ndf, rms);
}

void residuals(void)  /* �c���̐Ϙa�s����o�� */
{
	int i, j, k;

	for (i = 0; i <= m; i += 5) {
		for (k = i; k < i + 5 && k <= m; k++)
			printf("      %-8d", k);
		printf("\n");
		for (j = 0; j <= m; j++) {
			printf("%4d  ", j);
			for (k = i; k < i + 5 && k <= m; k++)
				printf("% -14g", a[j][k]);
			printf("\n");
		}
	}
}

int main(int argc, char *argv[])
{
	int i, j, k, c;
	FILE *datafile;
	vector x;

	printf("********** �Θb�^��A���� **********\n\n");
	if (argc != 2) error("�g�p�@: reg datafile");
	datafile = fopen(argv[1], "r");
	if (datafile == NULL) error("�t�@�C�����ǂ߂܂���.");
	n = ndf = getnum(datafile);  m = getnum(datafile);
	printf("%d �� �~ %d �ϐ�\n", n, m);
	if (n < 1 || m < 1) error("�f�[�^�s��");
	if ((added = malloc(m + 1)) == NULL
	 || (a = newmat(m + 1, m + 1)) == NULL
	 || (x = newvec(m + 1)) == NULL) error("�L���̈�s��");
	for (j = 0; j <= m; j++) {
		added[j] = 0;
		for (k = j; k <= m; k++) a[j][k] = 0;
	}
	for (i = 0; i < n; i++) {
		printf(".");  x[0] = 1;
		for (j = 1; j <= m; j++) {
			x[j] = getnum(datafile);
			if (missing(x[j])) error("�f�[�^�s��");
		}
		for (j = 0; j <= m; j++)
			for (k = j; k <= m; k++) a[j][k] += x[j] * x[k];
	}
	printf("\n");  fclose(datafile);
	for (j = 0; j <= m; j++)
		for (k = 0; k < j; k++) a[j][k] = a[k][j];
	c = '\n';
	do {
		if (c == 'X' || c == 'Y')
			if (scanf("%d", &j) != 1 || j < 0 || j > m)
				c = '\0';
		switch (c) {
		case 'X':  sweep(j);  break;
		case 'Y':  regress(j);  break;
		case 'R':  residuals();  break;
		case '\n': printf("����(Xj/Yj/R/Q)? ");
		           break;
		default:   printf("???\n");  break;
		}
	} while ((c = toupper(getchar())) != EOF && c != 'Q');
	return EXIT_SUCCESS;
}
