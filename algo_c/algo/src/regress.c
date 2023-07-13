/***********************************************************
	regress.c -- ��A����
***********************************************************/
#include "statutil.c"

#define PIVOTING 0    /* �s�{�b�g�I�����s���� */
#define VERBOSE  0    /* �r���o�߂��o�͂��邩 */
#define EPS   1e-6    /* ���e�덷 */

#if ! PIVOTING  /* �s�{�b�g�I�����s��Ȃ��ꍇ */

int lsq(int n, int m, matrix x, vector b,
		int *col, vector normsq)  /* �ŏ�2��@ */
{
	int i, j, k, r;
	double s, t, u;
	vector v, w;

	for (j = 0; j < m; j++)
		normsq[j] = innerproduct(n, x[j], x[j]);
	r = 0;
	for (k = 0; k < m; k++) {
		if (normsq[k] == 0) continue;
		v = x[k];  u = innerproduct(n - r, &v[r], &v[r]);
		#if VERBOSE
			printf("\n%4d: 2��a������2��a = %-14g",
				k + 1, u / normsq[k]);
		#endif
		if (u / normsq[k] < EPS * EPS) continue;
		x[r] = v;  col[r] = k;
		u = sqrt(u);  if (v[r] < 0) u = -u;
		v[r] += u;  t = 1 / (v[r] * u);
		for (j = k + 1; j <= m; j++) {
			w = x[j];
			s = t * innerproduct(n - r, &v[r], &w[r]);
			for (i = r; i < n; i++) w[i] -= s * v[i];
		}
		v[r] = -u;
		#if VERBOSE
			printf("  �c��2��a = %g",
			  innerproduct(n-r-1, &x[m][r+1], &x[m][r+1]));
		#endif
		r++;
	}
	for (j = r - 1; j >= 0; j--) {
		s = x[m][j];
		for (i = j + 1; i < r; i++) s -= x[i][j] * b[i];
		b[j] = s / x[j][j];
	}
	#if VERBOSE
		printf("\n\n");
	#endif
	return r;  /* rank */
}

#else /* �s�{�b�g�I�����s���ꍇ */

#define swap(a, i, j, t)  t = a[i];  a[i] = a[j];  a[j] = t

int lsq(int n, int m, matrix x, vector b,
		int *col, vector initnormsq, vector normsq)
{
	int i, j, r;
	double s, t, u;
	vector v, w;

	for (j = 0; j < m; j++) {
		col[j] = j;
		normsq[j] = innerproduct(n, x[j], x[j]);
		initnormsq[j] = (normsq[j] != 0) ? normsq[j] : -1;
	}
	for (r = 0; r < m; r++) {
		if (r != 0) {
			j = r;  u = 0;
			for (i = r; i < m; i++) {
				t = normsq[i] / initnormsq[i];
				if (t > u) {  u = t;  j = i;  }
			}
			swap(col, j, r, i);
			swap(normsq, j, r, t);
			swap(initnormsq, j, r, t);
			swap(x, j, r, v);
		}
		v = x[r];  u = innerproduct(n - r, &v[r], &v[r]);
		if (u / initnormsq[r] < EPS * EPS) break;
		u = sqrt(u);  if (v[r] < 0) u = -u;
		v[r] += u;  t = 1 / (v[r] * u);
		for (j = r + 1; j <= m; j++) {
			w = x[j];
			s = t * innerproduct(n - r, &v[r], &w[r]);
			for (i = r; i < n; i++) w[i] -= s * v[i];
			if (j < m) normsq[j] -= w[r] * w[r];
		}
		v[r] = -u;
	}
	for (j = r - 1; j >= 0; j--) {
		s = x[m][j];
		for (i = j + 1; i < r; i++) s -= x[i][j] * b[i];
		b[j] = s / x[j][j];
	}
	return r;  /* rank */
}

#endif /* PIVOTING */

void invr(int r, matrix x)  /* ��O�p�s��̋t�s�� */
{
	int i, j, k;
	double s;

	for (k = 0; k < r; k++) {
		x[k][k] = 1 / x[k][k];
		for (j = k - 1; j >= 0; j--) {
			s = 0;
			for (i = j + 1; i <= k; i++)
				s -= x[i][j] * x[i][k];
			x[j][k] = s * x[j][j];
		}
	}
}

int main(int argc, char *argv[])
{
	int i, j, n, m, p, r, con, *col;  /* {\tt col} �͗�ԍ��̕\ */
	double s, t, rss;
	matrix x;
	vector b, normsq;  /* ��A�W��, �m����2�� */
	FILE *datafile;
#if PIVOTING
	vector initnormsq;  /* �����m����2�� */
#endif /* PIVOTING */

	if (argc != 2) error("�g�p�@: regress filename");
	datafile = open_data(argv[1], &n, &m);
	if (datafile == NULL) error("�f�[�^�s��");
	printf("�萔�����܂߂܂���(y/n)? ");
	con = (i = getchar()) == 'y' || i == 'Y';  p = m + con - 1;
	col = malloc(p * sizeof(int));
	x = new_matrix(p + 1, n);                       /* �L���̈���l�� */
	b = new_vector(p);  normsq = new_vector(p);
#if PIVOTING
	initnormsq = new_vector(p);                     /* �ŏ��̃m����2�� */
#endif /* PIVOTING */
	if (read_data(datafile, n, m, &x[con])) error("�f�[�^�s��");
	if (con) for (i = 0; i < n; i++) x[0][i] = 1;   /* �萔�� */
#if ! PIVOTING
	r = lsq(n, p, x, b, col, normsq);   /* �ŏ�2��@ (�s�{�b�g�����Ȃ�) */
#else /* PIVOTING */
	r = lsq(n, p, x, b, col, initnormsq, normsq); /* (�s�{�b�g��������) */
#endif /* PIVOTING */
	rss = innerproduct(n - r, &x[p][r], &x[p][r]);  /* �c��2��a */
	invr(r, x);                                     /* {\tt r} ���t�s��� */
	printf("�ϐ�  ��A�W��       �W���덷        t\n");
	for (j = 0; j < r; j++) {
		t = innerproduct(r - j, &x[j][j], &x[j][j]);  /* ���� */
		s = sqrt(t * rss / (n - r));
		printf("%4d  % #-14g % #-14g", col[j] + 1 - con, b[j], s);
		if (s > 0) printf("  % #-11.3g", fabs(b[j] / s));
		printf("\n");
	}
	printf("�c��2��a / ���R�x = %g / %d = %g\n",
		rss, n - r, rss / (n - r));
	return EXIT_SUCCESS;
}
