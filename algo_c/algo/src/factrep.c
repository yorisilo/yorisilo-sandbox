/***********************************************************
	factrep.c -- �K��i�@
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define N  4
int main()
{
	int i, k, c[N + 2];

	for (k = 1; k <= N + 1; k++) c[k] = 0;  /* c[N+1] �͔Ԑl */
	i = 0;
	do {
		printf("%3d:", i++);
		for (k = N; k >= 1; k--) printf(" %d", c[k]);
		printf("\n");
		k = 1;
		while (c[k] == k) {  c[k] = 0;  k++;  }
		c[k]++;
	} while (k <= N);
	return EXIT_SUCCESS;
}
