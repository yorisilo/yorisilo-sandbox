/***********************************************************
	marriage.c -- ����Ȍ����̖��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define N  3  /* �e���̐l�� */

int boy[N+1], girl[N+1][N+1], position[N+1], rank[N+1][N+1];

int main()
{
	int b, g, r, s, t;

	for (g = 1; g <= N; g++) {  /* �e�����̍D�� */
		for (r = 1; r <= N; r++) {
			scanf("%d", &b);  rank[g][b] = r;
		}
		boy[g] = 0;  rank[g][0] = N + 1;  /* �Ԑl */
	}
	for (b = 1; b <= N; b++) {  /* �e�j���̍D�� */
		for (r = 1; r <= N; r++) scanf("%d", &girl[b][r]);
		position[b] = 0;
	}
	for (b = 1; b <= N; b++) {
		s = b;
		while (s != 0) {
			g = girl[s][++position[s]];
			if (rank[g][s] < rank[g][boy[g]]) {
				t = boy[g];  boy[g] = s;  s = t;
			}
		}
	}
	for (g = 1; g <= N; g++)
		printf("�� %d - �j %d\n", g, boy[g]);
	return EXIT_SUCCESS;
}
