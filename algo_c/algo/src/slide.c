/***********************************************************
	slide.c -- LZ�@
***********************************************************/
/* �X���C�h�����@ */

#include <stdio.h>
#include <stdlib.h>

#define N   4096  /* ��o�b�t�@�̑傫�� */
#define F     18  /* �Œ���v�� */

FILE *infile, *outfile;      /* ���̓t�@�C��, �o�̓t�@�C�� */
unsigned long outcount = 0;  /* �o�̓o�C�g���J�E���^ */
unsigned char text[N+F-1]; /* �e�L�X�g�p�o�b�t�@ */
int dad[N+1], lson[N+1], rson[N+257];  /* �� */
#define NIL    N  /* �؂̖��[ */

void error(char *message)  /* ���b�Z�[�W��\�����I�� */
{
	fprintf(stderr, "\n%s\n", message);
	exit(EXIT_FAILURE);
}

void init_tree(void)  /* �؂̏����� */
{
	int i;

	for (i = N + 1; i <= N + 256; i++) rson[i] = NIL;
	for (i = 0; i < N; i++) dad[i] = NIL;
}

int matchpos, matchlen;  /* �Œ���v�ʒu, ��v�� */

void insert_node(int r)  /* �� r ��؂ɑ}�� */
{
	int i, p, cmp;
	unsigned char *key;

	cmp = 1;  key = &text[r];  p = N + 1 + key[0];
	rson[r] = lson[r] = NIL;  matchlen = 0;
	for ( ; ; ) {
		if (cmp >= 0) {
			if (rson[p] != NIL) p = rson[p];
			else {  rson[p] = r;  dad[r] = p;  return;  }
		} else {
			if (lson[p] != NIL) p = lson[p];
			else {  lson[p] = r;  dad[r] = p;  return;  }
		}
		for (i = 1; i < F; i++)
			if ((cmp = key[i] - text[p + i]) != 0)  break;
		if (i > matchlen) {
			matchpos = p;
			if ((matchlen = i) >= F)  break;
		}
	}
	dad[r] = dad[p];  lson[r] = lson[p];  rson[r] = rson[p];
	dad[lson[p]] = r;  dad[rson[p]] = r;
	if (rson[dad[p]] == p) rson[dad[p]] = r;
	else                   lson[dad[p]] = r;
	dad[p] = NIL;  /* p ���O�� */
}

void delete_node(int p)  /* �� p ��؂������ */
{
	int  q;

	if (dad[p] == NIL) return;  /* ������Ȃ� */
	if (rson[p] == NIL) q = lson[p];
	else if (lson[p] == NIL) q = rson[p];
	else {
		q = lson[p];
		if (rson[q] != NIL) {
			do {  q = rson[q];  } while (rson[q] != NIL);
			rson[dad[q]] = lson[q];  dad[lson[q]] = dad[q];
			lson[q] = lson[p];  dad[lson[p]] = q;
		}
		rson[q] = rson[p];  dad[rson[p]] = q;
	}
	dad[q] = dad[p];
	if (rson[dad[p]] == p) rson[dad[p]] = q;
	else                   lson[dad[p]] = q;
	dad[p] = NIL;
}

void encode(void)  /* ���k */
{
	int i, c, len, r, s, lastmatchlen, codeptr;
	unsigned char code[17], mask;
	unsigned long int incount = 0, printcount = 0, cr;

	init_tree();  /* �؂������� */
	code[0] = 0;  codeptr = mask = 1;
	s = 0;  r = N - F;
	for (i = s; i < r; i++) text[i] = 0;  /* �o�b�t�@�������� */
	for (len = 0; len < F ; len++) {
		c = getc(infile);  if (c == EOF) break;
		text[r + len] = c;
	}
	incount = len;  if (incount == 0) return;
	for (i = 1; i <= F; i++) insert_node(r - i);
	insert_node(r);
	do {
		if (matchlen > len) matchlen = len;
		if (matchlen < 3) {
			matchlen = 1;  code[0] |= mask;  code[codeptr++] = text[r];
		} else {
			code[codeptr++] = (unsigned char) matchpos;
			code[codeptr++] = (unsigned char)
				(((matchpos >> 4) & 0xf0) | (matchlen - 3));
		}
		if ((mask <<= 1) == 0) {
			for (i = 0; i < codeptr; i++) putc(code[i], outfile);
			outcount += codeptr;
			code[0] = 0;  codeptr = mask = 1;
		}
		lastmatchlen = matchlen;
		for (i = 0; i < lastmatchlen; i++) {
			c = getc(infile);  if (c == EOF) break;
			delete_node(s);  text[s] = c;
			if (s < F - 1) text[s + N] = c;
			s = (s + 1) & (N - 1);  r = (r + 1) & (N - 1);
			insert_node(r);
		}
		if ((incount += i) > printcount) {
			printf("%12lu\r", incount);  printcount += 1024;
		}
		while (i++ < lastmatchlen) {
			delete_node(s);
			s = (s + 1) & (N - 1);  r = (r + 1) & (N - 1);
			if (--len) insert_node(r);
		}
	} while (len > 0);
	if (codeptr > 1) {
		for (i = 0; i < codeptr; i++) putc(code[i], outfile);
		outcount += codeptr;
	}
	printf("In : %lu bytes\n", incount);  /* ���ʕ� */
	printf("Out: %lu bytes\n", outcount);
	if (incount != 0) {  /* ���k������߂ĕ� */
		cr = (1000 * outcount + incount / 2) / incount;
		printf("Out/In: %lu.%03lu\n", cr / 1000, cr % 1000);
	}
}

void decode(unsigned long int size)  /* ���� */
{
	int i, j, k, r, c;
	unsigned int flags;

	for (i = 0; i < N - F; i++) text[i] = 0;
	r = N - F;  flags = 0;
	for ( ; ; ) {
		if (((flags >>= 1) & 256) == 0) {
			if ((c = getc(infile)) == EOF) break;
			flags = c | 0xff00;
		}
		if (flags & 1) {
			if ((c = getc(infile)) == EOF) break;
			putc(c, outfile);  text[r++] = c;  r &= (N - 1);
		} else {
			if ((i = getc(infile)) == EOF) break;
			if ((j = getc(infile)) == EOF) break;
			i |= ((j & 0xf0) << 4);  j = (j & 0x0f) + 2;
			for (k = 0; k <= j; k++) {
				c = text[(i + k) & (N - 1)];  putc(c, outfile);
				text[r++] = c;  r &= (N - 1);
			}
		}
	}
	printf("%12lu\n", size);
}

int main(int argc, char *argv[])
{
	int c;
	unsigned long int size;  /* ���̃o�C�g�� */

	if (argc != 4 || ((c = *argv[1]) != 'E' && c != 'e'
	                            && c != 'D' && c != 'd'))
		error("�g�p�@�͖{�����Q�Ƃ��Ă�������");
	if ((infile  = fopen(argv[2], "rb")) == NULL)
		error("���̓t�@�C�����J���܂���");
	if ((outfile = fopen(argv[3], "wb")) == NULL)
		error("�o�̓t�@�C�����J���܂���");
	if (c == 'E' || c == 'e') {
		fseek(infile, 0L, SEEK_END);  /* infile �̖�����T�� */
		size = ftell(infile);     /* infile �̃o�C�g�� */
		fwrite(&size, sizeof size, 1, outfile);
		rewind(infile);
		encode();  /* ���k */
	} else {
		fread(&size, sizeof size, 1, infile);  /* ���̃o�C�g�� */
		decode(size);  /* ���� */
	}
	fclose(infile);  fclose(outfile);
	return EXIT_SUCCESS;
}
