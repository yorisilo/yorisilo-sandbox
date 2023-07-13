/***********************************************************
	tbintree.c -- �Ђ��t��2����
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char keytype[21];  /* �T���̃L�[�̌^ */
typedef struct node {      /* struct node �͖؂̃m�[�h */
	struct node *left, *right;  /* ���E�̎q�ւ̃|�C���^ */
	unsigned int count;    /* �Q�Ɖ񐔃J�E���^ */
	keytype key;           /* �T���̃L�[(�o�^������) */
	char flags;            /* �{���Q�� */
} *nodeptr;  /* {\tt nodeptr} �̓m�[�h�ւ̃|�C���^ */

#define LBIT 1  /* ��� {\tt flags} �̐����Q�� */
#define RBIT 2

struct node root = {&root, &root, 0, "", 0};  /* �؂̍� */

nodeptr newnode(keytype key)  /* �V�����m�[�h�𐶐� */
{
	nodeptr p;

	if ((p = malloc(sizeof *p)) == NULL) {
		printf("�������s��.\n");  exit(EXIT_FAILURE);
	}
	strcpy(p->key, key);  /* �L�[���R�s�[���� */
	p->count = 1;         /* �Q�Ɖ񐔂�1�ɂ��� */
	return p;
}

void insertright(nodeptr p, keytype key)  /* �m�[�h p �̉E�ɑ}�� */
{
	nodeptr q;

	q = newnode(key);     /* �V�����m�[�h�𐶐� */
	q->right = p->right;  /* �E�̎q�͐e�̉E�̎q���󂯌p�� */
	q->left = p;          /* ���̎q�͂��͐e���w���Ђ� */
	q->flags = p->flags & RBIT;  /* �E�t���O�͐e�̉E�t���O���󂯌p�� */
	p->flags |= RBIT;     /* {\tt q} �͂Ђ��łȂ��̂Őe�̉E�t���O�𗧂Ă� */
	p->right = q;         /* {\tt q} ��e {\tt p} �̉E�̎q�ɂ��� */
}

void insertleft(nodeptr p, keytype key)  /* �m�[�h p �̍��ɑ}�� */
{                                        /* �����͏�Ɠ��l�Ȃ̂ŏȂ� */
	nodeptr q;

	q = newnode(key);
	q->left = p->left;  q->right = p;
	q->flags = p->flags & LBIT;
	p->flags |= LBIT;  p->left = q;
}

void insert(keytype key)  /* �}��(�o�^) */
{
	int cmp;    /* ��r���� */
	nodeptr p;

	p = &root;  cmp = 1;  /* �ŏ��̎q�͐e�̉E�� */
	do {
		if (cmp < 0) {    /* ��������΍��ɓo�^ */
			if (p->flags & LBIT) p = p->left;
			else {  insertleft(p, key);  return;  }
		} else {          /* �傫����ΉE�ɓo�^ */
			if (p->flags & RBIT) p = p->right;
			else {  insertright(p, key);  return;  }
		}
	} while ((cmp = strcmp(key, p->key)) != 0);
	p->count++;           /* ��������ΎQ�Ɖ񐔂𑝂����� */
}

nodeptr successor(nodeptr p)  /* ������ {\tt p} �̒���̃m�[�h */
{  /* ${\tt right} \leftrightarrow {\tt left}$, ${\tt RBIT} \leftrightarrow {\tt LBIT}$ �Ƃ���Β��O�̃m�[�h�ɂȂ� */
	nodeptr q;

	q = p->right;
	if (p->flags & RBIT)
		while (q->flags & LBIT) q = q->left;
	return q;
}

void printinorder(void)  /* �����őS�L�[���o�� */
{
	nodeptr p;

	p = &root;
	while ((p = successor(p)) != &root)
		printf("%-20s %5d\n", p->key, p->count);
}

int main()
{
	char word[21];

	while (scanf("%20s%*[^ \n\t]", word) == 1)
		insert(word);  /* �W�����͂���P���ǂݓo�^ */
	printinorder();    /* �e�P��Əo���񐔂������ɏo�� */
	return EXIT_SUCCESS;
}
