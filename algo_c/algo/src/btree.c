/***********************************************************
	btree.c -- B��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define M  2  /* 1�y�[�W�̃f�[�^���̏���̔��� */

typedef int keytype;                 /* �T���̃L�[�̌^ */
typedef enum {FALSE, TRUE} boolean;  /* ${\tt FALSE} = 0$, ${\tt TRUE} = 1$ */

typedef struct page {                /* �y�[�W�̒�` */
	int n;                           /* �f�[�^�� */
	keytype key[2 * M];              /* �L�[ */
	struct page *branch[2 * M + 1];  /* ���y�[�W�ւ̃|�C���^ */
} *pageptr;        /* {\tt pageptr} �̓y�[�W�ւ̃|�C���^�̌^ */

pageptr root = NULL;                 /* B�؂̍� */
keytype key;                         /* �L�[ */
boolean done, deleted, undersize;    /* �_���^�̕ϐ� */
pageptr newp;       /* {\tt insert()} �̐��������V�����y�[�W */
char *message;                       /* �֐��̕Ԃ����b�Z�[�W */

pageptr newpage(void)  /* �V�����y�[�W�̐��� */
{
	pageptr p;

	if ((p = malloc(sizeof *p)) == NULL) {
		printf("�������s��.\n");  exit(EXIT_FAILURE);
	}
	return p;
}

void search(void)  /* �L�[ {\tt key} ��B�؂���T�� */
{
	pageptr p;
	int k;

	p = root;
	while (p != NULL) {
		k = 0;
		while (k < p->n && p->key[k] < key) k++;
		if (k < p->n && p->key[k] == key) {
			message = "������܂���";  return;
		}
		p = p->branch[k];
	}
	message = "������܂���";
}

void insertitem(pageptr p, int k)  /* {\tt key} �� {\tt p->key[k]} �ɑ}�� */
{
	int i;

	for (i = p->n; i > k; i--) {
		p->key[i] = p->key[i - 1];
		p->branch[i + 1] = p->branch[i];
	}
	p->key[k] = key;  p->branch[k + 1] = newp;  p->n++;
}

void split(pageptr p, int k)  /* {\tt key} �� {\tt p->key[k]} �ɑ}����, �y�[�W {\tt p} ������ */
{
	int j, m;
	pageptr q;

	if (k <= M) m = M;  else m = M + 1;
	q = newpage();
	for (j = m + 1; j <= 2 * M; j++) {
		q->key[j - m - 1] = p->key[j - 1];
		q->branch[j - m] = p->branch[j];
	}
	q->n = 2 * M - m;  p->n = m;
	if (k <= M) insertitem(p, k);
	else        insertitem(q, k - m);
	key = p->key[p->n - 1];
	q->branch[0] = p->branch[p->n];  p->n--;
	newp = q;  /* �V�����y�[�W�� {\tt newp} �ɓ���Ė߂� */
}

void insertsub(pageptr p)  /* {\tt p} ����؂��ċA�I�ɂ��ǂ��đ}�� */
{
	int k;

	if (p == NULL) {
		done = FALSE;  newp = NULL;  return;
	}
	k = 0;
	while (k < p->n && p->key[k] < key) k++;
	if (k < p->n && p->key[k] == key) {
		message = "�����o�^����Ă��܂�";  done = TRUE;
		return;
	}
	insertsub(p->branch[k]);
	if (done) return;
	if (p->n < 2 * M) {   /* �y�[�W������Ȃ��ꍇ */
		insertitem(p, k);  done = TRUE;
	} else {              /* �y�[�W�������ꍇ */
		split(p, k);  done = FALSE;
	}
}

void insert(void)  /* �L�[ {\tt key} ��B�؂ɑ}�� */
{
	pageptr p;

	message = "�o�^���܂���";
	insertsub(root);  if (done) return;
	p = newpage();  p->n = 1;  p->key[0] = key;
	p->branch[0] = root;  p->branch[1] = newp;  root = p;
}

void removeitem(pageptr p, int k)
	/* {\tt p->key[k]}, {\tt p->branch[k+1]} ���O��. */
	/* �y�[�W���������Ȃ肷������ {\tt undersize} �t���O�𗧂Ă�. */
{
	while (++k < p->n) {
		p->key[k - 1] = p->key[k];
		p->branch[k] = p->branch[k + 1];
	}
	undersize = --(p->n) < M;
}

void moveright(pageptr p, int k)
	/* {\tt p->branch[k - 1]} �̍ŉE�v�f�� */
	/* {\tt p->key[k - 1]} �o�R�� {\tt p->branch[k]} �ɓ����� */
{
	int j;
	pageptr left, right;

	left = p->branch[k - 1];  right = p->branch[k];
	for (j = right->n; j > 0; j--) {
		right->key[j] = right->key[j - 1];
		right->branch[j + 1] = right->branch[j];
	}
	right->branch[1] = right->branch[0];
	right->n++;
	right->key[0] = p->key[k - 1];
	p->key[k - 1] = left->key[left->n - 1];
	right->branch[0] = left->branch[left->n];
	left->n--;
}

void moveleft(pageptr p, int k)
	/* {\tt p->branch[k]} �̍ō��v�f�� */
	/* {\tt p->key[k - 1]} �o�R�� {\tt p->branch[k - 1]} �ɓ����� */
{
	int j;
	pageptr left, right;

	left = p->branch[k - 1];  right = p->branch[k];
	left->n++;
	left->key[left->n - 1] = p->key[k - 1];
	left->branch[left->n] = right->branch[0];
	p->key[k - 1] = right->key[0];
	right->branch[0] = right->branch[1];
	right->n--;
	for (j = 1; j <= right->n; j++) {
		right->key[j - 1] = right->key[j];
		right->branch[j] = right->branch[j + 1];
	}
}

void combine(pageptr p, int k)  /* {\tt p->branch[k - 1]}, {\tt p->branch[k]} ���������� */
{
	int j;
	pageptr left, right;

	right = p->branch[k];
	left = p->branch[k - 1];
	left->n++;
	left->key[left->n - 1] = p->key[k - 1];
	left->branch[left->n] = right->branch[0];
	for (j = 1; j <= right->n; j++) {
		left->n++;
		left->key[left->n - 1] = right->key[j - 1];
		left->branch[left->n] = right->branch[j];
	}
	removeitem(p, k - 1);
	free(right);
}

void restore(pageptr p, int k)  /* �������Ȃ肷�����y�[�W {\tt p->branch[k]} ���C������ */
{
	undersize = FALSE;
	if (k > 0) {
		if (p->branch[k - 1]->n > M) moveright(p, k);
		else combine(p, k);
	} else {
		if (p->branch[1]->n > M) moveleft(p, 1);
		else combine(p, 1);
	}
}

void deletesub(pageptr p)  /* �y�[�W {\tt p} ����ċA�I�ɖ؂����ǂ�폜 */
{
	int k;
	pageptr q;

	if (p == NULL) return;  /* ������Ȃ����� */
	k = 0;
	while (k < p->n && p->key[k] < key) k++;
	if (k < p->n && p->key[k] == key) {  /* �������� */
		deleted = TRUE;
		if ((q = p->branch[k + 1]) != NULL) {
			while (q->branch[0] != NULL) q = q->branch[0];
			p->key[k] = key = q->key[0];
			deletesub(p->branch[k + 1]);
			if (undersize) restore(p, k + 1);
		} else removeitem(p, k);
	} else {
		deletesub(p->branch[k]);
		if (undersize) restore(p, k);
	}
}

void delete(void)  /* �L�[ {\tt key} ��B�؂���O�� */
{
	pageptr p;

	deleted = undersize = FALSE;
	deletesub(root);  /* ������ċA�I�ɖ؂����ǂ�폜���� */
	if (deleted) {
		if (root->n == 0) {  /* ������ɂȂ����ꍇ */
			p = root;  root = root->branch[0];  free(p);
		}
		message = "�폜���܂���";
	} else message = "������܂���";
}

void printtree(pageptr p)  /* �f���p��B�؂�\�� */
{
	static int depth = 0;
	int k;

	if (p == NULL) {  printf(".");  return;  }
	printf("(");  depth++;
	for (k = 0; k < p->n; k++) {
		printtree(p->branch[k]);  /* �ċA�ďo�� */
		printf("%d", p->key[k]);
	}
	printtree(p->branch[p->n]);  /* �ċA�ďo�� */
	printf(")");  depth--;
}

#include <ctype.h>

int main()
{
	char s[2];

	for ( ; ; ) {
		printf("�}�� In, ���� Sn, �폜 Dn (n:����) ? ");
		if (scanf("%1s%d", s, &key) != 2) break;
		switch (s[0]) {
		case 'I':  case 'i':  insert();  break;
		case 'S':  case 's':  search();  break;
		case 'D':  case 'd':  delete();  break;
		default :  message = "???";  break;
		}
		printf("%s\n\n", message);
		printtree(root);  printf("\n\n");
	}
	return EXIT_SUCCESS;
}
