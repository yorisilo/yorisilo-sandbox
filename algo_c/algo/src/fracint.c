/***********************************************************
	fracint.c -- �t���N�^�����
***********************************************************/
#include "window.c"  /* ���[�W���f���ŃR���p�C�� */

double left = 0, bottom = 0, right = 100, top = 100,       /* ���W�͈̔� */
	   x[] = { 0, 30, 60, 100 }, y[] = { 0, 50, 40, 10 };  /* �e�_�̍��W */

#define N (sizeof x / sizeof x[0] - 1)

int main()
{
	int i, j;
	double p, q, a[N], c[N], d[N], e[N], f[N];

	/* �A�t�B���ϊ������߂� */
	q = x[N] - x[0];
	for (i = 0; i < N; i++) {
		printf("d[%d] = ", i);  scanf("%lf", &d[i]);
		a[i] = (x[i+1] - x[i]) / q;
		e[i] = (x[N] * x[i] - x[0] * x[i+1]) / q;
		c[i] = (y[i+1] - y[i] - d[i] * (y[N] - y[0])) / q;
		f[i] = (x[N] * y[i] - x[0] * y[i+1] -
				d[i] * (x[N] * y[0] - x[0] * y[N])) / q;
	}
	/* �A�g���N�^���v���b�g���� */
	gr_on();
	gr_window(left, bottom, right, top, 0, 0);
	p = x[0];  q = y[0];
	for (i = 0; i < 5000; i++) {
		j = rand() / (RAND_MAX / N + 1);
		q = c[j] * p + d[j] * q + f[j];
		p = a[j] * p            + e[j];
		gr_wdot(p, q, WHITE);
	}
	hitanykey();
	return EXIT_SUCCESS;
}
