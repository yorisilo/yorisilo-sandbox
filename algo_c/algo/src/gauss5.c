/***********************************************************
	gauss5.c -- 5�d�Ίp�ȘA��������
***********************************************************/
#include "matutil.c"

void gauss5(int n, vector diag, vector sub1, vector sub2,
            vector sup1, vector sup2, vector b)
{
	int i;
	double t;

	for (i = 0; i < n - 2; i++) {  /* �����@ */
		t = sub1[i] / diag[i];
		diag[i + 1] -= t * sup1[i];
		sup1[i + 1] -= t * sup2[i];
		b   [i + 1] -= t * b   [i];
		t = sub2[i] / diag[i];
		sub1[i + 1] -= t * sup1[i];
		diag[i + 2] -= t * sup2[i];
		b   [i + 2] -= t * b   [i];
	}
	t = sub1[n - 2] / diag[n - 2];
	diag[n - 1] -= t * sup1[n - 2];
	b   [n - 1] -= t * b   [n - 2];
	b[n - 1] /= diag[n - 1];       /* ��ޑ�� */
	b[n - 2] = (b[n - 2] - sup1[n - 2] * b[n - 1]) / diag[n - 2];
	for (i = n - 3; i >= 0; i--)
		b[i] = (b[i] - sup1[i] * b[i + 1]
				- sup2[i] * b[i + 2]) / diag[i];
}

int main()
{
	int i, n;
	vector diag, sub1, sub2, sup1, sup2, b;

	printf("n = ");  scanf("%d", &n);
	if (n < 3) return EXIT_FAILURE;
	diag = new_vector(n);
	sub1 = new_vector(n);
	sub2 = new_vector(n);
	sup1 = new_vector(n);
	sup2 = new_vector(n);
	b    = new_vector(n);
	/* ���.  �����͂��ׂ� 1 */
	for (i = 0; i < n; i++) {
		diag[i] = 11;  sub1[i] = 3;  sub2[i] = 1;
		sup1[i] =  4;  sup2[i] = 2;  b[i] = 21;
	}
	b[0] = 17;  b[n - 1] = 15;
	b[1] -= 1;  b[n - 2] -= 2;
	gauss5(n, diag, sub1, sub2, sup1, sup2, b);
	vecprint(b, n, 8, "%9.6f");
	printf("�����͂��ׂ� 1\n");
	return EXIT_SUCCESS;
}
