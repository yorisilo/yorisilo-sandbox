/***********************************************************
	water.c -- �����͂�����
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int gcd(int x, int y)  /* �ő���� */
{
	if (x == 0) return y;  else return gcd(y % x, x);
}

int main()
{
	int a, b, v, x, y;

	printf("�e��`�̗e��? ");  scanf("%d", &a);
	printf("�e��a�̗e��? ");  scanf("%d", &b);
	printf("�͂��肽���e��? ");  scanf("%d", &v);
	if (v > a && v > b || v % gcd(a, b) != 0) {
		printf("�͂���܂���\n");  return EXIT_FAILURE;
	}
	x = y = 0;
	do {
		if (x == 0) {
			printf("�`�ɐ��𖞂����܂�\n");  x = a;
		} else if (y == b) {
			printf("�a����ɂ��܂�\n");  y = 0;
		} else if (x < b - y) {
			printf("�`�̐������ׂĂa�Ɉڂ��܂�\n");
			y += x;  x = 0;
		} else {
			printf("�`�̐����a�������ς��ɂȂ�܂�"
				"�a�Ɉڂ��܂�\n");  x -= b - y;  y = b;
		}
	} while (x != v && y != v);
	if      (x == v) printf("�`�ɂ͂���܂���\n");
	else if (y == v) printf("�a�ɂ͂���܂���\n");
	return EXIT_SUCCESS;
}
