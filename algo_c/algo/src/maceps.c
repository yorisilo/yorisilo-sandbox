/***********************************************************
	maceps.c -- �@�B�G�v�V����
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	float e, w;

	printf(" e              1 + e          (1 + e) - 1   \n");
	printf("-------------- -------------- -------------- \n");
	e = 1;  w = 1 + e;
	while (w > 1) {
		printf("% -14g % -14g % -14g\n", e, w, w - 1);
		e /= 2;  w = 1 + e;
	}
	return EXIT_SUCCESS;
}
