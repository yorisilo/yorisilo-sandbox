/***********************************************************
	ccurve.c -- C�Ȑ�
***********************************************************/
#include "plotter.c"          /* ���[�W���f���ŃR���p�C�� */

void c(int i, double dx, double dy)
{
	if (i == 0) draw_rel(dx, dy);
	else {
		c(i - 1, (dx + dy) / 2, (dy - dx) / 2);
		c(i - 1, (dx - dy) / 2, (dy + dx) / 2);
	}
}

int main()
{
	int order;

	printf("�ʐ� = ");  scanf("%d", &order);
	gr_on();  gr_window(0, 0, 4, 3, 1, GREEN);
	move(1, 2);  c(order, 2, 0);
	hitanykey();
	return EXIT_SUCCESS;
}
