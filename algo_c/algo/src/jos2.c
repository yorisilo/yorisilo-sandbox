/***********************************************************
	jos2.c -- Josephus (���Z�t�X) �̖��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int k, n, p;

	printf("�l��? ");  scanf("%d", &n);
	printf("���l����? ");  scanf("%d", &p);
	k = p - 1;
	while (k < (p - 1) * n)
		k = (p * k) / (p - 1) + 1;
	printf("%d �Ԃ̐l���c��܂�\n", p * n - k);
	return EXIT_SUCCESS;
}
