/***********************************************************
	lissaj.c -- Lissajous (���T�W���[) �}�`
***********************************************************/
#include "plotter.c"  /* ���[�W���f���ŃR���p�C�� */
#include <math.h>  /* sin, cos */
#define PI 3.141592653589793

int main()
{
	int i;
	double t;

	gr_on();
	gr_window(-1, -1, 1, 1, 1, 0);  /* ���W�w�� */
	move(cos(0), sin(0));  /* �����y���ʒu */
	for (i = 1; i <= 360; i++) {
		t = (PI / 180) * i;
		draw(cos(3 * t), sin(5 * t));  /* �y���ړ� */
	}
	hitanykey();
	return EXIT_SUCCESS;
}
