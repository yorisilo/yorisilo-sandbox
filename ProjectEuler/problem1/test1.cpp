#include <stdio.h>
#include <string.h>
#define N 10

int main(int argc, char* argv[])
{
  bool prime[N];
  memset(prime, 1, sizeof(bool) * N);
  prime[1] = false;// 1 は素数ではない
  for (int d = 2; d <= N / 2; d ++) {//エラトステネスのふるい
    printf("%d ",d);
    for (int i = 2*d; i < N; i += d) {
      printf("i = %d  ",i);
      //2*2 4+2 6+2 8+2  ...
      //3*2 6+3 9+3 12+3  ...
      //4*2 8+4 12+4 16+4 ...
      prime[i] = false;
    }
    printf("\n");
  }
  unsigned int sum = 0;
  for (int p = 2, n = 1; p < N; p ++) {
    if (prime[p]) {
      if (prime[n]) {
        printf ("%d ",p);
        sum += p;
      }
      printf ("\n");
      n++;
    }
  }
  printf("%u\n", sum);
  return 0;
}
