/***********************************************************
	sboymoo.c -- Boyer--Moore�@
***********************************************************/
/* �ȗ�Boyer-Moore�@ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>  /* #define UCHAR_MAX 255 */
#define DEMO         /* �f�����X�g���[�V���� */

int position(unsigned char text[], unsigned char pattern[])
{
	int i, j, k, len;
	static int skip[UCHAR_MAX + 1];
	unsigned char c, tail;

	len = strlen((char *)pattern);  /* ������̒��� */
	if (len == 0) return -1;        /* �G���[: ����0 */
	tail = pattern[len - 1];        /* �Ō�̕��� */
	if (len == 1) {                 /* ����1�Ȃ�ȒP! */
		for (i = 0; text[i] != '\0'; i++)
			if (text[i] == tail) return i;
	} else {                        /* ����2�ȏ�Ȃ�\������āc */
		for (i = 0; i <= UCHAR_MAX; i++) skip[i] = len;
		for (i = 0; i < len - 1; i++)
			skip[pattern[i]] = len - 1 - i;
		/* i = len - 1; */          /* ���悢��ƍ� */
		while ((c = text[i]) != '\0') {
#ifdef DEMO                         /* �f�����X�g���[�V�����p */
			printf("�e: %s\n", text);
			printf("��: %*s\n", i + 1, pattern);
#endif
			if (c == tail) {
				j = len - 1;  k = i;
				while (pattern[--j] == text[--k])
					if (j == 0) return k;  /* �������� */
			}
			i += skip[c];
		}
	}
	return -1;  /* ������Ȃ����� */
}

int mygets(int n, unsigned char s[])  /* n �����܂� s[] �ɓǂݍ��� */
{
	int i, c;

	i = 0;
	while ((c = getchar()) != EOF && c != '\n')
		if (i < n) s[i++] = (unsigned char)c;
	if (i != 0) s[i] = '\0';
	return i;
}

int main()
{
	int n, m, p;
	static unsigned char
		text[256] = "supercalifragilisticexpialidocious",
		pattern[128];

	for ( ; ; ) {
		printf("�e�L�X�g������ (���^�[��: %s)\n  ? ", text);
		if ((n = mygets(127, text)) == 0) n = strlen((char *)text);
		printf("�ƍ������� (���^�[��: �I��)\n  ? ");
		if ((m = mygets(127, pattern)) == 0) break;
		memset(text + n, 0, m);
		p = position(text, pattern);
		if (p >= 0) printf("�ʒu = %d\n\n", p);
		else        printf("������܂���.\n\n");
	}
	return EXIT_SUCCESS;
}
