/***********************************************************
	hanoi.c -- �n�m�C�̓�
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

void movedisk(int n, int a, int b)
{
	if (n > 1) movedisk(n - 1, a, 6 - a - b);
	printf("�~�� %d �� %d ���� %d �Ɉڂ�\n", n, a, b);
	if (n > 1) movedisk(n - 1, 6 - a - b, b);
}

int main()
{
	int n;

	printf("�~�Ղ̖���? ");  scanf("%d", &n);
	printf("�~�� %d ���� 1 ���璌 2 �Ɉڂ����@��"
		"���� %lu ��ł�.\n", n, (1UL << n) - 1);
	movedisk(n, 1, 2);
	return EXIT_SUCCESS;
}
