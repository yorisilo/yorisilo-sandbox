/***********************************************************
	movebloc.c -- �u���b�N�ړ�
***********************************************************/
char a[] = "SUPERCALIFRAGILISTICEXPIALIDOCIOUS"; /* Mary Poppins�̖��@�̌��t */

void reverse(int i, int j)
{
	int t;

	while (i < j) {
		t = a[i];  a[i] = a[j];  a[j] = t;
		i++;  j--;
	}
}

void rotate(int left, int mid, int right)
{
	reverse(left, mid);
	reverse(mid + 1, right);
	reverse(left, right);
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;

	printf("%s\n", a);
	for (i = 0; i < 17; i++) {
		rotate(0, 5, 33);  printf("%s\n", a);
	}
	return EXIT_SUCCESS;
}
