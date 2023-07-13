/***********************************************************
	arith.c -- �Z�p���k
***********************************************************/
#include "bitio.c"	/* \see\ Huffman�@ */
#include <limits.h>
#ifdef max
	#undef max
#endif
#define max(x, y) ((x) > (y) ? (x) : (y))  /* 2���̍ő�l */
#define N  256		/* �����̎�� (�����R�[�h{\tt = 0..N-1}) */
#define USHRT_BIT (CHAR_BIT * sizeof(unsigned short))
					/* {\tt unsigned short} �̃r�b�g�� */
#define Q1 (1U << (USHRT_BIT - 2))
#define Q2 (2U * Q1)
#define Q3 (3U * Q1)

unsigned cum[N + 1];  /* �ݐϓx�� */
int ns;  /* ���� {\tt output()} �ŏo�͂���␔�̃J�E���^ */

static void output(int bit)  /* {\tt bit} �ɑ����Ă��̕␔�� {\tt ns} �o�� */
{
	putbit(bit);  /* 1�r�b�g�����o�� */
	while (ns > 0) {  putbit(! bit);  ns--;  }  /* ���̕␔�������o�� */
}

void encode(void)  /* ���k */
{
	int c;
	unsigned long range, maxcount, incount, cr, d;
	unsigned short low, high;
	static unsigned long count[N];

	for (c = 0; c < N; c++) count[c] = 0;  /* �p�x�̏����� */
	while ((c = getc(infile)) != EOF) count[c]++;  /* �e�����̕p�x */
	incount = 0;  maxcount = 0;  /* �����̑傫��, �p�x�̍ő�l */
	for (c = 0; c < N; c++) {
		incount += count[c];
		if (count[c] > maxcount) maxcount = count[c];
	}
	if (incount == 0) return;  /* 0�o�C�g�̃t�@�C�� */
	/* �p�x���v�� {\tt Q1} ����, �e�p�x��1�o�C�g�Ɏ��܂�悤�K�i�� */
	d = max((maxcount + N - 2) / (N - 1),
	        (incount + Q1 - 257) / (Q1 - 256));
	if (d != 1)
		for (c = 0; c < N; c++)
			count[c] = (count[c] + d - 1) / d;
	cum[0] = 0;
	for (c = 0; c < N; c++) {
		fputc((int)count[c], outfile);  /* �p�x�\�̏o�� */
		cum[c + 1] = cum[c] + (unsigned)count[c];  /* �ݐϕp�x */
	}
	outcount = N;
	rewind(infile);  incount = 0;  /* �����߂��čđ��� */
	low = 0;  high = USHRT_MAX;  ns = 0;
	while ((c = getc(infile)) != EOF) {  /* �e�����𕄍��� */
		range = (unsigned long)(high - low) + 1;
		high = (unsigned short)
		       (low + (range * cum[c + 1]) / cum[N] - 1);
		low  = (unsigned short)
		       (low + (range * cum[c    ]) / cum[N]);
		for ( ; ; ) {
			if      (high < Q2) output(0);
			else if (low >= Q2) output(1);
			else if (low >= Q1 && high < Q3) {
				ns++;  low -= Q1;  high -= Q1;
			} else break;
			low <<= 1;  high = (high << 1) + 1;
		}
		if ((++incount & 1023) == 0) printf("%12lu\r", incount);
	}
	ns += 8;  /* �Ō��7�r�b�g�̓o�b�t�@�t���b�V���̂��� */
	if (low < Q1) output(0);  else output(1);  /* 01�܂���10 */
	printf("In : %lu bytes\n", incount);  /* �����̑傫�� */
	printf("Out: %lu bytes (table: %d)\n", outcount, N);
	cr = (1000 * outcount + incount / 2) / incount;  /* ���k�� */
	printf("Out/In: %lu.%03lu\n", cr / 1000, cr % 1000);
}

int binarysearch(unsigned x)  /* $\mbox{\tt cum[i]} \le x < \mbox{\tt cum[i+1]}$ �ƂȂ� {\tt i} ��񕪒T���ŋ��߂� */
{
	int i, j, k;

	i = 1;  j = N;
	while (i < j) {
		k = (i + j) / 2;
		if (cum[k] <= x) i = k + 1;  else j = k;
	}
	return i - 1;
}

void decode(unsigned long size)  /* ���� */
{
	int c;
	unsigned char count[N];
	unsigned short low, high, value;
	unsigned long i, range;

	if (size == 0) return;  /* 0�o�C�g�̃t�@�C�� */
	cum[0] = 0;
	for (c = 0; c < N; c++) {
		count[c] = fgetc(infile);  /* �p�x���z��ǂ� */
		cum[c + 1] = cum[c] + count[c];  /* �ݐϕp�x�����߂� */
	}
	value = 0;
	for (c = 0; c < USHRT_BIT; c++)
		value = 2 * value + getbit();  /* �o�b�t�@�𖞂��� */
	low = 0;  high = USHRT_MAX;
	for (i = 0; i < size; i++) {  /* �e�����𕜌����� */
		range = (unsigned long)(high - low) + 1;
		c = binarysearch((unsigned)((((unsigned long)
			(value - low) + 1) * cum[N] - 1) / range));
		high = (unsigned short)
		       (low + (range * cum[c + 1]) / cum[N] - 1);
		low  = (unsigned short)
		       (low + (range * cum[c    ]) / cum[N]);
		for ( ; ; ) {
			if      (high < Q2) { /* �������Ȃ� */ }
			else if (low >= Q2) { /* �������Ȃ� */ }
			else if (low >= Q1 && high < Q3) {
				value -= Q1;  low -= Q1;  high -= Q1;
			} else break;
			low <<= 1;  high = (high << 1) + 1;
			value = (value << 1) + getbit();  /* 1�r�b�g�ǂ� */
		}
		putc(c, outfile);  /* �������������������o�� */
		if ((i & 1023) == 0) printf("%12lu\r", i);
	}
	printf("%12lu\n", size);  /* �����̃o�C�g�� */
}

int main(int argc, char *argv[])
{
	int c;
	unsigned long size;  /* ���̃o�C�g�� */

	if (argc != 4 || ((c = *argv[1]) != 'E' && c != 'e'
	                            && c != 'D' && c != 'd'))
		error("�g�p�@�͖{�����Q�Ƃ��Ă�������");
	if ((infile  = fopen(argv[2], "rb")) == NULL)
		error("���̓t�@�C�����J���܂���");
	if ((outfile = fopen(argv[3], "wb")) == NULL)
		error("�o�̓t�@�C�����J���܂���");
	if (c == 'E' || c == 'e') {
		fseek(infile, 0L, SEEK_END);  /* infile �̖�����T�� */
		size = ftell(infile);         /* infile �̃o�C�g�� */
		fwrite(&size, sizeof size, 1, outfile);
		rewind(infile);
		encode();       /* ���k */
	} else {
		fread(&size, sizeof size, 1, infile);  /* ���̃o�C�g�� */
		decode(size);   /* ���� */
	}
	fclose(infile);  fclose(outfile);
	return EXIT_SUCCESS;
}
