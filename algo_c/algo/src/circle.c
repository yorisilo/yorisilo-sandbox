/***********************************************************
	circle.c -- �O���t�B�b�N�X
***********************************************************/
#include "gr98.c"  /* �܂��� "grega.c". ���[�W���f���ŃR���p�C�� */

void gr_circle(int xc, int yc, int r, int color)
{
	int x, y;

	x = r;  y = 0;
	while (x >= y) {
		gr_dot(xc + x, yc + y, color);
		gr_dot(xc + x, yc - y, color);
		gr_dot(xc - x, yc + y, color);
		gr_dot(xc - x, yc - y, color);
		gr_dot(xc + y, yc + x, color);
		gr_dot(xc + y, yc - x, color);
		gr_dot(xc - y, yc + x, color);
		gr_dot(xc - y, yc - x, color);
		if ((r -= (y++ << 1) - 1) < 0)
			r += (x-- - 1) << 1;
	}
}

#if 0   /* �e�X�g�p */

int main()
{
	int i;

	gr_on();
	for (i = 0; i < 100; i++)
		gr_circle(rand() % XMAX, rand() % YMAX,
		          rand() % 100,  rand() % WHITE + 1);
	hitanykey();
	return EXIT_SUCCESS;
}

#endif
