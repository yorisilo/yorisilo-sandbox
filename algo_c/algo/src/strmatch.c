/***********************************************************
	strmatch.c -- ������ƍ�
***********************************************************/
int position(char text[], char pattern[])
{
	int i, j, k, c;

	c = pattern[0];  i = 0;
	while (text[i] != 0) {
		if (text[i++] == c) {
			k = i;  j = 1;
			while (text[k] == pattern[j] && pattern[j] != 0) {
				k++;  j++;
			}
			if (pattern[j] == '\0') return k - j;  /* �������� */
		}
	}
	return -1;  /* ������Ȃ����� */
}

#if 0   /***** ���邢�͓������Ƃł��邪... *****/
int position(char text[], char pattern[])
{
	int i, j;

	i = j = 0;
	while (text[i] != '\0' && pattern[j] != '\0')
		if (text[i] == pattern[j]) {  i++;  j++;  }
		else {  i = i - j + 1;  j = 0;  }
	if (pattern[j] == '\0') return i - j;  /* �������� */
	return -1;  /* ������Ȃ����� */
}
#endif

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	char text[] = "AAAAAABAAAC",
		 pattern[4][4] = { "AAA", "AAB", "AAC", "AAD" };

	for (i = 0; i < 4; i++)
		printf("position(\"%s\", \"%s\") = %d\n",
			text, pattern[i], position(text, pattern[i]));
	return EXIT_SUCCESS;
}
