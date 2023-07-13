//各桁の和がNになる最小の自然数を求める
#include <stdio.h>

int main()
{
  int N;
  scanf ("%d", &N);

  int i,x,ans=0;

  for (i = 0;; i++) {
    x=i;
    while (x>0) {
      ans += x%10;
      x = x/10;
    }
    if (ans==N) break;
    ans = 0;
  }

  printf ("%d\n",i);

  return 0;
}
