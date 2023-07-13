/***********************************************************
	tree.c -- 2���T����
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char keytype[21];

typedef struct node {
	struct node *left, *right;
	keytype key;
} *nodeptr;

struct node nil;
nodeptr root = &nil;

nodeptr insert(keytype key)  /* �}�� (�o�^) */
{
	int cmp;
	nodeptr *p, q;

	strcpy(nil.key, key);  /* �Ԑl */
	p = &root;
	while ((cmp = strcmp(key, (*p)->key)) != 0)
		if (cmp < 0) p = &((*p)->left );
		else         p = &((*p)->right);
	if (*p != &nil) return NULL;  /* ���łɓo�^����Ă��� */
	if ((q = malloc(sizeof *q)) == NULL) {
		printf("�������s��.\n");  exit(EXIT_FAILURE);
	}
	strcpy(q->key, key);
	q->left = &nil;  q->right = *p;  *p = q;
	return q;  /* �o�^���� */
}

int delete(keytype key)  /* �폜�ł���� 0, ���s�Ȃ� 1 ��Ԃ� */
{
	int cmp;
	nodeptr *p, *q, r, s;

	strcpy(nil.key, key);  /* �Ԑl */
	p = &root;
	while ((cmp = strcmp(key, (*p)->key)) != 0)
		if (cmp < 0) p = &((*p)->left);
		else         p = &((*p)->right);
	if (*p == &nil) return 1;  /* �����炸 */
	r = *p;
	if      (r->right == &nil) *p = r->left;
	else if (r->left  == &nil) *p = r->right;
	else {
		q = &(r->left);
		while ((*q)->right != &nil) q = &((*q)->right);
		s = *q;  *q = s->left;
		s->left = r->left;  s->right = r->right;
		*p = s;
	}
	free(r);
	return 0;  /* �폜���� */
}

nodeptr search(keytype key)  /* ���� (���o�^�Ȃ�NULL��Ԃ�) */
{
	int cmp;
	nodeptr p;

	strcpy(nil.key, key);  /* �Ԑl */
	p = root;
	while ((cmp = strcmp(key, p->key)) != 0)
		if (cmp < 0) p = p->left;
		else         p = p->right;
	if (p != &nil) return p;     /* �������� */
	else           return NULL;  /* ������Ȃ� */
}

void printtree(nodeptr p)
{
	static int depth = 0;

	if (p->left != &nil) {
		depth++;  printtree(p->left);  depth--;
	}
	printf("%*c%s\n", 5 * depth, ' ', p->key);
	if (p->right != &nil) {
		depth++;  printtree(p->right);  depth--;
	}
}

int main()
{
	char buf[22];

	printf("���� Iabc:  abc��}��\n"
		   "     Dabc:  abc���폜\n"
		   "     Sabc:  abc������\n");
	for ( ; ; ) {
		printf("����? ");
		if (scanf("%21s%*[^\n]", buf) != 1) break;
		switch (buf[0]) {
		case 'I':  case 'i':
			if (insert(&buf[1])) printf("�o�^���܂���.\n");
			else                 printf("�o�^���݂ł�.\n");
			break;
		case 'D':  case 'd':
			if (delete(&buf[1])) printf("�o�^����Ă��܂���.\n");
			else                 printf("�폜���܂���.\n");
			break;
		case 'S':  case 's':
			if (search(&buf[1])) printf("�o�^����Ă��܂�.\n");
			else                 printf("�o�^����Ă��܂���\n");
			break;
		default:
			printf("�g����̂� I, D, S �ł�.\n");
			break;
		}
		if (root != &nil) {
			printf("\n");  printtree(root);  printf("\n");
		}
	}
	return EXIT_SUCCESS;
}
