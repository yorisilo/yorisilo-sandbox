/***********************************************************
	list2.c -- ���X�g
***********************************************************/
#include <stdio.h>              /********* Pascal *********/
#include <stdlib.h>             /* type infotype = int;   */
typedef int infotype;           /*      pointer = ^item;  */
                                /*      item = record     */
typedef struct item {           /*        info: infotype; */
    infotype info;              /*        next: pointer   */
    struct item *next;          /*      end;              */
} *pointer;                     /**************************/

pointer add_list(infotype x, pointer p)
{
	pointer q;
                                       /***** Pascal ******/
	q = malloc(sizeof *q);             /*  new(q);        */
	if (q == NULL) {
		printf("�������s��.\n");  exit(EXIT_FAILURE);
	}
	q->info = x;  q->next = p;         /*  q^.info := x;  */
	return q;                          /*  q^.next := p;  */
}                                      /*******************/

void show_list(pointer p)
{
	while (p != NULL) {
		printf(" %d", p->info);  p = p->next;
	}
	printf("\n");
}

pointer reverse_list(pointer p)
{
	pointer q, t;

	q = NULL;
	while (p != NULL) {
		t = q;  q = p;  p = p->next;  q->next = t;
	}
	return q;
}

int main()
{
	infotype x;
	pointer head;

	head = NULL;  /* ��̃��X�g */
	for (x = 1; x <= 9; x++)
		head = add_list(x, head);
	show_list(head);
	head = reverse_list(head);
	show_list(head);
	return EXIT_SUCCESS;
}
