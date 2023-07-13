#include <stdio.h>

int multiplication(int, int);
int division(int*, int*);

int main()
{
  int x,y;
  printf ("input a b\n");

  scanf ("%d %d", &x, &y);

  printf ("x * y = %d\n", multiplication(x,y));
  division(&x, &y);
  printf ("x / y = %d ... %d\n", y, x);
  return 0;
}

int multiplication(int a, int b) {
  int i;
  int t=0;
  for (i = 0; i < b ; i++) {
    t += a;
  }
  return t;
}

int division(int* a, int* b) {
  int t=0;
  while (1) {
    if (*a < *b) {
      break;
    }
    *a -= *b;
    t++;
  }
  *b = t;
}
