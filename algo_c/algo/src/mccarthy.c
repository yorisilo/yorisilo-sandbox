/***********************************************************
	mccarthy.c -- McCarthy (�}�b�J�[�V�[) �֐�
***********************************************************/
#define N 100

int McCarthy(int x)
{
	if (x > N) return x - 10;
	/* else */ return McCarthy(McCarthy(x + 11));
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x;

	for ( ; ; ) {
		printf("0 �ȏ� %d �ȉ��̐��� x: ", N);
		scanf("%d", &x);
		if (x < 0 || x > N) break;
		printf("McCarthy(x) = %d\n", McCarthy(x));
	}
	return EXIT_SUCCESS;
}
