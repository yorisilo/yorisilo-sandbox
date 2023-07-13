/***********************************************************
	huffman.c -- Huffman (�n�t�}��) �@
***********************************************************/
#include "bitio.c"              /* �r�b�g���o�� */

#define N       256             /* �����̎�� */
#define CHARBITS  8             /* 1�o�C�g�̃r�b�g�� */
int heapsize, heap[2*N-1],      /* �D��҂��s��p�q�[�v */
    parent[2*N-1], left[2*N-1], right[2*N-1];  /* Huffman�� */
unsigned long int freq[2*N-1];  /* �e�����̏o���p�x */

static void downheap(int i)  /* �D��҂��s��ɑ}�� */
{
	int j, k;

	k = heap[i];
	while ((j = 2 * i) <= heapsize) {
		if (j < heapsize && freq[heap[j]] > freq[heap[j + 1]])
			j++;
		if (freq[k] <= freq[heap[j]]) break;
		heap[i] = heap[j];  i = j;
	}
	heap[i] = k;
}

void writetree(int i)  /* �}���o�� */
{
	if (i < N) {  /* �t */
		putbit(0);
		putbits(CHARBITS, i);  /* �������̂��� */
	} else {      /* �� */
		putbit(1);
		writetree(left[i]);  writetree(right[i]);  /* ���E�̎} */
	}
}

void encode(void)  /* ���k */
{
	int i, j, k, avail, tablesize;
	unsigned long int incount, cr;
	static char codebit[N];  /* ������ */

	for (i = 0; i < N; i++) freq[i] = 0;  /* �p�x�̏����� */
	while ((i = getc(infile)) != EOF) freq[i]++;  /* �p�x���� */
	heap[1] = 0;  /* ����0�̃t�@�C���ɔ����� */
	heapsize = 0;
	for (i = 0; i < N; i++)
		if (freq[i] != 0) heap[++heapsize] = i;  /* �D��҂��s��ɓo�^ */
	for (i = heapsize / 2; i >= 1; i--) downheap(i);  /* �q�[�v��� */
	for (i = 0; i < 2 * N - 1; i++) parent[i] = 0;  /* �O�̂��� */
	k = heap[1];  /* �ȉ��̃��[�v��1������s����Ȃ��ꍇ�ɔ����� */
	avail = N;  /* �ȉ��̃��[�v�Ńn�t�}���؂���� */
	while (heapsize > 1) {  /* 2�ȏ�c�肪����� */
		i = heap[1];  /* �ŏ��̗v�f�����o�� */
		heap[1] = heap[heapsize--];  downheap(1);  /* �q�[�v�č\�� */
		j = heap[1];  /* ���ɍŏ��̗v�f�����o�� */
		k = avail++;  /* �V�����߂𐶐����� */
		freq[k] = freq[i] + freq[j];  /* �p�x�����v */
		heap[1] = k;  downheap(1);  /* �҂��s��ɓo�^ */
		parent[i] = k;  parent[j] = -k;  /* �؂���� */
		left[k] = i;  right[k] = j;      /* �V */
	}
	writetree(k);  /* �؂��o�� */
	tablesize = (int) outcount;  /* �\�̑傫�� */
	incount = 0;  rewind(infile);  /* �đ��� */
	while ((j = getc(infile)) != EOF) {
		k = 0;
		while ((j = parent[j]) != 0)
			if (j > 0) codebit[k++] = 0;
			else {     codebit[k++] = 1;  j = -j;  }
		while (--k >= 0) putbit(codebit[k]);
		if ((++incount & 1023) == 0)
			printf("%12lu\r", incount);  /* �󋵕� */
	}
	putbits(7, 0);  /* �o�b�t�@�̎c����t���b�V�� */
	printf("In : %lu bytes\n", incount);  /* ���ʕ� */
	printf("Out: %lu bytes (table: %d bytes)\n",
		outcount, tablesize);
	if (incount != 0) {  /* ���k������߂ĕ� */
		cr = (1000 * outcount + incount / 2) / incount;
		printf("Out/In: %lu.%03lu\n", cr / 1000, cr % 1000);
	}
}

int readtree(void)  /* �؂�ǂ� */
{
	int i;
	static int avail = N;

	if (getbit()) {  /* bit=1: �t�łȂ��� */
		if ((i = avail++) >= 2 * N - 1) error("�\���Ԉ���Ă��܂�");
		left [i] = readtree();  /* ���̎}��ǂ� */
		right[i] = readtree();  /* �E�̎}��ǂ� */
		return i;               /* �߂�Ԃ� */
	} else return (int) getbits(CHARBITS);  /* ���� */
}

void decode(unsigned long int size)  /* ���� */
{
	int j, root;
	unsigned long int k;

	root = readtree();  /* �؂�ǂ� */
	for (k = 0; k < size; k++) {  /* �e�����𕜌� */
		j = root;  /* �� */
		while (j >= N)
			if (getbit()) j = right[j];  else j = left[j];
		putc(j, outfile);
		if ((k & 1023) == 0) printf("%12lu\r", k);  /* �o�̓o�C�g�� */
	}
	printf("%12lu\n", size);  /* ���������o�C�g�� */
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
