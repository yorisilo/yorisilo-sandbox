/***********************************************************
	ishi1.c -- �Ύ��Q�[�� 1
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, m, x, r, my_turn;

	printf("�Ō�ɐ΂���������������ł�. �p�X�͂ł��܂���.\n");
	printf("�΂̐�? ");  scanf("%d", &n);
	printf("�P��Ɏ���ő�̐΂̐�? ");  scanf("%d", &m);
	if (n < 1 || m < 1) return EXIT_FAILURE;
	for (my_turn = 1; n != 0; my_turn ^= 1) {
		if (my_turn) {
			x = (n - 1) % (m + 1);  if (x == 0) x = 1;
			printf("���� %d �̐΂����܂�.\n", x);
		} else do {
			printf("�����܂���? ");
			r = scanf("%d", &x);  scanf("%*[^\n]");
		} while (r != 1 || x <= 0 || x > m || x > n);
		n -= x;  printf("�c��� %d �ł�.\n", n);
	}
	if (my_turn) printf("���Ȃ��̕����ł�!\n");
	else         printf("���̕����ł�!\n");
	return EXIT_SUCCESS;
}
