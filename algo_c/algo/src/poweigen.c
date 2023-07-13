/***********************************************************
	poweigen.c -- �ݏ�@
***********************************************************/
#include "matutil.c"  /* �s��p������W */
#include <math.h>
#define TEST  /* ���ꂪ����Ɠr���o�߂�� */

#define EPS       1E-6  /* �ŗL�x�N�g���̋��e�덷 */
#define MAX_ITER  200   /* �ő�J�Ԃ��� */
#define forall(i) for (i = 0; i < n; i++)

int power(int n, int m, matrix a, vector lambda, matrix x)
{
	int i, j, k, kk, iter;
	double s, s1, t, u, d, d1, e;
	vector xk, y;

	y = new_vector(n);  /* {\tt y[0..n-1]} �̋L���̈���m�� */
	kk = m;             /* ���ۂɋ��߂�ꂽ�ŗL�l�E�ŗL�x�̌� */
	for (k = 0; k < m; k++) { /* {\tt k} �Ԗڂ̌ŗL�l�E�ŗL�x�����߂� */
		xk = x[k];  t = 1 / sqrt(n);
		forall(i) xk[i] = t;   /* �傫��1�̏����l�x�N�g�� */
		d = s = 0;  iter = 0;
		do {
			d1 = d;  s1 = s;  s = e = 0;
			forall(i) {
				t = 0;
				forall(j) t += a[i][j] * xk[j];
				y[i] = t;  s += t * t;  /* $y = Ax$ */
			}
			s = sqrt(s);  if (s1 < 0) s = -s;  /* $s = \pm \| y \|$ */
			forall(i) {
				t = y[i] / s;  u = xk[i] - t;
				e += u * u;  xk[i] = t;  /* {\tt xk[]}: �ŗL�x�N�g�� */
			}
			if (e > 2) s = -s;  /* �x�N�g�������]�����Ȃ�ŗL�l�͕� */
			d = sqrt(e);  d1 -= d;
			#ifdef TEST
				printf("iter = %3d  lambda[%d] = %10.6f  "
					"||x' - x|| = %10.8f\n", iter, k, s, d);
			#endif
		} while (++iter < MAX_ITER && e > EPS * d1);
		if (iter >= MAX_ITER && kk == m) kk = k;
		lambda[k] = s;  /* �ŗL�l */
		if (k < m - 1)
			forall(i) forall(j)
				a[i][j] -= s * xk[i] * xk[j];
	}
	free_vector(y);
	return kk;  /* ���������ŗL�x�N�g���̐� */
}

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
	matrix a, b, x;
	vector lambda;

	printf("n = ");  scanf("%d", &n);
	printf("�����̎� (���̐���) = ");
	scanf("%ul", &seed);  seed |= 1;
	a = new_matrix(n, n);
	b = new_matrix(n, n);
	x = new_matrix(n, n);
	lambda = new_vector(n);
	forall(i) for (j = 0; j <= i; j++)
		a[i][j] = a[j][i] =
		b[i][j] = b[j][i] = rnd() - rnd();
	matprint(a, n, 7, "%10.6f");
	k = power(n, n, a, lambda, x);
	printf("���������ŗL�x�N�g���̐�: %d\n", k);
	printf("�ŗL�l:\n");
	vecprint(lambda, n, 5, "% -14g");
	e = 0;
	forall(i) forall(j) {
		s = b[i][j];
		forall(k) s -= lambda[k] * x[k][i] * x[k][j];
		e += s * s;
	}
	printf("��敽�ό덷: %g\n", sqrt(e / (n * n)));
	return EXIT_SUCCESS;
}
