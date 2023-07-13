/***********************************************************
	primes.c -- �f��
***********************************************************/
#define N 168
int prime[N];

void generate_primes(void)
{
	int j, k, x;

	prime[0] = 2;  x = 1;  k = 1;
	while (k < N) {
		x += 2;  j = 0;
		while (j < k && x % prime[j] != 0) j++;
		if (j == k) prime[k++] = x;
	}
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;

	generate_primes();
	printf("�f���\");
	for (i = 0; i < N; i++) {
		if (i % 10 == 0) printf("\n");
		printf("%5d", prime[i]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
