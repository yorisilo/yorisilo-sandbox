/***********************************************************
	multprec.c -- ���{�����Z
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define RADIXBITS 15                    /* ��̃r�b�g�� */
#define RADIX (1U << RADIXBITS)                   /* � */
#define N  225    /* RADIX�i�@�ŏ�����N�ʂ܂� */
#define M  250    /* 10�i�ŏ����� 4�~M �ʂ܂� */

typedef unsigned int   uint;    /* 16�r�b�g�ȏ� */
typedef unsigned short ushort;  /* 16�r�b�g�ȏ� */
typedef unsigned long  ulong;   /* 32�r�b�g�ȏ� */

void error(char message[])
{
	printf("%s\n", message);  exit(EXIT_FAILURE);
}

void add(ushort a[], ushort b[], ushort c[])
{
	int i;
	uint u;

	u = 0;
	for (i = N; i >= 0; i--) {
		u += a[i] + b[i];
		c[i] = u & (RADIX - 1);  u >>= RADIXBITS;
	}
	if (u) error("Overflow");
}

void sub(ushort a[], ushort b[], ushort c[])
{
	int i;
	uint u;

	u = 0;
	for (i = N; i >= 0; i--) {
		u = a[i] - b[i] - u;
		c[i] = u & (RADIX - 1);
		u = (u >> RADIXBITS) & 1;
	}
	if (u) error("Overflow");
}

void muls(ushort a[], uint x, ushort b[])
{
	int i;
	ulong t;

	t = 0;
	for (i = N; i >= 0; i--) {
		t += (ulong) a[i] * x;
		b[i] = (uint) t & (RADIX - 1);  t >>= RADIXBITS;
	}
	if (t) error("Overflow");
}

int divs(int m, ushort a[], uint x, ushort b[])
{
	int i;
	ulong t;

	t = 0;
	for (i = m; i <= N; i++) {
		t = (t << RADIXBITS) + a[i];
		b[i] = t / x;  t %= x;
	}
	if (2 * t >= x)  /* �l�̌ܓ� */
		for (i = N; ++b[i] & RADIX; i--) b[i] &= RADIX - 1;
	return (b[m] != 0) ? m : (m + 1);  /* 0�łȂ��ō��ʒu */
}

void print(ushort a[])
{
	int i;

	printf("%5u.", a[0]);
	for (i = 0; i < M; i++) {
		a[0] = 0;  muls(a, 10000, a);
		printf("%04u", a[0]);
	}
	printf("\n");
}

ushort a[N+1], t[N+1], u[N+1];  /* e() �����Ȃ� u[] �͕s�v. */

void e(void)  /* ���R�ΐ��̒� */
{
	int m;
	uint k;

	for (m = 0; m <= N; m++) a[m] = t[m] = 0;  /* a := t := 0 */
	a[0] = 2;  a[1] = t[1] = RADIX / 2;        /* a := 2.5, t := 0.5 */
	k = 3;  m = 1;
	while ((m = divs(m, t, k, t)) <= N) {      /* t := t/k */
		add(a, t, a);                          /* a := a + t */
		if (++k == RADIX) error("�������������܂�");
	}
	print(a);
}

void pi(void)  /* �~���� (Machin�̌���) */
{
	int i, m;
	uint k;

	t[0] = 16;  for (i = 1; i <= N; i++) t[i] = 0;   /* t := 16 */
	divs(0, t, 5, t);                                /* t := t/5 */
	for (i = 0; i <= N; i++) a[i] = t[i];            /* a := t */
	i = m = 0;  k = 1;
	for ( ; ; ) {
		if ((m = divs(m, t, 25, t)) > N) break;      /* t := t/25 */
		if ((k += 2) >= RADIX) error("�������������܂�");
		while (i < m) u[i++] = 0;
		if (divs(m, t, k, u) > N) break;             /* u := t/k */
		if (k & 2) sub(a, u, a);  else add(a, u, a); /* a := a -+ u */
	}
	t[0] = 4;  for (i = 1; i <= N; i++) t[i] = 0;    /* t := 4 */
	divs(0, t, 239, t);                              /* t := t/239 */
	sub(a, t, a);                                    /* a :=a - t */
	i = m = 0;  k = 1;
	for ( ; ; ) {
		if ((m = divs(m, t, 239, t)) > N) break;     /* t := t/239 */
		if ((m = divs(m, t, 239, t)) > N) break;     /* t := t/239 */
		if ((k += 2) >= RADIX) error("�������������܂�");
		while (i < m) u[i++] = 0;
		if (divs(m, t, k, u) > N) break;             /* u := t/k */
		if (k & 2) add(a, u, a);  else sub(a, u, a); /* a := a +- u */
	}
	print(a);
}

int main()
{
	e();
	pi();
	return EXIT_SUCCESS;
}
