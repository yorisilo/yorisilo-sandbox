/***********************************************************
	gasket.c -- Sierpi\'{n}ski (�V�F���s���X�L�[) �̎O�p�`
***********************************************************/
#include "window.c"  /* ���[�W���f���ŃR���p�C�� */
#define N  65

void triangle(int i, int j)
{
	gr_wline(i, j+1, i-1, j, WHITE);
	gr_wline(i-1, j, i+1, j, WHITE);
	gr_wline(i+1, j, i, j+1, WHITE);
}

int main()
{
	int i, j;
	static char a[2 * N + 1], b[2 * N + 1];

	gr_on();  gr_window(0, 0, 2 * N, N, 0, 0);
	for (i = 0; i <= 2 * N; i++) a[i] = 0;
	a[N] = 1;
	for (j = 1; j < N; j++) {
		for (i = N - j; i <= N + j; i++)
			if (a[i]) triangle(i, N - j);
		for (i = N - j; i <= N + j; i++)
			b[i] = (a[i - 1] != a[i + 1]);
		for (i = N - j; i <= N + j; i++)
			a[i] = b[i];
	}
	hitanykey();
	return EXIT_SUCCESS;
}
