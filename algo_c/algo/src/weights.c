/***********************************************************
	weights.c -- ���̖��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int k, x, r;
	char side[2][3] = { "��", "�E" };

	printf("���O�������͂���܂���? ");  scanf("%d", &x);
	printf("�͂�����̂����̎M�ɏ悹�Ă�������.\n");
	k = 1;
	while (x > 0) {
		r = x % 3;  x /= 3;
		if (r != 0) {
			printf("%5d�O�����̏d���%s�̎M�ɏ悹�܂�.\n",
				k, side[r - 1]);
			if (r == 2) x++;
		}
		k *= 3;
	}
	return EXIT_SUCCESS;
}
