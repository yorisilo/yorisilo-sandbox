/***********************************************************
	toposort.c -- �g�|���W�J���E�\�[�e�B���O
	�g�p��: toposort <toposort.dat
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NMAX 100                                /* �_�̐��̏�� */
char adjacent[NMAX + 1][NMAX + 1];              /* �אڍs�� */
char visited[NMAX + 1];                         /* �K�ꂽ�� */

int n;                                          /* �_�̐� */

void readgraph(void)                            /* �f�[�^���� */
{
	int i, j;

	if (scanf("%d%*[^\n]", &n) != 1 || n > NMAX) {
		n = 0;  return;
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) adjacent[i][j] = 0;
	while (scanf("%d%d%*[^\n]", &i, &j) == 2)
		adjacent[i][j] = 1;
	printf("�אڍs��:\n");
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
		printf("\n");
	}
}

enum {NEVER, JUST, ONCE};

void visit(int i)
{
	int j;

	visited[i] = JUST;
	for (j = 1; j <= n; j++) {
		if (! adjacent[j][i]) continue;
		if (visited[j] == NEVER) visit(j);
		else if (visited[j] == JUST) {
			printf("\n�T�C�N������!n");  exit(EXIT_FAILURE);
		}
	}
	visited[i] = ONCE;  printf(" %d", i);
}

int main()
{
	int i;

	readgraph();  /* �f�[�^ {\tt n}, {\tt adjacent[1..n][1..n]} ��ǂ� */
	for (i = 1; i <= n; i++) visited[i] = NEVER;
	printf("�g�|���W�J���E�\�[�e�B���O�̌���:\n");
	for (i = 1; i <= n; i++)
		if (visited[i] == NEVER) visit(i);
	printf("\n");
	return EXIT_SUCCESS;
}
