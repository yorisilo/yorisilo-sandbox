/***********************************************************
	euler.c -- ��M����
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NMAX    100                     /* �_�̐��̏�� */
#define EDGEMAX 100                     /* ���̐��̏�� */
int adjacent[NMAX + 1][NMAX + 1];       /* �אڍs�� */
int position[EDGEMAX + 1];
int n, n_edge, edge, solution;          /* �_, ���̐�; ��, ���̔ԍ� */

void readgraph(void)                    /* �f�[�^���� */
{
	int i, j;

	if (scanf("%d%*[^\n]", &n) != 1 || n > NMAX) {  /* �_�̐� */
		n = 0;  return;
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) adjacent[i][j] = 0;
	while (scanf("%d%d%*[^\n]", &i, &j) == 2) {
		n_edge++;                       /* ���̐� */
		adjacent[i][j]++;
		adjacent[j][i]++;               /* �L���O���t�Ȃ炱�̍s�͍폜 */
	}
	printf("�אڍs��:\n");
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
		printf("\n");
	}
}

void visit(int i)
{
	int j;

	position[edge] = i;
	if (edge == n_edge) {
		printf("�� %d: ", ++solution);
		for (i = 0; i <= n_edge; i++) printf(" %d", position[i]);
		printf("\n");
	} else {
		for (j = 1; j <= n; j++) if (adjacent[i][j]) {
			adjacent[i][j]--;
			adjacent[j][i]--;  /* �L���O���t�Ȃ炱�̍s�͍폜 */
			edge++;  visit(j);  edge--;
			adjacent[i][j]++;
			adjacent[j][i]++;  /* �L���O���t�Ȃ炱�̍s�͍폜 */
		}
	}
}

int main()
{
	readgraph();                     /* �f�[�^��ǂ� */
	solution = edge = 0;  visit(1);  /* �_1����o�� */
	if (solution == 0) printf("���Ȃ�\n");
	return EXIT_SUCCESS;
}
