/***********************************************************
	dfs.c -- �c�`�T��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define NMAX 100                                /* �_�̐��̏�� */
char adjacent[NMAX + 1][NMAX + 1];              /* �אڍs�� */

int n = 7;                                      /* �_�̐� (��) */
int data[] = { 1, 2, 2, 3, 1, 3, 2, 4, 5, 7 };  /* �f�[�^ (��) */

void readgraph(void)  /* �O���t���� */
{
	int i, j, k;

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) adjacent[i][j] = 0;
	for (k = 0; k < (sizeof data) / (sizeof *data); k++) {
		if (k % 2 == 0) i = data[k];
		else {
			j = data[k];
			adjacent[i][j] = adjacent[j][i] = 1;
		}
	}
	printf("�אڍs��:\n");
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
		printf("\n");
	}
}

char visited[NMAX + 1];  /* �K�ꂽ�Ȃ�1 */

void visit(int i)  /* �_ {\tt i} ��K��� (�ċA�I) */
{
	int j;

	printf(" %d", i);  visited[i] = 1;
	for (j = 1; j <= n; j++)
		if (adjacent[i][j] && ! visited[j]) visit(j);
}

int main()
{
	int i, count;

	readgraph();                              /* �O���t�̃f�[�^��ǂ� */
	for (i = 1; i <= n; i++) visited[i] = 0;  /* �܂��ǂ����K��Ă��Ȃ� */
	printf("�A������:\n");
	count = 0;                                /* �A�������𐔂��� */
	for (i = 1; i <= n; i++)
		if (! visited[i]) {
			printf("%3d:", ++count);
			visit(i);  printf("\n");
		}
	return EXIT_SUCCESS;
}
