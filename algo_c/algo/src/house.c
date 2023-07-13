/***********************************************************
	house.c -- Householder (�n�E�X�z���_�[) �ϊ�
***********************************************************/
#include "matutil.c"  /* �s��p������W */
#include <math.h>

double house(int n, vector x)
{
	int i;
	double s, t;

	s = sqrt(innerproduct(n, x, x));  /* ���ς̕�����, ���Ȃ킿�x�N�g�� $x$ �̑傫�� */
	if (s != 0) {
		if (x[0] < 0) s = -s;
		x[0] += s;  t = 1 / sqrt(x[0] * s);
		for (i = 0; i < n; i++) x[i] *= t;
	}
	return -s;
}

/************** �ȉ��̓e�X�g�p ****************/

#include <limits.h>
static unsigned long seed;

double rnd(void)  /* ����  0 < rnd() < 1 */
{
	return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main()
{
	int i, n;
	double s, x1;
	vector x, v;

	printf("n = ");  scanf("%d", &n);
	printf("�����̎� (���̐���) = ");
	scanf("%ul", &seed);  seed |= 1;
	x = new_vector(n);  v = new_vector(n);
	s = 0;
	for (i = 0; i < n; i++) {
		x[i] = v[i] = rnd() - rnd();
		s += x[i] * x[i];
	}
	printf("x:\n");
	vecprint(x, n, 7, "%10.6f");
	printf("||x|| = %g\n", sqrt(s));

	x1 = house(n, v);  /* Householder�ϊ� */

	printf("x' = (%g, 0, ..., 0)\n", x1);  /* �ϊ���̃x�N�g�����o�� */

	s = 0;  /* �ȉ��͊m�F */
	for (i = 0; i < n; i++) s += v[i] * x[i];
	for (i = 0; i < n; i++) x[i] -= s * v[i];
	s = (x[0] - x1) * (x[0] - x1);
	for (i = 1; i < n; i++) s += x[i] * x[i];
	printf("��敽�ό덷: %g\n", sqrt(s / n));

	return EXIT_SUCCESS;
}
