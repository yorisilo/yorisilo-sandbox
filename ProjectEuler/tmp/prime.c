#include <stdio.h>
void prime(int);

int main()
{
  int N;
  printf ("print prime number until ... ");
  scanf ("%d", &N);
  prime(N);
  return 0;
}

void prime(int N) {
  int i,j,k,t;
  t = 0;
  for (i = 2; i <= N ; i++) {
    j = 0;
    for (k = 2; k <= i/2 ; k++) {
      if (i % k == 0) {
        j=1;
        break;//るーぷをひとつぬける
      }
    }
    if (j==0) {
      t++;
      printf ("prime %d = %d\n",t,i);
    }
  }
}
