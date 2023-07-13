/***********************************************************
	factanal.c -- ���q����
***********************************************************/
#include "statutil.c"     /* ���ϗʃf�[�^���̓��[�`�� */

#define EPS         1E-6  /* ��Ίp�����̋��e�덷 */
#define MAX_ITER    100   /* �ő�̌J�Ԃ��� */

double house(int n, vector x)  /* Householder�ϊ� */
{
	int i;
	double s, t;

	s = sqrt(innerproduct(n, x, x));  /* ���ς̕�����, ���Ȃ킿�傫�� */
	if (s != 0) {
		if (x[0] < 0) s = -s;
		x[0] += s;  t = 1 / sqrt(x[0] * s);
		for (i = 0; i < n; i++) x[i] *= t;
	}
	return -s;
}

void tridiagonalize(int n, matrix a, vector d, vector e) /* 3�d�Ίp�� */
{
	int i, j, k;
	double s, t, p, q;
	vector v, w;

	for (k = 0; k < n - 2; k++) {
		v = a[k];  d[k] = v[k];
		e[k] = house(n - k - 1, &v[k + 1]);
		if (e[k] == 0) continue;
		for (i = k + 1; i < n; i++) {
			s = 0;
			for (j = k + 1; j < i; j++) s += a[j][i] * v[j];
			for (j = i;     j < n; j++) s += a[i][j] * v[j];
			d[i] = s;
		}
		t = innerproduct(n-k-1, &v[k+1], &d[k+1]) / 2;
		for (i = n - 1; i > k; i--) {
			p = v[i];  q = d[i] - t * p;  d[i] = q;
			for (j = i; j < n; j++)
				a[i][j] -= p * d[j] + q * v[j];
		}
	}
	if (n >= 2) {  d[n - 2] = a[n - 2][n - 2];
	               e[n - 2] = a[n - 2][n - 1];  }
	if (n >= 1)    d[n - 1] = a[n - 1][n - 1];
	for (k = n - 1; k >= 0; k--) {
		v = a[k];
		if (k < n - 2) {
			for (i = k + 1; i < n; i++) {
				w = a[i];
				t = innerproduct(n-k-1, &v[k+1], &w[k+1]);
				for (j = k + 1; j < n; j++)
					w[j] -= t * v[j];
			}
		}
		for (i = 0; i < n; i++) v[i] = 0;
		v[k] = 1;
	}
}

int eigen(int n, matrix a, vector d, vector e)
{
	int i, j, k, h, iter;
	double c, s, t, w, x, y;
	vector v;

	tridiagonalize(n, a, d, &e[1]);  /* 3�d�Ίp�� */
	e[0] = 0;  /* �Ԑl */
	for (h = n - 1; h > 0; h--) {  /* �s��̃T�C�Y�����������Ă��� */
		j = h;
		while (fabs(e[j]) > EPS * (fabs(d[j - 1]) + fabs(d[j])))
			j--;  /* $\mbox{\tt e[$j$]} \ne 0$ �̃u���b�N�̎n�_�������� */
		if (j == h) continue;
		iter = 0;
		do {
			if (++iter > MAX_ITER) return EXIT_FAILURE;
			w = (d[h - 1] - d[h]) / 2;
			t = e[h] * e[h];
			s = sqrt(w * w + t);  if (w < 0) s = -s;
			x = d[j] - d[h] + t / (w + s);  y = e[j + 1];
			for (k = j; k < h; k++) {
				if (fabs(x) >= fabs(y)) {
					t = -y / x;  c = 1 / sqrt(t * t + 1);
					s = t * c;
				} else {
					t = -x / y;  s = 1 / sqrt(t * t + 1);
					c = t * s;
				}
				w = d[k] - d[k + 1];
				t = (w * s + 2 * c * e[k + 1]) * s;
				d[k] -= t;  d[k + 1] += t;
				if (k > j) e[k] = c * e[k] - s * y;
				e[k + 1] += s * (c * w - 2 * s * e[k + 1]);
				for (i = 0; i < n; i++) {           /* �ŗL�x */
					x = a[k][i];  y = a[k + 1][i];  /* �N�g�� */
					a[k    ][i] = c * x - s * y;    /* ������ */
					a[k + 1][i] = s * x + c * y;    /* �Ȃ��� */
				}                                   /* ��s�v */
				if (k < h - 1) {
					x = e[k + 1];  y = -s * e[k + 2];
					e[k + 2] *= c;
				}
			}
		} while (fabs(e[h]) >
				EPS * (fabs(d[h - 1]) + fabs(d[h])));
	}
	for (k = 0; k < n - 1; k++) {
		h = k;  t = d[h];
		for (i = k + 1; i < n; i++)
			if (d[i] > t) {  h = i;  t = d[h];  }
		d[h] = d[k];  d[k] = t;
		v = a[h];  a[h] = a[k];  a[k] = v;
	}
	return EXIT_SUCCESS;
}
/*
  {\tt r[0..m-1][0..m-1]} �ɓ��������֌W���̍s��ɑ΂��Ĉ��q���͂��s��,
  {\tt nfac} ($< {\tt m}) �̋��ʈ��q�𒊏o����.
  {\tt r} �̑Ίp�����͋��ʐ��̐���l�ŏ㏑�������.
  {\tt q[$k$][$j$]} �ɂ͑� $j + 1$ �ϐ��̑� $k + 1$ ���q���ח� ($0 \le
  k < {\tt nfac}$, $0 \le j < {\tt m}$ ������.
*/
void factor(int m, int nfac, matrix r, matrix q,
            vector lambda, vector work)
{
	int i, j, k, iter, maxiter;
	double s, t, percent;

	iter = maxiter = 0;
	for ( ; ; ) {
		if (++iter > maxiter) {
			printf("�J�Ԃ��� (0:�J�Ԃ��I��) ? ");
			scanf("%d", &i);  if (i <= 0) break;
			maxiter += i;
		}
		for (j = 0; j < m; j++) for (k = 0; k < m; k++)
			q[j][k] = r[j][k];
		if (eigen(m, q, lambda, work)) error("�������܂���");
		s = innerproduct(m - nfac, &lambda[nfac], &lambda[nfac]);
		printf("%3d: ��Ίp������RMS�덷 %.3g\n",
			iter, sqrt(s / (m * (m - 1)))); /* RMS: root mean square (2��̕��ς̕�����) */
		for (j = 0; j < m; j++) {
			s = 0;
			for (k = 0; k < nfac; k++)
				s += lambda[k] * q[k][j] * q[k][j];
			r[j][j] = s;  /* ���ʐ� */
		}
	}
	t = 0;  /* trace */
	for (k = 0; k < m; k++) t += lambda[k];
	printf("���q    �ŗL�l     ��  �ݐρ�\n");
	s = 0;
	for (k = 0; k < m; k++) {
		printf((k < nfac) ? " %3d " : "(%3d)", k + 1);
		percent = 100 * lambda[k] / t;  s += percent;
		printf(" %8.4f  %5.1f  %5.1f\n", lambda[k], percent, s);
	}
	printf("���v  %8.4f  %5.1f\n", t, s);
	for (k = 0; k < nfac; k++)
		work[k] = sqrt(fabs(lambda[k]));    /* {\tt lambda[k]} �͕����� */
	printf("�ϐ�  ���ʐ�   ���q���ח�\n");
	for (j = 0; j < m; j++) {
		printf("%4d  %6.3f ", j + 1, r[j][j]);
		for (k = 0; k < nfac; k++) {
			q[k][j] *= work[k];
			if (k < 9) printf("%7.3f", q[k][j]);
		}
		printf("\n");
	}
#ifdef CHECK  /* �덷�̃`�F�b�N�p */
	t = 0;
	for (j = 0; j < m; j++) for (k = 0; k < j; k++) {
		s = 0;
		for (i = 0; i < nfac; i++) s += q[i][j] * q[i][k];
		t += (r[j][k] - s) * (r[j][k] - s);
	}
	printf("���q���חʂ���Č��������֌W����RMS�덷: %g\n",
		sqrt(t / (m * (m - 1) / 2)));
#endif /* CHECK */
}
/*
  ���q���͂̃��C�����[�`��. �P�ɑ��֌W�������߂邾���ł��邪,
  �f�[�^����L���Ɉ�x�ɓǂݍ��ނ̂łȂ�,
  �Q�������g���ĕ���, ���U, ���֌W�����X�V������@��p���Ă���.
*/
int main(int argc, char *argv[])
{
	int i, j, k, n, m, nfac;
	double t;
	vector mean, lambda, work;  /* ����, �ŗL�l, ��Ɨp */
	matrix r, q;                /* ���֌W��, �ŗL�x�N�g�� */
	FILE *datafile;

	if (argc != 2) error("�g�p�@: factanal filename");
	datafile = open_data(argv[1], &n, &m);
	if (datafile == NULL) error("�f�[�^�s��");
	r = new_matrix(m, m);  q = new_matrix(m, m);
	mean = new_vector(m);  lambda = new_vector(m);
	work = new_vector(m);
	for (j = 0; j < m; j++) {
		mean[j] = 0;
		for (k = 0; k <= j; k++) r[j][k] = 0;
	}
	for (i = 0; i < n; i++) for (j = 0; j < m; j++) {
		t = getnum(datafile);                          /* ���l���� */
		if (missing(t)) error("�f�[�^�s��");           /* �����l���G���[ */
		work[j] = t - mean[j];  mean[j] += work[j] / (i + 1);
		for (k = 0; k <= j; k++)
			r[j][k] += i * work[j] * work[k] / (i + 1);
	}
	for (j = 0; j < m; j++) {
		work[j] = sqrt(r[j][j]);  r[j][j] = 1;
		for (k = 0; k < j; k++) {
			r[j][k] /= work[j] * work[k];  r[k][j] = r[j][k];
		}
	}
	t = 1 / sqrt(n - 1.0);
	printf("�ϐ�  ���ϒl        �W���΍�\n");
	for (j = 0; j < m; j++)
		printf("%4d  % -12.5g  % -12.5g\n",
			j + 1, mean[j], t * work[j]);
	printf("���֌W��\n");                     /* �������������\�� */
	for (j = 0; j < m; j++) {
		for (k = 0; k <= j; k++) printf("%8.4f", r[j][k]);
		printf("\n");
	}
	for ( ; ; ) {
		printf("\n���ʈ��q�̐� (0:���s�I��) ? ");
		scanf("%d", &nfac);
		if (nfac > m) nfac = m;
		if (nfac < 1) break;
		factor(m, nfac, r, q, lambda, work);
	}
	return EXIT_SUCCESS;
}
