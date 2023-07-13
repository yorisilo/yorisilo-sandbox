/***********************************************************
	squeeze.c -- LZ�@
***********************************************************/
/* ���I�����@ */

#include "bitio.c"
#define N        256    /* �����̎�� (���� = 0..N-1) */
#define MAXDICT 4096    /* �����T�C�Y 4096, 8192, ... */
#define MAXMATCH 100    /* �ő��v�� */
#define NIL  MAXDICT    /* �m�[�h�ԍ��Ƃ��đ��݂��Ȃ��l */

static unsigned char character[MAXDICT];
static int parent[MAXDICT], lchild[MAXDICT],  /* �e, ���̎q */
           rsib[MAXDICT], lsib[MAXDICT],  /* �E���̂��傤���� */
           dictsize = N;  /* ���݂̎����T�C�Y */
static int newer[MAXDICT], older[MAXDICT];  /* �҂��s��|�C���^ */
static int qin = NIL, qout = NIL;       /* �҂��s��̓���, �o�� */
static int match[MAXMATCH];  /* ��v������ */
static int bitlen = 1;  /* ���݂̕�����̒��� */
static int bitmax = 2;  /* 1 << bitlen */

/* �m�[�h p �� LRU �҂��s�񂩂�O�� (size > 1; p �͍Ō�łȂ�) */
void dequeue(int p)
{
	int n, o;

	if (p == qout) {  /* �擪�̏ꍇ */
		qout = newer[p];  older[qout] = NIL;
	} else {
		o = older[p];  n = newer[p];
		newer[o] = n;  older[n] = o;
	}
}

/* �m�[�h p ��҂��s��̗v�f q �̌��ɑ}�� (q �� NIL �Ȃ�ŏ���) */
void enqueue(int p, int q)
{
	if (qin == NIL) {  /* �҂��s�񂪋� */
		older[p] = newer[p] = NIL;  qin = qout = p;
	} else if (q == NIL) {  /* �҂��s��̍ŏ��ɕt���� */
		older[p] = NIL;  newer[p] = qout;
		qout = older[qout] = p;
	} else if (q == qin) {  /* �҂��s��̍Ō�ɕt���� */
		older[p] = qin;  newer[p] = NIL;
		qin = newer[qin] = p;
	} else {  /* �҂��s��̓r���Ɋ������ */
		older[p] = q;
		newer[p] = newer[q];
		newer[q] = older[newer[p]] = p;
	}
}

/* �m�[�h p �̕��� c �ɓ�����q��Ԃ� (�Ȃ���� NIL) */
int child(int p, int c)
{
	p = lchild[p];
	while (p != NIL && c != character[p]) p = rsib[p];
	return p;
}

/* �e�m�[�h parp �̕��� c �ɓ�����q�Ƃ��ėt�m�[�h p ��}�� */
void addleaf(int parp, int p, int c)
{
	int q;

	character[p] = c;
	parent[p] = parp;
	lchild[p] = lsib[p] = NIL;
	q = lchild[parp];  rsib[p] = q;
	if (q != NIL) lsib[q] = p;
	lchild[parp] = p;
}

/* �t�m�[�h p ���폜 */
void deleteleaf(int p)
{
	int left, right;

	left = lsib[p];  right = rsib[p];
	if (left != NIL) rsib[left] = right;
	else      lchild[parent[p]] = right;
	if (right != NIL) lsib[right] = left;
}

/* �����؂̏����� */
void init_tree(void)
{
	int i;

	for (i = 0; i < N; i++) {
		character[i] = i;
		parent[i] = lchild[i] = lsib[i] = rsib[i] = NIL;
	}
}

/* �؂̍X�V */
void update(int *match, int curlen, int prevp, int prevlen)
{
	int p, c, i;

	if (prevp == NIL) return;
	for (i = 0; i < curlen; i++) {
		if (++prevlen > MAXMATCH) return;
		c = match[i];
		if ((p = child(prevp, c)) == NIL) {
			if (dictsize < MAXDICT) p = dictsize++;  /* dictsize < NIL */
			else {
				if (prevp == qout) return;
				p = qout;  dequeue(p);  deleteleaf(p);
			}
			addleaf(prevp, p, c);
			if (prevp < N) enqueue(p, qin);
			else           enqueue(p, older[prevp]);
		}
		prevp = p;
	}
}

void output(int p)
{
	if (p < N) {
		putbit(0);  putbits(8, p);
	} else {
		while ((dictsize - N) >= bitmax) {
			bitlen++;  bitmax <<= 1;
		}
		putbit(1);  putbits(bitlen, p - N);
	}
}

int	input(void)
{
	int i;

	if ((dictsize - N) >= bitmax) {
		bitmax <<= 1;  bitlen++;
	}
	if ((i = getbit()) == EOF) return EOF;
	if (i == 0) return getbits(8);
	if ((i = getbits(bitlen)) == EOF) return EOF;
	return i + N;
}

void encode(void)  /* ���k */
{
	int p, c, q, curptr, curlen, prevptr, prevlen;
	unsigned long int incount, printcount, cr;

	init_tree();  curptr = NIL;  curlen = 0;
	incount = printcount = 0;  c = getc(infile);
	while (c != EOF) {
		prevptr = curptr;  prevlen = curlen;  curlen = 0;
		q = qin;  p = c;
		do {
			if (p >= N)
				if (p == q)	q = older[p];
				else {  dequeue(p);  enqueue(p, q);  }
			match[curlen++] = c;  curptr = p;
			c = getc(infile);  p = child(curptr, c);
		} while (p != NIL);
		output(curptr);
		update(match, curlen, prevptr, prevlen);
		if ((incount += curlen) > printcount) {
			printf("%12lu\r", incount);  printcount += 1024;
		}
	}
	putbits(7, 0);  /* �r�b�g�o�b�t�@���t���b�V�� */
	printf("In : %lu bytes\n", incount);
	printf("Out: %lu bytes\n", outcount);
	if (incount != 0) {
		cr = (1000 * outcount + incount / 2) / incount;
		printf("Out/In: %1lu.%03lu\n", cr / 1000, cr % 1000);
	}
}

void decode(unsigned long int size)  /* ���� */
{
	int p, i, curptr, curlen, prevptr, prevlen, *base;
	unsigned long int count, printcount;

	init_tree();
	curptr = NIL;  curlen = 0;  count = printcount = 0;
	while (count < size) {
		if ((p = input()) == EOF) error("�ǂ߂܂���");
		if (p >= dictsize) error("���̓G���[");
		prevptr = curptr;  prevlen = curlen;
		curptr = p;  curlen = 0;
		while (p != NIL) {
			if (p >= N && p != qin) {
				dequeue(p);  enqueue(p, qin);
			}
			curlen++;
			match[MAXMATCH - curlen] = character[p];
			p = parent[p];
		}
		base = &match[MAXMATCH - curlen];
		for (i = 0; i < curlen ; i++) putc(base[i], outfile);
		update(base, curlen, prevptr, prevlen);
		if ((count += curlen) > printcount) {
			printf("%12lu\r", count);  printcount += 1024;
		}
	}
	printf("%12lu\n", count);
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
