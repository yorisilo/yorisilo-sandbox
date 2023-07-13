/***********************************************************
	solst.c -- ���ȑg�D���T��
***********************************************************/
/* �擪�ړ��@ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYSIZE     15  /* ���O���̑傫�� */
#define INFOSIZE   127  /* �Z�����̑傫�� */
typedef char keytype[KEYSIZE + 1], infotype[INFOSIZE + 1];
typedef struct item {
    struct item *next;
    keytype key;
	infotype info;
} *pointer;

static struct item head = { &head, "", "" };  /* ���X�g�̓� */

void insert(keytype key, infotype info)
{
	pointer p;

	if ((p = malloc(sizeof *p)) == NULL) {
		printf("�������s��.\n");  exit(EXIT_FAILURE);
	}
	strcpy(p->key, key);  strcpy(p->info, info);
	p->next = head.next;  head.next = p;
}

pointer search(keytype x)
{
	pointer p, q;

	strcpy(head.key, x);  p = &head;  /* �Ԑl */
	do {
		q = p;  p = p->next;
	} while (strcmp(p->key, x) != 0);
	if (p == &head) return NULL;
	q->next = p->next;  p->next = head.next;  head.next = p;
	return p;
}

#define ReadString(len, x) (scanf("%" #len "s%*[^\n]", x) == 1)

int main()
{
	keytype key;
	infotype info;
	pointer p;

	for ( ; ; ) {
		printf("���O? ");
		if (! ReadString(KEYSIZE, key)) break;
		if ((p = search(key)) != NULL)
			printf("�Z��: %s\n", p->info);
		else {
			printf("�Z��? ");
			if (ReadString(INFOSIZE, info)) insert(key, info);
		}
	}
	return EXIT_SUCCESS;
}
