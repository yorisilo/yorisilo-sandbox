/***********************************************************
	ukanji.c -- �V�t�gJIS�R�[�h
***********************************************************/
#define iskanji(c) \
	((c)>=0x81 && (c)<=0x9F || (c)>=0xE0 && (c)<=0xFC)
	/* �V�t�gJIS 1�o�C�g�� */
#define iskanji2(c) ((c)>=0x40 && (c)<=0xFC && (c)!=0x7F)
	/* �V�t�gJIS 2�o�C�g�� */

void jis(int *ph, int *pl)  /* �V�t�gJIS��JIS�� */
{
	if (*ph <= 0x9F) {
		if (*pl < 0x9F)  *ph = (*ph << 1) - 0xE1;
		else             *ph = (*ph << 1) - 0xE0;
	} else {
		if (*pl < 0x9F)  *ph = (*ph << 1) - 0x161;
		else             *ph = (*ph << 1) - 0x160;
	}
	if      (*pl < 0x7F) *pl -= 0x1F;
	else if (*pl < 0x9F) *pl -= 0x20;
	else                 *pl -= 0x7E;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int c, d;

	while ((c = getchar()) != EOF) {
		if (iskanji(c)) {
			d = getchar();
			if (iskanji2(d)) {
				jis(&c, &d);
				putchar(c | 0x80);  putchar(d | 0x80);
			} else {
				putchar(c);
				if (d != EOF) putchar(d);
			}
		} else putchar(c);
	}
	return EXIT_SUCCESS;
}
