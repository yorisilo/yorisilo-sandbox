/***********************************************************
	list1.c -- ���X�g
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NIL 100  /* �ő�̓Y�� + 1 */
typedef int indextype, infotype;

infotype info[NIL];
indextype next[NIL];

indextype add_list(infotype x, indextype p)
{
	static indextype avail = 0;
	indextype q;

	q = avail++;
	if (q == NIL) {
		printf("���t�ł�.\n");  exit(EXIT_FAILURE);
	}
	info[q] = x;  next[q] = p;
	return q;
}

void show_list(indextype p)
{
	while (p != NIL) {
		printf(" %d", info[p]);  p = next[p];
	}
	printf("\n");
}

indextype reverse_list(indextype p)
{
	indextype q, t;

	q = NIL;
	while (p != NIL) {
		t = q;  q = p;  p = next[p];  next[q] = t;
	}
	return q;
}

int main()
{
	infotype x;
	indextype head;

	head = NIL;                             /* ��̃��X�g */
	for (x = 1; x <= 9; x++)
		head = add_list(x, head);                 /* �o�^ */
	show_list(head);                              /* �\�� */
	head = reverse_list(head);        /* �t���ɕ��בւ��� */
	show_list(head);                              /* �\�� */
	return EXIT_SUCCESS;
}
