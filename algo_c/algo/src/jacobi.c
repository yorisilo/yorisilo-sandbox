/***********************************************************
	jacobi.c -- Jacobi (���R�r) �@
***********************************************************/
#include "matutil.c"  /* �s��p������W */
#include <math.h>
#define TEST

#define EPS         1E-6  /* ���e�덷 */
#define TINY        1E-20 /* 0 �ƌ��Ȃ��Ă悢�l */
#define MAX_ITER    100   /* �ő�̌J�Ԃ��� */
#define forall(i)   for (i = 0; i < n; i++)
#define rotate(a, i, j, k, l) {      \
	double x = a[i][j], y = a[k][l]; \
	a[i][j] = x * c - y * s;         \
	a[k][l] = x * s + y * c;         }

int jacobi(int n, matrix a, matrix w)
{
	int i, j, k, iter;
	double t, c, s, tolerance, offdiag;
	vector v;

	s = offdiag = 0;
	forall(j) {
		forall(k) w[j][k] = 0;
		w[j][j] = 1;  s += a[j][j] * a[j][j];
		for (k = j + 1; k < n; k++)
			offdiag += a[j][k] * a[j][k];
	}
	tolerance = EPS * EPS * (s / 2 + offdiag);
	for (iter = 1; iter <= MAX_ITER; iter++) {
		offdiag = 0;
		for (j = 0; j < n - 1; j++)
			for (k = j + 1; k < n; k++)
				offdiag += a[j][k] * a[j][k];
		#ifdef TEST
			printf("%4d: %g\n",
				iter, sqrt(2 * offdiag / (n * (n - 1))));
		#endif
		if (offdiag < tolerance) break;
		for (j = 0; j < n - 1; j++) {
			for (k = j + 1; k < n; k++) {
				if (fabs(a[j][k]) < TINY) continue;
				t = (a[k][k] - a[j][j]) / (2 * a[j][k]);
				if (t >= 0) t = 1 / (t + sqrt(t * t + 1));
				else        t = 1 / (t - sqrt(t * t + 1));
				c = 1 / sqrt(t * t + 1);
				s = t * c;  t *= a[j][k];
				a[j][j] -= t;  a[k][k] += t;  a[j][k] = 0;
				for (i = 0; i < j; i++)     rotate(a, i, j, i, k)
				for (i = j + 1; i < k; i++) rotate(a, j, i, i, k)
				for (i = k + 1; i < n; i++) rotate(a, j, i, k, i)
				forall(i)                   rotate(w, j, i, k, i)
			}
		}
	}
	if (iter > MAX_ITER) return EXIT_FAILURE;  /* �������� */
	for (i = 0; i < n - 1; i++) {
		k = i;  t = a[k][k];
		for (j = i + 1; j < n; j++)
			if (a[j][j] > t) {  k = j;  t = a[k][k];  }
		a[k][k] = a[i][i];  a[i][i] = t;
		v = w[k];  w[k] = w[i];  w[i] = v;
	}
	return EXIT_SUCCESS;  /* ���� */
}

/*************** �ȉ��̓e�X�g�p *****************/

#include <limits.h>
static unsigned long seed;
double rnd(void)  /* ����  0 < rnd() < 1 */
{
	return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main()
{
	int i, j, k, n;
	double s, e;
	matrix a, b, w;
	vector lambda;

	printf("n = ");  scanf("%d", &n);
	printf("�����̎� (���̐���) = ");
	scanf("%ul", &seed);  seed |= 1;
	a = new_matrix(n, n);
	b = new_matrix(n, n);
	w = new_matrix(n, n);
	lambda = new_vector(n);
	forall(i) for (j = 0; j <= i; j++)
		a[i][j] = a[j][i] =
		b[i][j] = b[j][i] = rnd() - rnd();
	matprint(a, n, 7, "%10.6f");
	if (jacobi(n, a, w) == EXIT_FAILURE)
		printf("�������܂���\n");
	forall(i) lambda[i] = a[i][i];
	printf("�ŗL�l:\n");
	vecprint(lambda, n, 5, "% -14g");
	e = 0;
	forall(i) forall(j) {
		s = b[i][j];
		forall(k) s -= lambda[k] * w[k][i] * w[k][j];
		e += s * s;
	}
	printf("��敽�ό덷: %g\n", sqrt(e / (n * n)));
	return EXIT_SUCCESS;
}
