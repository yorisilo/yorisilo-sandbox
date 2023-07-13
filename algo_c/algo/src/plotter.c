/***********************************************************
	plotter.c -- �O���t�B�b�N�X
***********************************************************/
/* �v���b�^�̃V�~�����[�V���� */

#include "gr98.c"  /* �܂��� "grega.c".  ���[�W���f���ŃR���p�C�� */
#include "window.c"
static double xpen = 0, ypen = 0;  /* �y���̌��݈ʒu */

void move(double x, double y)  /* �y���A�b�v�ňړ� */
{
	xpen = x;  ypen = y;
}

void move_rel(double dx, double dy)  /* ���� (���΍��W) */
{
	xpen += dx;  ypen += dy;
}

void draw(double x, double y)  /* �y���_�E���ňړ� */
{
	gr_wline(xpen, ypen, x, y, WHITE);
	xpen = x;  ypen = y;
}

void draw_rel(double dx, double dy)  /* ���� (���΍��W) */
{
	gr_wline(xpen, ypen, xpen + dx, ypen + dy, WHITE);
	xpen += dx;  ypen += dy;
}
