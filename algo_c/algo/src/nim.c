/***********************************************************
	nim.c -- �O�R������
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a[4], i, j, imax, max, n, r, x, my_turn;

	for (i = 1; i <= 3; i++) {
		printf("%d �Ԃ̎R�̐΂̐�? ", i);  scanf("%d", &a[i]);
		if (a[i] <= 0) return EXIT_FAILURE;
	}
	for (my_turn = 1; ; my_turn ^= 1) {
		max = 0;
		for (i = 1; i <= 3; i++) {
			printf(" %d ", i);
			for (j = 1; j <= a[i]; j++) printf("*");
			printf("\n");
			if (a[i] > max) {
				max = a[i];  imax = i;
			}
		}
		if (max == 0) break;
		if (my_turn) {
			printf("���̔Ԃł�.\n");
			x = a[1] ^ a[2] ^ a[3];  /* �r���I�_���a */
			j = 0;
			for (i = 1; i <= 3; i++)
				if (a[i] > (a[i] ^ x)) j = i;
			if (j != 0) a[j] ^= x;  else a[imax]--;
		} else {
			do {
				printf("���Ԃ̎R����Ƃ�܂���? ");
				r = scanf("%d", &i);  scanf("%*[^\n]");
			} while (r != 1 || i < 1 || i > 3 || a[i] == 0);
			do {
				printf("���Ƃ�܂���? ");
				r = scanf("%d", &n);  scanf("%*[^\n]");
			} while (r != 1 || n <= 0 || n > a[i]);
			a[i] -= n;
		}
	}
	if (my_turn) printf("���Ȃ��̏����ł�!\n");
	else         printf("���̏����ł�!\n");
	return EXIT_SUCCESS;
}
