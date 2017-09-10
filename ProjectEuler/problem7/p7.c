#include <stdio.h>
#include <math.h>
#define N 10001

// 10001 番目の素数を調べる
// 配列の番号と数字を一致させる．つまりhoge[0]は使わない．
int main()
{
  long int number[2*N];
  long int prime[N+1]; //1から100001の配列を使う
  int end=(int)(sqrt((double)N));
  int i,k=0;
  prime[1]=2;
  for (i = 1; i <= end; i++) {
    if (i%prime[k]!=0) {
      k++;
      prime[k]=i;
    }
  }

  printf ("%ld\n",prime[7]);
  return 0;
}
