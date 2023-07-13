/***********************************************************
	princo.c -- �听������
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
			j--;  /* $e[j] \ne 0$ �̃u���b�N�̎n�_�������� */
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

void princo(int n, int m, matrix x, matrix q, vector lambda,
            vector work, int method)
{
	int i, j, k, ndf;
	double s, t, percent;

	ndf = n - (method != 0);                      /* ���R�x */
	printf("�ϐ�  ���ϒl        %s\n",
		(method == 0) ? "�q�l�r" : "�W���΍�");
	for (j = 0; j < m; j++) {
		t = 0;
		for (i = 0; i < n; i++) t += x[j][i];
		t /= n;
		if (method != 0) for (i = 0; i < n; i++) x[j][i] -= t;
		q[j][j] = innerproduct(n, x[j], x[j]) / ndf;
		s = sqrt(q[j][j]);
		printf("%4d  % -12.5g  % -12.5g\n", j + 1, t, s);
		if (method == 2) {
			q[j][j] = 1;
			for (i = 0; i < n; i++) x[j][i] /= s;
		}
	}
	for (j = 0; j < m; j++) for (k = 0; k < j; k++)
		q[j][k] = q[k][j] = innerproduct(n, x[j], x[k]) / ndf;
	if (eigen(m, q, lambda, work)) error("�������܂���");
	t = 0;  /* trace */
	for (k = 0; k < m; k++) t += lambda[k];
	printf("�听��  �ŗL�l       ��   �ݐρ�\n");
	s = 0;
	for (k = 0; k < m; k++) {
		percent = 100 * lambda[k] / t;  s += percent;
		printf("%4d  % -12.5g  %5.1f  %5.1f\n",
			k + 1, lambda[k], percent, s);
	}
	printf("���v  % -12.5g  %5.1f\n\n", t, s);
	printf("�ϐ�  �d��\n");
	for (j = 0; j < m; j++) {
		printf("%4d", j + 1);
		for (k = 0; k < m && k < 5; k++)
			printf("%11.6f   ", q[k][j]);
		printf("\n");
	}
	printf("��  �听��\n");
	for (i = 0; i < n; i++) {
		printf("%4d  ", i + 1);
		for (k = 0; k < m && k < 5; k++) {
			s = 0;
			for (j = 0; j < m; j++) s += q[k][j] * x[j][i];
			printf("% -14.5g", s);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	int n, m, method;
	vector lambda, work;  /* �ŗL�l, ��Ɨp */
	matrix x, q;          /* �f�[�^, �����s�� */
	FILE *datafile;

	if (argc != 2) error("�g�p�@: princo filename");
	printf("0:���̂܂� 1:���ς����� 2:����ɕW���΍��Ŋ��� ?");
	scanf("%d", &method);
	if (method < 0 || method > 2) error("�����");
	datafile = open_data(argv[1], &n, &m);
	if (datafile == NULL) error("�f�[�^�s��");
	x = new_matrix(m, n);  q = new_matrix(m, m);
	lambda = new_vector(m);  work = new_vector(m);
	if (read_data(datafile, n, m, x)) error("�f�[�^�s��");
	princo(n, m, x, q, lambda, work, method);  /* �听������ */
	return EXIT_SUCCESS;
}
