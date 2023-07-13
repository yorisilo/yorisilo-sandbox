/***********************************************************
	wordcnt.c -- �n�b�V���@
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define HASHSIZE   101  /* �n�b�V���\�̑傫�� (�f��) */
#define MAXWORDLEN 128  /* �ő�P�꒷ */

int wordlen;                    /* �P�꒷ */
unsigned long words, newwords;  /* �P��, �V�P��J�E���^ */
char word[MAXWORDLEN + 1];      /* ���݂̒P�� */

typedef struct node {           /* 2���؂̃m�[�h */
	struct node *left, *right;  /* ���E�̎q */
	char *key;                  /* �L�[ (������) */
} *nodeptr;

struct node nil = {NULL, NULL, word};  /* �Ԑl */
nodeptr hashtable[HASHSIZE];    /* �n�b�V���\ */

int hash(char *s)               /* �ȒP�ȃn�b�V���֐� */
{
	unsigned v;

	for (v = 0; *s != '\0'; s++)
		v = ((v << CHAR_BIT) + *s) % HASHSIZE;
	return (int)v;
}

void insert(void)  /* �}�� (�o�^) */
{
	int cmp;
	nodeptr *p, q;

	words++;
	p = &hashtable[hash(word)];
	while ((cmp = strcmp(word, (*p)->key)) != 0)
		if (cmp < 0) p = &((*p)->left );
		else         p = &((*p)->right);
	if (*p != &nil) return;  /* ���łɓo�^����Ă��� */
	newwords++;
	if ((q = malloc(sizeof *q)) == NULL
	 || (q->key = malloc(wordlen + 1)) == NULL) {
		printf("�������s��.\n");  exit(EXIT_FAILURE);
	}
	strcpy(q->key, word);
	q->left = &nil;  q->right = *p;  *p = q;
}

void getword(void)
{
	int c;

	wordlen = 0;
	do {
		if ((c = getchar()) == EOF) return;
	} while (! isalpha(c));
	do {
		if (wordlen < MAXWORDLEN) word[wordlen++] = tolower(c);
		c = getchar();
	} while (isalpha(c));
	word[wordlen] = '\0';
}

int main()
{
	int i;

	words = newwords = 0;
	for (i = 0; i < HASHSIZE; i++) hashtable[i] = &nil;
	while (getword(), wordlen != 0) insert();
	printf("%lu words, %lu different words\n", words, newwords);
	return EXIT_SUCCESS;
}
