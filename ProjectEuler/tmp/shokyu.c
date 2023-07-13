//方針：まず素数のリストを作り，それから，素数番目の素数の和を求める．
//素数のリストを作る際に，愚直な方法で求めたのでは，計算量が大きくなりすぎるので，
//エラトステネスのふるいを使って作ること．寄って以下の方法でN=100000とかにすると，
//計算が終わらない

#include <stdio.h>
#include <math.h>
#define MAX 100000

void hurui(int n, int* prime) {
  for (i = 2; i < N ; i++) list[i]=i;



}

int main()
{
  int prime[N];
  int i;

  //printf ("primeNum %d = %d\n",4,prime[4]);
  while(prime[i]!='\0') {
    printf ("primeNum %d = %d\n",i,prime[i]);
    i++;
  }

  return 0;
}
