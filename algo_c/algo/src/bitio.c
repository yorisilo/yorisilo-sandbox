/***********************************************************
	bitio.c -- Huffman (�n�t�}��) �@
***********************************************************/

/* Huffman�@�ȂǂŎg���r�b�g���o�̓��[�`�� */

#include <stdio.h>
#include <stdlib.h>

FILE *infile, *outfile;      /* ���̓t�@�C��, �o�̓t�@�C�� */
unsigned long outcount = 0;  /* �o�̓o�C�g���J�E���^ */
static int getcount = 0, putcount = 8;  /* �r�b�g���o�̓J�E���^ */
static unsigned bitbuf = 0;  /* �r�b�g���o�̓o�b�t�@ */
#define rightbits(n, x) ((x) & ((1U << (n)) - 1U))  /* x�̉En�r�b�g */

void error(char *message)  /* ���b�Z�[�W��\�����I�� */
{
	fprintf(stderr, "\n%s\n", message);
	exit(EXIT_FAILURE);
}

unsigned getbit(void)  /* 1�r�b�g�ǂ� */
{
	if (--getcount >= 0) return (bitbuf >> getcount) & 1U;
	getcount = 7;  bitbuf = getc(infile);
	return (bitbuf >> 7) & 1U;
}

unsigned getbits(int n)  /* n�r�b�g�ǂ� */
{
	unsigned x;

	x = 0;
	while (n > getcount) {
		n -= getcount;
		x |= rightbits(getcount, bitbuf) << n;
		bitbuf = getc(infile);  getcount = 8;
	}
	getcount -= n;
	return x | rightbits(n, bitbuf >> getcount);
}

void putbit(unsigned bit)  /* 1�r�b�g�����o�� */
{
	putcount--;
	if (bit != 0) bitbuf |= (1 << putcount);
	if (putcount == 0) {
		if (putc(bitbuf, outfile) == EOF) error("�����܂���");
		bitbuf = 0;  putcount = 8;  outcount++;
	}
}

void putbits(int n, unsigned x)  /* n�r�b�g�����o�� */
{
	while (n >= putcount) {
		n -= putcount;
		bitbuf |= rightbits(putcount, x >> n);
		if (putc(bitbuf, outfile) == EOF) error("�����܂���");
		bitbuf = 0U;  putcount = 8;  outcount++;
	}
	putcount -= n;
	bitbuf |= rightbits(n, x) << putcount;
}
