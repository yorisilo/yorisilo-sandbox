/***********************************************************
	swap.c -- �l�̌���
***********************************************************/
void swap(int *x, int *y)
{
	int temp;

	temp = *x;  *x = *y;  *y = temp;
}

void swap1(int *x, int *y)
{
	*y ^= *x;  *x ^= *y;  *y ^= *x;
}

void swap2(int *x, int *y)
{
	*y = *x - *y;  *x -= *y;  *y += *x;
}

/*************** �ȉ��̓e�X�g�p *****************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x, y;

	printf("x = ");  scanf("%d", &x);
	printf("y = ");  scanf("%d", &y);

	printf("x = %d, y = %d\n", x, y);
	swap(&x, &y);
	printf("x = %d, y = %d\n", x, y);
	swap1(&x, &y);
	printf("x = %d, y = %d\n", x, y);
	swap2(&x, &y);
	printf("x = %d, y = %d\n", x, y);

	return EXIT_SUCCESS;
}
