/***********************************************************
	chaos.c -- �J�I�X�ƃA�g���N�^
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i;
	double p, k;

	printf("���萔: ");  scanf("%lf", &k);
	printf("�����l  : ");  scanf("%lf", &p);
	for (i = 1; i <= 100; i++) {
		printf("%10.3f", p);
		if (i % 4 == 0) printf("\n");
		p += k * p * (1 - p);
	}
	return EXIT_SUCCESS;
}
