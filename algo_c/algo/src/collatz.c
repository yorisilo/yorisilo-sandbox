/***********************************************************
	collatz.c -- Collatz (�R���b�c) �̗\�z
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LIMIT ((ULONG_MAX - 1) / 3)

int main()
{
	unsigned long  n;

	printf("n = ");  scanf("%lu", &n);
	while (n > 1) {
		if (n & 1) {  /* � */
			if (n > LIMIT) {
				printf("\nOverflow\n");  return 1;
			} else n = 3 * n + 1;
		} else n /= 2;
		printf(" %lu", n);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
