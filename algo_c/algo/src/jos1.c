/***********************************************************
	jos1.c -- Josephus (���Z�t�X) �̖��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int j, k, n, p;

	printf("�l��? ");  scanf("%d", &n);
	printf("���l����? ");  scanf("%d", &p);
	k = 1;
	for (j = 2; j <= n; j++) {
		k = (k + p) % j;
		if (k == 0) k = j;
	}
	printf("%d �Ԃ̐l���c��܂�\n", k);
	return EXIT_SUCCESS;
}
