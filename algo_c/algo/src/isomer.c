/***********************************************************
	isomer.c -- �ِ��̖̂��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define C    17  /* �Y�f���q�̐��̏�� */
#define L  2558  /* ���������̌��̏�� */

int size[L], length[L], count[C + 1];

int main()
{
	int i, j, k, h, len, n, si, sj, sk, sh;

	n = size[0] = length[0] = 0;
	for (i = 0; i < L; i++) {
		len = length[i] + 1;  if (len > C / 2) break;
		si = size[i] + 1;  if (si + len > C) continue;
		for (j = 0; j <= i; j++) {
			sj = si + size[j];  if (sj + len > C) continue;
			for (k = 0; k <= j; k++) {
				sk = sj + size[k];  if (sk + len > C) continue;
				if (++n >= L) return EXIT_FAILURE;
				size[n] = sk;  length[n] = len;
			}
		}
	}
	if (len <= C / 2) return EXIT_FAILURE;
	for (i = 0; i <= n; i++) {
		si = size[i];
		for (j = 0; j <= i; j++) {
			if (length[i] != length[j]) continue;
			sj = si + size[j];  if (sj > C) continue;
			count[sj]++;  /* ���� */
			for (k = 0; k <= j; k++) {
				sk = sj + size[k] + 1;  if (sk > C) continue;
				for (h = 0; h <= k; h++) {
					sh = sk + size[h];
					if (sh <= C) count[sh]++;  /* � */
				}
			}
		}
	}
	for (i = 1; i <= C; i++)
		printf("�Y�f���q�� %2d �̂��̂� %5d ���\n", i, count[i]);
	return EXIT_SUCCESS;
}
