/***********************************************************
	gf2fact.c -- �L����
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int poly;        /* �������̌^ */
poly quo, quo_low, res, res_low;  /* ��, �]�� */
#define MSB (~(~0U >> 1))         /* �ŏ�ʃr�b�g */
/*
  ���������o�͂��郋�[�`��.
  ���Ƃ��� $x^3 + x + 1$ �� {\tt 1011} �Əo�͂���.
*/
void write_poly(poly p, poly p_low)
{
	poly q;

	q = MSB;
	while (q >= p_low) {
		putchar((p & q) ? '1' : '0');
		q >>= 1;
	}
}
/*
  �������̊���Z�̃��[�`��.
  ������ {\tt a} �𑽍��� {\tt b} �Ŋ���, �� {\tt quo},
  �]�� {\tt res} �����߂�.
  ���O�� {\TT \_low} �ŏI���ϐ��͍ŉ��ʃr�b�g�̈ʒu��\��.
  ����؂�邩�ǂ�������������΂悢�̂ŗ]�� {\tt res} �͍��񂹂ɂ��Ȃ�.
  �]������񂹂ɂ���ɂ͂��̃��[�`����
  �Ō�� \lq\lq {\TT res\_low} �� {\tt MSB} ��
  �Ȃ���� {\TT res\_low} �� {\tt res} ������1���V�t�g����'' �Ƃ���
  ���߂�����.
  ���Ȃ݂�, ���قǂ� \verb"res ^= b;" �� \verb"res -= b;" �Ƃ����
  ���ʂ� (���؂������) ����Z�ɂȂ�.
*/
void divide(poly a, poly a_low, poly b, poly b_low)
{
	quo = 0;  quo_low = MSB;  res = a;  res_low = a_low;
	if (res_low > b_low) return;
	for ( ; ; ) {
		if (res & MSB) {
			quo |= quo_low;  res ^= b;
		}
		if (res_low == b_low) break;
		res_low <<= 1;  res <<= 1;  quo_low >>= 1;
	}
}
/*
  ������ {\tt p} �������������郋�[�`��.
*/
void factorize(poly p, poly p_low)
{
	poly d, d_low;

	d = MSB;  d_low = MSB >> 1; /* ������ {\tt d} �� $1x + 0$ �ɏ����� */
	while (d_low > p_low) {
		divide(p, p_low, d, d_low);  /* {\tt p} �� {\tt d} �Ŋ��� */
		if (res == 0) {  /* ����؂���\ldots\ */
			write_poly(d, d_low);  printf("*");  /* ���q {\tt d} ���o�� */
			p = quo;  p_low = quo_low;  /* ��������Ɋ��� */
		} else {  /* ����؂�Ȃ���Ύ��̑����� {\tt d} ������ */
			d += d_low;  /* ���̑����� {\tt d} �𐶐����� */
			if (d == 0) {
				d = MSB;  d_low >>= 1;
			}
		}
	}  /* {\tt d} �̎����� {\tt p} �̎����ȏ�ɂȂ�����E�o */
	write_poly(p, p_low);  /* �c���������� {\tt p} ���o�� */
}

int main()
{
	poly p, p_low;

	p = MSB;  p_low = MSB >> 1;    /* {\tt p} �� $1x + 0$ �ɏ����� */
	while (p_low != 0) {
		write_poly(p, p_low);  printf(" = ");
		factorize(p, p_low);  printf("\n");  /* {\tt p} ���������� */
		p += p_low;            /* ���̑����� {\tt p} �𐶐����� */
		if (p == 0) {
			p = MSB;  p_low >>= 1;
		}
	}
	return EXIT_SUCCESS;
}
