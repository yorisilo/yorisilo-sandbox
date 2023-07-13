/***********************************************************
	postfix.c -- ��u�L�@
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int ch;

void readch(void)  /* �P������ǂ�. �󔒂͓ǂݔ�΂�. */
{
	do {
		if ((ch = getchar()) == EOF) return;
	} while (ch == ' ' || ch == '\t');
}

void expression(void);  /* �� */

void factor(void)  /* ���q */
{
	if (ch == '(') {
		readch();  expression();
		if (ch == ')') readch();  else putchar('?');
	} else if (isgraph(ch)) {
		putchar(ch);  readch();
	} else putchar('?');
}

void term(void) /* �� */
{
	factor();
	for ( ; ; )
		if (ch == '*') {
			readch();  factor();  putchar('*');
		} else if (ch == '/') {
			readch();  factor();  putchar('/');
		} else break;
}

void expression(void)  /* �� */
{
	term();
	for ( ; ; )
		if (ch == '+') {
			readch();  term();  putchar('+');
		} else if (ch == '-') {
			readch();  term();  putchar('-');
		} else break;
}

int main()
{
	do {
		readch();  expression();
		while (ch != '\n' && ch != EOF) {
			putchar('?');  readch();
		}
		putchar('\n');
	} while (ch != EOF);
	return EXIT_SUCCESS;
}
